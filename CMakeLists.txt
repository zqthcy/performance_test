cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME performance_test)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(LIBPROCESS ./3rdparty/libprocess)

include_directories(${LIBPROCESS}/include)
include_directories(${LIBPROCESS}/../picojson-1.3.0)
include_directories(${LIBPROCESS}/../boost-1.53.0)
include_directories(${LIBPROCESS}/../libev-4.22)
include_directories(${LIBPROCESS}/../glog-0.3.3/src)
include_directories(${LIBPROCESS}/../protobuf-2.6.1)

link_directories(${LIBPROCESS}/.libs)
link_directories(${LIBPROCESS}/../glog-0.3.3/.libs)
link_directories(${LIBPROCESS}/../libev-4.22/.libs)

aux_source_directory(./src SOURCE_FILES)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} -lprocess -lglog -lz -lev)
