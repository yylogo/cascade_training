cmake_minimum_required(VERSION 2.8)

find_package( OpenCV REQUIRED )

#SET(CMAKE_BUILD_TYPE "Debug")
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")

project( DisplayImage )

add_executable( train train.cpp )
add_executable( recognize recognize.cpp )
add_executable( edit edit.cpp sub_str.cpp sub_str.h)
add_executable( recognize_lbp recognize_lbp.cpp )

target_link_libraries( train ${OpenCV_LIBS} )
target_link_libraries( recognize ${OpenCV_LIBS} )
target_link_libraries( recognize_lbp ${OpenCV_LIBS} )
target_link_libraries( edit ${OpenCV_LIBS} )

