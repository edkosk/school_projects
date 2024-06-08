#include "../s21_math.h"

long double s21_log(double x) {
  long double result = 0.0, e_pow = 0.0, compare = 0.0;
  if (S21_isNAN(x)) {
    result = S21_NaN;
  } else if (x == 1) {
    result = +0;
  } else if (S21_isPOS_INF(x)) {
    result = S21_POS_INF;
  } else if (x == 0) {
    result = S21_NEG_INF;
  } else if (x < 0 || S21_isNEG_INF(x)) {
    result = S21_NaN;
  } else if (x > 0) {
    for (; x >= S21_EXP; x /= S21_EXP, e_pow++) continue;
    for (int i = 0; i < 100; i++) {
      compare = result;
      result = compare + 2 * ((x - s21_exp(compare)) / (x + s21_exp(compare)));
    }
    result += e_pow;
  }
  return result;
}