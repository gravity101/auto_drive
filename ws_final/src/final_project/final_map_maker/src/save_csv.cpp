#include "KusvLane.hpp"
#include "autonomous_msg/LanePointDataArray.h"
#include <ros/ros.h>
#include <string>

class SaveCsv {
  ////////////////////////////////////////////////////////////////////////////////
  // 0. Constructor & destructure
protected:
  ros::NodeHandle m_rosNodeHandler;
  ros::Subscriber m_rosSubCsvLaneArray;
  ros::Subscriber m_rosSubMidLaneArray;
  std::string m_path_csv;
  std::string m_path_mid;

public:
  SaveCsv() {
    m_rosSubCsvLaneArray = m_rosNodeHandler.subscribe(
        "csv_lanes", 10, &SaveCsv::csvLanesCallback, this);

    m_rosSubMidLaneArray = m_rosNodeHandler.subscribe(
        "ROI_lanes", 10, &SaveCsv::midLanesCallback, this);

    m_rosNodeHandler.param("save_csv/csvPath", m_path_csv, std::string(""));
    if (m_path_csv == std::string("")) {
      ROS_ERROR_STREAM("path를 지정해주세요.");
    }
    m_rosNodeHandler.param("save_csv/refPath", m_path_mid, std::string(""));
    if (m_path_mid == std::string("")) {
      ROS_ERROR_STREAM("path를 지정해주세요.");
    }
  }

  ~SaveCsv() {}

protected:
  autonomous_msg::LanePointDataArray m_csvLanes;
  autonomous_msg::LanePointDataArray m_midLanes;
  SKusvLanes m_csvFormatLanes;
  SKusvLanes m_csvFormatMid;

public:
  void
  csvLanesCallback(const autonomous_msg::LanePointDataArray::ConstPtr &msg) {
    m_csvLanes.frame_id = msg->frame_id;
    m_csvLanes.id = msg->id;
    m_csvLanes.lane = msg->lane;
  }

  void
  midLanesCallback(const autonomous_msg::LanePointDataArray::ConstPtr &msg) {
    m_midLanes.frame_id = msg->frame_id;
    m_midLanes.id = msg->id;
    m_midLanes.lane = msg->lane;
  }

  void saveMap() {

    if (m_path_csv == std::string("")) {
      ROS_ERROR_STREAM("path를 지정해주세요.");
      return;
    }
    if (m_path_mid == std::string("")) {
      ROS_ERROR_STREAM("path를 지정해주세요.");
      return;
    }

    m_csvFormatLanes.m_vecKusvLanes.clear();
    for (auto i_lane = 0; i_lane < m_csvLanes.lane.size(); i_lane++) {
      SKusvLane csvFormatLane;
      csvFormatLane.m_nLaneID = i_lane;
      for (auto i_point = 0; i_point < m_csvLanes.lane[i_lane].point.size();
           i_point++) {
        csvFormatLane.m_vecKusvLanePoint.push_back(
            SKusvLanePoint(m_csvLanes.lane[i_lane].point[i_point].x,
                           m_csvLanes.lane[i_lane].point[i_point].y));
      }
      m_csvFormatLanes.m_vecKusvLanes.push_back(csvFormatLane);
    }

    m_csvFormatLanes.ExportKusvLaneCsvFile(m_path_csv);



    m_csvFormatMid.m_vecKusvLanes.clear();
    for (auto i_lane = 0; i_lane < m_midLanes.lane.size(); i_lane++) {
      SKusvLane csvFormatLane;
      csvFormatLane.m_nLaneID = i_lane;
      for (auto i_point = 0; i_point < m_midLanes.lane[i_lane].point.size();
           i_point++) {
        csvFormatLane.m_vecKusvLanePoint.push_back(
            SKusvLanePoint(m_midLanes.lane[i_lane].point[i_point].x,
                           m_midLanes.lane[i_lane].point[i_point].y));
      }
      m_csvFormatMid.m_vecKusvLanes.push_back(csvFormatLane);
    }

    m_csvFormatMid.ExportKusvLaneCsvFile(m_path_mid);

    ROS_INFO_STREAM("**Save csv data**");
  }

  std::string getPath() { return m_path_csv; }
};

int main(int argc, char **argv) {

  ros::init(argc, argv, "save_csv");

  SaveCsv saveCsv;

  ros::Rate loop_rate(1.0);
  while (ros::ok()) {
    saveCsv.saveMap();
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
