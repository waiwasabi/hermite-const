#include <hlawka.h>

/**
 * @brief Compute the norm of a vector
 */
double norm(Vec<ZZ> a) {
  double res = 0;
  for (int i = 0; i < a.length(); i++) {
    res += conv<int>(a[i] * a[i]);
  }
  return sqrt(res);
}
