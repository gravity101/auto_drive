# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "autonomous_msg: 7 messages, 0 services")

set(MSG_I_FLAGS "-Iautonomous_msg:/home/q/ws_final/src/autonomous_msg/msg;-Igeometry_msgs:/opt/ros/melodic/share/geometry_msgs/cmake/../msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(autonomous_msg_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/AccelBrakeSteering.msg" NAME_WE)
add_custom_target(_autonomous_msg_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "autonomous_msg" "/home/q/ws_final/src/autonomous_msg/msg/AccelBrakeSteering.msg" ""
)

get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneDataArray.msg" NAME_WE)
add_custom_target(_autonomous_msg_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "autonomous_msg" "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneDataArray.msg" "autonomous_msg/PolyfitLaneData"
)

get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneData.msg" NAME_WE)
add_custom_target(_autonomous_msg_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "autonomous_msg" "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneData.msg" ""
)

get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/VehicleOutput.msg" NAME_WE)
add_custom_target(_autonomous_msg_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "autonomous_msg" "/home/q/ws_final/src/autonomous_msg/msg/VehicleOutput.msg" ""
)

get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/LanePointDataArray.msg" NAME_WE)
add_custom_target(_autonomous_msg_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "autonomous_msg" "/home/q/ws_final/src/autonomous_msg/msg/LanePointDataArray.msg" "geometry_msgs/Point:autonomous_msg/LanePointData"
)

get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/VehicleInput.msg" NAME_WE)
add_custom_target(_autonomous_msg_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "autonomous_msg" "/home/q/ws_final/src/autonomous_msg/msg/VehicleInput.msg" ""
)

get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/LanePointData.msg" NAME_WE)
add_custom_target(_autonomous_msg_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "autonomous_msg" "/home/q/ws_final/src/autonomous_msg/msg/LanePointData.msg" "geometry_msgs/Point"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/AccelBrakeSteering.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/autonomous_msg
)
_generate_msg_cpp(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneDataArray.msg"
  "${MSG_I_FLAGS}"
  "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneData.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/autonomous_msg
)
_generate_msg_cpp(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/autonomous_msg
)
_generate_msg_cpp(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/VehicleOutput.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/autonomous_msg
)
_generate_msg_cpp(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/LanePointDataArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/home/q/ws_final/src/autonomous_msg/msg/LanePointData.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/autonomous_msg
)
_generate_msg_cpp(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/VehicleInput.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/autonomous_msg
)
_generate_msg_cpp(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/LanePointData.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/autonomous_msg
)

### Generating Services

### Generating Module File
_generate_module_cpp(autonomous_msg
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/autonomous_msg
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(autonomous_msg_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(autonomous_msg_generate_messages autonomous_msg_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/AccelBrakeSteering.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_cpp _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneDataArray.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_cpp _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneData.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_cpp _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/VehicleOutput.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_cpp _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/LanePointDataArray.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_cpp _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/VehicleInput.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_cpp _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/LanePointData.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_cpp _autonomous_msg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(autonomous_msg_gencpp)
add_dependencies(autonomous_msg_gencpp autonomous_msg_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS autonomous_msg_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/AccelBrakeSteering.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/autonomous_msg
)
_generate_msg_eus(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneDataArray.msg"
  "${MSG_I_FLAGS}"
  "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneData.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/autonomous_msg
)
_generate_msg_eus(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/autonomous_msg
)
_generate_msg_eus(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/VehicleOutput.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/autonomous_msg
)
_generate_msg_eus(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/LanePointDataArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/home/q/ws_final/src/autonomous_msg/msg/LanePointData.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/autonomous_msg
)
_generate_msg_eus(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/VehicleInput.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/autonomous_msg
)
_generate_msg_eus(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/LanePointData.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/autonomous_msg
)

### Generating Services

### Generating Module File
_generate_module_eus(autonomous_msg
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/autonomous_msg
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(autonomous_msg_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(autonomous_msg_generate_messages autonomous_msg_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/AccelBrakeSteering.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_eus _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneDataArray.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_eus _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneData.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_eus _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/VehicleOutput.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_eus _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/LanePointDataArray.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_eus _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/VehicleInput.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_eus _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/LanePointData.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_eus _autonomous_msg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(autonomous_msg_geneus)
add_dependencies(autonomous_msg_geneus autonomous_msg_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS autonomous_msg_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/AccelBrakeSteering.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/autonomous_msg
)
_generate_msg_lisp(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneDataArray.msg"
  "${MSG_I_FLAGS}"
  "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneData.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/autonomous_msg
)
_generate_msg_lisp(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/autonomous_msg
)
_generate_msg_lisp(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/VehicleOutput.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/autonomous_msg
)
_generate_msg_lisp(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/LanePointDataArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/home/q/ws_final/src/autonomous_msg/msg/LanePointData.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/autonomous_msg
)
_generate_msg_lisp(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/VehicleInput.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/autonomous_msg
)
_generate_msg_lisp(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/LanePointData.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/autonomous_msg
)

### Generating Services

### Generating Module File
_generate_module_lisp(autonomous_msg
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/autonomous_msg
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(autonomous_msg_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(autonomous_msg_generate_messages autonomous_msg_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/AccelBrakeSteering.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_lisp _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneDataArray.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_lisp _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneData.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_lisp _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/VehicleOutput.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_lisp _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/LanePointDataArray.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_lisp _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/VehicleInput.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_lisp _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/LanePointData.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_lisp _autonomous_msg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(autonomous_msg_genlisp)
add_dependencies(autonomous_msg_genlisp autonomous_msg_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS autonomous_msg_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/AccelBrakeSteering.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/autonomous_msg
)
_generate_msg_nodejs(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneDataArray.msg"
  "${MSG_I_FLAGS}"
  "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneData.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/autonomous_msg
)
_generate_msg_nodejs(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/autonomous_msg
)
_generate_msg_nodejs(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/VehicleOutput.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/autonomous_msg
)
_generate_msg_nodejs(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/LanePointDataArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/home/q/ws_final/src/autonomous_msg/msg/LanePointData.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/autonomous_msg
)
_generate_msg_nodejs(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/VehicleInput.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/autonomous_msg
)
_generate_msg_nodejs(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/LanePointData.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/autonomous_msg
)

### Generating Services

### Generating Module File
_generate_module_nodejs(autonomous_msg
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/autonomous_msg
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(autonomous_msg_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(autonomous_msg_generate_messages autonomous_msg_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/AccelBrakeSteering.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_nodejs _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneDataArray.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_nodejs _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneData.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_nodejs _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/VehicleOutput.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_nodejs _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/LanePointDataArray.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_nodejs _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/VehicleInput.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_nodejs _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/LanePointData.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_nodejs _autonomous_msg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(autonomous_msg_gennodejs)
add_dependencies(autonomous_msg_gennodejs autonomous_msg_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS autonomous_msg_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/AccelBrakeSteering.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/autonomous_msg
)
_generate_msg_py(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneDataArray.msg"
  "${MSG_I_FLAGS}"
  "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneData.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/autonomous_msg
)
_generate_msg_py(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/autonomous_msg
)
_generate_msg_py(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/VehicleOutput.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/autonomous_msg
)
_generate_msg_py(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/LanePointDataArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/home/q/ws_final/src/autonomous_msg/msg/LanePointData.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/autonomous_msg
)
_generate_msg_py(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/VehicleInput.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/autonomous_msg
)
_generate_msg_py(autonomous_msg
  "/home/q/ws_final/src/autonomous_msg/msg/LanePointData.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/autonomous_msg
)

### Generating Services

### Generating Module File
_generate_module_py(autonomous_msg
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/autonomous_msg
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(autonomous_msg_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(autonomous_msg_generate_messages autonomous_msg_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/AccelBrakeSteering.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_py _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneDataArray.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_py _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/PolyfitLaneData.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_py _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/VehicleOutput.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_py _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/LanePointDataArray.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_py _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/VehicleInput.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_py _autonomous_msg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/q/ws_final/src/autonomous_msg/msg/LanePointData.msg" NAME_WE)
add_dependencies(autonomous_msg_generate_messages_py _autonomous_msg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(autonomous_msg_genpy)
add_dependencies(autonomous_msg_genpy autonomous_msg_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS autonomous_msg_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/autonomous_msg)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/autonomous_msg
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(autonomous_msg_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(autonomous_msg_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/autonomous_msg)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/autonomous_msg
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(autonomous_msg_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(autonomous_msg_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/autonomous_msg)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/autonomous_msg
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(autonomous_msg_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(autonomous_msg_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/autonomous_msg)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/autonomous_msg
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(autonomous_msg_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(autonomous_msg_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/autonomous_msg)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/autonomous_msg\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/autonomous_msg
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(autonomous_msg_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(autonomous_msg_generate_messages_py std_msgs_generate_messages_py)
endif()
