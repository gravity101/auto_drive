#include "KusvLane.hpp"
#include "autonomous_msg/LanePointDataArray.h"
#include "autonomous_msg/VehicleOutput.h"
#include "geometry_msgs/Point.h"

#include <math.h>
#include <ros/ros.h>
#include <string>
#include <tf/transform_listener.h>

class MapMaker {
protected:
  ros::NodeHandle m_rosNodeHandler;
  ros::Publisher m_rosPubCsvLanes;
  ros::Publisher m_rosPubMidLanes;
  ros::Subscriber m_rosSubVehicle_Output;

public:
  MapMaker() {
    m_rosPubCsvLanes =
        m_rosNodeHandler.advertise<autonomous_msg::LanePointDataArray>(
            "csv_lanes", 10);
    m_rosPubMidLanes =
        m_rosNodeHandler.advertise<autonomous_msg::LanePointDataArray>(
            "ROI_lanes", 10);

    m_rosSubVehicle_Output = m_rosNodeHandler.subscribe(
        "vehicle_output", 10, &MapMaker::vehicleOutputCallback, this);

    m_rosNodeHandler.param("map_maker/laneCount", m_laneCount_param, (int)3);
    m_rosNodeHandler.param("map_maker/laneWidth", m_laneWidth_param,
                           (double)3.3);
    m_rosNodeHandler.param("map_maker/interval", m_interval_param,
                           (double)0.25);

    m_lanes.frame_id = "world";
    for (auto i = 0; i < m_laneCount_param; i++) {
      autonomous_msg::LanePointData lane;
      lane.frame_id = "world";
      lane.id = std::to_string(i);
      m_lanes.lane.push_back(lane);
    }

    m_mids.frame_id = "world";
    for (auto i = 0; i < (m_laneCount_param - 1); i++) {
      autonomous_msg::LanePointData lane;
      lane.frame_id = "world";
      lane.id = std::to_string(i);
      m_mids.lane.push_back(lane);
    }
  }

  ~MapMaker() {}

protected:
  double m_dVehicleX = 0.0;
  double m_dVehicleY = 0.0;
  double m_dPrevVehicleX = 0.0;
  double m_dPrevVehicleY = 0.0;

public:
  void
  vehicleOutputCallback(const autonomous_msg::VehicleOutput::ConstPtr &msg) {
    m_dVehicleX = msg->x;
    m_dVehicleY = msg->y;
  }

protected:
  tf::TransformListener m_rosTfListenr;
  int m_laneCount_param;
  double m_laneWidth_param;
  double m_interval_param;
  autonomous_msg::LanePointDataArray m_lanes;
  autonomous_msg::LanePointDataArray m_mids;

public:
  void makeMap() {

    double dx = m_dVehicleX - m_dPrevVehicleX;
    double dy = m_dVehicleY - m_dPrevVehicleY;
    double distance_square = dx * dx + dy * dy;

    if (distance_square >= m_interval_param * m_interval_param) {

      m_dPrevVehicleX = m_dVehicleX;
      m_dPrevVehicleY = m_dVehicleY;

      double lane_y_body =
          -1.0 * ((double)(m_laneCount_param - 1)) / 2.0 * m_laneWidth_param;
      for (auto i = 0; i < m_laneCount_param; i++) {
        geometry_msgs::PointStamped lanePoint_body;
        lanePoint_body.header.frame_id = "/body";
        lanePoint_body.header.stamp = ros::Time(0);
        lanePoint_body.point.x = -1.646; //뒷바퀴 중심으로 기록
        lanePoint_body.point.y = lane_y_body;
        lane_y_body += m_laneWidth_param;
        geometry_msgs::PointStamped lanePoint_world;

        try {
          m_rosTfListenr.transformPoint("/world", lanePoint_body,
                                        lanePoint_world);

          m_lanes.lane[i].point.push_back(lanePoint_world.point);
        } catch (tf::TransformException &ex) {
          // ROS_ERROR(ex.what());
        }
      }

      lane_y_body =
          -1.0 * ((double)(m_laneCount_param - 2)) / 2.0 * m_laneWidth_param;
      for (auto i = 0; i < m_laneCount_param-1; i++) {
        geometry_msgs::PointStamped lanePoint_body;
        lanePoint_body.header.frame_id = "/body";
        lanePoint_body.header.stamp = ros::Time(0);
        lanePoint_body.point.x = -1.646; //뒷바퀴 중심으로 기록
        lanePoint_body.point.y = lane_y_body;
        lane_y_body += m_laneWidth_param;
        geometry_msgs::PointStamped lanePoint_world;

        try {
          m_rosTfListenr.transformPoint("/world", lanePoint_body,
                                        lanePoint_world);

          m_mids.lane[i].point.push_back(lanePoint_world.point);
        } catch (tf::TransformException &ex) {
          // ROS_ERROR(ex.what());
        }
      }
    }

    m_rosPubCsvLanes.publish(m_lanes);
    m_rosPubMidLanes.publish(m_mids);
  }
};

int main(int argc, char **argv) {

  ros::init(argc, argv, "map_maker");

  MapMaker mapMaker;

  double prev_vehiclesMarkTime = ros::Time::now().toSec();
  double prev_splinedWaysMarkTime = ros::Time::now().toSec();
  // The approximate control time is 100 Hz
  ros::Rate loop_rate(100);
  while (ros::ok()) {

    if ((ros::Time::now().toSec() - prev_vehiclesMarkTime) > 0.01) {
      prev_vehiclesMarkTime = ros::Time::now().toSec();
    }
    mapMaker.makeMap();
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
