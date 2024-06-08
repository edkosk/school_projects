#include "../s21_math.h"

long double s21_sin(double x) {
  long double result = 0.0, i = 1.0;
  if (S21_isNAN(x) || S21_isPOS_INF(x) || S21_isNEG_INF(x))
    result = S21_NaN;
  else {
    x = s21_fmod(x, S21_PI * 2);
    long double q = x;
    while (s21_fabs(q) > 1e-20) {
      result = result + q;
      q = q * (-1) * (x * x) / ((2 * i + 1) * (2 * i));
      i = i + 1.0;
    }
  }
  return result;
}