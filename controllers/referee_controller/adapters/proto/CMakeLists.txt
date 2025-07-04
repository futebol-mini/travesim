cmake_minimum_required(VERSION 3.6.1)

include(FindProtobuf)

find_package(Protobuf REQUIRED)

include_directories(${Protobuf_INCLUDE_DIRS})

# Generate source and header files for each .proto file
set(PROTO_MSGS
  referee/vssref_command
  referee/vssref_common
  referee/vssref_placement
  simulation/command
  simulation/common
  simulation/packet
  simulation/replacement
)

foreach(msg ${PROTO_MSGS})
  protobuf_generate_cpp(${msg}_PROTO_SRCS ${msg}_PROTO_HDRS ${msg}.proto)
  list(APPEND PB_PROTOCOL_SOURCES ${${msg}_PROTO_SRCS})
  list(APPEND PB_PROTOCOL_HEADERS ${${msg}_PROTO_HDRS})
endforeach()

set_source_files_properties(
  ${PB_PROTOCOL_SOURCES}
  ${PB_PROTOCOL_HEADERS}
  PROPERTIES GENERATED TRUE
)

# Create library
set(LIB_NAME pb_msgs_lib)

add_library(${LIB_NAME}
  ${PB_PROTOCOL_HEADERS}
  ${PB_PROTOCOL_SOURCES}
)

target_link_libraries(${LIB_NAME}
  ${Protobuf_LIBRARIES}
)

target_include_directories(${LIB_NAME}
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  PRIVATE
    ${Protobuf_INCLUDE_DIRS}
)
