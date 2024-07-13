#include "hlawka.h"

namespace hlawka {
    /**
     * @brief Initialize a vector in U(p)
     */
    void U(Vec<ZZ> &a) {
    a.SetLength(N);
    a[0] = 1;
    }

    void increment(Vec<ZZ> &a, int p) {
        for(int i = N - 1; i >= 0; i--) {
            if(a[i] < p - 1) {
                a[i]++;
                return;
            }
            a[i] = 0;
        }
    }


    /**
     * @brief Initialize the lattice basis B(p, a)
     */
    void B(Mat<ZZ> &B, int p, Vec<ZZ> a) {
    B = ident_mat_ZZ(N) * p;
    B[0] = a;
    }

    /**
     * @brief Compute q given p
     */
    double q(int p) { return pow(p, (N - 1.) / N); }
}
