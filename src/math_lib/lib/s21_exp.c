#include "../s21_math.h"

long double s21_exp(double x) {
  long double i = 1;
  long double step = 1;
  long double result = 1;

  if (S21_isNAN(x)) {
    result = S21_NaN;
  } else if (S21_isPOS_INF(x)) {
    result = S21_POS_INF;
  } else if (S21_isNEG_INF(x) || x < -30.5) {
    result = 0.0;
  } else {
    while (s21_fabs(step) > S21_EPS && result <= S21_MAX) {
      step *= x / i;
      i++;
      result += step;
    }
    if (result > S21_MAX) {
      result = S21_POS_INF;
    }
  }

  return result;
}