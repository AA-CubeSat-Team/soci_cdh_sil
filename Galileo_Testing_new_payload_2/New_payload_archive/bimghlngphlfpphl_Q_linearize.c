/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: bimghlngphlfpphl_Q_linearize.c
 *
 * Code generated for Simulink model 'gnc2_lib0'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 17:57:19 2019
 */

#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#include "cbaalnglphdjcjek_mrdivide.h"
#include "bimghlngphlfpphl_Q_linearize.h"

/*
 * Function for MATLAB Function: '<S1>/SOLVE'
 * function [ A,B,f ] = Q_linearize( t,x,u,J )
 * Q_LINEARIZE    Linearize the attitude dynamics
 *
 *  Q_linearize(t,x,u,P) returns the discrete representation of the
 *  quaternion-based attitude dynamics at the point (x,u) and time t.
 *
 *  T. Reynolds -- RAIN Lab.
 */
void bimghlngphlfpphl_Q_linearize(const real_T x[10], const real_T u[3], const
  real_T J[9], real_T A[100], real_T f[10])
{
  real_T q[4];
  real_T w[3];
  real_T dfq_dhb[12];
  real_T scale;
  real_T absxk;
  real_T t;
  real_T b_A[9];
  int32_T r1;
  int32_T r2;
  int32_T r3;
  real_T maxval;
  int32_T rtemp;
  real_T b_y[12];
  real_T a[3];
  static const int8_T b[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  real_T tmp[9];
  real_T tmp_0[9];
  real_T tmp_1[9];
  real_T q_0[12];
  real_T tmp_2[9];
  real_T tmp_3[9];
  real_T tmp_4[9];
  real_T tmp_5[16];
  real_T tmp_6[9];
  real_T tmp_7[9];

  /*  States */
  /* '<S3>:1:240' q   = x(1:4)./norm(x(1:4)); */
  scale = 2.2250738585072014E-308;
  absxk = fabs(x[0]);
  if (absxk > 2.2250738585072014E-308) {
    maxval = 1.0;
    scale = absxk;
  } else {
    t = absxk / 2.2250738585072014E-308;
    maxval = t * t;
  }

  absxk = fabs(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    maxval = maxval * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    maxval += t * t;
  }

  absxk = fabs(x[2]);
  if (absxk > scale) {
    t = scale / absxk;
    maxval = maxval * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    maxval += t * t;
  }

  absxk = fabs(x[3]);
  if (absxk > scale) {
    t = scale / absxk;
    maxval = maxval * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    maxval += t * t;
  }

  maxval = scale * sqrt(maxval);
  q[0] = x[0] / maxval;
  q[1] = x[1] / maxval;
  q[2] = x[2] / maxval;
  q[3] = x[3] / maxval;

  /* '<S3>:1:241' q0  = q(1); */
  /* '<S3>:1:242' qv  = q(2:4); */
  /* '<S3>:1:243' hb  = x(5:7); */
  /* '<S3>:1:244' hw  = x(8:10); */
  /* '<S3>:1:245' w   = J\hb; */
  memcpy(&b_A[0], &J[0], 9U * sizeof(real_T));
  r1 = 0;
  r2 = 1;
  r3 = 2;
  maxval = fabs(J[0]);
  scale = fabs(J[1]);
  if (scale > maxval) {
    maxval = scale;
    r1 = 1;
    r2 = 0;
  }

  if (fabs(J[2]) > maxval) {
    r1 = 2;
    r2 = 1;
    r3 = 0;
  }

  b_A[r2] = J[r2] / J[r1];
  b_A[r3] /= b_A[r1];
  b_A[3 + r2] -= b_A[3 + r1] * b_A[r2];
  b_A[3 + r3] -= b_A[3 + r1] * b_A[r3];
  b_A[6 + r2] -= b_A[6 + r1] * b_A[r2];
  b_A[6 + r3] -= b_A[6 + r1] * b_A[r3];
  if (fabs(b_A[3 + r3]) > fabs(b_A[3 + r2])) {
    rtemp = r2;
    r2 = r3;
    r3 = rtemp;
  }

  b_A[3 + r3] /= b_A[3 + r2];
  b_A[6 + r3] -= b_A[3 + r3] * b_A[6 + r2];
  w[1] = x[r2 + 4] - x[r1 + 4] * b_A[r2];
  w[2] = (x[r3 + 4] - x[r1 + 4] * b_A[r3]) - b_A[3 + r3] * w[1];
  w[2] /= b_A[6 + r3];
  w[0] = x[r1 + 4] - b_A[6 + r1] * w[2];
  w[1] -= b_A[6 + r2] * w[2];
  w[1] /= b_A[3 + r2];
  w[0] -= b_A[3 + r1] * w[1];
  w[0] /= b_A[r1];

  /*  Partials */
  /* '<S3>:1:248' dfq_dq  = 0.5 * [ 0 -w'; w -skew(w) ]; */
  /* 'skew:4' cross = [0 -a(3) a(2); */
  /* 'skew:5'          a(3) 0 -a(1); */
  /* 'skew:6'         -a(2) a(1) 0]; */
  /* '<S3>:1:249' dfq_dhb = 0.5 * [ -qv'; skew(qv)+q0*eye(3) ]/J; */
  /* 'skew:4' cross = [0 -a(3) a(2); */
  /* 'skew:5'          a(3) 0 -a(1); */
  /* 'skew:6'         -a(2) a(1) 0]; */
  scale = q[0];
  tmp_1[0] = 0.0;
  tmp_1[3] = -q[3];
  tmp_1[6] = q[2];
  tmp_1[1] = q[3];
  tmp_1[4] = 0.0;
  tmp_1[7] = -q[1];
  tmp_1[2] = -q[2];
  tmp_1[5] = q[1];
  tmp_1[8] = 0.0;
  for (r1 = 0; r1 < 3; r1++) {
    q_0[r1 << 2] = -q[1 + r1];
    q_0[1 + (r1 << 2)] = (real_T)b[3 * r1] * scale + tmp_1[3 * r1];
    q_0[2 + (r1 << 2)] = (real_T)b[3 * r1 + 1] * scale + tmp_1[3 * r1 + 1];
    q_0[3 + (r1 << 2)] = (real_T)b[3 * r1 + 2] * scale + tmp_1[3 * r1 + 2];
    b_y[r1 << 2] = q_0[r1 << 2] * 0.5;
    b_y[1 + (r1 << 2)] = q_0[(r1 << 2) + 1] * 0.5;
    b_y[2 + (r1 << 2)] = q_0[(r1 << 2) + 2] * 0.5;
    b_y[3 + (r1 << 2)] = q_0[(r1 << 2) + 3] * 0.5;
  }

  memcpy(&b_A[0], &J[0], 9U * sizeof(real_T));
  r1 = 0;
  r2 = 1;
  r3 = 2;
  maxval = fabs(J[0]);
  scale = fabs(J[1]);
  if (scale > maxval) {
    maxval = scale;
    r1 = 1;
    r2 = 0;
  }

  if (fabs(J[2]) > maxval) {
    r1 = 2;
    r2 = 1;
    r3 = 0;
  }

  b_A[r2] = J[r2] / J[r1];
  b_A[r3] /= b_A[r1];
  b_A[3 + r2] -= b_A[3 + r1] * b_A[r2];
  b_A[3 + r3] -= b_A[3 + r1] * b_A[r3];
  b_A[6 + r2] -= b_A[6 + r1] * b_A[r2];
  b_A[6 + r3] -= b_A[6 + r1] * b_A[r3];
  if (fabs(b_A[3 + r3]) > fabs(b_A[3 + r2])) {
    rtemp = r2;
    r2 = r3;
    r3 = rtemp;
  }

  b_A[3 + r3] /= b_A[3 + r2];
  b_A[6 + r3] -= b_A[3 + r3] * b_A[6 + r2];
  dfq_dhb[r1 << 2] = b_y[0] / b_A[r1];
  dfq_dhb[r2 << 2] = b_y[4] - dfq_dhb[r1 << 2] * b_A[3 + r1];
  dfq_dhb[r3 << 2] = b_y[8] - dfq_dhb[r1 << 2] * b_A[6 + r1];
  dfq_dhb[r2 << 2] /= b_A[3 + r2];
  dfq_dhb[r3 << 2] -= dfq_dhb[r2 << 2] * b_A[6 + r2];
  dfq_dhb[r3 << 2] /= b_A[6 + r3];
  dfq_dhb[r2 << 2] -= dfq_dhb[r3 << 2] * b_A[3 + r3];
  dfq_dhb[r1 << 2] -= dfq_dhb[r3 << 2] * b_A[r3];
  dfq_dhb[r1 << 2] -= dfq_dhb[r2 << 2] * b_A[r2];
  dfq_dhb[1 + (r1 << 2)] = b_y[1] / b_A[r1];
  dfq_dhb[1 + (r2 << 2)] = b_y[5] - dfq_dhb[(r1 << 2) + 1] * b_A[3 + r1];
  dfq_dhb[1 + (r3 << 2)] = b_y[9] - dfq_dhb[(r1 << 2) + 1] * b_A[6 + r1];
  dfq_dhb[1 + (r2 << 2)] /= b_A[3 + r2];
  dfq_dhb[1 + (r3 << 2)] -= dfq_dhb[(r2 << 2) + 1] * b_A[6 + r2];
  dfq_dhb[1 + (r3 << 2)] /= b_A[6 + r3];
  dfq_dhb[1 + (r2 << 2)] -= dfq_dhb[(r3 << 2) + 1] * b_A[3 + r3];
  dfq_dhb[1 + (r1 << 2)] -= dfq_dhb[(r3 << 2) + 1] * b_A[r3];
  dfq_dhb[1 + (r1 << 2)] -= dfq_dhb[(r2 << 2) + 1] * b_A[r2];
  dfq_dhb[2 + (r1 << 2)] = b_y[2] / b_A[r1];
  dfq_dhb[2 + (r2 << 2)] = b_y[6] - dfq_dhb[(r1 << 2) + 2] * b_A[3 + r1];
  dfq_dhb[2 + (r3 << 2)] = b_y[10] - dfq_dhb[(r1 << 2) + 2] * b_A[6 + r1];
  dfq_dhb[2 + (r2 << 2)] /= b_A[3 + r2];
  dfq_dhb[2 + (r3 << 2)] -= dfq_dhb[(r2 << 2) + 2] * b_A[6 + r2];
  dfq_dhb[2 + (r3 << 2)] /= b_A[6 + r3];
  dfq_dhb[2 + (r2 << 2)] -= dfq_dhb[(r3 << 2) + 2] * b_A[3 + r3];
  dfq_dhb[2 + (r1 << 2)] -= dfq_dhb[(r3 << 2) + 2] * b_A[r3];
  dfq_dhb[2 + (r1 << 2)] -= dfq_dhb[(r2 << 2) + 2] * b_A[r2];
  dfq_dhb[3 + (r1 << 2)] = b_y[3] / b_A[r1];
  dfq_dhb[3 + (r2 << 2)] = b_y[7] - dfq_dhb[(r1 << 2) + 3] * b_A[3 + r1];
  dfq_dhb[3 + (r3 << 2)] = b_y[11] - dfq_dhb[(r1 << 2) + 3] * b_A[6 + r1];
  dfq_dhb[3 + (r2 << 2)] /= b_A[3 + r2];
  dfq_dhb[3 + (r3 << 2)] -= dfq_dhb[(r2 << 2) + 3] * b_A[6 + r2];
  dfq_dhb[3 + (r3 << 2)] /= b_A[6 + r3];
  dfq_dhb[3 + (r2 << 2)] -= dfq_dhb[(r3 << 2) + 3] * b_A[3 + r3];
  dfq_dhb[3 + (r1 << 2)] -= dfq_dhb[(r3 << 2) + 3] * b_A[r3];
  dfq_dhb[3 + (r1 << 2)] -= dfq_dhb[(r2 << 2) + 3] * b_A[r2];

  /* '<S3>:1:250' dfq_dhw = zeros(4,3); */
  /* '<S3>:1:251' dfhb_dq  = zeros(3,4); */
  /* '<S3>:1:252' dfhb_dhb = skew(hb)/J - skew(w) + skew(hw)/J; */
  /* 'skew:4' cross = [0 -a(3) a(2); */
  /* 'skew:5'          a(3) 0 -a(1); */
  /* 'skew:6'         -a(2) a(1) 0]; */
  /* 'skew:4' cross = [0 -a(3) a(2); */
  /* 'skew:5'          a(3) 0 -a(1); */
  /* 'skew:6'         -a(2) a(1) 0]; */
  /* 'skew:4' cross = [0 -a(3) a(2); */
  /* 'skew:5'          a(3) 0 -a(1); */
  /* 'skew:6'         -a(2) a(1) 0]; */
  /* '<S3>:1:253' dfhb_dhw = -skew(w); */
  /* 'skew:4' cross = [0 -a(3) a(2); */
  /* 'skew:5'          a(3) 0 -a(1); */
  /* 'skew:6'         -a(2) a(1) 0]; */
  /* '<S3>:1:254' dfhw_dq = zeros(3,4); */
  /* '<S3>:1:255' dfhw_dhb = zeros(3,3); */
  /* '<S3>:1:256' dfhw_dhw = zeros(3,3); */
  /* '<S3>:1:257' dfq_du  = zeros(4,3); */
  /* '<S3>:1:258' dfhb_du  = -eye(3); */
  /* '<S3>:1:259' dfhw_du = eye(3); */
  /*  Kinematics & Dynamics */
  /* '<S3>:1:262' fq  = 0.5 * [ -qv'; skew(qv)+q0*eye(3) ] * w; */
  /* 'skew:4' cross = [0 -a(3) a(2); */
  /* 'skew:5'          a(3) 0 -a(1); */
  /* 'skew:6'         -a(2) a(1) 0]; */
  /* '<S3>:1:263' fhb = -u + skew(hb+hw)*w; */
  /* 'skew:4' cross = [0 -a(3) a(2); */
  /* 'skew:5'          a(3) 0 -a(1); */
  /* 'skew:6'         -a(2) a(1) 0]; */
  /* '<S3>:1:264' fhw = u; */
  /*  Outputs */
  /* '<S3>:1:267' f = [ fq; fhb; fhw ]; */
  scale = q[0];
  tmp_2[0] = 0.0;
  tmp_2[3] = -q[3];
  tmp_2[6] = q[2];
  tmp_2[1] = q[3];
  tmp_2[4] = 0.0;
  tmp_2[7] = -q[1];
  tmp_2[2] = -q[2];
  tmp_2[5] = q[1];
  tmp_2[8] = 0.0;
  for (r1 = 0; r1 < 3; r1++) {
    a[r1] = x[r1 + 4] + x[r1 + 7];
    q_0[r1 << 2] = -q[1 + r1];
    q_0[1 + (r1 << 2)] = (real_T)b[3 * r1] * scale + tmp_2[3 * r1];
    q_0[2 + (r1 << 2)] = (real_T)b[3 * r1 + 1] * scale + tmp_2[3 * r1 + 1];
    q_0[3 + (r1 << 2)] = (real_T)b[3 * r1 + 2] * scale + tmp_2[3 * r1 + 2];
    b_y[r1 << 2] = q_0[r1 << 2] * 0.5;
    b_y[1 + (r1 << 2)] = q_0[(r1 << 2) + 1] * 0.5;
    b_y[2 + (r1 << 2)] = q_0[(r1 << 2) + 2] * 0.5;
    b_y[3 + (r1 << 2)] = q_0[(r1 << 2) + 3] * 0.5;
  }

  tmp_3[0] = 0.0;
  tmp_3[3] = -a[2];
  tmp_3[6] = a[1];
  tmp_3[1] = a[2];
  tmp_3[4] = 0.0;
  tmp_3[7] = -a[0];
  tmp_3[2] = -a[1];
  tmp_3[5] = a[0];
  tmp_3[8] = 0.0;
  for (r1 = 0; r1 < 4; r1++) {
    q[r1] = b_y[r1 + 8] * w[2] + (b_y[r1 + 4] * w[1] + b_y[r1] * w[0]);
  }

  f[0] = q[0];
  f[1] = q[1];
  f[2] = q[2];
  f[3] = q[3];

  /* '<S3>:1:268' A = [ dfq_dq dfq_dhb dfq_dhw; */
  /* '<S3>:1:269'       dfhb_dq dfhb_dhb dfhb_dhw; */
  /* '<S3>:1:270'       dfhw_dq dfhw_dhb dfhw_dhw ]; */
  tmp[0] = 0.0;
  tmp[3] = -x[6];
  tmp[6] = x[5];
  tmp[1] = x[6];
  tmp[4] = 0.0;
  tmp[7] = -x[4];
  tmp[2] = -x[5];
  tmp[5] = x[4];
  tmp[8] = 0.0;
  cbaalnglphdjcjek_mrdivide(tmp, J, tmp_1);
  tmp_0[0] = 0.0;
  tmp_0[3] = -x[9];
  tmp_0[6] = x[8];
  tmp_0[1] = x[9];
  tmp_0[4] = 0.0;
  tmp_0[7] = -x[7];
  tmp_0[2] = -x[8];
  tmp_0[5] = x[7];
  tmp_0[8] = 0.0;
  cbaalnglphdjcjek_mrdivide(tmp_0, J, tmp_2);
  tmp_4[0] = 0.0;
  tmp_4[3] = -w[2];
  tmp_4[6] = w[1];
  tmp_4[1] = w[2];
  tmp_4[4] = 0.0;
  tmp_4[7] = -w[0];
  tmp_4[2] = -w[1];
  tmp_4[5] = w[0];
  tmp_4[8] = 0.0;
  tmp_5[0] = 0.0;
  for (r1 = 0; r1 < 3; r1++) {
    f[r1 + 4] = ((tmp_3[r1 + 3] * w[1] + tmp_3[r1] * w[0]) + tmp_3[r1 + 6] * w[2])
      + -u[r1];
    f[r1 + 7] = u[r1];
    tmp_5[(r1 + 1) << 2] = -w[r1];
    tmp_5[r1 + 1] = w[r1];
    tmp_5[1 + ((r1 + 1) << 2)] = -tmp_4[3 * r1];
    tmp_5[2 + ((r1 + 1) << 2)] = -tmp_4[3 * r1 + 1];
    tmp_5[3 + ((r1 + 1) << 2)] = -tmp_4[3 * r1 + 2];
  }

  tmp_6[0] = 0.0;
  tmp_6[3] = -w[2];
  tmp_6[6] = w[1];
  tmp_6[1] = w[2];
  tmp_6[4] = 0.0;
  tmp_6[7] = -w[0];
  tmp_6[2] = -w[1];
  tmp_6[5] = w[0];
  tmp_6[8] = 0.0;
  tmp_7[0] = 0.0;
  tmp_7[3] = -w[2];
  tmp_7[6] = w[1];
  tmp_7[1] = w[2];
  tmp_7[4] = 0.0;
  tmp_7[7] = -w[0];
  tmp_7[2] = -w[1];
  tmp_7[5] = w[0];
  tmp_7[8] = 0.0;
  for (r1 = 0; r1 < 4; r1++) {
    A[10 * r1] = tmp_5[r1 << 2] * 0.5;
    A[1 + 10 * r1] = tmp_5[(r1 << 2) + 1] * 0.5;
    A[2 + 10 * r1] = tmp_5[(r1 << 2) + 2] * 0.5;
    A[3 + 10 * r1] = tmp_5[(r1 << 2) + 3] * 0.5;
  }

  for (r1 = 0; r1 < 3; r1++) {
    A[10 * (r1 + 4)] = dfq_dhb[r1 << 2];
    A[10 * (r1 + 7)] = 0.0;
    A[1 + 10 * (r1 + 4)] = dfq_dhb[(r1 << 2) + 1];
    A[1 + 10 * (r1 + 7)] = 0.0;
    A[2 + 10 * (r1 + 4)] = dfq_dhb[(r1 << 2) + 2];
    A[2 + 10 * (r1 + 7)] = 0.0;
    A[3 + 10 * (r1 + 4)] = dfq_dhb[(r1 << 2) + 3];
    A[3 + 10 * (r1 + 7)] = 0.0;
  }

  for (r1 = 0; r1 < 4; r1++) {
    A[4 + 10 * r1] = 0.0;
    A[5 + 10 * r1] = 0.0;
    A[6 + 10 * r1] = 0.0;
  }

  for (r1 = 0; r1 < 3; r1++) {
    A[4 + 10 * (r1 + 4)] = (tmp_1[3 * r1] - tmp_6[3 * r1]) + tmp_2[3 * r1];
    A[4 + 10 * (r1 + 7)] = -tmp_7[3 * r1];
    A[5 + 10 * (r1 + 4)] = (tmp_1[3 * r1 + 1] - tmp_6[3 * r1 + 1]) + tmp_2[3 *
      r1 + 1];
    A[5 + 10 * (r1 + 7)] = -tmp_7[3 * r1 + 1];
    A[6 + 10 * (r1 + 4)] = (tmp_1[3 * r1 + 2] - tmp_6[3 * r1 + 2]) + tmp_2[3 *
      r1 + 2];
    A[6 + 10 * (r1 + 7)] = -tmp_7[3 * r1 + 2];
  }

  for (r1 = 0; r1 < 10; r1++) {
    A[7 + 10 * r1] = 0.0;
    A[8 + 10 * r1] = 0.0;
    A[9 + 10 * r1] = 0.0;
  }

  /* '<S3>:1:271' B = [ dfq_du; dfhb_du; dfhw_du ]; */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
