#include <fstream>
#include <iostream>

#include "hlawka.h"
#include "svp.h"
#include "vector.h"

using namespace std;

int main() {
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;

    ofstream file("svp_symmetric_9.txt");

    auto t1 = high_resolution_clock::now();

    // iterate over p in [2, 1000)
    for (int p = 2; p < 1000; p++) {
        svp_sym(p, exact_svp, 9, file);
    }

    auto t2 = high_resolution_clock::now();

    cout << "Time: " << duration_cast<milliseconds>(t2 - t1).count() / 1000.0 << "s" << endl;

    return 0;
}
