;; Auto-generated. Do not edit!


(when (boundp 'autonomous_msg::PolyfitLaneData)
  (if (not (find-package "AUTONOMOUS_MSG"))
    (make-package "AUTONOMOUS_MSG"))
  (shadow 'PolyfitLaneData (find-package "AUTONOMOUS_MSG")))
(unless (find-package "AUTONOMOUS_MSG::POLYFITLANEDATA")
  (make-package "AUTONOMOUS_MSG::POLYFITLANEDATA"))

(in-package "ROS")
;;//! \htmlinclude PolyfitLaneData.msg.html


(defclass autonomous_msg::PolyfitLaneData
  :super ros::object
  :slots (_frame_id _id _a0 _a1 _a2 _a3 ))

(defmethod autonomous_msg::PolyfitLaneData
  (:init
   (&key
    ((:frame_id __frame_id) "")
    ((:id __id) "")
    ((:a0 __a0) 0.0)
    ((:a1 __a1) 0.0)
    ((:a2 __a2) 0.0)
    ((:a3 __a3) 0.0)
    )
   (send-super :init)
   (setq _frame_id (string __frame_id))
   (setq _id (string __id))
   (setq _a0 (float __a0))
   (setq _a1 (float __a1))
   (setq _a2 (float __a2))
   (setq _a3 (float __a3))
   self)
  (:frame_id
   (&optional __frame_id)
   (if __frame_id (setq _frame_id __frame_id)) _frame_id)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:a0
   (&optional __a0)
   (if __a0 (setq _a0 __a0)) _a0)
  (:a1
   (&optional __a1)
   (if __a1 (setq _a1 __a1)) _a1)
  (:a2
   (&optional __a2)
   (if __a2 (setq _a2 __a2)) _a2)
  (:a3
   (&optional __a3)
   (if __a3 (setq _a3 __a3)) _a3)
  (:serialization-length
   ()
   (+
    ;; string _frame_id
    4 (length _frame_id)
    ;; string _id
    4 (length _id)
    ;; float64 _a0
    8
    ;; float64 _a1
    8
    ;; float64 _a2
    8
    ;; float64 _a3
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _frame_id
       (write-long (length _frame_id) s) (princ _frame_id s)
     ;; string _id
       (write-long (length _id) s) (princ _id s)
     ;; float64 _a0
       (sys::poke _a0 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _a1
       (sys::poke _a1 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _a2
       (sys::poke _a2 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _a3
       (sys::poke _a3 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _frame_id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _frame_id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float64 _a0
     (setq _a0 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _a1
     (setq _a1 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _a2
     (setq _a2 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _a3
     (setq _a3 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get autonomous_msg::PolyfitLaneData :md5sum-) "f8a9f56a6b73465e7e95b32b32224135")
(setf (get autonomous_msg::PolyfitLaneData :datatype-) "autonomous_msg/PolyfitLaneData")
(setf (get autonomous_msg::PolyfitLaneData :definition-)
      "string frame_id
string id 
float64 a0
float64 a1
float64 a2
float64 a3
")



(provide :autonomous_msg/PolyfitLaneData "f8a9f56a6b73465e7e95b32b32224135")


