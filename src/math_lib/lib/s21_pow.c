#include "../s21_math.h"

int s21_is_int(double d) { return d == (int)d; };

long double s21_check_value(double base, double exp) {
  long double result = 0;

  if (exp == 0) {
    result = 1;
  } else if (S21_isNAN(base) || S21_isNAN(exp)) {
    if (base == 1) {
      result = 1;
    } else if (exp == 0) {
      result = 1;
    } else {
      result = S21_NaN;
    }
  } else if (base == 0 || base == -0) {
    if (s21_is_int(exp) && exp > 0) {
      result = 0;
    } else if ((s21_is_int(exp) % 2 != 0) && exp < 0) {
      result = S21_POS_INF;
    }
  } else if (base == -1 && (S21_isPOS_INF(exp) || S21_isNEG_INF(exp))) {
    result = 1;
  } else if (s21_fabs(base) < 1 && S21_isNEG_INF(exp)) {
    result = S21_POS_INF;
  } else if (s21_fabs(base) < 1 && S21_isPOS_INF(exp)) {
    result = 0;
  } else if (s21_fabs(base) > 1 && S21_isNEG_INF(exp)) {
    result = +0;
  } else if (s21_fabs(base) > 1 && S21_isPOS_INF(exp)) {
    result = S21_POS_INF;
  } else if (S21_isNEG_INF(base)) {
    if ((s21_is_int(exp) % 2 != 0) && exp < 0) {
      result = -0;
    } else if ((s21_is_int(exp) % 2 == 0) && exp < 0) {
      result = 0;
    } else if ((s21_is_int(exp) % 2 != 0) && exp > 0) {
      result = S21_NEG_INF;
    }
  } else if (S21_isPOS_INF(base) && exp < 0) {
    result = +0;
  } else if (S21_isPOS_INF(base) && exp > 0) {
    result = S21_POS_INF;
  } else if (base < 0 && !s21_is_int(exp) && exp != 0) {
    result = S21_NaN;
  }
  return result;
}

long double s21_pow(double base, double exp) {
  long double result = 0, copy = base;

  if (s21_check_value(base, exp) == 0) {
    if (copy < 0) {
      copy = -copy;
      result = s21_exp(exp * s21_log(copy));
      if (s21_fmod(exp, 2) != 0) {
        result = -result;
      }
    } else {
      result = s21_exp(exp * s21_log(base));
    }
  } else {
    result = s21_check_value(base, exp);
  }
  if (result > S21_MAX) {
    result = S21_POS_INF;
  }

  return result;
}