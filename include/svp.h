#pragma once
#include <NTL/RR.h>
#include <NTL/ZZ.h>
#include <NTL/vector.h>

using namespace NTL;

double lll_svp(int p, Vec<ZZ> &a, int N);
double exact_svp(int p, Vec<ZZ> &a, int N);
void svp_all(double (*svp)(int, Vec<ZZ> &, int), int p, int N, std::ofstream &file);
void svp_sym(double (*svp)(int, Vec<ZZ> &, int), int p, int N, std::ofstream &file);
void svp_symc(double (*svp)(int, Vec<ZZ> &, int), int p, int N, Vec<RR> &center, RR radius, std::ofstream &file);