
#ifndef CUDA_UTILS_H
#define CUDA_UTILS_H

#include <driver_types.h>
#include <stdio.h>

#define gpuErrchk(ans)                                                                                                                                                                                 \
  { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort = true) {
  if (code != cudaSuccess) {
    fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line); // TODO: C++ version!
    if (abort)
      exit(code);
  }
}

#endif