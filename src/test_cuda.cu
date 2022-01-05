#include "test_cuda.hpp"
#include "cuda_utils.hpp"
#include <iostream>
using namespace std;

const int N = 32;

__global__ void root(float *c) {
  //   c[threadIdx.x + blockDim.x * blockIdx.x] =
  //       sqrt(c[threadIdx.x + blockDim.x * blockIdx.x]);
  c[threadIdx.x] = 0;
}

void print_tab(float *M, int N) {
  std::cout << "Print Tab" << std::endl << std::endl;
  for (int i = 0; i < N; i++) {
    std::cout << M[i] << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;
}

void testCuda() {
  float *c = new float[N];
  float *r = new float[N];
  int cudaCount;
  float *d_c;

  for (int i = 0; i < N; i++) {
    c[i] = i;
  }

  cudaDeviceProp prop;

  gpuErrchk(cudaGetDeviceCount(&cudaCount));
  cout << "Cuda count: " << cudaCount << endl;

  gpuErrchk(cudaSetDevice(0));
  gpuErrchk(cudaGetDeviceProperties(&prop, 0));

  cout << "maxThreadsPerBlock " << prop.maxThreadsPerBlock << endl;
  cout << "maxGridSize " << prop.maxGridSize[0] << " " << prop.maxGridSize[1] << " " << prop.maxGridSize[2] << endl;

  cout << "total glob mem: " << prop.totalGlobalMem << endl;
  cout << "name: " << prop.name << endl;

  print_tab(c, N);

  gpuErrchk(cudaMalloc(&d_c, N * sizeof(float)));
  gpuErrchk(cudaMemcpy(d_c, c, N * sizeof(float), cudaMemcpyHostToDevice));

  //   float theTime = 1;
  //   cudaEvent_t myEvent;
  //   cudaEvent_t laterEvent;
  //   cudaEventCreate(&myEvent);
  //   cudaEventCreate(&laterEvent);
  //   cudaEventRecord(myEvent, 0);
  //   cudaEventSynchronize(myEvent);
  root<<<1, 16>>>(d_c);
gpuErrchk( cudaPeekAtLastError() );
gpuErrchk( cudaDeviceSynchronize() );

  //   cudaEventRecord(laterEvent, 0);
  //   cudaEventElapsedTime(&theTime, myEvent, laterEvent);
  //   std::cout << theTime << std::endl;

  gpuErrchk(cudaMemcpy(r, d_c, N * sizeof(float), cudaMemcpyDeviceToHost));

  print_tab(c, N);
  print_tab(r, N);

  gpuErrchk(cudaFree(d_c));
}
