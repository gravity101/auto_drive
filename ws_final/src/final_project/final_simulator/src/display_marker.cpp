#include "autonomous_msg/LanePointDataArray.h"
#include "autonomous_msg/PolyfitLaneDataArray.h"
#include "autonomous_msg/VehicleOutput.h"
#include "visualization_msgs/Marker.h"
#include "visualization_msgs/MarkerArray.h"
#include <math.h>
#include <ros/ros.h>
#include <string>
#include <tf/tf.h>

#define PI 3.1415926579

class Display {
protected:
  ros::NodeHandle m_rosNodeHandler;

  ros::Publisher m_rosPubVehiclesMarker;
  ros::Subscriber m_rosSubVehicle_Output;

  ros::Publisher m_rosPubLanesMarkerArray;
  ros::Subscriber m_rosSubLanePointArray;

  ros::Publisher m_rosPubPolyMarkerArray;
  ros::Subscriber m_rosSubPolyLaneArray;

  ros::Publisher m_rosPubDrivingWay;
  ros::Subscriber m_rosSubDrivingWay;

  ros::Publisher m_rosPubCsvMarkerArray;
  ros::Subscriber m_rosSubCsvLaneArray;

public:
  Display() {

    m_rosPubVehiclesMarker =
        m_rosNodeHandler.advertise<visualization_msgs::Marker>("vehicle_marker",
                                                               10);
    m_rosSubVehicle_Output = m_rosNodeHandler.subscribe(
        "vehicle_output", 10, &Display::vehicleOutputCallback, this);

    m_rosPubCsvMarkerArray =
        m_rosNodeHandler.advertise<visualization_msgs::MarkerArray>(
            "csv_lanes_marker", 10);
    m_rosSubCsvLaneArray = m_rosNodeHandler.subscribe(
        "csv_lanes", 10, &Display::csvLanesCallback, this);

    m_rosPubLanesMarkerArray =
        m_rosNodeHandler.advertise<visualization_msgs::MarkerArray>(
            "ROI_lanes_marker", 10);
    m_rosSubLanePointArray = m_rosNodeHandler.subscribe(
        "ROI_lanes", 10, &Display::lanesCallback, this);

    m_rosPubPolyMarkerArray =
        m_rosNodeHandler.advertise<visualization_msgs::MarkerArray>(
            "polyfit_lanes_marker", 10);
    m_rosSubPolyLaneArray = m_rosNodeHandler.subscribe(
        "polyfit_lanes", 10, &Display::polyLanesCallback, this);

    m_rosPubDrivingWay =
        m_rosNodeHandler.advertise<visualization_msgs::MarkerArray>(
            "driving_way_marker", 10);
    m_rosSubDrivingWay = m_rosNodeHandler.subscribe(
        "driving_way", 10, &Display::drivingWayCallback, this);
  }

  ~Display() {}

protected:
  autonomous_msg::LanePointDataArray m_csvLanes;

public:
  void
  csvLanesCallback(const autonomous_msg::LanePointDataArray::ConstPtr &msg) {
    // std::string id = msg->id;
    m_csvLanes.frame_id = msg->frame_id;
    m_csvLanes.id = msg->id;
    m_csvLanes.lane = msg->lane;
  }

  void mark_csvLanes() {

    visualization_msgs::MarkerArray markerArray;

    int id = 0;

    for (auto i_lane = 0; i_lane < m_csvLanes.lane.size(); i_lane++) {
      visualization_msgs::Marker marker;
      marker.header.frame_id = m_csvLanes.frame_id;
      marker.header.stamp = ros::Time::now();

      marker.ns = m_csvLanes.lane[i_lane].id;
      marker.id = id++;

      marker.type = visualization_msgs::Marker::LINE_STRIP;
      marker.action = visualization_msgs::Marker::ADD;

      marker.color.r = 0.9f;
      marker.color.g = 0.9f;
      marker.color.b = 0.9f;
      marker.color.a = 0.7;
      marker.scale.x = 0.2;
      marker.lifetime = ros::Duration();

      geometry_msgs::Point prevPoint;
      bool first = true;

      for (auto i_point = 0; i_point < m_csvLanes.lane[i_lane].point.size();
           i_point++) {
        geometry_msgs::Point currPoint;
        currPoint.x = m_csvLanes.lane[i_lane].point[i_point].x;
        currPoint.y = m_csvLanes.lane[i_lane].point[i_point].y;
        currPoint.z = 0.0;

        if (first == true) {
          first = false;
        } else {
          double dx = currPoint.x - prevPoint.x;
          double dy = currPoint.y - prevPoint.y;
          if ((dx * dx + dy * dy) <= 2.0 * 2.0) {
            marker.points.push_back(prevPoint);
            marker.points.push_back(currPoint);
          } else {
            markerArray.markers.push_back(marker);
            marker.points.clear();
            marker.id = id++;
          }
        }
        prevPoint = currPoint;
      }
      markerArray.markers.push_back(marker);
    }
    m_rosPubCsvMarkerArray.publish(markerArray);
  }

protected:
  std::string m_sVehicle_id = "";
  double m_dVehicleX = 0.0;
  double m_dVehicleY = 0.0;
  double m_dVehicleYaw = 0.0;
  bool m_isVehicleExist = false;

public:
  void
  vehicleOutputCallback(const autonomous_msg::VehicleOutput::ConstPtr &msg) {
    m_sVehicle_id = msg->id;
    m_dVehicleX = msg->x;
    m_dVehicleY = msg->y;
    m_dVehicleYaw = msg->yaw;
    m_isVehicleExist = true;
  }

  void mark_vehicle() {
    if (m_isVehicleExist == true) {
      tf::Quaternion q_temp;
      tf::Matrix3x3 m(q_temp);
      q_temp.setRPY(90.0 / 180.0 * PI, 0, 180.0 / 180.0 * PI + m_dVehicleYaw);
      tf::Quaternion q(q_temp.getX(), q_temp.getY(), q_temp.getZ(),
                       q_temp.getW());

      visualization_msgs::Marker vehicle_marker;
      vehicle_marker.header.frame_id = "/world";
      vehicle_marker.header.stamp = ros::Time::now();
      vehicle_marker.ns = m_sVehicle_id;
      vehicle_marker.id = 0;
      // Set the marker type
      vehicle_marker.type = visualization_msgs::Marker::MESH_RESOURCE;
      vehicle_marker.mesh_resource =
          "package://final_simulator/meshes/BMW_X5_4.dae";
      vehicle_marker.mesh_use_embedded_materials = false;

      vehicle_marker.pose.position.x = m_dVehicleX;
      vehicle_marker.pose.position.y = m_dVehicleY;
      vehicle_marker.pose.position.z = 0.0;
      vehicle_marker.pose.orientation.x = q.getX();
      vehicle_marker.pose.orientation.y = q.getY();
      vehicle_marker.pose.orientation.z = q.getZ();
      vehicle_marker.pose.orientation.w = q.getW();
      // Set the scale of the marker
      vehicle_marker.scale.x = 1.0;
      vehicle_marker.scale.y = 1.0;
      vehicle_marker.scale.z = 1.0;

      vehicle_marker.color.r = 1.0;
      vehicle_marker.color.g = 1.0;
      vehicle_marker.color.b = 1.0;
      vehicle_marker.color.a = 1.0;

      vehicle_marker.lifetime = ros::Duration(0.2);

      m_rosPubVehiclesMarker.publish(vehicle_marker);
    }
  }

protected:
  autonomous_msg::LanePointDataArray m_lanes;

public:
  void lanesCallback(const autonomous_msg::LanePointDataArray::ConstPtr &msg) {
    // std::string id = msg->id;
    m_lanes.frame_id = msg->frame_id;
    m_lanes.id = msg->id;
    m_lanes.lane = msg->lane;
  }

  void mark_ROILanes() {

    visualization_msgs::MarkerArray markerArray;
    int id = 0;
    for (auto i_lane = 0; i_lane < m_lanes.lane.size(); i_lane++) {
      visualization_msgs::Marker marker;
      marker.header.frame_id = m_lanes.lane[i_lane].frame_id;
      marker.header.stamp = ros::Time::now();

      marker.ns = m_lanes.lane[i_lane].id;
      marker.id = id++;

      marker.type = visualization_msgs::Marker::LINE_STRIP;
      marker.action = visualization_msgs::Marker::ADD;

      marker.color.r = 1.0f;
      marker.color.g = 0.0f;
      marker.color.b = 0.0f;
      marker.color.a = 1.0;
      marker.scale.x = 0.25;
      marker.lifetime = ros::Duration(0.2);

      geometry_msgs::Point prevPoint;
      bool first = true;
      for (auto i_point = 0; i_point < m_lanes.lane[i_lane].point.size();
           i_point++) {
        geometry_msgs::Point currPoint;
        currPoint.x = m_lanes.lane[i_lane].point[i_point].x;
        currPoint.y = m_lanes.lane[i_lane].point[i_point].y;
        currPoint.z = 0.0;

        if (first == true) {
          first = false;
        } else {
          double dx = currPoint.x - prevPoint.x;
          double dy = currPoint.y - prevPoint.y;
          if ((dx * dx + dy * dy) <= 5.0 * 5.0) {
            marker.points.push_back(prevPoint);
            marker.points.push_back(currPoint);
          } else {
            markerArray.markers.push_back(marker);
            marker.points.clear();
            marker.id = id++;
          }
        }
        prevPoint = currPoint;
      }
      markerArray.markers.push_back(marker);
    }
    m_rosPubLanesMarkerArray.publish(markerArray);
  }

protected:
  autonomous_msg::PolyfitLaneDataArray m_polyLanes;

public:
  void
  polyLanesCallback(const autonomous_msg::PolyfitLaneDataArray::ConstPtr &msg) {
    // std::string id = msg->id;
    m_polyLanes.frame_id = msg->frame_id;
    m_polyLanes.polyfitLanes = msg->polyfitLanes;
  }

  void mark_ROIpolyLanes(double interval = 0.1, double ROILength = 30.0) {

    visualization_msgs::MarkerArray markerArray;
    for (auto i_lane = 0; i_lane < m_polyLanes.polyfitLanes.size(); i_lane++) {

      double x = 0.0;
      double y = m_polyLanes.polyfitLanes[i_lane].a0;

      double distance_square = x * x + y * y;
      ;
      int id = 0;
      while (distance_square < ROILength * ROILength) {
        double a0 = m_polyLanes.polyfitLanes[i_lane].a0;
        double a1 = m_polyLanes.polyfitLanes[i_lane].a1;
        double a2 = m_polyLanes.polyfitLanes[i_lane].a2;
        double a3 = m_polyLanes.polyfitLanes[i_lane].a3;

        y = a0 + a1 * x + a2 * x * x + a3 * x * x * x;
        distance_square = x * x + y * y;

        visualization_msgs::Marker marker;
        marker.header.frame_id = m_polyLanes.polyfitLanes[i_lane].frame_id;
        marker.header.stamp = ros::Time::now();

        marker.ns = m_polyLanes.polyfitLanes[i_lane].id;
        marker.id = id;

        marker.type = visualization_msgs::Marker::CYLINDER;
        marker.action = visualization_msgs::Marker::ADD;

        marker.pose.position.x = x;
        marker.pose.position.y = y;
        marker.pose.position.z = 0.0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.1;
        marker.pose.orientation.w = 1.0;
        marker.color.r = 0.0f;
        marker.color.g = 1.0f;
        marker.color.b = 0.0f;
        marker.color.a = 1.0;
        marker.scale.x = 0.1;
        marker.scale.y = 0.1;
        marker.scale.z = 0.1;
        marker.lifetime = ros::Duration(0.2);

        markerArray.markers.push_back(marker);
        x += interval;
        id++;
      }
    }
    m_rosPubPolyMarkerArray.publish(markerArray);
  }

protected:
  autonomous_msg::PolyfitLaneData m_drivingWay;

public:
  void
  drivingWayCallback(const autonomous_msg::PolyfitLaneData::ConstPtr &msg) {
    m_drivingWay = *msg;
  }

  void mark_drivingWay(double interval = 0.1, double ROILength = 30.0) {

    double a0 = m_drivingWay.a0;
    double a1 = m_drivingWay.a1;
    double a2 = m_drivingWay.a2;
    double a3 = m_drivingWay.a3;

    double x = 0.0;
    double y = a0;

    double distance_square = x * x + y * y;
    int id = 0;
    visualization_msgs::MarkerArray markerArray;
    while (distance_square < ROILength * ROILength) {

      y = a0 + a1 * x + a2 * x * x + a3 * x * x * x;
      distance_square = x * x + y * y;

      visualization_msgs::Marker marker;
      marker.header.frame_id = m_drivingWay.frame_id;
      marker.header.stamp = ros::Time::now();

      marker.ns = m_drivingWay.id;
      marker.id = id;

      marker.type = visualization_msgs::Marker::CYLINDER;
      marker.action = visualization_msgs::Marker::ADD;

      marker.pose.position.x = x;
      marker.pose.position.y = y;
      marker.pose.position.z = 0.0;
      marker.pose.orientation.x = 0.0;
      marker.pose.orientation.y = 0.0;
      marker.pose.orientation.z = 0.1;
      marker.pose.orientation.w = 1.0;
      marker.color.r = 1.0f;
      marker.color.g = 1.0f;
      marker.color.b = 0.0f;
      marker.color.a = 1.0;
      marker.scale.x = 0.1;
      marker.scale.y = 0.1;
      marker.scale.z = 0.1;
      marker.lifetime = ros::Duration(0.2);

      markerArray.markers.push_back(marker);
      x += interval;
      id++;
    }

    m_rosPubDrivingWay.publish(markerArray);
  }
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "display");
  // Vehicle vehicle;
  Display display;

  double prev_vehiclesMarkTime = ros::Time::now().toSec();
  double prev_lanesMarkTime = ros::Time::now().toSec();
  double prev_csvlanesMarkTime = ros::Time::now().toSec();
  // The approximate control time is 100 Hz
  ros::Rate loop_rate(100);
  while (ros::ok()) {

    if ((ros::Time::now().toSec() - prev_vehiclesMarkTime) > 0.05) {
      prev_vehiclesMarkTime = ros::Time::now().toSec();
      display.mark_vehicle();
    }
    if ((ros::Time::now().toSec() - prev_lanesMarkTime) > 0.2) {
      prev_lanesMarkTime = ros::Time::now().toSec();
      display.mark_ROILanes();
      display.mark_ROIpolyLanes();
      display.mark_drivingWay();
    }
    if ((ros::Time::now().toSec() - prev_csvlanesMarkTime) > 1.0) {
      prev_csvlanesMarkTime = ros::Time::now().toSec();
      display.mark_csvLanes();
    }

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
