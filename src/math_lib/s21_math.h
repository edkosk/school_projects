#include <stdint.h>
#define S21_PI 3.1415926535897932
#define S21_EXP 2.7182818284590452
#define S21_EPS 1e-30
#define S21_MAX 1e100
#define S21_NaN (0.0 / 0.0)
#define S21_POS_INF (1.0 / 0.0)
#define S21_NEG_INF (-1.0 / 0.0)
#define S21_isNAN(x) (x != x)
#define S21_isPOS_INF(x) (x == S21_POS_INF)
#define S21_isNEG_INF(x) (x == S21_NEG_INF)

int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);
