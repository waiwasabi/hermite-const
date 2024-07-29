#include <NTL/LLL.h>

#include <deque>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "hlawka.h"
#include "vector.h"

void EXACT_LLL(Mat<ZZ> &B, int) {
    ZZ det2;
    LLL(det2, B, 99, 100);
}

void KZ(Mat<ZZ> &B, int N) {
    BKZ_FP(B, 0.99, N);
}

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
    Hlawka::B(B, p, a, N);
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
double lll_svp(int p, Vec<ZZ> &a, int N) {
    return svp(p, a, EXACT_LLL, N);
}

/**
 * @brief Compute the length of the shortest vector in the
 * KZ-reduced basis of B(p, a)
 *
 * @param p a non-negative integer
 * @param a a vector of type NTL::Vec<NTL::ZZ>
 * @param N the dimension of the lattice
 */
double exact_svp(int p, Vec<ZZ> &a, int N) {
    return svp(p, a, KZ, N);
}

/**
 * @brief Helper function to update the maximum value of svp(p, a)
 */
void update(double &l, double &m, std::deque<Vec<ZZ>> &v, Vec<ZZ> &a) {
    if (l > m) {
        m = l;
        v.clear();
    }
    if (l >= m) {
        v.push_back(a);
    }
}

void merge(std::deque<Vec<ZZ>> &v, std::deque<Vec<ZZ>> &vp, double &m, double &mp) {
    if (mp > m) {
        m = mp;
        v = vp;
    } else if (mp == m) {
        v.insert(v.end(), vp.begin(), vp.end());
    }
}

void write(std::ofstream &file, int p, double m, std::deque<Vec<ZZ>> &v, int N) {
    file << p << ',' << m / Hlawka::q(p, N);
    for (auto &i : v) {
        file << ',' << i;
    }
    file << std::endl;
}

/**
 * @brief Compute svp(p, a) for each a in U(p)
 *
 * @param p a non-negative integer
 * @param svp a pointer to a function that computes svp(p, a)
 * @param N the dimension of the lattice
 */
void svp_all(int p, double (*svp)(int, Vec<ZZ> &, int), int N, std::ofstream &) {
    Vec<ZZ> a;
    Hlawka::U(a, N);

    for (int i = 0; i < pow(p, N - 1); i++) {
        svp(p, a, N);
        Hlawka::incr(a, p, N);
    }
}

/**
 * @brief Parallel computation svp(p, a) for each a in a
 * symmetric subdivision of U(p)
 *
 * @param p a non-negative integer
 * @param svp a pointer to a function that computes svp(p, a)
 * @param N the dimension of the lattice
 * @param file a reference to an output file stream
 */
void svp_sym(int p, double (*svp)(int, Vec<ZZ> &, int), int N, std::ofstream &file) {
    int b = p / 4;
    Vec<ZZ> a;        // shared counter
    Hlawka::U(a, N);  // initialize a to the first element of U(p)

    double m = -1;          // maximum value of svp(p, a)
    std::deque<Vec<ZZ>> v;  // vectors that achieve the maximum value of svp(p, a)

    int sstop = 0;  // shared stop condition
#pragma omp parallel
    {  // parallel region
        Vec<ZZ> ap;
        double mp = -1;
        std::deque<Vec<ZZ>> vp;

        while (!sstop) {
#pragma omp critical
            {            // increment a
                ap = a;  // thread makes a copy
                Hlawka::sym_incr(a, p, N);
            }

            if (ap[1] < b) {
                double l = svp(p, ap, N);  // compute svp(p, a)
                update(l, mp, vp, ap);     // update maximum across thread
            } else {
#pragma omp atomic
                sstop++;
            }
        }

#pragma omp critical
        merge(v, vp, m, mp);  // merge results across threads
    }

    write(file, p, m, v, N);  // write results to file
}

/**
 * @brief Parallel computation of svp(p, a) for each a in the hypercube of
 * given center and radius lying in the symmetric subdivision of U(p).
 */
void svp_symc(int p, Vec<RR> &center, RR radius, double (*svp)(int, Vec<ZZ> &, int), int N, std::ofstream &file) {
    int b = p / 4;

    Vec<ZZ> c = conv<Vec<ZZ>>(center * p);
    ZZ r = conv<ZZ>(radius * p);

    Vec<ZZ> a;
    Hlawka::U_center(a, c, r, N);

    double m = -1;
    std::deque<Vec<ZZ>> v;

    int sstop = 0;
#pragma omp parallel
    {
        Vec<ZZ> ap;
        double mp = -1;
        std::deque<Vec<ZZ>> vp;

        while (!sstop) {
#pragma omp critical
            {
                ap = a;
                Hlawka::symc_incr(a, p, c, r, N);
            }
            if (ap[1] < b && ap[1] < c[1] + r) {
                double l = svp(p, ap, N);
                update(l, mp, vp, ap);
            } else {
#pragma omp atomic
                sstop++;
            }
        }
#pragma omp critical
        merge(v, vp, m, mp);
    }

    write(file, p, m, v, N);
}