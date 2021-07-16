; Auto-generated. Do not edit!


(cl:in-package autonomous_msg-msg)


;//! \htmlinclude AccelBrakeSteering.msg.html

(cl:defclass <AccelBrakeSteering> (roslisp-msg-protocol:ros-message)
  ((accel
    :reader accel
    :initarg :accel
    :type cl:float
    :initform 0.0)
   (brake
    :reader brake
    :initarg :brake
    :type cl:float
    :initform 0.0)
   (frontAngle
    :reader frontAngle
    :initarg :frontAngle
    :type cl:float
    :initform 0.0))
)

(cl:defclass AccelBrakeSteering (<AccelBrakeSteering>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <AccelBrakeSteering>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'AccelBrakeSteering)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name autonomous_msg-msg:<AccelBrakeSteering> is deprecated: use autonomous_msg-msg:AccelBrakeSteering instead.")))

(cl:ensure-generic-function 'accel-val :lambda-list '(m))
(cl:defmethod accel-val ((m <AccelBrakeSteering>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autonomous_msg-msg:accel-val is deprecated.  Use autonomous_msg-msg:accel instead.")
  (accel m))

(cl:ensure-generic-function 'brake-val :lambda-list '(m))
(cl:defmethod brake-val ((m <AccelBrakeSteering>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autonomous_msg-msg:brake-val is deprecated.  Use autonomous_msg-msg:brake instead.")
  (brake m))

(cl:ensure-generic-function 'frontAngle-val :lambda-list '(m))
(cl:defmethod frontAngle-val ((m <AccelBrakeSteering>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader autonomous_msg-msg:frontAngle-val is deprecated.  Use autonomous_msg-msg:frontAngle instead.")
  (frontAngle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <AccelBrakeSteering>) ostream)
  "Serializes a message object of type '<AccelBrakeSteering>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'accel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'brake))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'frontAngle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <AccelBrakeSteering>) istream)
  "Deserializes a message object of type '<AccelBrakeSteering>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'accel) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'brake) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'frontAngle) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<AccelBrakeSteering>)))
  "Returns string type for a message object of type '<AccelBrakeSteering>"
  "autonomous_msg/AccelBrakeSteering")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'AccelBrakeSteering)))
  "Returns string type for a message object of type 'AccelBrakeSteering"
  "autonomous_msg/AccelBrakeSteering")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<AccelBrakeSteering>)))
  "Returns md5sum for a message object of type '<AccelBrakeSteering>"
  "27a9643207b32f2deac0ed64a59c362d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'AccelBrakeSteering)))
  "Returns md5sum for a message object of type 'AccelBrakeSteering"
  "27a9643207b32f2deac0ed64a59c362d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<AccelBrakeSteering>)))
  "Returns full string definition for message of type '<AccelBrakeSteering>"
  (cl:format cl:nil "float64 accel~%float64 brake~%float64 frontAngle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'AccelBrakeSteering)))
  "Returns full string definition for message of type 'AccelBrakeSteering"
  (cl:format cl:nil "float64 accel~%float64 brake~%float64 frontAngle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <AccelBrakeSteering>))
  (cl:+ 0
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <AccelBrakeSteering>))
  "Converts a ROS message object to a list"
  (cl:list 'AccelBrakeSteering
    (cl:cons ':accel (accel msg))
    (cl:cons ':brake (brake msg))
    (cl:cons ':frontAngle (frontAngle msg))
))
