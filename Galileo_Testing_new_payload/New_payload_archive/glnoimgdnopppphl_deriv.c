/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: glnoimgdnopppphl_deriv.c
 *
 * Code generated for Simulink model 'gnc2_interface_lib0'.
 *
 * Model version                  : 1.10
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Sat May 25 15:05:05 2019
 */

#include "rtwtypes.h"
#include <math.h>
#include "ohdbngdjimopdbim_mldivide.h"
#include "glnoimgdnopppphl_deriv.h"

/*
 * Function for MATLAB Function: '<S1>/INTERP'
 * function dx = deriv(t,x,u,J,tspan)
 *  States
 */
void glnoimgdnopppphl_deriv(real_T t, const real_T x[10], const real_T u[6],
  const real_T J[9], const real_T tspan[2], real_T dx[10])
{
  real_T q[4];
  real_T lam_km;
  real_T u_t[3];
  real_T scale;
  real_T absxk;
  real_T b_t;
  static const int8_T b[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  real_T u_t_0[3];
  int32_T i;
  real_T tmp[9];
  real_T J_0[3];
  real_T tmp_0[9];
  real_T q_0[12];
  real_T tmp_1[12];

  /* '<S4>:1:69' q   = x(1:4)./norm(x(1:4)); */
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

  /* '<S4>:1:70' q0  = q(1); */
  /* '<S4>:1:71' qv  = q(2:4); */
  /* '<S4>:1:72' w   = x(5:7); */
  /* '<S4>:1:73' hw  = x(8:10); */
  /*  interpolate u_opt at time t */
  /* '<S4>:1:76' tkm     = tspan(1); */
  /* '<S4>:1:77' tkp     = tspan(2); */
  /* '<S4>:1:78' lam_km  = (tkp - t)/(tkp - tkm); */
  lam_km = (tspan[1] - t) / (tspan[1] - tspan[0]);

  /* '<S4>:1:79' lam_kp  = (t - tkm)/(tkp - tkm); */
  scale = (t - tspan[0]) / (tspan[1] - tspan[0]);

  /* '<S4>:1:80' u_t     = lam_km .* u(:,1) + lam_kp .* u(:,2); */
  /*  Kinematics & Dynamics */
  /* '<S4>:1:83' fq  = 0.5 * [ -qv'; skew(qv)+q0*eye(3) ] * w; */
  /* 'skew:4' cross = [0 -a(3) a(2); */
  /* 'skew:5'          a(3) 0 -a(1); */
  /* 'skew:6'         -a(2) a(1) 0]; */
  /* '<S4>:1:84' fw  = J\(-u_t - skew(w) * (J*w + hw)); */
  /* 'skew:4' cross = [0 -a(3) a(2); */
  /* 'skew:5'          a(3) 0 -a(1); */
  /* 'skew:6'         -a(2) a(1) 0]; */
  /* '<S4>:1:85' fhw = u_t; */
  /* '<S4>:1:87' dx = [ fq; fw; fhw ]; */
  tmp[0] = 0.0;
  tmp[3] = -x[6];
  tmp[6] = x[5];
  tmp[1] = x[6];
  tmp[4] = 0.0;
  tmp[7] = -x[4];
  tmp[2] = -x[5];
  tmp[5] = x[4];
  tmp[8] = 0.0;
  for (i = 0; i < 3; i++) {
    u_t[i] = u[3 + i] * scale + lam_km * u[i];
    J_0[i] = ((J[i + 3] * x[5] + J[i] * x[4]) + J[i + 6] * x[6]) + x[7 + i];
  }

  for (i = 0; i < 3; i++) {
    u_t_0[i] = -u_t[i] - ((tmp[i + 3] * J_0[1] + tmp[i] * J_0[0]) + tmp[i + 6] *
                          J_0[2]);
  }

  ohdbngdjimopdbim_mldivide(J, u_t_0, J_0);
  scale = q[0];
  tmp_0[0] = 0.0;
  tmp_0[3] = -q[3];
  tmp_0[6] = q[2];
  tmp_0[1] = q[3];
  tmp_0[4] = 0.0;
  tmp_0[7] = -q[1];
  tmp_0[2] = -q[2];
  tmp_0[5] = q[1];
  tmp_0[8] = 0.0;
  for (i = 0; i < 3; i++) {
    q_0[i << 2] = -q[1 + i];
    q_0[1 + (i << 2)] = (real_T)b[3 * i] * scale + tmp_0[3 * i];
    q_0[2 + (i << 2)] = (real_T)b[3 * i + 1] * scale + tmp_0[3 * i + 1];
    q_0[3 + (i << 2)] = (real_T)b[3 * i + 2] * scale + tmp_0[3 * i + 2];
    tmp_1[i << 2] = q_0[i << 2] * 0.5;
    tmp_1[1 + (i << 2)] = q_0[(i << 2) + 1] * 0.5;
    tmp_1[2 + (i << 2)] = q_0[(i << 2) + 2] * 0.5;
    tmp_1[3 + (i << 2)] = q_0[(i << 2) + 3] * 0.5;
  }

  for (i = 0; i < 4; i++) {
    dx[i] = tmp_1[i + 8] * x[6] + (tmp_1[i + 4] * x[5] + tmp_1[i] * x[4]);
  }

  dx[4] = J_0[0];
  dx[7] = u_t[0];
  dx[5] = J_0[1];
  dx[8] = u_t[1];
  dx[6] = J_0[2];
  dx[9] = u_t[2];
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
