#include "vectorSum.cuh"
#include <iostream>
#include <cmath>
#include <assert.h>
#include <cuda_runtime.h>

using namespace std;

int main(int argc, char** argv) {
  const uint per_block_thread_count = 1024;
  const uint max_block_count = 65535;

  const uint array_size = (uint)1e7;

  float* a = new float[array_size];
  float* b = new float[array_size];
  float* c = new float[array_size];
  float* time = new float;

  for(uint i = 0;i < array_size; i++) {
    a[i] = i;
    b[i] = array_size - i;
  }

  float* dev_a;
  float* dev_b;
  float* dev_c;
  cudaMalloc((void**) &dev_a, array_size * sizeof(float));
  cudaMalloc((void**) &dev_b, array_size * sizeof(float));
  cudaMalloc((void**) &dev_c, array_size * sizeof(float));

  cudaMemcpy(dev_a, a, array_size * sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(dev_b, b, array_size * sizeof(float), cudaMemcpyHostToDevice);

  uint block_count = min(max_block_count, (uint) ceil(array_size / (float) per_block_thread_count));
  cudaCallAddVectorKernel(block_count,
                          per_block_thread_count,
                          dev_a,
                          dev_b,
                          dev_c,
                          array_size,
                          time);

  cudaMemcpy(c, dev_c, array_size * sizeof(float), cudaMemcpyDeviceToHost);

  for(uint i = 0; i < array_size; i++) {
    assert(c[i] == array_size);
  }
  cout << "GPU runtime: " << *time << " ms" << endl;
  cout << "program check complete. (PASS)" << endl;

  delete[] a;
  delete[] b;
  delete[] c;
  delete time;
  cudaFree(dev_a);
  cudaFree(dev_b);
  cudaFree(dev_c);

  return 0;
}