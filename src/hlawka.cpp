#include "hlawka.hpp"

using namespace NTL;

namespace Hlawka {
/**
 * @brief Initialize a vector in U(p)
 */
void U(Vec<ZZ> &a, int N) {
    a.SetLength(N);
    a[0] = 1;
}

/**
 * @brief Initialize a vector in U(p) centered at c with radius r
 */
void U_center(Vec<ZZ> &a, Vec<ZZ> &c, ZZ r, int N) {
    U(a, N);
    for (int i = 1; i < N; i++) {
        a[i] = c[i] - r;
    }
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
double q(int p, int N) {
    return pow(p, (N - 1.) / N);
}

/**
 * @brief Increment a vector in U(p)
 */
void incr(Vec<ZZ> &a, int p, int N) {
    for (int i = N - 1; i >= 0; i--) {
        if (a[i] < p - 1) {
            a[i]++;
            return;
        }
        a[i] = 0;
    }
}

/**
 * @brief Increment a vector in the symmetric subdivision of U(p)
 */
void sym_incr(Vec<ZZ> &a, int, int N) {
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
 * @brief Increment a vector in the symmetric subdivision of U(p) within the
 * hypercube centered at c with radius r
 */
void center_incr(Vec<ZZ> &a, int, Vec<ZZ> &c, ZZ &r, int N) {
    for (int i = N - 1; i > 1; i--) {
        if (a[i] < a[i - 1] - 1 && a[i] < c[i] + r) {
            a[i]++;
            return;
        }
        a[i] = c[i] - r;
    }
    a[1]++;
}
}  // namespace Hlawka