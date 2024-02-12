add_library(inference STATIC inference.cpp)


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

target_link_libraries(inference ${OpenCV_LIBS})

target_include_directories(inference PUBLIC "./")