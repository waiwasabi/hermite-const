#pragma once
#include <NTL/ZZ.h>
#include <NTL/mat_ZZ.h>
#include <NTL/vector.h>

// function prototypes
namespace Hlawka {
// increment patterns
void incr(NTL::Vec<NTL::ZZ> &a, int p, int N);
void sym_incr(NTL::Vec<NTL::ZZ> &a, int p, int N);
void center_incr(NTL::Vec<NTL::ZZ> &a, int p, NTL::Vec<NTL::ZZ> &center, NTL::ZZ &r, int N);

// initialize vector/matrix
void U(NTL::Vec<NTL::ZZ> &a, int N);
void U_center(NTL::Vec<NTL::ZZ> &a, NTL::Vec<NTL::ZZ> &c, NTL::ZZ r, int N);
void B(NTL::Mat<NTL::ZZ> &B, int p, NTL::Vec<NTL::ZZ> a, int N);
double q(int p, int N);
}  // namespace Hlawka