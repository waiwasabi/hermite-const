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

  ofstream file("svp_symmetric.txt");

  auto t1 = high_resolution_clock::now();

  for (int p = 2; p < 1000; p++) {
    svp_symmetric(p, exact_svp, 5, file);
  }
  
  auto t2 = high_resolution_clock::now();

  return 0;
}