#include <fstream>
#include <iostream>

#include <random>

#include "hlawka.h"
#include "svp.h"
#include "vector.h"

using namespace std;

int main() {
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;

    ofstream file("svp_best.txt");

    auto t1 = high_resolution_clock::now();

    // iterate over p in [2, 1000)
    // for (int p = 2; p < 1000; p++) {
    //     svp_sym(p, exact_svp, 60, file);
    // }

    for (int n = 2; n < 1000; n++) {
        int p = 4 * n;
        // random_device rd; // obtain a random number from hardware
        // mt19937 gen(rd()); // seed the generator
        // uniform_int_distribution<> distr(0, p - 1); // define the range

        // Vec<ZZ> a;
        // Hlawka::U(a, n);

        // for (int i = 1; i < n; i++) {
        //     a[i] = distr(gen);
        // }

        svp_sym(exact_svp, p, n, file);
        // file << n << "," << p << "," << exact_svp(p, a, n) / Hlawka::q(p, n) << endl;
    }

    auto t2 = high_resolution_clock::now();

    cout << "Time: " << duration_cast<milliseconds>(t2 - t1).count() / 1000.0 << "s" << endl;

    return 0;
}
