;; Auto-generated. Do not edit!


(when (boundp 'autonomous_msg::PolyfitLaneDataArray)
  (if (not (find-package "AUTONOMOUS_MSG"))
    (make-package "AUTONOMOUS_MSG"))
  (shadow 'PolyfitLaneDataArray (find-package "AUTONOMOUS_MSG")))
(unless (find-package "AUTONOMOUS_MSG::POLYFITLANEDATAARRAY")
  (make-package "AUTONOMOUS_MSG::POLYFITLANEDATAARRAY"))

(in-package "ROS")
;;//! \htmlinclude PolyfitLaneDataArray.msg.html


(defclass autonomous_msg::PolyfitLaneDataArray
  :super ros::object
  :slots (_frame_id _polyfitLanes ))

(defmethod autonomous_msg::PolyfitLaneDataArray
  (:init
   (&key
    ((:frame_id __frame_id) "")
    ((:polyfitLanes __polyfitLanes) (let (r) (dotimes (i 0) (push (instance autonomous_msg::PolyfitLaneData :init) r)) r))
    )
   (send-super :init)
   (setq _frame_id (string __frame_id))
   (setq _polyfitLanes __polyfitLanes)
   self)
  (:frame_id
   (&optional __frame_id)
   (if __frame_id (setq _frame_id __frame_id)) _frame_id)
  (:polyfitLanes
   (&rest __polyfitLanes)
   (if (keywordp (car __polyfitLanes))
       (send* _polyfitLanes __polyfitLanes)
     (progn
       (if __polyfitLanes (setq _polyfitLanes (car __polyfitLanes)))
       _polyfitLanes)))
  (:serialization-length
   ()
   (+
    ;; string _frame_id
    4 (length _frame_id)
    ;; autonomous_msg/PolyfitLaneData[] _polyfitLanes
    (apply #'+ (send-all _polyfitLanes :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _frame_id
       (write-long (length _frame_id) s) (princ _frame_id s)
     ;; autonomous_msg/PolyfitLaneData[] _polyfitLanes
     (write-long (length _polyfitLanes) s)
     (dolist (elem _polyfitLanes)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _frame_id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _frame_id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; autonomous_msg/PolyfitLaneData[] _polyfitLanes
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _polyfitLanes (let (r) (dotimes (i n) (push (instance autonomous_msg::PolyfitLaneData :init) r)) r))
     (dolist (elem- _polyfitLanes)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get autonomous_msg::PolyfitLaneDataArray :md5sum-) "1c4f872af1e86d670a3cbaed9d3c5647")
(setf (get autonomous_msg::PolyfitLaneDataArray :datatype-) "autonomous_msg/PolyfitLaneDataArray")
(setf (get autonomous_msg::PolyfitLaneDataArray :definition-)
      "string frame_id
PolyfitLaneData[] polyfitLanes
================================================================================
MSG: autonomous_msg/PolyfitLaneData
string frame_id
string id 
float64 a0
float64 a1
float64 a2
float64 a3
")



(provide :autonomous_msg/PolyfitLaneDataArray "1c4f872af1e86d670a3cbaed9d3c5647")


