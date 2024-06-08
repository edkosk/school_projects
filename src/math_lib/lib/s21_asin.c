#include "../s21_math.h"

long double s21_asin(double x) {
  long double result = 0.0, i = 1.0;
  if (S21_isNAN(x) || s21_fabs(x) > 1)
    result = S21_NaN;
  else if (s21_fabs(x) >= 0.5)
    result = S21_PI / 2 - s21_acos(x);
  else {
    long double q = x;
    while (s21_fabs(q) > 1e-30) {
      result = result + q;
      q = q * ((long double)x * (long double)x) * (2 * i - 1) * (2 * i - 1) /
          ((2 * i + 1) * (2 * i));
      i = i + 1.0;
    }
  }
  return result;
}