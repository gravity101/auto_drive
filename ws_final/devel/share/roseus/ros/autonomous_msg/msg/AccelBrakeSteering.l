;; Auto-generated. Do not edit!


(when (boundp 'autonomous_msg::AccelBrakeSteering)
  (if (not (find-package "AUTONOMOUS_MSG"))
    (make-package "AUTONOMOUS_MSG"))
  (shadow 'AccelBrakeSteering (find-package "AUTONOMOUS_MSG")))
(unless (find-package "AUTONOMOUS_MSG::ACCELBRAKESTEERING")
  (make-package "AUTONOMOUS_MSG::ACCELBRAKESTEERING"))

(in-package "ROS")
;;//! \htmlinclude AccelBrakeSteering.msg.html


(defclass autonomous_msg::AccelBrakeSteering
  :super ros::object
  :slots (_accel _brake _frontAngle ))

(defmethod autonomous_msg::AccelBrakeSteering
  (:init
   (&key
    ((:accel __accel) 0.0)
    ((:brake __brake) 0.0)
    ((:frontAngle __frontAngle) 0.0)
    )
   (send-super :init)
   (setq _accel (float __accel))
   (setq _brake (float __brake))
   (setq _frontAngle (float __frontAngle))
   self)
  (:accel
   (&optional __accel)
   (if __accel (setq _accel __accel)) _accel)
  (:brake
   (&optional __brake)
   (if __brake (setq _brake __brake)) _brake)
  (:frontAngle
   (&optional __frontAngle)
   (if __frontAngle (setq _frontAngle __frontAngle)) _frontAngle)
  (:serialization-length
   ()
   (+
    ;; float64 _accel
    8
    ;; float64 _brake
    8
    ;; float64 _frontAngle
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _accel
       (sys::poke _accel (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _brake
       (sys::poke _brake (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _frontAngle
       (sys::poke _frontAngle (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _accel
     (setq _accel (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _brake
     (setq _brake (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _frontAngle
     (setq _frontAngle (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get autonomous_msg::AccelBrakeSteering :md5sum-) "27a9643207b32f2deac0ed64a59c362d")
(setf (get autonomous_msg::AccelBrakeSteering :datatype-) "autonomous_msg/AccelBrakeSteering")
(setf (get autonomous_msg::AccelBrakeSteering :definition-)
      "float64 accel
float64 brake
float64 frontAngle

")



(provide :autonomous_msg/AccelBrakeSteering "27a9643207b32f2deac0ed64a59c362d")


