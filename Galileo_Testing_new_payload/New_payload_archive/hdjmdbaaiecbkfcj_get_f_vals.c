/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: hdjmdbaaiecbkfcj_get_f_vals.c
 *
 * Code generated for Simulink model 'gnc2_lib0'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 17:57:19 2019
 */

#include "rtwtypes.h"
#include "bimghlngphlfpphl_Q_linearize.h"
#include "hdjmdbaaiecbkfcj_get_f_vals.h"

/*
 * Function for MATLAB Function: '<S1>/SOLVE'
 * function [f,A,Bp,Bm,Z] = get_f_vals(t,x,u,tspan,J)
 */
void hdjmdbaaiecbkfcj_get_f_vals(real_T t, const real_T x[10], const real_T u[6],
  const real_T tspan[10], const real_T J[9], real_T f[10], real_T A[100], real_T
  Bp[30], real_T Bm[30], real_T Z[10])
{
  real_T lam_km;
  real_T lam_kp;
  real_T u_tau[3];
  static const int8_T b[30] = { 0, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, -1,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 1 };

  int32_T i;
  real_T A_0[100];
  real_T A_1[10];
  real_T b_0[10];
  int32_T i_0;

  /* '<S3>:1:212' tkm     = tspan(1); */
  /* '<S3>:1:213' tkp     = tspan(end); */
  /* '<S3>:1:214' lam_km  = (tkp - t)/(tkp - tkm); */
  lam_km = (tspan[9] - t) / (tspan[9] - tspan[0]);

  /* '<S3>:1:215' lam_kp  = (t - tkm)/(tkp - tkm); */
  lam_kp = (t - tspan[0]) / (tspan[9] - tspan[0]);

  /*  Interpolate u */
  /* '<S3>:1:218' u_tau = lam_km .* u(:,1) + lam_kp .* u(:,2); */
  u_tau[0] = lam_km * u[0] + lam_kp * u[3];
  u_tau[1] = lam_km * u[1] + lam_kp * u[4];
  u_tau[2] = lam_km * u[2] + lam_kp * u[5];

  /*  compute jacobian matrices */
  /* '<S3>:1:221' [A,B,f] = Q_linearize(t,x,u_tau,J); */
  bimghlngphlfpphl_Q_linearize(x, u_tau, J, A, f);

  /* '<S3>:1:223' Bp  = lam_kp*B; */
  /* '<S3>:1:224' Bm  = lam_km*B; */
  for (i = 0; i < 30; i++) {
    Bp[i] = lam_kp * (real_T)b[i];
    Bm[i] = lam_km * (real_T)b[i];
  }

  /*  compute z */
  /* '<S3>:1:227' Z   = - A*x - B*u_tau; */
  for (i = 0; i < 10; i++) {
    for (i_0 = 0; i_0 < 10; i_0++) {
      A_0[i_0 + 10 * i] = -A[10 * i + i_0];
    }
  }

  for (i = 0; i < 10; i++) {
    A_1[i] = 0.0;
    for (i_0 = 0; i_0 < 10; i_0++) {
      A_1[i] += A_0[10 * i_0 + i] * x[i_0];
    }

    b_0[i] = 0.0;
    b_0[i] += (real_T)b[i] * u_tau[0];
    b_0[i] += (real_T)b[i + 10] * u_tau[1];
    b_0[i] += (real_T)b[i + 20] * u_tau[2];
    Z[i] = A_1[i] - b_0[i];
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
