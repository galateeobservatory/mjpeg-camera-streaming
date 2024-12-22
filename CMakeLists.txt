cmake_minimum_required(VERSION 2.8)
project(MJPeg)
set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
include_directories("/usr/include/opencv4/", "/usr/include/libcamera/")
add_executable(MJPeg main.cpp MJPEGWriter.cpp
        libcamera_app_options.cpp
        libcamera_app.cpp
        lccv.cpp
        libcamera_app_options.h
        libcamera_app.h
        lccv.h)
target_link_libraries(MJPeg -lpthread -lopencv_core -lopencv_videoio -lopencv_imgcodecs -lcamera -lcamera-base)