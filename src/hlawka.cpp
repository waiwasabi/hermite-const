#include "hlawka.hpp"

using namespace NTL;

namespace Hlawka {
/**
 * @brief Initialize a "zero" vector in U(p)
 */
void U(Vec<ZZ> &a, int N) {
    a.SetLength(N);
    a[0] = 1;
}

void U_max(Vec<ZZ> &a, int p, int N) {
    a.SetLength(N);
    a[0] = 1;
    for (int i = 1; i < N; i++) {
        a[i] = p;
    }
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
 * @brief Generate a random vector in U(p)
 */
Vec<ZZ> random_U(int N, int b, int m) {
    Vec<ZZ> res;
    Hlawka::U(res, N);
    for (int i = 1; i < N; i++) {
        res[i] = RandomBnd(m-b) + b;
    }
    return res;
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
 * @brief Compute the Minkowski lower bound for a shortest lattice vector given N
 */
double minkowski(int N) {
    return std::pow(2 * std::tgamma(N / 2. + 1) / std::pow(M_PI, N / 2.), 1. / N);
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
        if (a[i] < a[i - 1]) {
            a[i]++;
            return;
        }
        a[i] = 0;
    }
    a[1]++;
}

/**
 * @brief Increment a vector in the symmetric subdivision of U(p) within a radius along the diagonal
 */
void sym_diag_incr(Vec<ZZ> &a, int, int N, double r) {
    for (int i = N - 1; i > 1; i--) {
        if (a[i] < a[i - 1]) {
            a[i]++;
            return;
        }
        a[i] = max(0, (int)((1 - r) * conv<int>(a[i - 1])));
    }
    a[1]++;
}

/**
 * @brief Decrement a vector in the symmetric subdivision of U(p) within a radius along the diagonal
 */
void sym_diag_decr(Vec<ZZ> &a, int, int N, double r) {
    for (int i = N - 1; i > 1; i--) {
        if (a[i] > ((1 - r) * conv<int>(a[i - 1]))) {
            a[i]--;
            return;
        }
        a[i] = max(0, conv<int>(a[i - 1] - 1));
    }
    a[1]--;
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
        a[i] = max(0, conv<int>(c[i] - r));
    }
    a[1]++;
}
}  // namespace Hlawka