# Ref: https://www.cyberbotics.com/doc/guide/using-your-ide?version=released&tab-language=c++#cmake

cmake_minimum_required(VERSION 3.22)

project(referee_controller CXX)

add_subdirectory(adapters)

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
    adapters/include
)

add_executable(referee_controller
    referee_controller.cpp
    src/Robot.cpp
)

target_link_directories(referee_controller PUBLIC
    $ENV{WEBOTS_HOME}/lib/controller
)

target_link_libraries(referee_controller
    ${LIBRARIES}
    travesim_adapters_protobuf_comm
    pb_msgs_lib
)

# Copy the target executable at the right location.
add_custom_command(TARGET referee_controller POST_BUILD COMMAND ${CMAKE_COMMAND} -E
  copy ${CMAKE_BINARY_DIR}/referee_controller ${CMAKE_SOURCE_DIR}
)