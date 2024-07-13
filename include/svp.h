#pragma once
#include <NTL/vector.h>
#include <NTL/ZZ.h>

using namespace NTL;

double svp(int p, Vec<ZZ> a, double delta = 0.99);
void svp_all(int p, double delta = 0.99);
void svp_symmetric(int p, double delta = 0.99);
