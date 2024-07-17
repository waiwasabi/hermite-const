#pragma once
#include <NTL/ZZ.h>
#include <NTL/vector.h>

using namespace NTL;

double lll_svp(int p, Vec<ZZ> &a);
double exact_svp(int p, Vec<ZZ> &a);
void svp_all(int p, double (*svp)(int, Vec<ZZ> &), std::ofstream &file);
void svp_symmetric(int p, double (*svp)(int, Vec<ZZ> &), std::ofstream &file);
