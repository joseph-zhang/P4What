#include "vectorSum.cuh"

__global__
void cudaAddVectorKernel(const float *a,
                         const float* b,
                         float* c,
                         const uint size) {
  uint thread_idx = blockIdx.x * blockDim.x + threadIdx.x;
  while (thread_idx < size) {
    c[thread_idx] = a[thread_idx] + b[thread_idx];
    thread_idx += blockDim.x * gridDim.x;
  }
}

void cudaCallAddVectorKernel(const uint block_count,
                             const uint per_block_thread_count,
                             const float* a,
                             const float* b,
                             float* c,
                             const uint size,
                             float* time) {
  cudaEvent_t start, stop;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);
  cudaEventRecord(start, 0);

  cudaAddVectorKernel<<<block_count, per_block_thread_count>>>(a, b, c, size);

  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);
  float elapsedTime;
  cudaEventElapsedTime(&elapsedTime, start, stop);
  cudaEventDestroy(start);
  cudaEventDestroy(stop);
  *time =  elapsedTime;
}