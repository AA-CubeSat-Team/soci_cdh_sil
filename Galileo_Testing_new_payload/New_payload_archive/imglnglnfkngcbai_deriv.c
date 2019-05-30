/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: imglnglnfkngcbai_deriv.c
 *
 * Code generated for Simulink model 'gnc2_interface_lib0'.
 *
 * Model version                  : 1.8
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May 24 16:44:58 2019
 */

#include "rtwtypes.h"
#include <math.h>
#include "ohdbngdjimopdbim_mldivide.h"
#include "imglnglnfkngcbai_deriv.h"

/*
 * Function for MATLAB Function: '<S1>/INTERP'
 * function dx = deriv(t,x,u,J,tspan)
 *  States
 */
void imglnglnfkngcbai_deriv(real_T t, const real_T x[10], const real_T u[6],
  const real_T J[9], const real_T tspan[2], real_T dx[10])
{
  real_T q[4];
  real_T hb[3];
  real_T w[3];
  real_T lam_km;
  real_T u_tau[3];
  real_T scale;
  real_T absxk;
  real_T b_t;
  static const int8_T b[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  int32_T i;
  real_T tmp[9];
  real_T q_0[12];
  real_T tmp_0[12];
  real_T tmp_1[9];

  /* '<S4>:1:57' q   = x(1:4)./norm(x(1:4)); */
  scale = 2.2250738585072014E-308;
  absxk = fabs(x[0]);
  if (absxk > 2.2250738585072014E-308) {
    lam_km = 1.0;
    scale = absxk;
  } else {
    b_t = absxk / 2.2250738585072014E-308;
    lam_km = b_t * b_t;
  }

  absxk = fabs(x[1]);
  if (absxk > scale) {
    b_t = scale / absxk;
    lam_km = lam_km * b_t * b_t + 1.0;
    scale = absxk;
  } else {
    b_t = absxk / scale;
    lam_km += b_t * b_t;
  }

  absxk = fabs(x[2]);
  if (absxk > scale) {
    b_t = scale / absxk;
    lam_km = lam_km * b_t * b_t + 1.0;
    scale = absxk;
  } else {
    b_t = absxk / scale;
    lam_km += b_t * b_t;
  }

  absxk = fabs(x[3]);
  if (absxk > scale) {
    b_t = scale / absxk;
    lam_km = lam_km * b_t * b_t + 1.0;
    scale = absxk;
  } else {
    b_t = absxk / scale;
    lam_km += b_t * b_t;
  }

  lam_km = scale * sqrt(lam_km);
  q[0] = x[0] / lam_km;
  q[1] = x[1] / lam_km;
  q[2] = x[2] / lam_km;
  q[3] = x[3] / lam_km;

  /* '<S4>:1:58' q0  = q(1); */
  /* '<S4>:1:59' qv  = q(2:4); */
  /* '<S4>:1:60' hb  = x(5:7); */
  /* '<S4>:1:61' hw  = x(8:10); */
  /* '<S4>:1:62' w   = J\hb; */
  ohdbngdjimopdbim_mldivide(J, &x[4], w);

  /*  interpolate u_opt at time t */
  /* '<S4>:1:65' tkm     = tspan(1); */
  /* '<S4>:1:66' tkp     = tspan(2); */
  /* '<S4>:1:67' lam_km  = (tkp - t)/(tkp - tkm); */
  lam_km = (tspan[1] - t) / (tspan[1] - tspan[0]);

  /* '<S4>:1:68' lam_kp  = (t - tkm)/(tkp - tkm); */
  scale = (t - tspan[0]) / (tspan[1] - tspan[0]);

  /*  Interpolate u */
  /* '<S4>:1:71' u_tau = lam_km .* u(:,1) + lam_kp .* u(:,2); */
  /*  Kinematics & Dynamics */
  /* '<S4>:1:74' fq  = 0.5 * [ -qv'; skew(qv)+q0*eye(3) ] * w; */
  /* 'skew:4' cross = [0 -a(3) a(2); */
  /* 'skew:5'          a(3) 0 -a(1); */
  /* 'skew:6'         -a(2) a(1) 0]; */
  /* '<S4>:1:75' fhb = -u_tau + skew(hb+hw) * w; */
  /* 'skew:4' cross = [0 -a(3) a(2); */
  /* 'skew:5'          a(3) 0 -a(1); */
  /* 'skew:6'         -a(2) a(1) 0]; */
  /* '<S4>:1:76' fhw = u_tau; */
  /* '<S4>:1:78' dx = [ fq; fhb; fhw ]; */
  absxk = q[0];
  tmp[0] = 0.0;
  tmp[3] = -q[3];
  tmp[6] = q[2];
  tmp[1] = q[3];
  tmp[4] = 0.0;
  tmp[7] = -q[1];
  tmp[2] = -q[2];
  tmp[5] = q[1];
  tmp[8] = 0.0;
  for (i = 0; i < 3; i++) {
    u_tau[i] = u[3 + i] * scale + lam_km * u[i];
    hb[i] = x[i + 4] + x[i + 7];
    q_0[i << 2] = -q[1 + i];
    q_0[1 + (i << 2)] = (real_T)b[3 * i] * absxk + tmp[3 * i];
    q_0[2 + (i << 2)] = (real_T)b[3 * i + 1] * absxk + tmp[3 * i + 1];
    q_0[3 + (i << 2)] = (real_T)b[3 * i + 2] * absxk + tmp[3 * i + 2];
    tmp_0[i << 2] = q_0[i << 2] * 0.5;
    tmp_0[1 + (i << 2)] = q_0[(i << 2) + 1] * 0.5;
    tmp_0[2 + (i << 2)] = q_0[(i << 2) + 2] * 0.5;
    tmp_0[3 + (i << 2)] = q_0[(i << 2) + 3] * 0.5;
  }

  tmp_1[0] = 0.0;
  tmp_1[3] = -hb[2];
  tmp_1[6] = hb[1];
  tmp_1[1] = hb[2];
  tmp_1[4] = 0.0;
  tmp_1[7] = -hb[0];
  tmp_1[2] = -hb[1];
  tmp_1[5] = hb[0];
  tmp_1[8] = 0.0;
  for (i = 0; i < 4; i++) {
    q[i] = tmp_0[i + 8] * w[2] + (tmp_0[i + 4] * w[1] + tmp_0[i] * w[0]);
  }

  for (i = 0; i < 3; i++) {
    hb[i] = ((tmp_1[i + 3] * w[1] + tmp_1[i] * w[0]) + tmp_1[i + 6] * w[2]) +
      -u_tau[i];
  }

  dx[0] = q[0];
  dx[1] = q[1];
  dx[2] = q[2];
  dx[3] = q[3];
  dx[4] = hb[0];
  dx[7] = u_tau[0];
  dx[5] = hb[1];
  dx[8] = u_tau[1];
  dx[6] = hb[2];
  dx[9] = u_tau[2];
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
