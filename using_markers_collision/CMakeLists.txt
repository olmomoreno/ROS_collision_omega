# What version of CMake is needed?
cmake_minimum_required(VERSION 2.8.3)

# The name of this package.
project(using_markers_collision)

# Find the catkin build system, and any other packages on which we depend.
find_package(catkin REQUIRED COMPONENTS roscpp visualization_msgs)

# Declare our catkin package.
catkin_package()

# Specify locations of header files.
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(marker_array_collision_exe src/mac_collision.cpp)
target_link_libraries(marker_array_collision_exe ${catkin_LIBRARIES})

add_executable(collision_engine_exe src/collision_engine.cpp)
target_link_libraries(collision_engine_exe ${catkin_LIBRARIES})

