#include "../s21_math.h"

long double s21_sqrt(double x) {
  long double result = 0;
  if (S21_isNAN(x)) {
    result = S21_NaN;
  } else if (x == 0 || x == -0) {
    result = 0;
  } else if (S21_isPOS_INF(x)) {
    result = S21_POS_INF;
  } else if (x < -0) {
    result = S21_NaN;
  } else {
    result = s21_pow(x, 0.5);
  }
  return result;
}