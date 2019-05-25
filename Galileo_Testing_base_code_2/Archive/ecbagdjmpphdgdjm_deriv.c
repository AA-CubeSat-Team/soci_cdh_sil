/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ecbagdjmpphdgdjm_deriv.c
 *
 * Code generated for Simulink model 'gnc2_lib'.
 *
 * Model version                  : 1.5
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 14:12:23 2019
 */

#include "rtwtypes.h"
#include <string.h>
#include "aieknglfdbimpppp_mldivide.h"
#include "hdjmdbaaiecbkfcj_get_f_vals.h"
#include "phlnfknoohlfohdj_mldivide.h"
#include "ecbagdjmpphdgdjm_deriv.h"

/*
 * Function for MATLAB Function: '<S1>/SOLVE'
 * function DX = deriv(t,X,u,tspan,s,J)
 */
void ecbagdjmpphdgdjm_deriv(real_T t, const real_T X_1[190], const real_T u[6],
  const real_T tspan[10], real_T s, const real_T J[9], real_T DX[190])
{
  real_T Phi[100];
  real_T Bdp_dot[30];
  real_T Bdm_dot[30];
  real_T Sd_dot[10];
  real_T Zd_dot[10];
  real_T f[10];
  real_T A[100];
  int32_T i;
  real_T s_0[100];
  int32_T i_0;
  int32_T i_1;

  /* '<S3>:1:192' Nx = 10; */
  /* '<S3>:1:193' x   = X(1:Nx); */
  /* '<S3>:1:195' [f,A,Bp,Bm,Z] = get_f_vals(t,x,u,tspan,J); */
  hdjmdbaaiecbkfcj_get_f_vals(t, &X_1[0], u, tspan, J, f, A, Bdp_dot, Bdm_dot,
    Zd_dot);

  /* '<S3>:1:197' Phi = reshape(X(Nx+1:Nx*(Nx+1)),size(A)); */
  memcpy(&Phi[0], &X_1[10], 100U * sizeof(real_T));

  /* '<S3>:1:199' xdot        = s*f; */
  /* '<S3>:1:200' Phi_dot     = (s*A)*Phi; */
  /* '<S3>:1:201' Bdp_dot     = Phi\(s*Bp); */
  for (i = 0; i < 30; i++) {
    Bdp_dot[i] *= s;
  }

  aieknglfdbimpppp_mldivide(Phi, Bdp_dot);

  /* '<S3>:1:202' Bdm_dot     = Phi\(s*Bm); */
  for (i = 0; i < 30; i++) {
    Bdm_dot[i] *= s;
  }

  aieknglfdbimpppp_mldivide(Phi, Bdm_dot);

  /* '<S3>:1:203' Sd_dot      = Phi\f; */
  memcpy(&Sd_dot[0], &f[0], 10U * sizeof(real_T));
  phlnfknoohlfohdj_mldivide(Phi, Sd_dot);

  /* '<S3>:1:204' Zd_dot      = Phi\(s*Z); */
  for (i = 0; i < 10; i++) {
    Zd_dot[i] *= s;
  }

  phlnfknoohlfohdj_mldivide(Phi, Zd_dot);

  /* '<S3>:1:206' DX      = [ xdot(:); Phi_dot(:); Bdp_dot(:);... */
  /* '<S3>:1:207'                 Bdm_dot(:); Sd_dot(:); Zd_dot(:)]; */
  for (i = 0; i < 10; i++) {
    for (i_0 = 0; i_0 < 10; i_0++) {
      s_0[i + 10 * i_0] = 0.0;
      for (i_1 = 0; i_1 < 10; i_1++) {
        s_0[i + 10 * i_0] += A[10 * i_1 + i] * s * Phi[10 * i_0 + i_1];
      }
    }

    DX[i] = s * f[i];
  }

  memcpy(&DX[10], &s_0[0], 100U * sizeof(real_T));
  for (i = 0; i < 30; i++) {
    DX[i + 110] = Bdp_dot[i];
    DX[i + 140] = Bdm_dot[i];
  }

  for (i = 0; i < 10; i++) {
    DX[i + 170] = Sd_dot[i];
    DX[i + 180] = Zd_dot[i];
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
