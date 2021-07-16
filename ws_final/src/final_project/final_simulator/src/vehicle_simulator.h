#ifndef VEHICLE_SIMULATOR_H
#define VEHICLE_SIMULATOR_H

#include "autonomous_msg/VehicleInput.h"
#include "visualization_msgs/Marker.h"
#include <geometry_msgs/Pose.h>
#include <ros/ros.h>
#include <string>
#include <tf/transform_broadcaster.h>

#define PI 3.14159265358979323846 /* pi */

class Vehicle {
protected:
  ros::NodeHandle m_rosNodeHandler;
  ros::Publisher m_rosPubVehicle_output;
  ros::Publisher m_rosPubVehicle_output_grobal;
  ros::Subscriber m_rosSubVehicle_Input;
  
  tf::TransformBroadcaster m_rosTfBroadcaster;
  ros::Publisher m_rosPubVehicleMarker;

  std::string m_vehicle_namespace;

  double m_dAccelInput = 0.0;
  double m_dBrakeInput = 0.0;
  double m_dFrontAngle_rps = 0.0;

  double m_dDt = 0.0;
  double m_dPrevTime;

  double m_dX = 0.0;
  double m_dY = 0.0;
  double m_dYaw = 0.0;
  double m_dYawRate = 0.0;
  double m_dSlipAngle = 0.0;
  double m_dVehicleVel_ms = 0;

  double m_dCr = 183350.0; // N/rad
  double m_dCf = 154700.0; // N/rad

  double m_dMass = 1653.0;             // kg
  double m_dInertia = 2765.0;          // kg*m^2
  double m_dWheelBase = 1.402 + 1.646; // m
  double m_dLf = 1.402;                // m
  double m_dLr = 1.646;                // m

  double m_dIw = 0.3312; // kg m^2
  double m_dIt = 0.060;  // kg m^2
  double m_dIm = 0.015;  // kg m^2

  double m_dSlope_rad = 0.0 / 180.0 * 3.141592; // rad (=degree/180.0*PI)

  double m_dReff = 0.305;           // m
  double m_dGearRatio = 1.0 / 7.98; // m

  double m_dAccelConst = 293.1872055; // Nm T_motor = accel(0~1)*m_dAccelConst
  double m_dBrakeConst = 4488.075;    // Nm T_Brake = brake(0~1)*m_dAccelConst

  double m_dP = 0.1;
  double m_dI = 0.01;

public:
  Vehicle();
  ~Vehicle();
  void setInitialState(double x = 0.0, double y = 0.0, double yaw = 0.0,
                       double speed_mps = 0.0);
  bool simVehicleModel();
  void simVehicleController(double &aceel_out, double &brake_out);
  void simVehicleLongitudinalModel();
  void simVehicleLateralModel();
  void callback(const autonomous_msg::VehicleInput::ConstPtr &msg);

private:
  void broadcasting_tf_vehicle();
};

#endif
