#include "../s21_math.h"

long double s21_acos(double x) {
  long double result = 0.0;
  if (S21_isNAN(x) || s21_fabs(x) > 1)
    result = S21_NaN;
  else if (s21_fabs(x) < 0.5)
    result = S21_PI / 2 - s21_asin(x);
  else
    result = 2 * s21_asin(s21_sqrt((1 - x) / 2));
  return result;
}