/**
 * @file vehicle_model.cpp
 * @author Eunsan Jo (eunsan.mountain@gmail.com)
 * @brief 차량의 움직임에 대한 클래스
 * @details
 * @version 0.1
 * @date 2018-11-16
 *
 * @copyright Copyright (c) 2018
 *
 */

#include "vehicle_simulator.h"
#include "autonomous_msg/AccelBrakeSteering.h"
#include "autonomous_msg/VehicleInput.h"
#include "autonomous_msg/VehicleOutput.h"
#include "std_msgs/Float64.h"
#include <cmath>
#include <nav_msgs/Odometry.h>
#include <ros/ros.h>
#include <string>
#include <tf/transform_broadcaster.h>
#include <visualization_msgs/MarkerArray.h>

#define PI 3.14159265358979323846 /* pi */

/**
 * @brief Construct a new Vehicle:: Vehicle object
 *
 * @param vehicle_ID : ck
 */
Vehicle::Vehicle() {
  m_rosPubVehicle_output =
      m_rosNodeHandler.advertise<autonomous_msg::VehicleOutput>(
          "vehicle_output", 10);
  m_rosPubVehicle_output_grobal =
      m_rosNodeHandler.advertise<autonomous_msg::VehicleOutput>(
          "/vehicle_output", 10);

  m_rosSubVehicle_Input =
      m_rosNodeHandler.subscribe("vehicle_input", 10, &Vehicle::callback, this);

  double init_x, init_y, init_yaw;
  m_rosNodeHandler.param("vehicle/ns", m_vehicle_namespace, std::string(""));
  m_rosNodeHandler.param("vehicle/init_x", init_x, 0.0);
  m_rosNodeHandler.param("vehicle/init_y", init_y, 0.0);
  m_rosNodeHandler.param("vehicle/init_yaw", init_yaw, 0.0);
  this->setInitialState(init_x, init_y, init_yaw, 0.0);

  m_dDt = 0.0;
  m_dPrevTime = ros::Time::now().toSec();
}

Vehicle::~Vehicle() {}

void Vehicle::callback(const autonomous_msg::VehicleInput::ConstPtr &msg) {
  m_dAccelInput = msg->accel;
  m_dBrakeInput = msg->brake;
#if 0
  double max_steering_Accel = 30.0 / 100.0 * 3.141592 / 180.0;
  if ((m_dFrontAngle_rps - msg->steering) > max_steering_Accel) {
    m_dFrontAngle_rps -= max_steering_Accel;
  } else if ((m_dFrontAngle_rps - msg->steering) < -1.0 * max_steering_Accel) {
    m_dFrontAngle_rps += max_steering_Accel;
  } else {
    m_dFrontAngle_rps = msg->steering;
  }

#endif

#if 1
  m_dFrontAngle_rps = msg->steering;
#endif

}

void Vehicle::setInitialState(double x, double y, double yaw,
                              double speed_mps) {
  m_dX = x;
  m_dY = y;
  m_dYaw = yaw;
  m_dVehicleVel_ms = speed_mps;
}

bool Vehicle::simVehicleModel() {
  // Calculate dt_ by dividing the previous time and the current time
  m_dDt = ros::Time::now().toSec() - m_dPrevTime;
  if (m_dDt <= 0.0) {
    return false;
  }
  m_dPrevTime = ros::Time::now().toSec();

  this->simVehicleLongitudinalModel();
  this->simVehicleLateralModel();

  // broadcasting the vehicle's body coordinate system
  broadcasting_tf_vehicle();

  autonomous_msg::VehicleOutput output;
  output.x = m_dX;
  output.y = m_dY;
  output.yaw = m_dYaw;
  output.velocity = m_dVehicleVel_ms;
  output.id = m_vehicle_namespace;

  m_rosPubVehicle_output.publish(output);
  m_rosPubVehicle_output_grobal.publish(output);
  return true;
}

void Vehicle::simVehicleLongitudinalModel() {
  /* Longutudinal simulation using accel (0~1) and brake (0~1)
   * TODO: FIX the code below
   * Input: accel(0~1) and brake(0~1)
   * Output: m_dVehicleVel_ms
   */

  if (m_dVehicleVel_ms < 0.0001 && m_dBrakeInput >= 0.0001) {
    m_dVehicleVel_ms = 0.0;
    return;
  }
  if (m_dVehicleVel_ms < 0.0001 && m_dAccelInput <= 0.0001) {
    m_dVehicleVel_ms = 0.0;
    return;
  }

  double t_motor = m_dAccelConst * m_dAccelInput; // Nm
  double t_brake = m_dBrakeConst * m_dBrakeInput; // Nm

  double j_m_eq = m_dIm + m_dIt + m_dIw * m_dGearRatio * m_dGearRatio +
                  m_dMass * m_dReff * m_dReff * m_dGearRatio * m_dGearRatio;

  double rollingResistance = 0.015 * m_dMass * 9.81 * cos(m_dSlope_rad);
  if (m_dVehicleVel_ms < 0.0) {
    rollingResistance *= -1.0;
  }
  double aeroDrag =
      0.5 * 1.225 * 0.32 * 1.55 * 1.8 * m_dVehicleVel_ms * m_dVehicleVel_ms;
  double dOmega_motor =
      (t_motor -
       m_dGearRatio * m_dReff *
           (rollingResistance + aeroDrag + m_dMass * 9.81 * sin(m_dSlope_rad)) -
       m_dGearRatio * t_brake) /
      j_m_eq;

  m_dVehicleVel_ms += m_dDt * (m_dReff * (dOmega_motor * m_dGearRatio));
}

void Vehicle::simVehicleLateralModel() {
  /* Dynamics simulation using velocity and steering angle
   * TODO: FIX the code below.
   * Input(Sensors output) : m_dFrontAngle_rps
   * output : pose.position.x, pose.position.y, yaw
   */
  double max_alpha_rad = 7.0 * 3.14141592 / 180.0;

  double dx = 0.0;
  double dy = 0.0;
  double dslipAngle = 0.0;
  double dyaw = 0.0;
  double dyawrate = 0.0;

  double Fyf = 0.0;
  double Fyr = 0.0;

  if (m_dFrontAngle_rps > 30.0 * 3.141592 / 180.0) {
    m_dFrontAngle_rps = 30.0 * 3.141592 / 180.0;
  } else if (m_dFrontAngle_rps < -30.0 * 3.141592 / 180.0) {
    m_dFrontAngle_rps = -30.0 * 3.141592 / 180.0;
  }

  if (fabs(m_dVehicleVel_ms) >= 5.0) // 5.0 || m_dVehicleVel_ms <= -5.0)
  {
    dx = m_dDt * m_dVehicleVel_ms * cos(m_dYaw + m_dSlipAngle);
    dy = m_dDt * m_dVehicleVel_ms * sin(m_dYaw + m_dSlipAngle);

    double alpha_f = m_dFrontAngle_rps - m_dSlipAngle -
                     (m_dLf * m_dYawRate) / (m_dVehicleVel_ms);
    if (alpha_f > max_alpha_rad) {
      alpha_f = max_alpha_rad;
    } else if (alpha_f < -1.0 * max_alpha_rad) {
      alpha_f = -1.0 * max_alpha_rad;
    }
    Fyf = (2 * m_dCf) * alpha_f;

    double alpha_r = -m_dSlipAngle + (m_dLr * m_dYawRate) / (m_dVehicleVel_ms);
    if (alpha_r > max_alpha_rad) {
      alpha_r = max_alpha_rad;
    } else if (alpha_r < -1.0 * max_alpha_rad) {
      alpha_r = -1.0 * max_alpha_rad;
    }
    Fyr = (2 * m_dCr) * alpha_r;

    dslipAngle = m_dDt * (Fyf / (m_dMass * m_dVehicleVel_ms) +
                          Fyr / (m_dMass * m_dVehicleVel_ms) - m_dYawRate);

    dyaw = m_dDt * m_dYawRate;
    dyawrate =
        m_dDt *
        ((2 * m_dLf * m_dCf) / (m_dInertia) *
             (m_dFrontAngle_rps - m_dSlipAngle -
              (m_dLf * m_dYawRate) / (m_dVehicleVel_ms)) -
         (2 * m_dLr * m_dCr) / (m_dInertia) *
             (-m_dSlipAngle + (m_dLr * m_dYawRate) / (m_dVehicleVel_ms)));

    m_dX += dx;
    m_dY += dy;
    m_dSlipAngle += dslipAngle;
    m_dYaw += dyaw;
    m_dYawRate += dyawrate;
  } else {
    m_dSlipAngle = atan((m_dLr * tan(m_dFrontAngle_rps)) / (m_dLf + m_dLr));

    dx = m_dDt * m_dVehicleVel_ms * cos(m_dYaw + m_dSlipAngle);
    dy = m_dDt * m_dVehicleVel_ms * sin(m_dYaw + m_dSlipAngle);

    m_dYawRate = ((m_dVehicleVel_ms * cos(m_dSlipAngle)) / (m_dLf + m_dLr)) *
                 (tan(m_dFrontAngle_rps));
    dyaw = m_dDt * m_dYawRate;

    m_dX += dx;
    m_dY += dy;
    m_dYaw += dyaw;
  }
}

void Vehicle::broadcasting_tf_vehicle() {
  tf::Quaternion q;
  q.setRPY(0, 0, m_dYaw);
  geometry_msgs::Pose pose;

  pose.position.x = m_dX;
  pose.position.y = m_dY;
  pose.orientation.x = q.getX();
  pose.orientation.y = q.getY();
  pose.orientation.z = q.getZ();
  pose.orientation.w = q.getW();

  tf::Transform transform;

  transform.setOrigin(tf::Vector3(m_dX, m_dY, 0.0));
  transform.setRotation(q);

  // broadcasting the vehicle's body coordinate system
  // The parent coordinate is world, child coordinate is body.
  m_rosTfBroadcaster.sendTransform(tf::StampedTransform(
      transform, ros::Time::now(), "/world", m_vehicle_namespace + "/body"));
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "vehicle");
  Vehicle vehicle;
  // The approximate control time is 100 Hz
  ros::Rate loop_rate(100);
  while (ros::ok()) {
    vehicle.simVehicleModel();
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
