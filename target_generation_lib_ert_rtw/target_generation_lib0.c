/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: target_generation_lib0.c
 *
 * Code generated for Simulink model 'target_generation_lib0'.
 *
 * Model version                  : 1.39
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Fri May  3 16:50:56 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "target_generation_lib0.h"

/* External inputs (root inport signals with auto storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with auto storage) */
ExtY rtY;

/* Real-time model */
RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/* Forward declaration for local functions */
static real_T norm(const real_T x[3]);

/* Function for MATLAB Function: '<S1>/MATLAB Function2' */
static real_T norm(const real_T x[3])
{
  real_T y;
  real_T scale;
  real_T absxk;
  real_T t;
  scale = 2.2250738585072014E-308;
  absxk = fabs(x[0]);
  if (absxk > 2.2250738585072014E-308) {
    y = 1.0;
    scale = absxk;
  } else {
    t = absxk / 2.2250738585072014E-308;
    y = t * t;
  }

  absxk = fabs(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  absxk = fabs(x[2]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  return scale * sqrt(y);
}

/* Model step function */
void target_generation_lib0_step(void)
{
  int32_T flag;
  real_T C_cmd[9];
  real_T tr;
  static const int8_T a[9] = { 0, 0, -1, 1, 0, 0, 0, -1, 0 };

  static const int8_T b_a[9] = { 0, -1, 0, 1, 0, 0, 0, 0, 1 };

  real_T sc2gs_unit[3];
  real_T sc2gs_unit_0[3];
  real_T sc2gs_unit_1[9];
  int32_T i;
  int32_T i_0;
  real_T sc2gs_unit_idx_1;
  real_T sc2sun_unit_idx_2;
  real_T sc2gs_unit_idx_2;
  real_T sc2sun_unit_idx_1;
  real_T sc2sun_unit_idx_0;
  real_T sc2gs_unit_idx_0;
  real_T Yti_idx_0;
  real_T vel_unit_idx_1;
  real_T vel_unit_idx_2;
  real_T vel_unit_idx_0;

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Inport: '<Root>/sc_mode'
   */
  /*  FSW Target Generation Library */
  /*  */
  /*  Computes desired quaternion and angular velocity depending on the sc_mode */
  /*    mode_logic.bdot             = 1; */
  /*    mode_logic.desat_eclipse    = 2; */
  /*    mode_logic.point            = 3; */
  /*        point.velocity          = 31; */
  /*        point.ground            = 32; */
  /*        point.MPC               = 33; */
  /*    mode_logic.low_power        = 4; */
  /*  */
  /*    RAIN-SAT -- T. Reynolds 1.15.18 */
  /* MATLAB Function 'target_generation_lib/MATLAB Function': '<S2>:1' */
  /*  Constants */
  /* '<S2>:1:17' XSPDA   = 86400; */
  /*  seconds per day */
  /* '<S2>:1:18' DE2RA   = 0.174532925e-1; */
  /*  radians/degree */
  /* '<S2>:1:19' n_orb   = [ 0.0; 0.0; orbit_tle(9)*2*pi/XSPDA ]; */
  /*  mean motion [rad/s] */
  /* '<S2>:1:20' INC     = orbit_tle(4)*DE2RA; */
  /*  inclination [rad] */
  /* '<S2>:1:21' RAAN    = orbit_tle(5)*DE2RA; */
  /*  right ascension of ascending node [rad] */
  /* '<S2>:1:22' AOP     = orbit_tle(7)*DE2RA; */
  /*  argument of perigee [rad] */
  /* '<S2>:1:24' C_orb2eci   = rot3(-RAAN)*rot1(-INC)*rot3(-AOP); */
  /* '<S2>:1:25' n_eci       = C_orb2eci*n_orb; */
  /* '<S2>:1:27' C_eci2body  = quat2DCM(sc_quat); */
  /* '<S2>:1:55' q0  = q(1); */
  /* '<S2>:1:56' qv  = reshape(q(2:4),3,1); */
  /* '<S2>:1:58' DCM     = (2*q0^2 - 1)*eye(3) + 2*(qv*qv') - 2*q0*skew(qv); */
  /* 'skew:4' cross = [0 -a(3) a(2); */
  /* 'skew:5'          a(3) 0 -a(1); */
  /* 'skew:6'         -a(2) a(1) 0]; */
  /* '<S2>:1:28' n_body      = C_eci2body'*n_eci; */
  /* '<S2>:1:30' if( sc_mode == 31 || sc_mode == 32 ) */
  if ((rtU.sc_mode == 31.0) || (rtU.sc_mode == 32.0)) {
    /* Outport: '<Root>/omega_cmd_radps' */
    /*  Commanded Angular Velocity */
    /* '<S2>:1:32' omega_cmd   = zeros(3,1); */
    rtY.omega_cmd_radps[0] = 0.0;
    rtY.omega_cmd_radps[1] = 0.0;
    rtY.omega_cmd_radps[2] = 0.0;
  } else {
    /* Outport: '<Root>/omega_cmd_radps' */
    /* '<S2>:1:33' else */
    /*  Commanded Angular Velocity */
    /* '<S2>:1:35' omega_cmd   = zeros(3,1); */
    rtY.omega_cmd_radps[0] = 0.0;
    rtY.omega_cmd_radps[1] = 0.0;
    rtY.omega_cmd_radps[2] = 0.0;
  }

  /* End of MATLAB Function: '<S1>/MATLAB Function' */

  /* MATLAB Function: '<S1>/MATLAB Function2' incorporates:
   *  Inport: '<Root>/sc2gs_eci_unit'
   *  Inport: '<Root>/sc2sun_eci_unit'
   *  Inport: '<Root>/sc_mode'
   *  Inport: '<Root>/vel_eci_kmps'
   */
  /*  FSW Target Generation Library */
  /*  */
  /*  Computes desired quaternion and angular velocity depending on the sc_mode */
  /*    mode_logic.bdot             = 1; */
  /*    mode_logic.desat_eclipse    = 2; */
  /*    mode_logic.point            = 3; */
  /*        point.velocity          = 31; */
  /*        point.ground            = 32; */
  /*    mode_logic.low_power        = 4; */
  /*  */
  /*    RAIN-SAT -- T. Reynolds 7.7.18 */
  /* MATLAB Function 'target_generation_lib/MATLAB Function2': '<S3>:1' */
  /*  Constants */
  /* '<S3>:1:16' COM2    = [ 0.0; -1.0; 0.0 ]; */
  /*  COMM antenna boresight vector (F_body) */
  /* '<S3>:1:17' PPT     = [ 0.0; 0.0; -1.0 ]; */
  /*  thruster boresight vector (F_body) */
  /* '<S3>:1:18' SP      = [ 0.0; 1.0; 0.0 ]; */
  /*  solar panel boresight vector (F_body) */
  /* '<S3>:1:19' flag    = 0; */
  flag = 0;

  /* '<S3>:1:20' tol     = 1e-3; */
  /* '<S3>:1:21' Cx5     = [ 1 0 0; 0 cosd(5) sind(5); 0 -sind(5) cosd(5)]; */
  /*  Uncomment for testing only % */
  /*  PPT     = [0;1;2];     */
  /*  SP      = [1;3;0]; */
  /*  -------------------------- % */
  /*  Validity Checks */
  /* '<S3>:1:29' if( norm(vel_eci_kmps) < tol || norm(sc2sun_eci) < tol ... */
  /* '<S3>:1:30'                                                 || norm(sc2gs_eci) < tol ) */
  if ((norm(rtU.vel_eci_kmps) < 0.001) || (norm(rtU.sc2sun_eci_unit) < 0.001) ||
      (norm(rtU.sc2gs_eci_unit) < 0.001)) {
    /* '<S3>:1:31' vel_unit        = zeros(3,1); */
    /* '<S3>:1:32' sc2sun_unit     = zeros(3,1); */
    /* '<S3>:1:33' sc2gs_unit      = zeros(3,1); */
    vel_unit_idx_0 = 0.0;
    sc2sun_unit_idx_0 = 0.0;
    sc2gs_unit_idx_0 = 0.0;
    vel_unit_idx_1 = 0.0;
    sc2sun_unit_idx_1 = 0.0;
    sc2gs_unit_idx_1 = 0.0;
    vel_unit_idx_2 = 0.0;
    sc2sun_unit_idx_2 = 0.0;
    sc2gs_unit_idx_2 = 0.0;

    /* '<S3>:1:34' flag = -1; */
    flag = -1;
  } else {
    /* '<S3>:1:35' else */
    /*  Compute unit vectors */
    /* '<S3>:1:37' vel_unit    = vel_eci_kmps./norm(vel_eci_kmps); */
    tr = norm(rtU.vel_eci_kmps);
    vel_unit_idx_0 = rtU.vel_eci_kmps[0] / tr;
    vel_unit_idx_1 = rtU.vel_eci_kmps[1] / tr;
    vel_unit_idx_2 = rtU.vel_eci_kmps[2] / tr;

    /* '<S3>:1:38' sc2sun_unit = sc2sun_eci./norm(sc2sun_eci); */
    tr = norm(rtU.sc2sun_eci_unit);
    sc2sun_unit_idx_0 = rtU.sc2sun_eci_unit[0] / tr;
    sc2sun_unit_idx_1 = rtU.sc2sun_eci_unit[1] / tr;
    sc2sun_unit_idx_2 = rtU.sc2sun_eci_unit[2] / tr;

    /* '<S3>:1:39' sc2gs_unit  = sc2gs_eci./norm(sc2gs_eci); */
    tr = norm(rtU.sc2gs_eci_unit);
    sc2gs_unit_idx_0 = rtU.sc2gs_eci_unit[0] / tr;
    sc2gs_unit_idx_1 = rtU.sc2gs_eci_unit[1] / tr;
    sc2gs_unit_idx_2 = rtU.sc2gs_eci_unit[2] / tr;

    /*  Check for parallel unit vectors */
    /* '<S3>:1:41' if ( abs(dot(vel_unit,sc2sun_unit)) > 1-tol ... */
    /* '<S3>:1:42'                             || abs(dot(vel_unit,sc2gs_unit)) > 1-tol ... */
    /* '<S3>:1:43'                             || abs(dot(sc2sun_unit,sc2gs_unit)) > 1-tol ) */
    if ((fabs((vel_unit_idx_0 * sc2sun_unit_idx_0 + vel_unit_idx_1 *
               sc2sun_unit_idx_1) + vel_unit_idx_2 * sc2sun_unit_idx_2) > 0.999)
        || (fabs((vel_unit_idx_0 * sc2gs_unit_idx_0 + vel_unit_idx_1 *
                  sc2gs_unit_idx_1) + vel_unit_idx_2 * sc2gs_unit_idx_2) > 0.999)
        || (fabs((sc2sun_unit_idx_0 * sc2gs_unit_idx_0 + sc2sun_unit_idx_1 *
                  sc2gs_unit_idx_1) + sc2sun_unit_idx_2 * sc2gs_unit_idx_2) >
            0.999)) {
      /* '<S3>:1:44' flag = -1; */
      flag = -1;
    }
  }

  /*  Main Code */
  /* '<S3>:1:49' if( sc_mode == 31 && flag == 0 ) */
  if ((rtU.sc_mode == 31.0) && (flag == 0)) {
    /*  Body vectors */
    /* '<S3>:1:52' B1      = PPT; */
    /* '<S3>:1:53' B2      = SP; */
    /* '<S3>:1:54' Xtb     = B1; */
    /* '<S3>:1:55' Ytb     = cross(B1,B2)/norm(cross(B1,B2)); */
    /* '<S3>:1:56' Ztb     = cross(B1,Ytb)/norm(cross(B1,Ytb)); */
    /*  Inertial vectors */
    /* '<S3>:1:59' S1      = vel_unit; */
    /* '<S3>:1:60' S2      = sc2sun_unit; */
    /* '<S3>:1:61' Xti     = S1; */
    /* '<S3>:1:62' Yti     = cross(S1,S2)/norm(cross(S1,S2)); */
    sc2gs_unit_0[0] = vel_unit_idx_1 * sc2sun_unit_idx_2 - vel_unit_idx_2 *
      sc2sun_unit_idx_1;
    sc2gs_unit_0[1] = vel_unit_idx_2 * sc2sun_unit_idx_0 - vel_unit_idx_0 *
      sc2sun_unit_idx_2;
    sc2gs_unit_0[2] = vel_unit_idx_0 * sc2sun_unit_idx_1 - vel_unit_idx_1 *
      sc2sun_unit_idx_0;
    tr = norm(sc2gs_unit_0);
    Yti_idx_0 = (vel_unit_idx_1 * sc2sun_unit_idx_2 - vel_unit_idx_2 *
                 sc2sun_unit_idx_1) / tr;
    sc2sun_unit_idx_2 = (vel_unit_idx_2 * sc2sun_unit_idx_0 - vel_unit_idx_0 *
                         sc2sun_unit_idx_2) / tr;
    sc2sun_unit_idx_0 = (vel_unit_idx_0 * sc2sun_unit_idx_1 - vel_unit_idx_1 *
                         sc2sun_unit_idx_0) / tr;

    /* '<S3>:1:63' Zti     = cross(S1,Yti)/norm(cross(S1,Yti)); */
    sc2gs_unit[0] = vel_unit_idx_1 * sc2sun_unit_idx_0 - vel_unit_idx_2 *
      sc2sun_unit_idx_2;
    sc2gs_unit[1] = vel_unit_idx_2 * Yti_idx_0 - vel_unit_idx_0 *
      sc2sun_unit_idx_0;
    sc2gs_unit[2] = vel_unit_idx_0 * sc2sun_unit_idx_2 - vel_unit_idx_1 *
      Yti_idx_0;
    tr = norm(sc2gs_unit);

    /*  Stack vectors */
    /* '<S3>:1:66' Cb  = [Xtb, Ytb, Ztb]; */
    /* '<S3>:1:67' Ci  = [Xti, Yti, Zti]; */
    /*  Commanded DCM ( body to inertial ) */
    /* '<S3>:1:70' C_cmd   = Cb*Ci'; */
    sc2gs_unit_1[0] = vel_unit_idx_0;
    sc2gs_unit_1[1] = Yti_idx_0;
    sc2gs_unit_1[2] = (vel_unit_idx_1 * sc2sun_unit_idx_0 - vel_unit_idx_2 *
                       sc2sun_unit_idx_2) / tr;
    sc2gs_unit_1[3] = vel_unit_idx_1;
    sc2gs_unit_1[4] = sc2sun_unit_idx_2;
    sc2gs_unit_1[5] = (vel_unit_idx_2 * Yti_idx_0 - vel_unit_idx_0 *
                       sc2sun_unit_idx_0) / tr;
    sc2gs_unit_1[6] = vel_unit_idx_2;
    sc2gs_unit_1[7] = sc2sun_unit_idx_0;
    sc2gs_unit_1[8] = (vel_unit_idx_0 * sc2sun_unit_idx_2 - vel_unit_idx_1 *
                       Yti_idx_0) / tr;
    for (i_0 = 0; i_0 < 3; i_0++) {
      for (i = 0; i < 3; i++) {
        C_cmd[i + 3 * i_0] = 0.0;
        C_cmd[i + 3 * i_0] += sc2gs_unit_1[3 * i_0] * (real_T)a[i];
        C_cmd[i + 3 * i_0] += sc2gs_unit_1[3 * i_0 + 1] * (real_T)a[i + 3];
        C_cmd[i + 3 * i_0] += sc2gs_unit_1[3 * i_0 + 2] * (real_T)a[i + 6];
      }
    }
  } else if ((rtU.sc_mode == 32.0) && (flag == 0)) {
    /* '<S3>:1:72' elseif( sc_mode == 32 && flag == 0 ) */
    /*  Tilted so doesn't aling with COM2 -- chose a 5[deg] roll. */
    /* '<S3>:1:75' SP      = Cx5*[0;1;0]; */
    /*  Body */
    /* '<S3>:1:78' B1      = COM2; */
    /* '<S3>:1:79' B2      = SP./norm(SP); */
    /* '<S3>:1:80' Xtb     = B1; */
    /* '<S3>:1:81' Ytb     = cross(B1,B2)/norm(cross(B1,B2)); */
    /* '<S3>:1:82' Ztb     = cross(B1,Ytb)/norm(cross(B1,Ytb)); */
    /*  Inertial */
    /* '<S3>:1:85' S1      = sc2gs_unit; */
    /* '<S3>:1:86' S2      = sc2sun_unit; */
    /* '<S3>:1:87' Xti     = S1; */
    /* '<S3>:1:88' Yti     = cross(S1,S2)/norm(cross(S1,S2)); */
    sc2gs_unit_0[0] = sc2gs_unit_idx_1 * sc2sun_unit_idx_2 - sc2gs_unit_idx_2 *
      sc2sun_unit_idx_1;
    sc2gs_unit_0[1] = sc2gs_unit_idx_2 * sc2sun_unit_idx_0 - sc2gs_unit_idx_0 *
      sc2sun_unit_idx_2;
    sc2gs_unit_0[2] = sc2gs_unit_idx_0 * sc2sun_unit_idx_1 - sc2gs_unit_idx_1 *
      sc2sun_unit_idx_0;
    tr = norm(sc2gs_unit_0);
    Yti_idx_0 = (sc2gs_unit_idx_1 * sc2sun_unit_idx_2 - sc2gs_unit_idx_2 *
                 sc2sun_unit_idx_1) / tr;
    sc2sun_unit_idx_2 = (sc2gs_unit_idx_2 * sc2sun_unit_idx_0 - sc2gs_unit_idx_0
                         * sc2sun_unit_idx_2) / tr;
    sc2sun_unit_idx_0 = (sc2gs_unit_idx_0 * sc2sun_unit_idx_1 - sc2gs_unit_idx_1
                         * sc2sun_unit_idx_0) / tr;

    /* '<S3>:1:89' Zti     = cross(S1,Yti)/norm(cross(S1,Yti)); */
    sc2gs_unit[0] = sc2gs_unit_idx_1 * sc2sun_unit_idx_0 - sc2gs_unit_idx_2 *
      sc2sun_unit_idx_2;
    sc2gs_unit[1] = sc2gs_unit_idx_2 * Yti_idx_0 - sc2gs_unit_idx_0 *
      sc2sun_unit_idx_0;
    sc2gs_unit[2] = sc2gs_unit_idx_0 * sc2sun_unit_idx_2 - sc2gs_unit_idx_1 *
      Yti_idx_0;
    tr = norm(sc2gs_unit);

    /*  Stack vectors */
    /* '<S3>:1:92' Cb  = [Xtb, Ytb, Ztb]; */
    /* '<S3>:1:93' Ci  = [Xti, Yti, Zti]; */
    /*  Commanded DCM ( body to inertial ) */
    /* '<S3>:1:96' C_cmd   = Cb*Ci'; */
    sc2gs_unit_1[0] = sc2gs_unit_idx_0;
    sc2gs_unit_1[1] = Yti_idx_0;
    sc2gs_unit_1[2] = (sc2gs_unit_idx_1 * sc2sun_unit_idx_0 - sc2gs_unit_idx_2 *
                       sc2sun_unit_idx_2) / tr;
    sc2gs_unit_1[3] = sc2gs_unit_idx_1;
    sc2gs_unit_1[4] = sc2sun_unit_idx_2;
    sc2gs_unit_1[5] = (sc2gs_unit_idx_2 * Yti_idx_0 - sc2gs_unit_idx_0 *
                       sc2sun_unit_idx_0) / tr;
    sc2gs_unit_1[6] = sc2gs_unit_idx_2;
    sc2gs_unit_1[7] = sc2sun_unit_idx_0;
    sc2gs_unit_1[8] = (sc2gs_unit_idx_0 * sc2sun_unit_idx_2 - sc2gs_unit_idx_1 *
                       Yti_idx_0) / tr;
    for (i_0 = 0; i_0 < 3; i_0++) {
      for (i = 0; i < 3; i++) {
        C_cmd[i + 3 * i_0] = 0.0;
        C_cmd[i + 3 * i_0] += sc2gs_unit_1[3 * i_0] * (real_T)b_a[i];
        C_cmd[i + 3 * i_0] += sc2gs_unit_1[3 * i_0 + 1] * (real_T)b_a[i + 3];
        C_cmd[i + 3 * i_0] += sc2gs_unit_1[3 * i_0 + 2] * (real_T)b_a[i + 6];
      }
    }
  } else {
    /* '<S3>:1:98' else */
    /* '<S3>:1:100' C_cmd   = eye(3); */
    memset(&C_cmd[0], 0, 9U * sizeof(real_T));
    C_cmd[0] = 1.0;
    C_cmd[4] = 1.0;
    C_cmd[8] = 1.0;
  }

  /*  Compute commanded quaternion from DCM */
  /* '<S3>:1:105' q_cmd   = myDCM2quat( C_cmd ); */
  /*  This is my function */
  /*  q   = zeros(4,1); */
  /*  tr  = trace(DCM); */
  /*   */
  /*  q(1)    = 0.5*sqrt(tr + 1); */
  /*   */
  /*  if( q(1) ~= 0 ) */
  /*      eta     = 1/(4*q(1)); */
  /*      q(2)    = eta*(DCM(2,3) - DCM(3,2)); */
  /*      q(3)    = eta*(DCM(3,1) - DCM(1,3)); */
  /*      q(4)    = eta*(DCM(1,2) - DCM(2,1)); */
  /*  else */
  /*      q(2)  = sqrt(0.5*(DCM(1,1) + 1)); */
  /*      q(3)  = sign(DCM(1,2))*sqrt(0.5*(DCM(2,2) + 1)); */
  /*      q(4)  = sign(DCM(1,3))*sqrt(0.5*(DCM(3,3) + 1)); */
  /*  end */
  /*  DCM2quat assumes the scalar part is >= 0 to simplify code */
  /*  This is the Matlab internal function dcm2quat.m repurposed */
  /* '<S3>:1:130' q  = zeros(4,1); */
  /* '<S3>:1:131' tr = trace(DCM); */
  tr = (C_cmd[0] + C_cmd[4]) + C_cmd[8];

  /* '<S3>:1:133' if (tr > 0) */
  if (tr > 0.0) {
    /* '<S3>:1:134' sqtrp1 = sqrt( tr + 1.0 ); */
    tr = sqrt(tr + 1.0);

    /* '<S3>:1:136' q(1) = 0.5*sqtrp1; */
    vel_unit_idx_1 = 0.5 * tr;

    /* '<S3>:1:137' q(2) = (DCM(2, 3) - DCM(3, 2))/(2.0*sqtrp1); */
    vel_unit_idx_0 = (C_cmd[7] - C_cmd[5]) / (2.0 * tr);

    /* '<S3>:1:138' q(3) = (DCM(3, 1) - DCM(1, 3))/(2.0*sqtrp1); */
    vel_unit_idx_2 = (C_cmd[2] - C_cmd[6]) / (2.0 * tr);

    /* '<S3>:1:139' q(4) = (DCM(1, 2) - DCM(2, 1))/(2.0*sqtrp1); */
    sc2gs_unit_idx_0 = (C_cmd[3] - C_cmd[1]) / (2.0 * tr);
  } else {
    /* '<S3>:1:140' else */
    /* '<S3>:1:141' d = diag(DCM); */
    /* '<S3>:1:142' if ((d(2) > d(1)) && (d(2) > d(3))) */
    if ((C_cmd[4] > C_cmd[0]) && (C_cmd[4] > C_cmd[8])) {
      /* '<S3>:1:143' sqdip1 = sqrt(d(2) - d(1) - d(3) + 1.0 ); */
      tr = sqrt(((C_cmd[4] - C_cmd[0]) - C_cmd[8]) + 1.0);

      /* '<S3>:1:145' q(3) = 0.5*sqdip1; */
      vel_unit_idx_2 = 0.5 * tr;

      /* '<S3>:1:147' if ( sqdip1 ~= 0 ) */
      if (tr != 0.0) {
        /* '<S3>:1:148' sqdip1 = 0.5/sqdip1; */
        tr = 0.5 / tr;
      }

      /* '<S3>:1:151' q(1) = (DCM(3, 1) - DCM(1, 3))*sqdip1; */
      vel_unit_idx_1 = (C_cmd[2] - C_cmd[6]) * tr;

      /* '<S3>:1:152' q(2) = (DCM(1, 2) + DCM(2, 1))*sqdip1; */
      vel_unit_idx_0 = (C_cmd[3] + C_cmd[1]) * tr;

      /* '<S3>:1:153' q(4) = (DCM(2, 3) + DCM(3, 2))*sqdip1; */
      sc2gs_unit_idx_0 = (C_cmd[7] + C_cmd[5]) * tr;
    } else if (C_cmd[8] > C_cmd[0]) {
      /* '<S3>:1:154' elseif (d(3) > d(1)) */
      /* '<S3>:1:155' sqdip1 = sqrt(d(3) - d(1) - d(2) + 1.0 ); */
      tr = sqrt(((C_cmd[8] - C_cmd[0]) - C_cmd[4]) + 1.0);

      /* '<S3>:1:157' q(4) = 0.5*sqdip1; */
      sc2gs_unit_idx_0 = 0.5 * tr;

      /* '<S3>:1:159' if ( sqdip1 ~= 0 ) */
      if (tr != 0.0) {
        /* '<S3>:1:160' sqdip1 = 0.5/sqdip1; */
        tr = 0.5 / tr;
      }

      /* '<S3>:1:163' q(1) = (DCM(1, 2) - DCM(2, 1))*sqdip1; */
      vel_unit_idx_1 = (C_cmd[3] - C_cmd[1]) * tr;

      /* '<S3>:1:164' q(2) = (DCM(3, 1) + DCM(1, 3))*sqdip1; */
      vel_unit_idx_0 = (C_cmd[2] + C_cmd[6]) * tr;

      /* '<S3>:1:165' q(3) = (DCM(2, 3) + DCM(3, 2))*sqdip1; */
      vel_unit_idx_2 = (C_cmd[7] + C_cmd[5]) * tr;
    } else {
      /* '<S3>:1:166' else */
      /* '<S3>:1:167' sqdip1 = sqrt(d(1) - d(2) - d(3) + 1.0 ); */
      tr = sqrt(((C_cmd[0] - C_cmd[4]) - C_cmd[8]) + 1.0);

      /* '<S3>:1:169' q(2) = 0.5*sqdip1; */
      vel_unit_idx_0 = 0.5 * tr;

      /* '<S3>:1:171' if ( sqdip1 ~= 0 ) */
      if (tr != 0.0) {
        /* '<S3>:1:172' sqdip1 = 0.5/sqdip1; */
        tr = 0.5 / tr;
      }

      /* '<S3>:1:175' q(1) = (DCM(2, 3) - DCM(3, 2))*sqdip1; */
      vel_unit_idx_1 = (C_cmd[7] - C_cmd[5]) * tr;

      /* '<S3>:1:176' q(3) = (DCM(1, 2) + DCM(2, 1))*sqdip1; */
      vel_unit_idx_2 = (C_cmd[3] + C_cmd[1]) * tr;

      /* '<S3>:1:177' q(4) = (DCM(3, 1) + DCM(1, 3))*sqdip1; */
      sc2gs_unit_idx_0 = (C_cmd[2] + C_cmd[6]) * tr;
    }
  }

  /* Outport: '<Root>/quat_cmd' */
  rtY.quat_cmd[0] = vel_unit_idx_1;
  rtY.quat_cmd[1] = vel_unit_idx_0;
  rtY.quat_cmd[2] = vel_unit_idx_2;
  rtY.quat_cmd[3] = sc2gs_unit_idx_0;

  /* Outport: '<Root>/flag' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function2'
   */
  rtY.flag = flag;
}

/* Model initialize function */
void target_generation_lib0_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void target_generation_lib0_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
