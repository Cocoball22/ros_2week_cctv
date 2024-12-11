cmake_minimum_required(VERSION 3.0.2)
project(cctv_pkg)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  cv_bridge
  sensor_msgs

)

find_package(OpenCV REQUIRED)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES cctv_pkg
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node src/cctv_pkg_node.cpp)

set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)
