CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(VectorSum)

FIND_PACKAGE(CUDA REQUIRED)
if (NOT CUDA_FOUND)
message(STATUS "CUDA not found. Project will not be built.")
endif(NOT CUDA_FOUND)

CUDA_ADD_EXECUTABLE(VectorSum
    main.cu vectorSum.cu)
