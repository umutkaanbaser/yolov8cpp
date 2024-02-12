cmake_minimum_required(VERSION 3.5)

project(yolo_cpp VERSION 0.0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# CUDA
set(CUDA_TOOLKIT_ROOT_DIR "/usr/local/cuda")
find_package(CUDA 11 REQUIRED)

set(CMAKE_CUDA_STANDARD 11)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
# !CUDA

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
# !OpenCV

add_subdirectory(include)


add_executable(yolo_cpp main.cpp)
target_link_libraries(yolo_cpp  ${OpenCV_LIBS} inference)

