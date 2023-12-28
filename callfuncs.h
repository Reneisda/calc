#include "calculations.h"
#include "func.h"

#ifndef CALC_CALLFUNCS_H
#define CALC_CALLFUNCS_H
#endif

void init(int base_, int precision_);
void out_pq(char* str);
void out_fac(char* str);
void out_ncr(char* str);
void out_bin_pdf(char* str);
void out_bin_cdf(char* str);
func get_func(char* str);
double out_bisection(char* str, double a, double b);
