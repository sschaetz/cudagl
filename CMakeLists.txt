cmake_minimum_required(VERSION 2.8)
find_package(Qt4 REQUIRED)
find_package(CUDA)

SET(CMAKE_CXX_FLAGS "-O3 -Wall -msse3 -g")
SET(CUDA_NVCC_FLAGS "-O3")

include_directories(${QT_INCLUDE_DIR})
include_directories(${QT_QTOPENGL_INCLUDE_DIR})
include_directories(${QT_QTGUI_INCLUDE_DIR})
include_directories(${QT_QTCORE_INCLUDE_DIR})
include_directories(/usr/local/cuda/sdk/C/common/inc)
link_directories(/usr/local/cuda/sdk/C/common/lib/linux)

qt4_wrap_cpp (CUDAGL_QT4_MOCFILES cudagl_widget.hpp)

CUDA_ADD_EXECUTABLE(cgl main.cpp cudagl_widget.cpp kernel.cu ${CUDAGL_QT4_MOCFILES})

target_link_libraries(cgl GLEW_x86_64)
target_link_libraries(cgl GLU)
target_link_libraries(cgl ${QT_QTGUI_LIBRARY})
target_link_libraries(cgl ${QT_QTOPENGL_LIBRARY})
