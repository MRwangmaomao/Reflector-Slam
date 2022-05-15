cmake_minimum_required(VERSION 2.8.3)
project(reflector_slam)

# add_compile_options(-std=c++11)


set(PACKAGE_DEPENDENCIES
  roscpp
  sensor_msgs
)

find_package(catkin REQUIRED COMPONENTS ${PACKAGE_DEPENDENCIES})


catkin_package(CATKIN_DEPENDS
    ${PACKAGE_DEPENDENCIES}
)

include_directories(
    ${catkin_INCLUDE_DIRS}
)

add_executable(slam_node node.cpp)

target_link_libraries(slam_node
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
)

