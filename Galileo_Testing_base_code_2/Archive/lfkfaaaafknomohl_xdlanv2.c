/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: lfkfaaaafknomohl_xdlanv2.c
 *
 * Code generated for Simulink model 'gnc2_lib'.
 *
 * Model version                  : 1.5
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 14:12:23 2019
 */

#include "rtwtypes.h"
#include <math.h>
#include "rt_hypotd_snf.h"
#include "lfkfaaaafknomohl_xdlanv2.h"

/* Function for MATLAB Function: '<S1>/INITIALIZE' */
void lfkfaaaafknomohl_xdlanv2(real_T *a, real_T *b, real_T *c, real_T *d, real_T
  *rt1r, real_T *rt1i, real_T *rt2r, real_T *rt2i, real_T *cs, real_T *sn)
{
  real_T temp;
  real_T p;
  real_T bcmax;
  real_T bcmis;
  real_T scale;
  real_T z;
  int32_T b_0;
  int32_T c_0;
  if (*c == 0.0) {
    *cs = 1.0;
    *sn = 0.0;
  } else if (*b == 0.0) {
    *cs = 0.0;
    *sn = 1.0;
    temp = *d;
    *d = *a;
    *a = temp;
    *b = -*c;
    *c = 0.0;
  } else if ((*a - *d == 0.0) && ((*b < 0.0) != (*c < 0.0))) {
    *cs = 1.0;
    *sn = 0.0;
  } else {
    temp = *a - *d;
    p = 0.5 * temp;
    bcmax = fmax(fabs(*b), fabs(*c));
    if (!(*b < 0.0)) {
      b_0 = 1;
    } else {
      b_0 = -1;
    }

    if (!(*c < 0.0)) {
      c_0 = 1;
    } else {
      c_0 = -1;
    }

    bcmis = fmin(fabs(*b), fabs(*c)) * (real_T)b_0 * (real_T)c_0;
    scale = fmax(fabs(p), bcmax);
    z = p / scale * p + bcmax / scale * bcmis;
    if (z >= 8.8817841970012523E-16) {
      temp = sqrt(scale) * sqrt(z);
      if (p < 0.0) {
        temp = -temp;
      }

      z = p + temp;
      *a = *d + z;
      *d -= bcmax / z * bcmis;
      bcmax = rt_hypotd_snf(*c, z);
      *cs = z / bcmax;
      *sn = *c / bcmax;
      *b -= *c;
      *c = 0.0;
    } else {
      bcmis = *b + *c;
      bcmax = rt_hypotd_snf(bcmis, temp);
      *cs = sqrt((fabs(bcmis) / bcmax + 1.0) * 0.5);
      if (!(bcmis < 0.0)) {
        b_0 = 1;
      } else {
        b_0 = -1;
      }

      *sn = -(p / (bcmax * *cs)) * (real_T)b_0;
      temp = *a * *cs + *b * *sn;
      p = -*a * *sn + *b * *cs;
      bcmax = *c * *cs + *d * *sn;
      bcmis = -*c * *sn + *d * *cs;
      *b = p * *cs + bcmis * *sn;
      *c = -temp * *sn + bcmax * *cs;
      temp = ((temp * *cs + bcmax * *sn) + (-p * *sn + bcmis * *cs)) * 0.5;
      *a = temp;
      *d = temp;
      if (*c != 0.0) {
        if (*b != 0.0) {
          if ((*b < 0.0) == (*c < 0.0)) {
            z = sqrt(fabs(*b));
            bcmis = sqrt(fabs(*c));
            p = z * bcmis;
            if (*c < 0.0) {
              p = -p;
            }

            bcmax = 1.0 / sqrt(fabs(*b + *c));
            *a = temp + p;
            *d = temp - p;
            *b -= *c;
            *c = 0.0;
            p = z * bcmax;
            bcmax *= bcmis;
            temp = *cs * p - *sn * bcmax;
            *sn = *cs * bcmax + *sn * p;
            *cs = temp;
          }
        } else {
          *b = -*c;
          *c = 0.0;
          temp = *cs;
          *cs = -*sn;
          *sn = temp;
        }
      }
    }
  }

  *rt1r = *a;
  *rt2r = *d;
  if (*c == 0.0) {
    *rt1i = 0.0;
    *rt2i = 0.0;
  } else {
    *rt1i = sqrt(fabs(*b)) * sqrt(fabs(*c));
    *rt2i = -*rt1i;
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
