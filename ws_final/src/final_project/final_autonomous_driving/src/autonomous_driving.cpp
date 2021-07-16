#include <math.h>
#include <ros/ros.h>
#include <string>
#include "autonomous_msg/PolyfitLaneDataArray.h"
#include "autonomous_msg/VehicleInput.h"
#include "autonomous_msg/VehicleOutput.h"
#include "std_msgs/Float64.h"

class AutonomousDriving {
 protected:
  ros::NodeHandle m_rosNodeHandler;
  ros::Publisher m_rosPubVehicleInput;

  ros::Subscriber m_rosSubVehicleState;
  ros::Subscriber m_rosSubPolyLanes;
  ros::Subscriber m_rosSubDrivingInput;
  ros::Subscriber m_rosLimitSpeed;
  ros::Subscriber m_rosSubLidar;

  ros::Publisher m_rosPubDrivingWay;

  std::string m_vehicle_namespace_param;
  double m_lookAhead_param = 0.0;
  
 public:
  AutonomousDriving() {
    m_rosSubVehicleState = m_rosNodeHandler.subscribe(
        "vehicle_output", 10, &AutonomousDriving::vehicleStateCallback, this);

    m_rosPubVehicleInput =
        m_rosNodeHandler.advertise<autonomous_msg::VehicleInput>(
            "vehicle_input", 10);

    m_rosSubPolyLanes = m_rosNodeHandler.subscribe(
        "polyfit_lanes", 10, &AutonomousDriving::polyLanesCallback, this);

    m_rosLimitSpeed = m_rosNodeHandler.subscribe(
        "/limit_speed", 10, &AutonomousDriving::limitSpeedCallback, this);

    m_rosSubDrivingInput = m_rosNodeHandler.subscribe(
        "/driving_input", 10, &AutonomousDriving::drivingInputCallback, this);

    m_rosSubLidar = m_rosNodeHandler.subscribe(
        "/lidar", 10, &AutonomousDriving::lidarSensorCallback, this);

    m_rosPubDrivingWay =
        m_rosNodeHandler.advertise<autonomous_msg::PolyfitLaneData>(
            "driving_way", 10);

    m_rosNodeHandler.param("autonomous_driving/ns", m_vehicle_namespace_param,
                           std::string(""));
    m_rosNodeHandler.param("autonomous_driving/lookAhead", m_lookAhead_param,
                           5.0);
  }

  ~AutonomousDriving() {}

 protected:
  autonomous_msg::PolyfitLaneDataArray m_polyLanes;
  autonomous_msg::VehicleInput m_drivingInput;
  autonomous_msg::PolyfitLaneData m_midPolyLane;
  autonomous_msg::VehicleOutput m_vehicleState;
  autonomous_msg::VehicleOutput m_lidarOutput;
  double m_limitSpeed = 0.0;
  bool isLidarDataExist = false;
  
  float distance = 0.0;
  

 public:
  /**
   * @brief Temporary functions for debugging pure pursuit
   *
   * @param VehicleInput accel and brake
   */
  void drivingInputCallback(const autonomous_msg::VehicleInput::ConstPtr &msg) {
    m_drivingInput.accel = msg->accel;
    m_drivingInput.brake = msg->brake;
    // m_drivingInput.steering = msg->steering;
  }

  void vehicleStateCallback(
      const autonomous_msg::VehicleOutput::ConstPtr &msg) {
    m_vehicleState = *msg;
  }

  void limitSpeedCallback(const std_msgs::Float64::ConstPtr &msg) {
    m_limitSpeed = msg->data;

  }

  void polyLanesCallback(
    const autonomous_msg::PolyfitLaneDataArray::ConstPtr &msg) {
    m_polyLanes = *msg;
  }
  void lidarSensorCallback(const autonomous_msg::VehicleOutput::ConstPtr &msg)
  {
    m_lidarOutput = *msg;
    isLidarDataExist = true;
    distance = sqrt((m_lidarOutput.x - m_vehicleState.x)*(m_lidarOutput.x - m_vehicleState.x) + (m_lidarOutput.y - m_vehicleState.y)*(m_lidarOutput.y - m_vehicleState.y));
    
  }

  void controlVehicleSpeed(double targetSpeed_ms) {
      
   double angle = 0;   
   if ( abs(m_drivingInput.steering) > 0.06 )
   {
   int angle = 0.5;
   }
   
   
   
   
    
  
      m_limitSpeed = 30.0;

      
   

   //ROS_INFO_STREAM_THROTTLE(0.1," targetSpeed_ms : "<<targetSpeed_ms);
   //ROS_INFO_STREAM_THROTTLE(0.1,"m_limitSpeed : "<<m_limitSpeed);
        //ROS_INFO_STREAM_THROTTLE(0.1,"distance : "<<distance);


    if (m_vehicleState.velocity >= m_limitSpeed)
    {
      
      m_drivingInput.brake = 1;
      
      
       
    }
    else
    {
      
       m_drivingInput.accel = targetSpeed_ms;
      
      if (distance <= 10 && distance > 0)
      {
          m_drivingInput.brake = 100;
      }
      
      
    }   
   
       
  }

  /**
   * brief: Find the left lane and the right lane, then change to the actual
   * driving lane. input: m_polyLanes output: m_midPolyLane
   */
  void findDrivingWay() 
  {
    
    auto lanesize = m_polyLanes.polyfitLanes.size();
   
   
    
    int index1=8;
    int index2=8;
    
    
    ROS_INFO_STREAM_THROTTLE(0.1," lanesize : "<<lanesize);
    
   
    //printf("%ld\n", lanesize);
    if (lanesize == 0) 
    {
      
            m_midPolyLane.a0 = m_midPolyLane.a0;
            m_midPolyLane.a1 = m_midPolyLane.a1;
            m_midPolyLane.a2 = m_midPolyLane.a2;
            m_midPolyLane.a3 = m_midPolyLane.a3;
    }
    else if (lanesize == 2)
    {
   
          
   
       if (  (abs(m_polyLanes.polyfitLanes[0].a0) + abs(m_polyLanes.polyfitLanes[1].a0 ))/2 <= 1.80 )
       {
              m_midPolyLane.a0 = (m_polyLanes.polyfitLanes[0].a0 + m_polyLanes.polyfitLanes[1].a0)/2;
              m_midPolyLane.a1 = (m_polyLanes.polyfitLanes[0].a1 + m_polyLanes.polyfitLanes[1].a1)/2;
              m_midPolyLane.a2 = (m_polyLanes.polyfitLanes[0].a2 + m_polyLanes.polyfitLanes[1].a2)/2;
              m_midPolyLane.a3 = (m_polyLanes.polyfitLanes[0].a3 + m_polyLanes.polyfitLanes[1].a3)/2; 
         }
       
       
     
            
   }
   else if (lanesize >= 3)
   {  
     
      for(int i = 0; i<lanesize; i++) 
        {
           if ( m_polyLanes.polyfitLanes[i].a0 > 3.7 )
           {
           index1= i;
           }
           else if( m_polyLanes.polyfitLanes[i].a0 < -3.7 )
           {
           index2 = i;
           }
        }
      
      if( ( index1 == 8 || index2 == 8 ) )
      {
      	ROS_INFO_STREAM_THROTTLE(0.1," Error : "<<m_polyLanes.polyfitLanes[0].a0<<"   "<<m_polyLanes.polyfitLanes[1].a0<<"   "<<m_polyLanes.polyfitLanes[2].a0);

      	for(int i = 0; i<lanesize; i++) 
        {
           if ( m_polyLanes.polyfitLanes[i].a0 < -1.2 && m_polyLanes.polyfitLanes[i].a0 >= -2.2 )
           {
           index1= i;
           }
           else if( m_polyLanes.polyfitLanes[i].a0 > 1.2 && m_polyLanes.polyfitLanes[i].a0 <= 2.2 )
           {
           index2 = i;
           }
        }
      }



      	


	
   	m_midPolyLane.a0 = (m_polyLanes.polyfitLanes[index1].a0 + m_polyLanes.polyfitLanes[index2].a0)/2;
        m_midPolyLane.a1 = (m_polyLanes.polyfitLanes[index1].a1 + m_polyLanes.polyfitLanes[index2].a1)/2;
        m_midPolyLane.a2 = (m_polyLanes.polyfitLanes[index1].a2 + m_polyLanes.polyfitLanes[index2].a2)/2;
        m_midPolyLane.a3 = (m_polyLanes.polyfitLanes[index1].a3 + m_polyLanes.polyfitLanes[index2].a3)/2;
   }
 


      

    

    
   
   
    
    m_midPolyLane.frame_id = m_vehicle_namespace_param + "/body";
    m_rosPubDrivingWay.publish(m_midPolyLane);
}

  /**
   * brief: Find the steering angle for driving in the driving lane.
   * input: m_midPolyLane
   * output: m_drivingInput.steering
   */
void calcSteeringAngle() {
      double gx = 7;

      double L = 1.402 + 1.646;

      double gy = m_midPolyLane.a0 + m_midPolyLane.a1*gx + m_midPolyLane.a2*gx*gx + m_midPolyLane.a3*gx*gx*gx;
      
      double ld_square = gx*gx + gy*gy;
      
      if(ld_square==0) ld_square = INT_MIN;
      double eld = gy;

      m_drivingInput.steering = atan(2*L*eld/ld_square);
      
    }


  void publishVehicleInput() { m_rosPubVehicleInput.publish(m_drivingInput); }
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "autonomous_driving");

  AutonomousDriving autonomousDriving;

  double prev_csvLaneMarkTime = ros::Time::now().toSec();
  // The approximate control time is 100 Hz
  ros::Rate loop_rate(100);
    int count = 0;
    while (ros::ok()) {

   
    
    autonomousDriving.controlVehicleSpeed(1);
    
    autonomousDriving.findDrivingWay();
    autonomousDriving.calcSteeringAngle();
    autonomousDriving.publishVehicleInput();

    if ((ros::Time::now().toSec() - prev_csvLaneMarkTime) > 1.0) {
      prev_csvLaneMarkTime = ros::Time::now().toSec();
    }
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
