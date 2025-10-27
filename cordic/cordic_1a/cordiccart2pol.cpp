#include "cordiccart2pol.h"

data_t Kvalues[] = {1,	0.500000000000000,	0.250000000000000,	0.125000000000000,	0.0625000000000000,	0.0312500000000000,	0.0156250000000000,	0.00781250000000000,	0.00390625000000000,	0.00195312500000000,	0.000976562500000000,	0.000488281250000000,	0.000244140625000000,	0.000122070312500000,	6.10351562500000e-05,	3.05175781250000e-05,/*custom Kvalues*/ 1.52587890625000e-5,7.62939453125000e-6,3.81469726562500e-6,1.90734863281250e-6};

data_t angles[] = {0.785398163397448,	0.463647609000806,	0.244978663126864,	0.124354994546761,	0.0624188099959574,	0.0312398334302683,	0.0156237286204768,	0.00781234106010111,	0.00390623013196697,	0.00195312251647882,	0.000976562189559320,	0.000488281211194898,	0.000244140620149362,	0.000122070311893670,	6.10351561742088e-05,	3.05175781155261e-05,/*custom angles*/ 1.52587890613158e-05,	7.62939453110197e-06,	3.8146972656065e-06,	1.90734863281019e-06};

// K = 2^-i
// angle = arctan(2^-i)

// x = cos theta * r
// y = sin theta * r
// r = sqrt(x^2 + y^2)
// theta = arctan2(y/x)
//
// arctan2(y, x) = {
//  if x > 0, theta = arctan(y/x)
//  if x < 0 and y >= 0, theta = arctan(y/x) + pi
//  if x < 0 and y < 0, theta = arctan(y/x) - pi
//  if x = 0 and y > 0, theta = pi/2
//  if x = 0 and y < 0, theta = -pi/2
//  if x = 0 and y = 0, theta = undefined
// }
//
// given arctan only, so we should ensure x > 0

#include <math.h>

void cordiccart2pol(data_t x, data_t y, data_t * r,  data_t * theta)
{
	// Write your code here
  if (x == 0 && y == 0) {
    *r = 0;
    *theta = 0;
    return;
  }

  data_t cum_angle = 0;
  data_t PI = 3.141592653589793;

  if (x < data_t (0)) {
    x = -x;
    y = -y;
    cum_angle += PI;
  }

  data_t temp;
  for (int i = 0; i < NO_ITER; i++){
    if(y >= data_t (0)){
      temp = x + (y * Kvalues[i]);
      y = y - (x * Kvalues[i]);
      x = temp;
      cum_angle += angles[i];
    }else{
      temp = x - (y * Kvalues[i]);
      y = y + (x * Kvalues[i]);
      x = temp;
      cum_angle -= angles[i];
    }
  }

  data_t K_cum = 1;
  for (int i = 0; i < NO_ITER; i++){
    K_cum *= (data_t)(1.0 / sqrtf(1.0f + Kvalues[i] * Kvalues[i]));
  }

  *r = x * K_cum;

  if (cum_angle > PI) cum_angle -= 2 * PI;
  if (cum_angle < -PI) cum_angle += 2 * PI;
  *theta = cum_angle;
}
