#ifndef CUDA_VECSUM
#define CUDA_VECSUM

#include <iostream>
#include <cuda_runtime.h>

#ifdef __CUDACC__
#define CUDA_CALLABLE __host__ __device__
#else
#define CUDA_CALLABLE
#endif

extern "C"

void cudaCallAddVectorKernel(const uint block_count,
                             const uint per_block_thread_count,
                             const float* a,
                             const float* b,
                             float* c,
                             const uint size,
                             float* time);

#endif