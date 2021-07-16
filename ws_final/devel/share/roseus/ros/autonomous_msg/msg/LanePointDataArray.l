;; Auto-generated. Do not edit!


(when (boundp 'autonomous_msg::LanePointDataArray)
  (if (not (find-package "AUTONOMOUS_MSG"))
    (make-package "AUTONOMOUS_MSG"))
  (shadow 'LanePointDataArray (find-package "AUTONOMOUS_MSG")))
(unless (find-package "AUTONOMOUS_MSG::LANEPOINTDATAARRAY")
  (make-package "AUTONOMOUS_MSG::LANEPOINTDATAARRAY"))

(in-package "ROS")
;;//! \htmlinclude LanePointDataArray.msg.html


(defclass autonomous_msg::LanePointDataArray
  :super ros::object
  :slots (_frame_id _id _lane ))

(defmethod autonomous_msg::LanePointDataArray
  (:init
   (&key
    ((:frame_id __frame_id) "")
    ((:id __id) "")
    ((:lane __lane) (let (r) (dotimes (i 0) (push (instance autonomous_msg::LanePointData :init) r)) r))
    )
   (send-super :init)
   (setq _frame_id (string __frame_id))
   (setq _id (string __id))
   (setq _lane __lane)
   self)
  (:frame_id
   (&optional __frame_id)
   (if __frame_id (setq _frame_id __frame_id)) _frame_id)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:lane
   (&rest __lane)
   (if (keywordp (car __lane))
       (send* _lane __lane)
     (progn
       (if __lane (setq _lane (car __lane)))
       _lane)))
  (:serialization-length
   ()
   (+
    ;; string _frame_id
    4 (length _frame_id)
    ;; string _id
    4 (length _id)
    ;; autonomous_msg/LanePointData[] _lane
    (apply #'+ (send-all _lane :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _frame_id
       (write-long (length _frame_id) s) (princ _frame_id s)
     ;; string _id
       (write-long (length _id) s) (princ _id s)
     ;; autonomous_msg/LanePointData[] _lane
     (write-long (length _lane) s)
     (dolist (elem _lane)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _frame_id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _frame_id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; autonomous_msg/LanePointData[] _lane
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _lane (let (r) (dotimes (i n) (push (instance autonomous_msg::LanePointData :init) r)) r))
     (dolist (elem- _lane)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get autonomous_msg::LanePointDataArray :md5sum-) "3d7bdca5f96098a16da2bfbfc64643b3")
(setf (get autonomous_msg::LanePointDataArray :datatype-) "autonomous_msg/LanePointDataArray")
(setf (get autonomous_msg::LanePointDataArray :definition-)
      "string frame_id
string id 
LanePointData[] lane

================================================================================
MSG: autonomous_msg/LanePointData
string frame_id
string id 
geometry_msgs/Point[] point

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :autonomous_msg/LanePointDataArray "3d7bdca5f96098a16da2bfbfc64643b3")


