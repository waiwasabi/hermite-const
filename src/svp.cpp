#include <NTL/LLL.h>

#include <filesystem>
#include <fstream>
#include <iostream>

#include "hlawka.h"
#include "vector.h"

void EXACT_LLL(Mat<ZZ> &B) {
  ZZ det2;
  LLL(det2, B, 99, 100);
}

void KZ(Mat<ZZ> &B) { BKZ_FP(B, 0.99, N); }

/**
 * @brief Compute the length of the shortest vector
 * in the R-reduced basis of B(p, a)
 *
 * @param p a non-negative integer
 * @param a a vector of type NTL::Vec<NTL::ZZ>
 * @param R a pointer to a function that performs a lattice basis reduction
 */
double svp(int p, Vec<ZZ> &a, void (*R)(Mat<ZZ> &)) {
  Mat<ZZ> B;
  hlawka::B(B, p, a);
  R(B);
  return norm(B[0]);
}

/**
 * @brief Compute the length of the shortest vector in the
 * LLL-reduced basis of B(p, a)
 *
 * @param p a non-negative integer
 * @param a a vector of type NTL::Vec<NTL::ZZ>
 */
double lll_svp(int p, Vec<ZZ> &a) { return svp(p, a, EXACT_LLL); }

/**
 * @brief Compute the length of the shortest vector in the
 * KZ-reduced basis of B(p, a)
 *
 * @param p a non-negative integer
 * @param a a vector of type NTL::Vec<NTL::ZZ>
 */
double exact_svp(int p, Vec<ZZ> &a) { return svp(p, a, KZ); }

/**
 * @brief Compute svp(p, a) for each a in U(p)
 * and save results to a file
 *
 * @param p a non-negative integer
 * @param svp a pointer to a function that computes svp(p, a)
 * @param file a reference to an output file stream
 */
void svp_all(int p, double (*svp)(int, Vec<ZZ> &), std::ofstream &file) {
  Vec<ZZ> a;
  hlawka::U(a);

  for (int i = 0; i < pow(p, N - 1); i++) {
    file << svp(p, a) << " ";
    hlawka::increment(a, p);
  }
}

/**
 *
 */
void svp_symmetric(int p, double (*svp)(int, Vec<ZZ> &), std::ofstream &file) {
  int b = p / 2;
  Vec<ZZ> a;
  hlawka::U(a);

  for (int i = 0; i < pow(b, N - 1); i++) {
    file << svp(p, a) << " ";
    hlawka::increment(a, b);
  }
}
