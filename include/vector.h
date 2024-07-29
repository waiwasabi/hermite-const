#pragma once
#include <NTL/ZZ.h>
#include <NTL/vector.h>

using namespace NTL;

// function prototypes
double norm(Vec<ZZ> a);
Vec<RR> arr_to_vec(double *arr, int N);
