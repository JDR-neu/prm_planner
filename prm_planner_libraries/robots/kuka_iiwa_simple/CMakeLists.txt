cmake_minimum_required(VERSION 2.8.3)
project(kuka_iiwa_simple)

set(CMAKE_BUILD_TYPE RelWithDebInfo) #RelWithDebInfo

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  prm_planner
  roscpp
)

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS system thread)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
    INCLUDE_DIRS include
    LIBRARIES kuka_iiwa_simple
    CATKIN_DEPENDS prm_planner roscpp
    DEPENDS Boost
)

###########
## Build ##
###########

ADD_DEFINITIONS(
    -std=c++11
    -D__cplusplus=201103L #for eclipse
)

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)

## Declare a C++ library
add_library(kuka_iiwa_simple
   src/iiwa_simple_interface.cpp
)

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(kuka_iiwa_vrep ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
# add_executable(kuka_iiwa_vrep_node src/kuka_robot_executers_node.cpp)

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(kuka_iiwa_vrep_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(kuka_iiwa_simple
   ${catkin_LIBRARIES}
)

