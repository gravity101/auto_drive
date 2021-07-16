;; Auto-generated. Do not edit!


(when (boundp 'autonomous_msg::VehicleOutput)
  (if (not (find-package "AUTONOMOUS_MSG"))
    (make-package "AUTONOMOUS_MSG"))
  (shadow 'VehicleOutput (find-package "AUTONOMOUS_MSG")))
(unless (find-package "AUTONOMOUS_MSG::VEHICLEOUTPUT")
  (make-package "AUTONOMOUS_MSG::VEHICLEOUTPUT"))

(in-package "ROS")
;;//! \htmlinclude VehicleOutput.msg.html


(defclass autonomous_msg::VehicleOutput
  :super ros::object
  :slots (_id _x _y _yaw _velocity ))

(defmethod autonomous_msg::VehicleOutput
  (:init
   (&key
    ((:id __id) "")
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:yaw __yaw) 0.0)
    ((:velocity __velocity) 0.0)
    )
   (send-super :init)
   (setq _id (string __id))
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _yaw (float __yaw))
   (setq _velocity (float __velocity))
   self)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:yaw
   (&optional __yaw)
   (if __yaw (setq _yaw __yaw)) _yaw)
  (:velocity
   (&optional __velocity)
   (if __velocity (setq _velocity __velocity)) _velocity)
  (:serialization-length
   ()
   (+
    ;; string _id
    4 (length _id)
    ;; float64 _x
    8
    ;; float64 _y
    8
    ;; float64 _yaw
    8
    ;; float64 _velocity
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _id
       (write-long (length _id) s) (princ _id s)
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y
       (sys::poke _y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _yaw
       (sys::poke _yaw (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _velocity
       (sys::poke _velocity (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y
     (setq _y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _yaw
     (setq _yaw (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _velocity
     (setq _velocity (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get autonomous_msg::VehicleOutput :md5sum-) "8e71ca8b40f5ece91a4b535460967ce7")
(setf (get autonomous_msg::VehicleOutput :datatype-) "autonomous_msg/VehicleOutput")
(setf (get autonomous_msg::VehicleOutput :definition-)
      "string id 
float64 x
float64 y
float64 yaw
float64 velocity
")



(provide :autonomous_msg/VehicleOutput "8e71ca8b40f5ece91a4b535460967ce7")


