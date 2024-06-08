#include "../s21_math.h"

long double s21_atan(double x) {
  long double result = 0.0;
  if (S21_isNAN(x))
    result = S21_NaN;
  else if (S21_isPOS_INF(x))
    result = S21_PI / 2;
  else if (S21_isNEG_INF(x))
    result = -S21_PI / 2;
  else
    result = s21_asin(x / (s21_sqrt(1 + x * x)));
  return result;
}