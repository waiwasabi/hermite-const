#pragma once
#include <NTL/RR.h>
#include <NTL/ZZ.h>
#include <NTL/vector.h>

namespace svp_algorithm {
using svp_alg = double (*)(int, NTL::Vec<NTL::ZZ> &, int);
double lll_svp(int p, NTL::Vec<NTL::ZZ> &a, int N);
double exact_svp(int p, NTL::Vec<NTL::ZZ> &a, int N);
void svp_all(svp_alg f, int p, int N, std::ofstream &file);
void svp_sym(svp_alg f, int p, int N, std::ofstream &file);
void svp_symc(svp_alg f, int p, int N, NTL::Vec<NTL::RR> &center, NTL::RR radius, std::ofstream &file);
}  // namespace svp_algorithm
