#pragma once
#include <NTL/RR.h>
#include <NTL/ZZ.h>
#include <NTL/vector.h>

using namespace NTL;

double lll_svp(int p, Vec<ZZ> &a, int N);
double exact_svp(int p, Vec<ZZ> &a, int N);
void svp_all(int p, double (*svp)(int, Vec<ZZ> &, int), int N, std::ofstream &file);
void svp_sym(int p, double (*svp)(int, Vec<ZZ> &, int), int N, std::ofstream &file);
void svp_symc(int p, Vec<RR> &center, RR radius, double (*svp)(int, Vec<ZZ> &, int), int N, std::ofstream &file);