#include "hlawka.h"
#include "vector.h"
#include "svp.h"

using namespace std;

int main() {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
    svp_symmetric(600);
    auto t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    std::cout << ms_int.count() << "ms\n";
    return 0;
}