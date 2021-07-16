/**
 * @file master_vehicle.cpp
 * @author Eunsan Jo (eunsan.mountain@gmail.com)
 * @brief
 * @version 0.1
 * @date 2018-11-28
 *
 * @copyright Copyright (c) 2018
 *
 */

#include "master_vehicle.h"
#include "KusvLane.hpp"
#include "autonomous_msg/VehicleInput.h"
#include "autonomous_msg/VehicleOutput.h"
#include <cmath>
#include <ros/ros.h>
#include <string>
#include <tf/transform_broadcaster.h>

#define PI 3.14159265358979323846 /* pi */

MasterVehicle::MasterVehicle() {
  m_rosPubVehicle_output =
      m_rosNodeHandler.advertise<autonomous_msg::VehicleOutput>(
          "vehicle_output", 10);

  m_rosTargetSpeed = m_rosNodeHandler.subscribe(
      "/master_target_speed", 10, &MasterVehicle::targetSpeedCallback, this);

  m_rosInitPoint = m_rosNodeHandler.subscribe(
      "/master_init_point", 10, &MasterVehicle::initPointCallback, this);

  double init_x, init_y, init_yaw;
  m_rosNodeHandler.param("master_vehicle/ns", m_vehicle_namespace,
                         std::string("front"));
  m_rosNodeHandler.param("master_vehicle/init_x", init_x, 0.0);
  m_rosNodeHandler.param("master_vehicle/init_y", init_y, 0.0);
  m_rosNodeHandler.param("master_vehicle/init_yaw", init_yaw, 0.0);

  m_rosNodeHandler.param("master_vehicle/refPath", m_ref_path_param,
                         std::string(""));
  m_rosNodeHandler.param("master_vehicle/laneId", m_laneId_param,
                         std::string("1"));

  m_dDt = 0.0;
  m_dPrevTime = ros::Time::now().toSec();
}

MasterVehicle::~MasterVehicle() {}

void MasterVehicle::targetSpeedCallback(
    const std_msgs::Float64::ConstPtr &msg) {
  m_targetSpeed = msg->data;
}
void MasterVehicle::initPointCallback(
    const geometry_msgs::Point::ConstPtr &msg) {
  double init_x = msg->x;
  double init_y = msg->y;

  //가장 가까운 점을 찾는다
  double min_distance_sq = std::numeric_limits<double>::max();
  int min_index = 0;
  for (int i = 0; i < m_refLane.point.size(); i++) {
    double dx = init_x - m_refLane.point[i].x;
    double dy = init_y - m_refLane.point[i].y;
    double distance_sq = dx * dx + dy * dy;

    if (distance_sq < min_distance_sq) {
      min_distance_sq = distance_sq;
      min_index = i;
    }
  }
  //그 다음의 인덱스 점의 yaw angle을 구한다.

  int next_index = (min_index + 1) % m_refLane.point.size();
  double init_yaw = atan2(m_refLane.point[next_index].y - init_y,
                          m_refLane.point[next_index].x - init_x);

  this->setInitialState(init_x, init_y, init_yaw, 0.0);
  isMasterCreated = true;
}

void MasterVehicle::setInitialState(double x, double y, double yaw,
                                    double speed_mps) {
  m_dX = x;
  m_dY = y;
  m_dYaw = yaw;
  m_dVehicleVel_ms = speed_mps;
}

void MasterVehicle::loadLaneData() {

  SKusvLanes csvRefLaneImport;
  csvRefLaneImport.ImportKusvLaneCsvFile(m_ref_path_param);

  m_refLane.frame_id = "/world";
  m_refLane.point.clear();
  m_refLane.id = m_laneId_param;

  for (auto i_lane = 0; i_lane < csvRefLaneImport.m_vecKusvLanes.size();
       i_lane++) {

    if (m_laneId_param ==
        std::to_string(csvRefLaneImport.m_vecKusvLanes[i_lane].m_nLaneID)) {

      for (auto i_point = 0;
           i_point <
           csvRefLaneImport.m_vecKusvLanes[i_lane].m_vecKusvLanePoint.size();
           i_point++) {
        geometry_msgs::Point point;
        point.x = csvRefLaneImport.m_vecKusvLanes[i_lane]
                      .m_vecKusvLanePoint[i_point]
                      .m_dPtX_m;
        point.y = csvRefLaneImport.m_vecKusvLanes[i_lane]
                      .m_vecKusvLanePoint[i_point]
                      .m_dPtY_m;
        m_refLane.point.push_back(point);
      }
    }
  }
}

bool MasterVehicle::simVehicleModel() {
  // Calculate dt_ by dividing the previous time and the current time
  m_dDt = ros::Time::now().toSec() - m_dPrevTime;
  if (m_dDt <= 0.0) {
    return false;
  }
  m_dPrevTime = ros::Time::now().toSec();
  if (isMasterCreated == true) {

    m_dVehicleVel_ms = simVehicleMaximumAcceleration(m_targetSpeed);
    m_dFrontAngle_rps = calcSteeringAngle();

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
    return true;
  } else {
    return false;
  }
}

double MasterVehicle::calcSteeringAngle() {
  //가장 가까운 점을 찾는다
  double min_distance_sq = std::numeric_limits<double>::max();
  int min_index = 0;
  for (int i = 0; i < m_refLane.point.size(); i++) {
    double dx = m_dX - m_refLane.point[i].x;
    double dy = m_dY - m_refLane.point[i].y;
    double distance_sq = dx * dx + dy * dy;

    if (distance_sq < min_distance_sq) {
      min_distance_sq = distance_sq;
      min_index = i;
    }
  }
  //그 다음의 +10 인덱스 점으로 이동하는 steering angle을 구한다.
  //만약 마지막점이면 처음으로 이동한다.
  int goalPoint_index = (min_index + 10) % m_refLane.point.size();
  double goalX = m_refLane.point[goalPoint_index].x - m_dX;
  double goalY = m_refLane.point[goalPoint_index].y - m_dY;
  double alpha = atan2(goalY, goalX) - m_dYaw;
  double lookAhead = pow(goalX * goalX + goalY * goalY, 0.5);

  return atan2(2 * m_dWheelBase * sin(alpha), lookAhead);
}

/**
 * @brief 차량의 한계 속도를 구한다.
 * @details
 * 차량의 최고 가속도는 제로백을 기반으로하고, 최고 감가속도는 -g/5.0를 기준으로
 * 한다, 이때 입력된 속도가 현재의 속도와 비교하여 가속도를 구한 뒤, 이 가속도가
 * 한계 가속도보다 크면 제한한다.
 *
 * @param speed_input : 원하는 속도
 * @return double  : 한계 속도
 */
double MasterVehicle::simVehicleMaximumAcceleration(double speed_input) {
  double acceleration = (speed_input - m_dVehicleVel_ms) / m_dDt;
  double zero2hundred = 15.0;
  double max_acceleration = ((100.0) / 3.6) / zero2hundred;
  double min_acceleration = -9.81 / 5.0;
  if (acceleration > max_acceleration) {
    acceleration = max_acceleration;
  } else if (acceleration < min_acceleration) {
    acceleration = min_acceleration;
  }
  double limitedSpeed = m_dVehicleVel_ms + acceleration * m_dDt;
  limitedSpeed = (limitedSpeed < 0.0) ? 0.0 : limitedSpeed;
  return limitedSpeed;
}

void MasterVehicle::simVehicleLateralModel() {
  /* Dynamics simulation using velocity and steering angle
   * TODO: FIX the code below.
   * Input(Sensors output) : m_dFrontAngle_rps
   * output : pose.position.x, pose.position.y, yaw
   */
  double dx = 0.0;
  double dy = 0.0;
  double dyaw = 0.0;
  double dyawrate = 0.0;

  if (m_dFrontAngle_rps > 30.0 * 3.141592 / 180.0) {
    m_dFrontAngle_rps = 30.0 * 3.141592 / 180.0;
  } else if (m_dFrontAngle_rps < -30.0 * 3.141592 / 180.0) {
    m_dFrontAngle_rps = -30.0 * 3.141592 / 180.0;
  }

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

void MasterVehicle::broadcasting_tf_vehicle() {
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

  ros::init(argc, argv, "master_vehicle");
  MasterVehicle vehicle;
  vehicle.loadLaneData();
  // The approximate control time is 100 Hz
  ros::Rate loop_rate(100);
  while (ros::ok()) {
    vehicle.simVehicleModel();
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
