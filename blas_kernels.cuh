#pragma once
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

extern "C" void fill_gpu(int N, float ALPHA, float * X, int INCX);



