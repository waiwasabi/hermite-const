#include <NTL/LLL.h>

#include "hlawka.h"
#include "vector.h"

/**
 * @brief Compute the length of the shortest vector
 * in the LLL-reduced basis of B(p, a)
 */
double svp(int p, Vec<ZZ> a, double delta = 0.99) {
  Mat<ZZ> B;
  hlawka::B(B, p, a);
  ZZ det2;
  LLL(det2, B, 99, 100);
  return norm(B[0]);
}

/**
 * @brief Compute svp(p, a) for each a in U(p)
 */
void svp_all(int p, double delta = 0.99) {
  Vec<ZZ> a;
  hlawka::U(a);

  for (int i = 0; i < pow(p, N - 1); i++) {
    svp(p, a, delta);
    hlawka::increment(a, p);
  }
}

/**
 *
 */
void svp_symmetric(int p, double delta = 0.99) {
  int b = p / 2;
  Vec<ZZ> a;
  hlawka::U(a);

  double m = 0;

  for (int i = 0; i < pow(b, N - 1); i++) {

    m = std::max(m, svp(p, a, delta));

    hlawka::increment(a, b);
  }

  std::cout << m / hlawka::q(p) << std::endl;
}
