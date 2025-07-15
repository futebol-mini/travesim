# Ref: https://www.cyberbotics.com/doc/guide/using-your-ide?version=released&tab-language=c++#cmake

cmake_minimum_required(VERSION 3.22)

project(vss_robot_controller CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

if(NOT DEFINED ENV{WEBOTS_HOME})
  if(WIN32)
    set(ENV{WEBOTS_HOME} "C:\\Program Files\\Webots")
  else()
    set(ENV{WEBOTS_HOME} "/usr/local/webots")
  endif()
endif()

if(WIN32)
  link_directories($ENV{WEBOTS_HOME}/msys64/mingw64/bin)
else()
  link_directories($ENV{WEBOTS_HOME}/lib)
endif()

set(LIBRARIES
    ${CMAKE_SHARED_LIBRARY_PREFIX}Controller${CMAKE_SHARED_LIBRARY_SUFFIX}
    ${CMAKE_SHARED_LIBRARY_PREFIX}CppController${CMAKE_SHARED_LIBRARY_SUFFIX}
)

include_directories(
    $ENV{WEBOTS_HOME}/include/controller/c
    $ENV{WEBOTS_HOME}/include/controller/cpp

    include
    ../common/include
)

add_executable(vss_robot_controller
    vss_robot_controller.cpp
)

target_link_directories(vss_robot_controller PUBLIC
    $ENV{WEBOTS_HOME}/lib/controller
)

target_link_libraries(vss_robot_controller
    ${LIBRARIES}
)

# Copy the target executable at the right location.
add_custom_command(TARGET vss_robot_controller POST_BUILD COMMAND ${CMAKE_COMMAND} -E
  copy ${CMAKE_BINARY_DIR}/vss_robot_controller ${CMAKE_SOURCE_DIR}
)

###############################################################################
# Test files
###############################################################################

# add_executable(command_sender
#   test/command_sender.test.cpp
# )

# target_link_libraries(command_sender
#   travesim_adapters_protobuf_comm
#   pb_msgs_lib
# )
