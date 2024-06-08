#include "../s21_math.h"

long double s21_fmod(double x, double y) {
  long double result = 0;
  int n = x / y;
  if (S21_isNAN(x) || S21_isNAN(y)) {
    result = S21_NaN;
  } else if (S21_isPOS_INF(x) || S21_isNEG_INF(x)) {
    result = S21_NaN;
  } else if (y == 0) {
    result = S21_NaN;
  } else if (x == 0 && y != 0) {
    result = 0;
  } else if (S21_isNEG_INF(y) || S21_isPOS_INF(y)) {
    result = x;
  } else {
    result = x - n * y;
  }
  return result;
}