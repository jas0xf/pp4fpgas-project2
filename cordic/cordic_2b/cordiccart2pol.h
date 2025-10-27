#ifndef CORDICCART2POL_H
#define CORDICCART2POL_H

#define NO_ITER 20

typedef int   coef_t;
#include <ap_fixed.h>
typedef  ap_fixed<32,4> data_t;
typedef float acc_t;

void cordiccart2pol(data_t x, data_t y, data_t * r,  data_t * theta);

#endif
