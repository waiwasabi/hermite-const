#pragma once
#include <NTL/RR.h>
#include <NTL/ZZ.h>
#include <NTL/vector.h>

// function prototypes
double norm(NTL::Vec<NTL::ZZ> a);
NTL::Vec<NTL::RR> arr_to_vec(double *arr, int N);
