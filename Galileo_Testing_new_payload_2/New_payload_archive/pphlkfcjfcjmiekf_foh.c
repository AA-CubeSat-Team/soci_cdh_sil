/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: pphlkfcjfcjmiekf_foh.c
 *
 * Code generated for Simulink model 'gnc2_lib0'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 17:57:19 2019
 */

#include "rtwtypes.h"
#include <string.h>
#include "baaicbaafcbiglfk_linspace.h"
#include "ecbagdjmpphdgdjm_deriv.h"
#include "fcbilfcbmohdjekn_eye.h"
#include "pphlkfcjfcjmiekf_foh.h"

/*
 * Function for MATLAB Function: '<S1>/SOLVE'
 * function [ EH,BE,ES,AR ] = foh( X,U,s,N,Nx,Nu,J )
 * FOH   first order hold discretization
 *
 *  FOH(X,U,s,N,J) Computes the matrices (A,B,S,Z) to numerically discretize
 *  a problem instance of SOAC about the most recent trajectory
 *  stored in X and U. Assumes a linear interpolation of the torque
 *  between control nodes, of which there are N.
 *
 *  These matrices give the first order Taylor series of the dynamics
 *  at the N time nodes dictated and correspond to a discrete time
 *  LTV system approximating the nonlinear dynamics.
 *
 *  Inputs:
 *    - X (N*Nx by 1) current state at each discrete node
 *    - U (N*Nu by 1) current control at each discrete node
 *    - s (1 by 1) current final time
 *    - N (1 by 1) number of discrete time nodes
 *    - J (3 by 3) spacecraft inertia matrix
 *  Outputs:
 *    - EH (N*Nx by N*Nx)
 *    - BE (N*Nu by N*Nu)
 *    - ES (N*Nx by 1)
 *    - ZE (N*Nx by 1)
 *
 *  T. Reynolds -- RAIN Lab
 */
void pphlkfcjfcjmiekf_foh(const real_T X_0[100], const real_T U[30], real_T s,
  const real_T J[9], real_T EH[10000], real_T BE[3000], real_T ES[100], real_T
  AR[100])
{
  real_T A0[100];
  real_T P0[190];
  real_T u[6];
  real_T tspan[10];
  real_T h;
  real_T k1[190];
  real_T k2[190];
  real_T k3[190];
  real_T k4[190];
  real_T Ad[100];
  int32_T k;
  int32_T b_k;
  real_T e_y;
  real_T P0_0[190];
  int32_T i;
  int32_T i_0;
  int32_T i_1;
  int32_T i_2;
  real_T Ad_0[10];
  real_T *c_y;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%% SUPPORT FUNCTIONS %%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* '<S3>:1:129' len     = N-1; */
  /*  number of transition matrices */
  /* '<S3>:1:130' tau     = linspace(0,1,N); */
  /*  normalized time */
  /* '<S3>:1:131' Nsub    = 10; */
  /*  number of sub-interval points */
  /*  Set sizes for each discrete matrix */
  /* '<S3>:1:134' EH          = zeros(Nx*(len+1),Nx*(len+1)); */
  memset(&EH[0], 0, 10000U * sizeof(real_T));

  /* '<S3>:1:135' EH(1:Nx,1:Nx) = eye(Nx); */
  fcbilfcbmohdjekn_eye(A0);
  for (i = 0; i < 10; i++) {
    memcpy(&EH[i * 100], &A0[i * 10], 10U * sizeof(real_T));
  }

  /* '<S3>:1:136' BE          = zeros(Nx*(len+1),Nu*(len+1)); */
  memset(&BE[0], 0, 3000U * sizeof(real_T));

  /* '<S3>:1:137' ES          = zeros(Nx*(len+1),1); */
  /* '<S3>:1:138' AR          = zeros(Nx*(len+1),1); */
  memset(&ES[0], 0, 100U * sizeof(real_T));
  memset(&AR[0], 0, 100U * sizeof(real_T));

  /*  Initial conditions */
  /* '<S3>:1:141' A0  = eye(Nx); */
  fcbilfcbmohdjekn_eye(A0);

  /* '<S3>:1:142' B0p = zeros(Nx*Nu,1); */
  /* '<S3>:1:143' B0m = zeros(Nx*Nu,1); */
  /* '<S3>:1:144' S0  = zeros(Nx,1); */
  /* '<S3>:1:145' R0  = zeros(Nx,1); */
  /* '<S3>:1:147' for k = 1:len */
  for (k = 0; k < 9; k++) {
    /*  (re)define initial condition for integration */
    /* '<S3>:1:150' xF = X(Nx*(k-1)+(1:Nx)); */
    /* '<S3>:1:151' P0 = [xF(:); A0(:); B0p(:); B0m(:); S0(:); R0(:)]; */
    i = 10 * k;
    memcpy(&P0[0], &X_0[i], 10U * sizeof(real_T));
    memcpy(&P0[10], &A0[0], 100U * sizeof(real_T));
    for (i = 0; i < 30; i++) {
      P0[i + 110] = 0.0;
      P0[i + 140] = 0.0;
    }

    for (i = 0; i < 10; i++) {
      P0[i + 170] = 0.0;
      P0[i + 180] = 0.0;
    }

    /* '<S3>:1:153' um = U(Nu*(k-1)+(1:Nu)); */
    /* '<S3>:1:154' up = U(Nu*k+(1:Nu)); */
    /* '<S3>:1:155' u  = [reshape(um,Nu,1) reshape(up,Nu,1)]; */
    u[0] = U[(int8_T)(3 * k)];
    u[3] = U[(int8_T)((1 + k) * 3)];
    u[1] = U[(int8_T)(3 * k) + 1];
    u[4] = U[(int8_T)((1 + k) * 3) + 1];
    u[2] = U[(int8_T)(3 * k) + 2];
    u[5] = U[(int8_T)((1 + k) * 3) + 2];

    /* '<S3>:1:156' tspan = linspace(tau(k), tau(k+1), N); */
    baaicbaafcbiglfk_linspace(0.1111111111111111 * (real_T)k, (1.0 + (real_T)k) *
      0.1111111111111111, tspan);

    /* '<S3>:1:158' for k_ = 1:Nsub-1 */
    for (b_k = 0; b_k < 9; b_k++) {
      /* '<S3>:1:160' tk      = tspan(k_); */
      /* '<S3>:1:161' tkp1    = tspan(k_+1); */
      /* '<S3>:1:162' h       = tkp1-tk; */
      h = tspan[1 + b_k] - tspan[b_k];

      /* '<S3>:1:164' k1 = deriv(tk    ,P0       ,u,tspan,s,J); */
      ecbagdjmpphdgdjm_deriv(tspan[b_k], P0, u, tspan, s, J, k1);

      /* '<S3>:1:165' k2 = deriv(tk+h/2,P0+h/2*k1,u,tspan,s,J); */
      e_y = h / 2.0;
      for (i = 0; i < 190; i++) {
        P0_0[i] = e_y * k1[i] + P0[i];
      }

      ecbagdjmpphdgdjm_deriv(h / 2.0 + tspan[b_k], P0_0, u, tspan, s, J, k2);

      /* '<S3>:1:166' k3 = deriv(tk+h/2,P0+h/2*k2,u,tspan,s,J); */
      e_y = h / 2.0;
      for (i = 0; i < 190; i++) {
        P0_0[i] = e_y * k2[i] + P0[i];
      }

      ecbagdjmpphdgdjm_deriv(h / 2.0 + tspan[b_k], P0_0, u, tspan, s, J, k3);

      /* '<S3>:1:167' k4 = deriv(tk+h  ,P0+h*k3  ,u,tspan,s,J); */
      for (i = 0; i < 190; i++) {
        P0_0[i] = h * k3[i] + P0[i];
      }

      ecbagdjmpphdgdjm_deriv(tspan[b_k] + h, P0_0, u, tspan, s, J, k4);

      /* '<S3>:1:169' P0 = (P0+h/6*(k1+2*k2+2*k3+k4)); */
      h /= 6.0;
      for (i = 0; i < 190; i++) {
        P0[i] += (((2.0 * k2[i] + k1[i]) + 2.0 * k3[i]) + k4[i]) * h;
      }
    }

    /* '<S3>:1:172' AF  = P0(Nx+1:Nx*(Nx+1)); */
    /* '<S3>:1:173' BFp = P0(Nx*(Nx+1)+1:Nx*(Nx+Nu+1)); */
    /* '<S3>:1:174' BFm = P0(Nx*(Nx+Nu+1)+1:Nx*(Nx+2*Nu+1)); */
    /* '<S3>:1:175' SF  = P0(Nx*(Nx+2*Nu+1)+1:Nx*(Nx+2*Nu+2)); */
    /* '<S3>:1:176' RF  = P0(Nx*(Nx+2*Nu+2)+1:Nx*(Nx+2*Nu+3)); */
    /*  Fill up matrices */
    /* '<S3>:1:179' Ad  = reshape(AF,Nx,Nx); */
    memcpy(&Ad[0], &P0[10], 100U * sizeof(real_T));

    /* '<S3>:1:180' EH(Nx*k+(1:Nx),Nx*(k-1)+(1:Nx)) = Ad; */
    i = (1 + k) * 10;
    i_0 = 10 * k;
    for (i_1 = 0; i_1 < 10; i_1++) {
      memcpy(&EH[(i_1 * 100 + i) + i_0 * 100], &Ad[i_1 * 10], 10U * sizeof
             (real_T));
    }

    /* '<S3>:1:181' BE(Nx*k+(1:Nx),Nu*(k-1)+(1:Nu)) = Ad*reshape(BFm,Nx,Nu); */
    c_y = &P0[140];
    i = (1 + k) * 10;
    i_0 = 3 * k;
    for (i_1 = 0; i_1 < 10; i_1++) {
      for (i_2 = 0; i_2 < 3; i_2++) {
        BE[(i_1 + i) + 100 * (i_2 + i_0)] = 0.0;
        for (b_k = 0; b_k < 10; b_k++) {
          BE[(i_1 + i) + 100 * (i_2 + i_0)] = BE[((i_2 + i_0) * 100 + i_1) + i]
            + Ad[10 * b_k + i_1] * c_y[10 * i_2 + b_k];
        }
      }
    }

    /* '<S3>:1:182' BE(Nx*k+(1:Nx),Nu*k+(1:Nu))     = Ad*reshape(BFp,Nx,Nu); */
    c_y = &P0[110];
    i = (1 + k) * 10;
    i_0 = (1 + k) * 3;

    /* '<S3>:1:183' ES(Nx*k+(1:Nx))                 = Ad*reshape(SF,Nx,1); */
    for (b_k = 0; b_k < 10; b_k++) {
      for (i_1 = 0; i_1 < 3; i_1++) {
        BE[(b_k + i) + 100 * (i_1 + i_0)] = 0.0;
        for (i_2 = 0; i_2 < 10; i_2++) {
          BE[(b_k + i) + 100 * (i_1 + i_0)] = BE[((i_1 + i_0) * 100 + b_k) + i]
            + Ad[10 * i_2 + b_k] * c_y[10 * i_1 + i_2];
        }
      }

      tspan[b_k] = P0[b_k + 170];
    }

    i = (1 + k) * 10;
    for (i_0 = 0; i_0 < 10; i_0++) {
      Ad_0[i_0] = 0.0;
      for (i_1 = 0; i_1 < 10; i_1++) {
        Ad_0[i_0] += Ad[10 * i_1 + i_0] * tspan[i_1];
      }

      ES[i_0 + i] = Ad_0[i_0];
    }

    /* '<S3>:1:184' AR(Nx*k+(1:Nx))                 = Ad*reshape(RF,Nx,1); */
    memcpy(&tspan[0], &P0[180], 10U * sizeof(real_T));
    i = (1 + k) * 10;
    for (i_0 = 0; i_0 < 10; i_0++) {
      Ad_0[i_0] = 0.0;
      for (i_1 = 0; i_1 < 10; i_1++) {
        Ad_0[i_0] += Ad[10 * i_1 + i_0] * tspan[i_1];
      }

      AR[i_0 + i] = Ad_0[i_0];
    }
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
