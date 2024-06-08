#include "../s21_math.h"

long double s21_tan(double x) {
  long double result = 0.0;
  if (S21_isNAN(x) || S21_isPOS_INF(x) || S21_isNEG_INF(x))
    result = S21_NaN;
  else
    result = s21_sin(x) / s21_cos(x);
  return result;
}