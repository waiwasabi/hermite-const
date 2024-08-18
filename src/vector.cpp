#include "vector.hpp"

using namespace NTL;

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

/**
 * @brief Convert an array to an NTL vector
 */
Vec<RR> arr_to_vec(double *arr, int N) {
    Vec<RR> res;
    res.SetLength(N);
    for (int i = 0; i < N; i++) {
        res[i] = arr[i];
    }
    return res;
}
