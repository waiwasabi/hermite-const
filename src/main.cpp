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

  ofstream all_timef("all_time_n" + to_string(N), ios::out | ios::app);
  ofstream sym_timef("sym_time_n" + to_string(N), ios::out | ios::app);
  for (int i = 2; i < 1000; i++) {
    string all_fname = "data/" + to_string(N) + "/all/" + to_string(i);
    ofstream all_file(all_fname, ios::out | ios::app);

    auto t1 = high_resolution_clock::now();
    svp_all(i, &exact_svp, all_file);
    auto t2 = high_resolution_clock::now();

    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    all_timef << to_string(i) << " " << ms_int.count() << endl;

    string sym_fname = "data/" + to_string(N) + "/sym/" + to_string(i);
    ofstream sym_file(sym_fname, ios::out | ios::app);

    t1 = high_resolution_clock::now();
    svp_symmetric(i, &exact_svp, sym_file);
    t2 = high_resolution_clock::now();

    ms_int = duration_cast<milliseconds>(t2 - t1);
    sym_timef << to_string(i) << " " << ms_int.count() << endl;
  }

  /* Getting number of milliseconds as an integer. */

  return 0;
}