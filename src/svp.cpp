#include <NTL/LLL.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include "hlawka.h"
#include "vector.h"

void EXACT_LLL(Mat<ZZ> &B, int) {
  ZZ det2;
  LLL(det2, B, 99, 100);
}

void KZ(Mat<ZZ> &B, int N) { BKZ_FP(B, 0.99, N); }

/**
 * @brief Compute the length of the shortest vector
 * in the R-reduced basis of B(p, a)
 *
 * @param p a non-negative integer
 * @param a a vector of type NTL::Vec<NTL::ZZ>
 * @param R a pointer to a function that performs a lattice basis reduction
 * @param N the dimension of the lattice
 */
double svp(int p, Vec<ZZ> &a, void (*R)(Mat<ZZ> &, int), int N) {
  Mat<ZZ> B;
  hlawka::B(B, p, a, N);
  R(B, N);
  return norm(B[0]);
}

/**
 * @brief Compute the length of the shortest vector in the
 * LLL-reduced basis of B(p, a)
 *
 * @param p a non-negative integer
 * @param a a vector of type NTL::Vec<NTL::ZZ>
 * @param N the dimension of the lattice
 */
double lll_svp(int p, Vec<ZZ> &a, int N) { return svp(p, a, EXACT_LLL, N); }

/**
 * @brief Compute the length of the shortest vector in the
 * KZ-reduced basis of B(p, a)
 *
 * @param p a non-negative integer
 * @param a a vector of type NTL::Vec<NTL::ZZ>
 * @param N the dimension of the lattice
 */
double exact_svp(int p, Vec<ZZ> &a, int N) { return svp(p, a, KZ, N); }

/**
 * @brief Compute svp(p, a) for each a in U(p)
 *
 * @param p a non-negative integer
 * @param svp a pointer to a function that computes svp(p, a)
 * @param N the dimension of the lattice
 */
void svp_all(int p, double (*svp)(int, Vec<ZZ> &, int), int N,
             std::ofstream &) {
  Vec<ZZ> a;
  hlawka::U(a, N);

  for (int i = 0; i < pow(p, N - 1); i++) {
    svp(p, a, N);
    hlawka::increment(a, p, N);
  }
}

/**
 * @brief Compute svp(p, a) for each a in a symmetric s U(p)
 *
 * @param p a non-negative integer
 * @param svp a pointer to a function that computes svp(p, a)
 * @param N the dimension of the lattice
 * @param file a reference to an output file stream
 */
void svp_symmetric(int p, double (*svp)(int, Vec<ZZ> &, int), int N,
                   std::ofstream &file) {
  int b = p / 4;
  Vec<ZZ> a;
  hlawka::U(a, N);

  double m = -1;
  std::vector<Vec<ZZ>> v;

  while (a[1] < b) {
    double l = svp(p, a, N);
    if (l > m) {
      m = l;
      v.clear();
    }
    if (l >= m) {
      v.push_back(a);
    }
    hlawka::symmetric_increment(a, p, N);
  }

  file << p << ' ' << m / hlawka::q(p, N) << ' ';
  for (auto &i : v) {
    file << i << ' ';
  }
  file << std::endl;
}
