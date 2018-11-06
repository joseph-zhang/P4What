cmake_minimum_required(VERSION 2.8)
project( Harris )
MESSAGE( STATUS "------------------" ${OpenCV_INCLUDE_DIRS} )
find_package( OpenCV REQUIRED )

add_definitions(
  -std=c++11)

add_executable( Harris
  harris.cpp
  main.cpp)

target_include_directories( Harris
  PRIVATE .
  ${OpenCV_INCLUDE_DIRS})

target_link_libraries( Harris
  ${OpenCV_LIBS})
