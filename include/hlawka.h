#pragma once
#include <NTL/mat_ZZ.h>

using namespace NTL;

// function prototypes
namespace Hlawka {

// increment patterns
void incr(Vec<ZZ> &a, int p, int N);
void sym_incr(Vec<ZZ> &a, int p, int N);
void symc_incr(Vec<ZZ> &a, int p, Vec<ZZ> &center, ZZ &r, int N);

// initialize vector/matrix
void U(Vec<ZZ> &a, int N);
void U_center(Vec<ZZ> &a, Vec<ZZ> &c, ZZ r, int N);
void B(Mat<ZZ> &B, int p, Vec<ZZ> a, int N);
double q(int p, int N);
}  // namespace Hlawka