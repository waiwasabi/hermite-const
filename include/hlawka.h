#pragma once
#include <NTL/mat_ZZ.h>

using namespace NTL;


// function prototypes
namespace hlawka {
void increment(Vec<ZZ> &a, int p, int N);
void symmetric_increment(Vec<ZZ> &a, int p, int N);
void U(Vec<ZZ> &a, int N);
void B(Mat<ZZ> &B, int p, Vec<ZZ> a, int N);
double q(int p, int N);
}  // namespace hlawka