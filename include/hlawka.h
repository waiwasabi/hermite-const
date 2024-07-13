#pragma once
#include <NTL/mat_ZZ.h>

using namespace NTL;

// constants
const int N = 4;

// function prototypes

namespace hlawka {
    void increment(Vec<ZZ> &a, int p);
    void U(Vec<ZZ> &a);
    void B(Mat<ZZ> &B, int p, Vec<ZZ> a);
    double q(int p);
}