#include "../s21_math.h"

long double s21_floor(double x) {
  long double result = 0.0;

  if (S21_isNAN(x) || S21_isPOS_INF(x) || S21_isNEG_INF(x) ||
      (long double)(int)x == x)
    result = x;
  else if (x > 0.0)
    result = (long double)(int)x;
  else if (x < 0.0)
    result = (long double)(int)x - 1.0;

  return result;
}