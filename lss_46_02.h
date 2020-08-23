#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#pragma warning(disable:4996)

#define epsilon 1e-50

int error, debug;

int lss_46_02(int n, double *A, double *B, double *X, double *tmpmem);
size_t stringLength(const char *str);
int stringComp(const char *str1, const char *str2);
void print(double *A, double *B, int n);