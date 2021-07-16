// Auto-generated. Do not edit!

// (in-package autonomous_msg.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let LanePointData = require('./LanePointData.js');

//-----------------------------------------------------------

class LanePointDataArray {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.frame_id = null;
      this.id = null;
      this.lane = null;
    }
    else {
      if (initObj.hasOwnProperty('frame_id')) {
        this.frame_id = initObj.frame_id
      }
      else {
        this.frame_id = '';
      }
      if (initObj.hasOwnProperty('id')) {
        this.id = initObj.id
      }
      else {
        this.id = '';
      }
      if (initObj.hasOwnProperty('lane')) {
        this.lane = initObj.lane
      }
      else {
        this.lane = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type LanePointDataArray
    // Serialize message field [frame_id]
    bufferOffset = _serializer.string(obj.frame_id, buffer, bufferOffset);
    // Serialize message field [id]
    bufferOffset = _serializer.string(obj.id, buffer, bufferOffset);
    // Serialize message field [lane]
    // Serialize the length for message field [lane]
    bufferOffset = _serializer.uint32(obj.lane.length, buffer, bufferOffset);
    obj.lane.forEach((val) => {
      bufferOffset = LanePointData.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type LanePointDataArray
    let len;
    let data = new LanePointDataArray(null);
    // Deserialize message field [frame_id]
    data.frame_id = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [id]
    data.id = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [lane]
    // Deserialize array length for message field [lane]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.lane = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.lane[i] = LanePointData.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.frame_id.length;
    length += object.id.length;
    object.lane.forEach((val) => {
      length += LanePointData.getMessageSize(val);
    });
    return length + 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'autonomous_msg/LanePointDataArray';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3d7bdca5f96098a16da2bfbfc64643b3';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string frame_id
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new LanePointDataArray(null);
    if (msg.frame_id !== undefined) {
      resolved.frame_id = msg.frame_id;
    }
    else {
      resolved.frame_id = ''
    }

    if (msg.id !== undefined) {
      resolved.id = msg.id;
    }
    else {
      resolved.id = ''
    }

    if (msg.lane !== undefined) {
      resolved.lane = new Array(msg.lane.length);
      for (let i = 0; i < resolved.lane.length; ++i) {
        resolved.lane[i] = LanePointData.Resolve(msg.lane[i]);
      }
    }
    else {
      resolved.lane = []
    }

    return resolved;
    }
};

module.exports = LanePointDataArray;
