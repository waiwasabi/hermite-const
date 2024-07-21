#include "hlawka.h"

namespace hlawka {
/**
 * @brief Initialize a vector in U(p)
 */
void U(Vec<ZZ> &a, int N) {
  a.SetLength(N);
  a[0] = 1;
}

void increment(Vec<ZZ> &a, int p, int N) {
  for (int i = N - 1; i >= 0; i--) {
    if (a[i] < p - 1) {
      a[i]++;
      return;
    }
    a[i] = 0;
  }
}

void symmetric_increment(Vec<ZZ> &a, int p, int N) {
  for (int i = N - 1; i > 1; i--) {
    if (a[i] < a[i - 1] - 1) {
      a[i]++;
      return;
    }
    a[i] = 0;
  }
  a[1]++;
}

/**
 * @brief Initialize the lattice basis B(p, a)
 */
void B(Mat<ZZ> &B, int p, Vec<ZZ> a, int N) {
  B = ident_mat_ZZ(N) * p;
  B[0] = a;
}

/**
 * @brief Compute q given p
 */
double q(int p, int N) { return pow(p, (N - 1.) / N); }
}  // namespace hlawka
