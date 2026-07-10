cmake_minimum_required(VERSION 3.10)
project(OpenCVLearning)
set(CMAKE_CXX_STANDARD 17)

set(OpenCV_DIR /opt/homebrew/lib/cmake/opencv4)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# add_executable(day1 day1_load_display.cpp)
# target_link_libraries(day1 ${OpenCV_LIBS})

# # add_executable(day2 day2_resize_crop.cpp)
# # target_link_libraries(day2 ${OpenCV_LIBS})

# add_executable(day3 day3_colors.cpp)
# target_link_libraries(day3 ${OpenCV_LIBS})

add_executable(day4 day4_practice.cpp)
target_link_libraries(day4 ${OpenCV_LIBS})
