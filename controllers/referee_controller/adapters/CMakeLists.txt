cmake_minimum_required(VERSION 3.0.2)
project(travesim_adapters)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Enable all warnings and treat warnings as errors
add_compile_options(-Wall -Werror)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  dynamic_reconfigure
  rospy
)

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS system thread)

## Add subdirectories
add_subdirectory(proto)

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## Generate dynamic reconfigure parameters in the 'cfg' folder
generate_dynamic_reconfigure_options(
  cfg/Vision.cfg
  cfg/Teams.cfg
  cfg/Replacer.cfg
)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES travesim_adapters
#  CATKIN_DEPENDS Boost roscpp std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

## Declare a C++ library
add_library(${PROJECT_NAME}_core
  src/lib/data/team_command.cpp
  src/lib/data/entity_state.cpp
  src/lib/data/robot_state.cpp
  src/lib/data/field_state.cpp
)

add_library(${PROJECT_NAME}_ros
  src/lib/data/converter/ros_side.cpp
  src/lib/ros/vision_receiver.cpp
  src/lib/ros/teams_sender.cpp
  src/lib/ros/replacer_sender.cpp
)

add_library(${PROJECT_NAME}_udp_comm
  src/lib/udp/sender.cpp
  src/lib/udp/receiver.cpp
  src/lib/udp/unicast_sender.cpp
  src/lib/udp/unicast_receiver.cpp
  src/lib/udp/multicast_sender.cpp
  src/lib/udp/multicast_receiver.cpp
)

add_library(${PROJECT_NAME}_protobuf_comm
  src/lib/protobuf/vision_sender.cpp
  src/lib/protobuf/team_receiver.cpp
  src/lib/protobuf/replacer_receiver.cpp
)

add_library(${PROJECT_NAME}_configurers
  src/lib/configurers/configurers_utils.cpp
  src/lib/configurers/replacer_configurer.cpp
  src/lib/configurers/teams_configurer.cpp
  src/lib/configurers/vision_configurer.cpp
)

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context

add_executable(multi_sender_example
  examples/udp/multicast_sender_example.cpp
)

add_executable(multi_receiver_example
  examples/udp/multicast_receiver_example.cpp
)

add_executable(multi_receiver_reset_example
  examples/udp/multicast_receiver_reset_example.cpp
)

add_executable(uni_receiver_example
examples/udp/unicast_receiver_example.cpp
)

add_executable(uni_sender_example
examples/udp/unicast_sender_example.cpp
)

add_executable(vision_sender_example
  examples/protobuf/vision_sender_example.cpp
)

add_executable(vision_receiver_example
  examples/protobuf/vision_receiver_example.cpp
)

add_executable(team_receiver_example
  examples/protobuf/team_receiver_example.cpp
)

add_executable(replacer_receiver_example
  examples/protobuf/replacer_receiver_example.cpp
)

add_executable(replacer_configurer_example
  examples/configurers/replacer_configurer_example.cpp
)

add_executable(teams_configurer_example
  examples/configurers/teams_configurer_example.cpp
)

add_executable(vision_configurer_example
  examples/configurers/vision_configurer_example.cpp
)

add_executable(vision_adapter
  src/bin/vision_adapter.cpp
)

add_executable(teams_adapter
  src/bin/teams_adapter.cpp
)

add_executable(replacer_adapter
  src/bin/replacer_adapter.cpp
)

## Add cmake target dependencies of the executables
## same as for the libraries above

add_dependencies(${PROJECT_NAME}_configurers ${PROJECT_NAME}_gencfg)

## Specify libraries to link a library or executable target against

target_link_libraries(${PROJECT_NAME}_udp_comm
  ${Boost_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME}_protobuf_comm
  ${PROJECT_NAME}_udp_comm
  ${PROJECT_NAME}_core
  pb_msgs_lib
)

target_link_libraries(${PROJECT_NAME}_ros
  ${PROJECT_NAME}_core
)

target_link_libraries(multi_sender_example
  ${PROJECT_NAME}_udp_comm
  ${catkin_LIBRARIES}
)

target_link_libraries(multi_receiver_example
  ${PROJECT_NAME}_udp_comm
  ${catkin_LIBRARIES}
)

target_link_libraries(multi_receiver_reset_example
  ${PROJECT_NAME}_udp_comm
  ${catkin_LIBRARIES}
)

target_link_libraries(uni_receiver_example
  ${PROJECT_NAME}_udp_comm
  ${catkin_LIBRARIES}
)

target_link_libraries(uni_sender_example
  ${PROJECT_NAME}_udp_comm
  ${catkin_LIBRARIES}
)

target_link_libraries(vision_sender_example
  ${PROJECT_NAME}_protobuf_comm
  ${catkin_LIBRARIES}
)

target_link_libraries(vision_receiver_example
  ${PROJECT_NAME}_protobuf_comm
  ${catkin_LIBRARIES}
)

target_link_libraries(team_receiver_example
  ${PROJECT_NAME}_protobuf_comm
  ${catkin_LIBRARIES}
)

target_link_libraries(replacer_receiver_example
  ${PROJECT_NAME}_protobuf_comm
  ${catkin_LIBRARIES}
)

target_link_libraries(replacer_configurer_example
  ${PROJECT_NAME}_configurers
  ${catkin_LIBRARIES}
)

target_link_libraries(teams_configurer_example
  ${PROJECT_NAME}_configurers
  ${catkin_LIBRARIES}
)

target_link_libraries(vision_configurer_example
  ${PROJECT_NAME}_configurers
  ${catkin_LIBRARIES}
)

target_link_libraries(vision_adapter
  ${PROJECT_NAME}_ros
  ${PROJECT_NAME}_protobuf_comm
  ${PROJECT_NAME}_configurers
  ${catkin_LIBRARIES}
)

target_link_libraries(teams_adapter
  ${PROJECT_NAME}_ros
  ${PROJECT_NAME}_protobuf_comm
  ${PROJECT_NAME}_configurers
  ${catkin_LIBRARIES}
)

target_link_libraries(replacer_adapter
  ${PROJECT_NAME}_ros
  ${PROJECT_NAME}_protobuf_comm
  ${PROJECT_NAME}_configurers
  ${catkin_LIBRARIES}
)

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executables for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_executables.html

install(TARGETS vision_adapter
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_vision_adapter.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME} ${catkin_LIBRARIES})
# endif()

if(CATKIN_ENABLE_TESTING)
  find_package(rostest REQUIRED)

  add_executable(gazebo_services.mock
    test/mocks/bin/gazebo_services.mock.cpp
  )

  catkin_add_gtest(ros_side_converter.test
    src/lib/data/converter/test/ros_side.test.cpp
  )

  catkin_add_gtest(configurers_utils.test
    src/lib/configurers/test/configurers_utils.test.cpp
  )

  add_rostest_gtest(vision_adapter.test
    test/vision_adapter.test
    src/bin/test/vision_adapter.test.cpp
  )

  add_rostest_gtest(replacer_sender.test
    test/replacer_sender.test
    src/lib/ros/test/replacer_sender.test.cpp
  )

  target_link_libraries(gazebo_services.mock
    ${PROJECT_NAME}_core
    ${PROJECT_NAME}_ros
    ${catkin_LIBRARIES}
  )

  target_link_libraries(ros_side_converter.test
    ${PROJECT_NAME}_core
    ${PROJECT_NAME}_ros
    ${catkin_LIBRARIES}
  )

  target_link_libraries(configurers_utils.test
    ${PROJECT_NAME}_configurers
    ${catkin_LIBRARIES}
  )

  target_link_libraries(vision_adapter.test
    ${PROJECT_NAME}_core
    ${PROJECT_NAME}_ros
    ${PROJECT_NAME}_protobuf_comm
    ${catkin_LIBRARIES}
  )

  target_link_libraries(replacer_sender.test
    ${PROJECT_NAME}_core
    ${PROJECT_NAME}_ros
    ${PROJECT_NAME}_protobuf_comm
    ${catkin_LIBRARIES}
  )

endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
