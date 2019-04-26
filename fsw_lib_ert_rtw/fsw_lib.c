/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: fsw_lib.c
 *
 * Code generated for Simulink model 'fsw_lib'.
 *
 * Model version                  : 1.372
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Thu Mar  7 16:07:53 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Altera->SoC (ARM Cortex A)
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "fsw_lib.h"
#define NumBitsPerChar                 8U

/* Block signals and states (auto storage) */
DW rtDW;

/* External inputs (root inport signals with auto storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with auto storage) */
ExtY rtY;

/* Real-time model */
RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
extern real_T rt_roundd_snf(real_T u);
extern real_T rt_remd_snf(real_T u0, real_T u1);
extern real_T rt_powd_snf(real_T u0, real_T u1);
extern real_T rt_atan2d_snf(real_T u0, real_T u1);
extern void rt_invd3x3_snf(const real_T u[9], real_T y[9]);

/* Forward declaration for local functions */
static real_T norm_c(const real_T x[3]);
static void mrdivide(real_T A[36], const real_T B_0[36]);
static real_T norm(const real_T x[3]);
static real_T norm_o(const real_T x[3]);
extern real_T rtGetInf(void);
extern real32_T rtGetInfF(void);
extern real_T rtGetMinusInf(void);
extern real32_T rtGetMinusInfF(void);
extern real_T rtGetNaN(void);
extern real32_T rtGetNaNF(void);

/*===========*
 * Constants *
 *===========*/
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
# if defined(__LCC__)
#   define UNUSED_PARAMETER(x)                                   /* do nothing */
# else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#   define UNUSED_PARAMETER(x)         (void) (x)
# endif
#endif

extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
extern void rt_InitInfAndNaN(size_t realSize);
extern boolean_T rtIsInf(real_T value);
extern boolean_T rtIsInfF(real32_T value);
extern boolean_T rtIsNaN(real_T value);
extern boolean_T rtIsNaNF(real32_T value);
typedef struct {
  struct {
    uint32_T wordH;
    uint32_T wordL;
  } words;
} BigEndianIEEEDouble;

typedef struct {
  struct {
    uint32_T wordL;
    uint32_T wordH;
  } words;
} LittleEndianIEEEDouble;

typedef struct {
  union {
    real32_T wordLreal;
    uint32_T wordLuint;
  } wordL;
} IEEESingle;

real_T rtInf;
real_T rtMinusInf;
real_T rtNaN;
real32_T rtInfF;
real32_T rtMinusInfF;
real32_T rtNaNF;

/*=========*
 * Asserts *
 *=========*/
#ifndef utAssert
# if defined(DOASSERTS)
#  if !defined(PRINT_ASSERTS)
#    include <assert.h>
#    define utAssert(exp)              assert(exp)
#  else
#    include <stdio.h>

static void _assert(char *statement, char *file, int line)
{
  printf("%s in %s on line %d\n", statement, file, line);
}

#   define utAssert(_EX)               ((_EX) ? (void)0 : _assert(#_EX, __FILE__, __LINE__))
#  endif

# else
#  define utAssert(exp)                                          /* do nothing */
# endif
#endif

/*
 * Initialize rtInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real_T rtGetInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T inf = 0.0;
  if (bitsPerReal == 32U) {
    inf = rtGetInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0x7FF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    inf = tmpVal.fltVal;
  }

  return inf;
}

/*
 * Initialize rtInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real32_T rtGetInfF(void)
{
  IEEESingle infF;
  infF.wordL.wordLuint = 0x7F800000U;
  return infF.wordL.wordLreal;
}

/*
 * Initialize rtMinusInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real_T rtGetMinusInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T minf = 0.0;
  if (bitsPerReal == 32U) {
    minf = rtGetMinusInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    minf = tmpVal.fltVal;
  }

  return minf;
}

/*
 * Initialize rtMinusInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real32_T rtGetMinusInfF(void)
{
  IEEESingle minfF;
  minfF.wordL.wordLuint = 0xFF800000U;
  return minfF.wordL.wordLreal;
}

/*
 * Initialize rtNaN needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
real_T rtGetNaN(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T nan = 0.0;
  if (bitsPerReal == 32U) {
    nan = rtGetNaNF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF80000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    nan = tmpVal.fltVal;
  }

  return nan;
}

/*
 * Initialize rtNaNF needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
real32_T rtGetNaNF(void)
{
  IEEESingle nanF = { { 0 } };

  nanF.wordL.wordLuint = 0xFFC00000U;
  return nanF.wordL.wordLreal;
}

/*
 * Initialize the rtInf, rtMinusInf, and rtNaN needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */
void rt_InitInfAndNaN(size_t realSize)
{
  (void) (realSize);
  rtNaN = rtGetNaN();
  rtNaNF = rtGetNaNF();
  rtInf = rtGetInf();
  rtInfF = rtGetInfF();
  rtMinusInf = rtGetMinusInf();
  rtMinusInfF = rtGetMinusInfF();
}

/* Test if value is infinite */
boolean_T rtIsInf(real_T value)
{
  return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
boolean_T rtIsNaN(real_T value)
{
  return (boolean_T)((value!=value) ? 1U : 0U);
}

/* Test if single-precision value is not a number */
boolean_T rtIsNaNF(real32_T value)
{
  return (boolean_T)(((value!=value) ? 1U : 0U));
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

real_T rt_remd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T u1_0;
  if (!((!rtIsNaN(u0)) && (!rtIsInf(u0)) && ((!rtIsNaN(u1)) && (!rtIsInf(u1)))))
  {
    y = (rtNaN);
  } else {
    if (u1 < 0.0) {
      u1_0 = ceil(u1);
    } else {
      u1_0 = floor(u1);
    }

    if ((u1 != 0.0) && (u1 != u1_0)) {
      u1_0 = u0 / u1;
      if (fabs(u1_0 - rt_roundd_snf(u1_0)) <= DBL_EPSILON * fabs(u1_0)) {
        y = 0.0;
      } else {
        y = fmod(u0, u1);
      }
    } else {
      y = fmod(u0, u1);
    }
  }

  return y;
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T tmp;
  real_T tmp_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = (rtNaN);
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2(u0_0, u1_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/* Function for MATLAB Function: '<S66>/MATLAB Function1' */
static real_T norm_c(const real_T x[3])
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

/* Function for MATLAB Function: '<S18>/kalman_gain' */
static void mrdivide(real_T A[36], const real_T B_0[36])
{
  int32_T jp;
  real_T temp;
  real_T b_A[36];
  int8_T ipiv[6];
  int32_T j;
  int32_T ix;
  real_T s;
  int32_T c_ix;
  int32_T d;
  int32_T ijA;
  int32_T b_jAcol;
  int32_T b_kBcol;
  memcpy(&b_A[0], &B_0[0], 36U * sizeof(real_T));
  for (j = 0; j < 6; j++) {
    ipiv[j] = (int8_T)(1 + j);
  }

  for (j = 0; j < 5; j++) {
    jp = j * 7;
    b_jAcol = 0;
    ix = jp;
    temp = fabs(b_A[jp]);
    for (b_kBcol = 2; b_kBcol <= 6 - j; b_kBcol++) {
      ix++;
      s = fabs(b_A[ix]);
      if (s > temp) {
        b_jAcol = b_kBcol - 1;
        temp = s;
      }
    }

    if (b_A[jp + b_jAcol] != 0.0) {
      if (b_jAcol != 0) {
        ipiv[j] = (int8_T)((j + b_jAcol) + 1);
        ix = j;
        b_jAcol += j;
        for (b_kBcol = 0; b_kBcol < 6; b_kBcol++) {
          temp = b_A[ix];
          b_A[ix] = b_A[b_jAcol];
          b_A[b_jAcol] = temp;
          ix += 6;
          b_jAcol += 6;
        }
      }

      b_jAcol = (jp - j) + 6;
      for (ix = jp + 1; ix + 1 <= b_jAcol; ix++) {
        b_A[ix] /= b_A[jp];
      }
    }

    b_jAcol = jp;
    ix = jp + 6;
    for (b_kBcol = 1; b_kBcol <= 5 - j; b_kBcol++) {
      temp = b_A[ix];
      if (b_A[ix] != 0.0) {
        c_ix = jp + 1;
        d = (b_jAcol - j) + 12;
        for (ijA = 7 + b_jAcol; ijA + 1 <= d; ijA++) {
          b_A[ijA] += b_A[c_ix] * -temp;
          c_ix++;
        }
      }

      ix += 6;
      b_jAcol += 6;
    }
  }

  for (j = 0; j < 6; j++) {
    jp = 6 * j;
    b_jAcol = 6 * j;
    for (ix = 1; ix <= j; ix++) {
      b_kBcol = (ix - 1) * 6;
      if (b_A[(ix + b_jAcol) - 1] != 0.0) {
        for (c_ix = 0; c_ix < 6; c_ix++) {
          A[c_ix + jp] -= b_A[(ix + b_jAcol) - 1] * A[c_ix + b_kBcol];
        }
      }
    }

    temp = 1.0 / b_A[j + b_jAcol];
    for (b_jAcol = 0; b_jAcol < 6; b_jAcol++) {
      A[b_jAcol + jp] *= temp;
    }
  }

  for (j = 5; j >= 0; j += -1) {
    jp = 6 * j;
    b_jAcol = 6 * j - 1;
    for (ix = j + 2; ix < 7; ix++) {
      b_kBcol = (ix - 1) * 6;
      if (b_A[ix + b_jAcol] != 0.0) {
        for (c_ix = 0; c_ix < 6; c_ix++) {
          A[c_ix + jp] -= b_A[ix + b_jAcol] * A[c_ix + b_kBcol];
        }
      }
    }
  }

  for (j = 4; j >= 0; j += -1) {
    if (j + 1 != ipiv[j]) {
      jp = ipiv[j] - 1;
      for (b_jAcol = 0; b_jAcol < 6; b_jAcol++) {
        temp = A[6 * j + b_jAcol];
        A[b_jAcol + 6 * j] = A[6 * jp + b_jAcol];
        A[b_jAcol + 6 * jp] = temp;
      }
    }
  }
}

/* Function for MATLAB Function: '<S68>/MATLAB Function1' */
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

/* Function for MATLAB Function: '<S7>/MATLAB Function2' */
static real_T norm_o(const real_T x[3])
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

void rt_invd3x3_snf(const real_T u[9], real_T y[9])
{
  real_T x[9];
  int32_T p1;
  int32_T p2;
  int32_T p3;
  real_T absx11;
  real_T absx21;
  real_T absx31;
  int32_T itmp;
  boolean_T guard1 = false;
  memcpy(&x[0], &u[0], 9U * sizeof(real_T));
  p1 = -1;
  p2 = 3;
  p3 = 6;
  absx11 = fabs(u[0]);
  absx21 = fabs(u[1]);
  absx31 = fabs(u[2]);
  if (absx21 > absx11) {
    if (absx21 > absx31) {
      p1 = 2;
      p2 = 0;
      x[0] = u[1];
      x[1] = u[0];
      x[3] = u[4];
      x[4] = u[3];
      x[6] = u[7];
      x[7] = u[6];
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1 && (absx31 > absx11)) {
    p1 = 5;
    p3 = 0;
    absx11 = x[0];
    x[0] = u[2];
    x[2] = absx11;
    absx11 = x[3];
    x[3] = u[5];
    x[5] = absx11;
    absx11 = x[6];
    x[6] = u[8];
    x[8] = absx11;
  }

  x[1] /= x[0];
  x[2] /= x[0];
  x[4] -= x[1] * x[3];
  x[5] -= x[2] * x[3];
  x[7] -= x[1] * x[6];
  x[8] -= x[2] * x[6];
  if (fabs(x[5]) > fabs(x[4])) {
    itmp = p2;
    p2 = p3;
    p3 = itmp;
    absx11 = x[1];
    x[1] = x[2];
    x[2] = absx11;
    absx11 = x[4];
    x[4] = x[5];
    x[5] = absx11;
    absx11 = x[7];
    x[7] = x[8];
    x[8] = absx11;
  }

  x[5] /= x[4];
  x[8] -= x[5] * x[7];
  absx11 = (x[5] * x[1] - x[2]) / x[8];
  absx21 = -(x[7] * absx11 + x[1]) / x[4];
  y[p1 + 1] = ((1.0 - x[3] * absx21) - x[6] * absx11) / x[0];
  y[p1 + 2] = absx21;
  y[p1 + 3] = absx11;
  absx11 = -x[5] / x[8];
  absx21 = (1.0 - x[7] * absx11) / x[4];
  y[p2] = -(x[3] * absx21 + x[6] * absx11) / x[0];
  y[p2 + 1] = absx21;
  y[p2 + 2] = absx11;
  absx11 = 1.0 / x[8];
  absx21 = -x[7] * absx11 / x[4];
  y[p3] = -(x[3] * absx21 + x[6] * absx11) / x[0];
  y[p3 + 1] = absx21;
  y[p3 + 2] = absx11;
}

/* Model step function for TID0 */
void fsw_lib_step0(void)               /* Sample time: [0.005s, 0.0s] */
{
  /* Update the flag to indicate when data transfers from
   *  Sample time: [0.005s, 0.0s] to Sample time: [0.1s, 0.0s]  */
  (rtM->Timing.RateInteraction.TID0_2)++;
  if ((rtM->Timing.RateInteraction.TID0_2) > 19) {
    rtM->Timing.RateInteraction.TID0_2 = 0;
  }

  /* RateTransition: '<S1>/Rate Transition7' incorporates:
   *  RateTransition: '<S1>/Rate Transition4'
   *  RateTransition: '<S1>/Rate Transition7'
   *  RateTransition: '<S5>/Rate Transition7'
   */
  if (rtM->Timing.RateInteraction.TID0_2 == 1) {
    /* Outport: '<Root>/sc_quat' */
    rtY.sc_quat[0] = rtDW.RateTransition7_1_Buffer0[0];
    rtY.sc_quat[1] = rtDW.RateTransition7_1_Buffer0[1];
    rtY.sc_quat[2] = rtDW.RateTransition7_1_Buffer0[2];
    rtY.sc_quat[3] = rtDW.RateTransition7_1_Buffer0[3];

    /* Outport: '<Root>/body_rates' */
    rtY.body_rates[0] = rtDW.RateTransition7_2_Buffer0[0];
    rtY.body_rates[1] = rtDW.RateTransition7_2_Buffer0[1];
    rtY.body_rates[2] = rtDW.RateTransition7_2_Buffer0[2];

    /* Outport: '<Root>/sc_mode' */
    rtY.sc_mode = rtDW.RateTransition7_3_Buffer0;

    /* Outport: '<Root>/vel_point' */
    rtY.vel_point = rtDW.RateTransition7_4_Buffer0;

    /* Outport: '<Root>/quat_cmd' */
    rtY.quat_cmd[0] = rtDW.RateTransition7_5_Buffer0[0];
    rtY.quat_cmd[1] = rtDW.RateTransition7_5_Buffer0[1];
    rtY.quat_cmd[2] = rtDW.RateTransition7_5_Buffer0[2];
    rtY.quat_cmd[3] = rtDW.RateTransition7_5_Buffer0[3];

    /* Outport: '<Root>/sc_above_gs' */
    rtY.sc_above_gs = rtDW.RateTransition7_6_Buffer0;

    /* Outport: '<Root>/sc_in_sun' */
    rtY.sc_in_sun = rtDW.RateTransition7_7_Buffer0;

    /* Outport: '<Root>/gyro_valid' */
    rtY.gyro_valid = rtDW.RateTransition7_11_Buffer0;

    /* Outport: '<Root>/mag_eci_unit' */
    rtY.mag_eci_unit[0] = rtDW.RateTransition7_8_Buffer0[0];

    /* Outport: '<Root>/cmd_RW_rpm' */
    rtY.cmd_RW_rpm[0] = rtDW.RateTransition4_Buffer0[0];
    rtDW.RateTransition7[0] = rtDW.RateTransition7_Buffer0[0];

    /* RateTransition: '<S5>/Rate Transition2' */
    rtDW.RateTransition2[0] = rtDW.RateTransition2_Buffer0[0];

    /* RateTransition: '<S5>/Rate Transition11' */
    rtDW.RateTransition11[0] = rtDW.RateTransition11_Buffer0[0];

    /* Outport: '<Root>/mag_eci_unit' */
    rtY.mag_eci_unit[1] = rtDW.RateTransition7_8_Buffer0[1];

    /* Outport: '<Root>/cmd_RW_rpm' */
    rtY.cmd_RW_rpm[1] = rtDW.RateTransition4_Buffer0[1];
    rtDW.RateTransition7[1] = rtDW.RateTransition7_Buffer0[1];

    /* RateTransition: '<S5>/Rate Transition2' */
    rtDW.RateTransition2[1] = rtDW.RateTransition2_Buffer0[1];

    /* RateTransition: '<S5>/Rate Transition11' */
    rtDW.RateTransition11[1] = rtDW.RateTransition11_Buffer0[1];

    /* Outport: '<Root>/mag_eci_unit' */
    rtY.mag_eci_unit[2] = rtDW.RateTransition7_8_Buffer0[2];

    /* Outport: '<Root>/cmd_RW_rpm' */
    rtY.cmd_RW_rpm[2] = rtDW.RateTransition4_Buffer0[2];
    rtDW.RateTransition7[2] = rtDW.RateTransition7_Buffer0[2];

    /* RateTransition: '<S5>/Rate Transition2' */
    rtDW.RateTransition2[2] = rtDW.RateTransition2_Buffer0[2];

    /* RateTransition: '<S5>/Rate Transition11' */
    rtDW.RateTransition11[2] = rtDW.RateTransition11_Buffer0[2];
  }

  /* End of RateTransition: '<S1>/Rate Transition7' */

  /* Outport: '<Root>/vel_eci_kmps' incorporates:
   *  Gain: '<S8>/M2KM'
   */
  rtY.vel_eci_kmps[0] = 0.001 * rtDW.RateTransition2[0];
  rtY.vel_eci_kmps[1] = 0.001 * rtDW.RateTransition2[1];
  rtY.vel_eci_kmps[2] = 0.001 * rtDW.RateTransition2[2];

  /* RateTransition: '<S9>/ 11' */
  if (rtM->Timing.RateInteraction.TID0_2 == 1) {
    rtDW.u1[0] = rtDW.RateTransition7[0];
    rtDW.u1[1] = rtDW.RateTransition7[1];
    rtDW.u1[2] = rtDW.RateTransition7[2];

    /* RateTransition: '<S9>/ 10' incorporates:
     *  Constant: '<S9>/Constant1'
     */
    memcpy(&rtDW.u0[0], &rtConstP.Constant1_Value[0], 36U * sizeof(real_T));

    /* RateTransition: '<S10>/ 11' */
    rtDW.u1_f[0] = rtDW.RateTransition7[0];

    /* RateTransition: '<S7>/Rate Transition1' */
    rtDW.RateTransition1[0] = rtDW.RateTransition7[0];

    /* RateTransition: '<S7>/Rate Transition2' */
    rtDW.RateTransition2_b[0] = rtDW.RateTransition2[0];

    /* RateTransition: '<S10>/ 11' */
    rtDW.u1_f[1] = rtDW.RateTransition7[1];

    /* RateTransition: '<S7>/Rate Transition1' */
    rtDW.RateTransition1[1] = rtDW.RateTransition7[1];

    /* RateTransition: '<S7>/Rate Transition2' */
    rtDW.RateTransition2_b[1] = rtDW.RateTransition2[1];

    /* RateTransition: '<S10>/ 11' */
    rtDW.u1_f[2] = rtDW.RateTransition7[2];

    /* RateTransition: '<S7>/Rate Transition1' */
    rtDW.RateTransition1[2] = rtDW.RateTransition7[2];

    /* RateTransition: '<S7>/Rate Transition2' */
    rtDW.RateTransition2_b[2] = rtDW.RateTransition2[2];
  }

  /* End of RateTransition: '<S9>/ 11' */

  /* Outport: '<Root>/pos_eci_km' incorporates:
   *  Gain: '<S8>/M2KM '
   */
  rtY.pos_eci_km[0] = 0.001 * rtDW.RateTransition11[0];
  rtY.pos_eci_km[1] = 0.001 * rtDW.RateTransition11[1];
  rtY.pos_eci_km[2] = 0.001 * rtDW.RateTransition11[2];
}

/* Model step function for TID1 */
void fsw_lib_step1(void)               /* Sample time: [0.05s, 0.0s] */
{
  /* Update the flag to indicate when data transfers from
   *  Sample time: [0.05s, 0.0s] to Sample time: [0.1s, 0.0s]  */
  (rtM->Timing.RateInteraction.TID1_2)++;
  if ((rtM->Timing.RateInteraction.TID1_2) > 1) {
    rtM->Timing.RateInteraction.TID1_2 = 0;
  }

  /* RateTransition: '<S1>/Rate Transition1' */
  if (rtM->Timing.RateInteraction.TID1_2 == 1) {
    rtDW.RateTransition1_n[0] = rtDW.RateTransition1_Buffer0[0];
    rtDW.RateTransition1_n[1] = rtDW.RateTransition1_Buffer0[1];
    rtDW.RateTransition1_n[2] = rtDW.RateTransition1_Buffer0[2];
  }

  /* End of RateTransition: '<S1>/Rate Transition1' */

  /* Outport: '<Root>/cmd_MT_dv' */
  rtY.cmd_MT_dv[0] = rtDW.RateTransition1_n[0];
  rtY.cmd_MT_dv[1] = rtDW.RateTransition1_n[1];
  rtY.cmd_MT_dv[2] = rtDW.RateTransition1_n[2];
}

/* Model step function for TID2 */
void fsw_lib_step2(void)               /* Sample time: [0.1s, 0.0s] */
{
  real_T JD_days_gps;
  real_T mean_anom_sun_rad;
  real_T long_eclp_rad;
  real_T oblq_rad;
  real_T s;
  real_T c;
  real_T b_s;
  real_T b_c;
  real_T c_s;
  real_T c_c;
  static const real_T a[9] = { 1.0, 0.0, 0.0, 0.0, 0.91748214306524178,
    0.397776969112606, 0.0, -0.397776969112606, 0.91748214306524178 };

  static const int8_T b[3] = { 1, 0, 0 };

  static const int8_T d[3] = { 0, 0, 1 };

  real_T tod_to_mod[9];
  static const real_T nc[300] = { 1.0, 9.0, 31.0, 2.0, 10.0, 32.0, 11.0, 33.0,
    34.0, 12.0, 35.0, 13.0, 36.0, 38.0, 37.0, 40.0, 39.0, 41.0, 14.0, 3.0, 42.0,
    45.0, 43.0, 44.0, 46.0, 15.0, 47.0, 16.0, 18.0, 48.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, -1.0, 1.0, 0.0, -1.0, -1.0, 1.0, 2.0,
    -2.0, 0.0, 2.0, 2.0, 1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 1.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0, 0.0, 0.0, 2.0, 2.0, 0.0,
    0.0, 0.0, 2.0, 2.0, 2.0, 2.0, 0.0, 2.0, 2.0, 0.0, 0.0, 2.0, 0.0, 2.0, 0.0,
    2.0, 2.0, 2.0, 0.0, 2.0, 2.0, 2.0, 2.0, 0.0, 2.0, 0.0, 0.0, -2.0, 0.0, 0.0,
    0.0, 0.0, -2.0, 0.0, 0.0, -2.0, -2.0, -2.0, 0.0, 0.0, 2.0, 2.0, 0.0, 0.0,
    -2.0, 0.0, 2.0, 0.0, 0.0, -2.0, 0.0, -2.0, 0.0, 0.0, -2.0, 2.0, 1.0, 2.0,
    2.0, 2.0, 0.0, 0.0, 2.0, 1.0, 2.0, 2.0, 0.0, 1.0, 2.0, 1.0, 0.0, 2.0, 1.0,
    1.0, 0.0, 1.0, 2.0, 2.0, 0.0, 2.0, 0.0, 0.0, 1.0, 0.0, 2.0, 1.0, -171996.0,
    -13187.0, -2274.0, 2062.0, 1426.0, 712.0, -517.0, -386.0, -301.0, 217.0,
    -158.0, 129.0, 123.0, 63.0, 63.0, -59.0, -58.0, -51.0, 48.0, 46.0, -38.0,
    -31.0, 29.0, 29.0, 26.0, -22.0, 21.0, 17.0, -16.0, 16.0, -174.2, -1.6, -0.2,
    0.2, -3.4, 0.1, 1.2, -0.4, 0.0, -0.5, 0.0, 0.1, 0.0, 0.1, 0.0, 0.0, -0.1,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.1, 0.1, 0.0, 92025.0,
    5736.0, 977.0, -895.0, 54.0, -7.0, 224.0, 200.0, 129.0, -95.0, -1.0, -70.0,
    -53.0, -33.0, -2.0, 26.0, 32.0, 27.0, 1.0, -24.0, 16.0, 13.0, -1.0, -12.0,
    -1.0, 0.0, -10.0, 0.0, 7.0, -8.0, 8.9, -3.1, -0.5, 0.5, -0.1, 0.0, -0.6, 0.0,
    -0.1, 0.3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  static const int8_T c_0[3] = { 1, 0, 0 };

  static const int8_T d_0[3] = { 0, 0, 1 };

  static const int8_T e[3] = { 0, 1, 0 };

  int32_T lowAlt;
  real_T xi;
  real_T b_o;
  real_T eta;
  real_T C_1;
  real_T C_4;
  real_T C_5;
  real_T D_2;
  real_T D_3;
  real_T D_4;
  real_T IL3;
  real_T IL4;
  real_T IL5;
  real_T M_DF;
  real_T M[3];
  real_T N[3];
  static const int8_T b_0[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  int8_T Phi_22[9];
  int8_T I[9];
  static const int8_T a_0[9] = { -1, 0, 0, 0, -1, 0, 0, 0, -1 };

  static const int8_T b_a[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  int32_T ABOVE;
  static const int8_T a_1[9] = { 0, 0, -1, 1, 0, 0, 0, -1, 0 };

  static const int8_T b_a_0[9] = { 0, -1, 0, 1, 0, 0, 0, 0, 1 };

  real_T rotation_matrix[9];
  static const int8_T b_1[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  real_T KHI[36];
  int8_T I_0[36];
  boolean_T rtb_LogicalOperator_m;
  real_T rtb_Sum_o[3];
  real_T rtb_TrigonometricFunction1_o1;
  real_T rtb_Normalization[3];
  real_T rtb_q_min_k1[4];
  real_T rtb_VectorConcatenate[9];
  real_T rtb_q_cmd[4];
  real_T rtb_omega_cmd[3];
  real_T rtb_Gain1_a[3];
  real_T rtb_body_est[6];
  real_T rtb_MatrixMultiply_p[6];
  real_T rtb_q_plu[4];
  real_T rtb_s[3];
  real_T rtb_MathFunction_n[9];
  real_T rtb_m[3];
  real_T rtb_S[3];
  real_T rtb_MatrixConcatenate[9];
  int8_T rtb_UnitDelay_d;
  real_T rtb_Sum_d[3];
  int32_T idx2;
  real_T rtb_TmpSignalConversionAtSFunct[3];
  int8_T rtb_Switch_j[3];
  boolean_T rtb_Switch_p;
  real_T rtb_T_TT_J2000;
  real_T rtb_T_ut1_J2000;
  real_T rtb_sun_vector_eci_km[3];
  real_T rtb_pos_teme_km[3];
  int8_T rtb_sc_mode;
  real_T rtb_Merge2[36];
  real_T rtb_mod_to_gcrf[9];
  real_T rtb_teme_to_gcrf[9];
  real_T rtb_K[36];
  real_T rtb_MatrixMultiply[9];
  real_T rtb_s_0[3];
  real_T rtb_s_1[3];
  real_T rtb_Merge2_0[36];
  real_T rtb_sun_vector_eci_km_0[3];
  real_T a_2[9];
  real_T b_2[9];
  real_T a_3[9];
  real_T mean_anom_sun_rad_0[3];
  real_T rtb_Normalization_0[6];
  real_T rtb_Merge2_1[36];
  real_T tmp[6];
  real_T tmp_0[12];
  real_T tmp_1[12];
  int32_T sigIdx;
  real_T KHI_0[36];
  real_T rtb_K_0[36];
  real_T tmp_2[9];
  real_T tmp_3[16];
  real_T rotation_matrix_0[9];
  real_T tmp_4[3];
  real_T rtb_s_2[9];

  /* Update the flag to indicate when data transfers from
   *  Sample time: [0.1s, 0.0s] to Sample time: [0.39999999999999997s, 0.0s]  */
  (rtM->Timing.RateInteraction.TID2_3)++;
  if ((rtM->Timing.RateInteraction.TID2_3) > 3) {
    rtM->Timing.RateInteraction.TID2_3 = 0;
  }

  /* Logic: '<S2>/Logical Operator' incorporates:
   *  Inport: '<Root>/MT_valid'
   */
  rtb_LogicalOperator_m = (rtU.MT_valid[0] && rtU.MT_valid[1] && rtU.MT_valid[2]);

  /* MATLAB Function: '<S115>/time-conversion-lib' incorporates:
   *  Constant: '<S67>/dut1'
   *  Inport: '<Root>/GPS_time'
   */
  /*  ----------------------------------------------------------------------- % */
  /*  Husky-Sat 1, ADCS Subsystem */
  /*   */
  /*  Convert a GPS time into date-time, Julian date and Julian century in the */
  /*  UT1 and TT frames. Accounts for leap seconds. */
  /*  */
  /*    dUT1 obtained from: */
  /*        http://maia.usno.navy.mil/ser7/finals.daily */
  /*  */
  /*  T. Reynolds -- 2.28.18 */
  /*  ----------------------------------------------------------------------- % */
  /*  #codegen */
  /* MATLAB Function 'time_conversion_lib/time-conversion-lib': '<S117>:1' */
  /*  Constants */
  /* '<S117>:1:16' dAT         = 37.0; */
  /*  From MJD 58158 (Feb 7, 2018) */
  /* '<S117>:1:17' gps2tai     = 19.0; */
  /*  From MJD 58158 */
  /* '<S117>:1:18' gps2tt      = 32.184 + gps2tai; */
  /* '<S117>:1:19' gps2utc     = gps2tai - dAT; */
  /* '<S117>:1:20' gps2ut1     = gps2tai - dAT + dUT1; */
  /* '<S117>:1:21' sec2day     = 1/86400; */
  /* '<S117>:1:22' week2day    = 7; */
  /* '<S117>:1:23' JD_GPSepoch = 2444244.5; */
  /* '<S117>:1:24' JD_J2000    = 2451545.0; */
  /* '<S117>:1:25' JD2cent     = 1/36525; */
  /* '<S117>:1:27' sec_in = cur_gps(1); */
  /* '<S117>:1:27' week_in = cur_gps(2); */
  /*  --------------------------- % */
  /*  Translate GPS w-s to JD and Gregorian ymd-hms */
  /* '<S117>:1:31' JD_days_gps     = JD_GPSepoch + week2day*week_in + sec2day*sec_in; */
  JD_days_gps = (7.0 * rtU.GPS_time[1] + 2.4442445E+6) + 1.1574074074074073E-5 *
    rtU.GPS_time[0];

  /* '<S117>:1:32' JD_utc          = JD_days_gps + sec2day*gps2utc; */
  /* '<S117>:1:33' JD_ut1          = JD_days_gps + sec2day*gps2ut1; */
  rtb_TrigonometricFunction1_o1 = JD_days_gps + -0.00020759027777777776;

  /* '<S117>:1:34' JD_TT           = JD_days_gps + sec2day*gps2tt; */
  /* '<S117>:1:36' JD_utc_J2000    = JD_utc - JD_J2000; */
  /* '<S117>:1:37' JD_ut1_J2000    = JD_ut1 - JD_J2000; */
  /* '<S117>:1:38' T_ut1_J2000     = JD_ut1_J2000*JD2cent; */
  rtb_T_ut1_J2000 = ((JD_days_gps + -0.00020759027777777776) - 2.451545E+6) *
    2.7378507871321012E-5;

  /* '<S117>:1:39' T_TT_J2000      = JD2cent*( JD_TT - JD_J2000 ); */
  rtb_T_TT_J2000 = ((JD_days_gps + 0.00059240740740740738) - 2.451545E+6) *
    2.7378507871321012E-5;

  /* MATLAB Function: '<S66>/MATLAB Function' */
  /* '<S117>:1:41' time_ut1 = JD_2_ymdhms( JD_ut1 ); */
  /*  This algorithm is based on Vallado 4e algorithm 22, pp 202. */
  /*  Constants */
  /* '<S117>:1:49' JD_1900     = 2415019.5; */
  /* '<S117>:1:50' Lmonth      = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]; */
  /*  Convert JD to date-time */
  /* '<S117>:1:53' T1900   = (JD - JD_1900)/365.25; */
  /*  base epoch is 1900 */
  /* '<S117>:1:54' year    = 1900 + floor(T1900); */
  /* '<S117>:1:56' leapyrs = floor((year - 1900 - 1)*0.25); */
  /* '<S117>:1:57' days    = (JD - JD_1900) - ((year - 1900)*365 + leapyrs ); */
  /* '<S117>:1:59' if days < 1 */
  /* '<S117>:1:65' if mod(year,4) == 0 */
  /* '<S117>:1:69' dayofyear   = floor(days); */
  /* '<S117>:1:71' day     = 0; */
  /* '<S117>:1:72' month   = 0; */
  /* '<S117>:1:74' while day < dayofyear */
  /* dayofmonth = dayofyear - (day - Lmonth(month)); */
  /* '<S117>:1:81' tau     = 24*( days-dayofyear ); */
  /* '<S117>:1:82' hour    = floor( tau ); */
  /* '<S117>:1:83' min     = floor( 60*(tau - hour) ); */
  /* '<S117>:1:84' sec     = 3600*( tau - hour - (min/60) ); */
  /* '<S117>:1:86' time    = [ year, month, dayofyear, hour, min, sec ]; */
  /*  ----------------------------------------------------------------------- % */
  /*  UW HuskySat-1, ADCS Team */
  /*  Algorithm to find the sun vector in the ECI frame. Based on algorithm 29  */
  /*    from Vallado 4e (pp. 279-280). */
  /*  */
  /*  T. Reynolds -- 2.23.18 */
  /*  ----------------------------------------------------------------------- % */
  /* MATLAB Function 'sun_vector_lib/MATLAB Function': '<S112>:1' */
  /*  Constants */
  /* '<S112>:1:11' AU2KM   = 149597870.700; */
  /* '<S112>:1:12' DEG2RAD     = pi/180.0; */
  /* '<S112>:1:13' TWOPI   = 2*pi; */
  /*  Mean longitude in a mean-equator of date frame */
  /* '<S112>:1:16' mean_long_sun  = rem(280.460 + 36000.771*JD_cent_ut1,360); */
  /*  [deg] */
  /*  Mean anomaly for the sun. Low precision formula since we're approximating */
  /*  T_TDB with T_UT1. */
  /* '<S112>:1:20' mean_anom_sun       = rem(357.5291092 + 35999.05034*JD_cent_ut1,360); */
  /* [deg] */
  /* '<S112>:1:21' mean_anom_sun_rad   = mod(DEG2RAD*mean_anom_sun,TWOPI); */
  mean_anom_sun_rad = rt_remd_snf(35999.05034 * rtb_T_ut1_J2000 + 357.5291092,
    360.0) * 0.017453292519943295 / 6.2831853071795862;
  if (fabs(mean_anom_sun_rad - rt_roundd_snf(mean_anom_sun_rad)) <=
      2.2204460492503131E-16 * fabs(mean_anom_sun_rad)) {
    mean_anom_sun_rad = 0.0;
  } else {
    mean_anom_sun_rad = (mean_anom_sun_rad - floor(mean_anom_sun_rad)) *
      6.2831853071795862;
  }

  /*  Approximate the ecliptic longitude of the sun */
  /* '<S112>:1:24' long_eclp       = mean_long_sun + 1.914666471*sin(mean_anom_sun_rad) + ... */
  /* '<S112>:1:25'                     0.019994643*sin(2*mean_anom_sun_rad); */
  /* [deg] */
  /* '<S112>:1:26' long_eclp       = rem(DEG2RAD*long_eclp,360); */
  /*  [rad]    */
  /* '<S112>:1:27' long_eclp_rad   = mod(DEG2RAD*long_eclp,TWOPI); */
  long_eclp_rad = rt_remd_snf(((rt_remd_snf(36000.771 * rtb_T_ut1_J2000 + 280.46,
    360.0) + 1.914666471 * sin(mean_anom_sun_rad)) + sin(2.0 * mean_anom_sun_rad)
    * 0.019994643) * 0.017453292519943295, 360.0) * 0.017453292519943295 /
    6.2831853071795862;
  if (fabs(long_eclp_rad - rt_roundd_snf(long_eclp_rad)) <=
      2.2204460492503131E-16 * fabs(long_eclp_rad)) {
    long_eclp_rad = 0.0;
  } else {
    long_eclp_rad = (long_eclp_rad - floor(long_eclp_rad)) * 6.2831853071795862;
  }

  /*  Assume the ecliptic latitude is zero */
  /* '<S112>:1:30' lat_eclp     = 0; */
  /* [deg] */
  /*  Approximate the obliquity of the ecliptic using */
  /* '<S112>:1:33' oblq        = 23.439291 - 0.0130042*JD_cent_ut1; */
  /* '<S112>:1:34' oblq_rad    = DEG2RAD*oblq; */
  oblq_rad = (23.439291 - 0.0130042 * rtb_T_ut1_J2000) * 0.017453292519943295;

  /*  Find the distance in AU from E to S */
  /* '<S112>:1:37' r           =  1.000140612 - 0.016708617*cos(mean_anom_sun_rad) - ... */
  /* '<S112>:1:38'                     0.000139589*cos(2*mean_anom_sun_rad); */
  mean_anom_sun_rad = (1.000140612 - 0.016708617 * cos(mean_anom_sun_rad)) - cos
    (2.0 * mean_anom_sun_rad) * 0.000139589;

  /* '<S112>:1:39' x_MOD_km    = r*cos(long_eclp_rad)*AU2KM; */
  /* '<S112>:1:40' y_MOD_km    = r*cos(oblq_rad)*sin(long_eclp_rad)*AU2KM; */
  /* '<S112>:1:41' z_MOD_km    = r*sin(oblq_rad)*sin(long_eclp_rad)*AU2KM; */
  /* '<S112>:1:43' sun_vector_mod_km = [x_MOD_km; y_MOD_km; z_MOD_km]; */
  /*  Convert to ECI (mean-equator-mean-equinox) frame  */
  /* '<S112>:1:46' sun_vector_eci_km   = mod2eci(sun_vector_mod_km,JD_cent_ut1); */
  /* '<S112>:1:52' [prec,~,~,~,~] = precess ( JD_cent_ut1 ); */
  /*  " to rad */
  /* '<S112>:1:60' convrt = pi / (180.0*3600.0); */
  /*  ------------------ iau 03 precession angles ------------------- */
  /* '<S112>:1:63' oblo =  84381.406; */
  /*  " */
  /* '<S112>:1:64' psia =  (((( -0.0000000951 * ttt + 0.000132851 ) * ttt - 0.00114045 ) *... */
  /* '<S112>:1:65'                         ttt - 1.0790069 ) * ttt + 5038.481507 ) * ttt; */
  /*  " */
  /* '<S112>:1:66' wa   =  ((((  0.0000003337 * ttt - 0.000000467 ) * ttt - 0.00772503 ) *... */
  /* '<S112>:1:67'                         ttt + 0.0512623 ) * ttt -    0.025754 ) * ttt + oblo; */
  /* '<S112>:1:68' ea   =  (((( -0.0000000434 * ttt - 0.000000576 ) * ttt + 0.00200340 ) *... */
  /* '<S112>:1:69'                         ttt - 0.0001831 ) * ttt -   46.836769 ) * ttt + oblo; */
  /* '<S112>:1:70' xa   =  (((( - 0.0000000560 * ttt + 0.000170663 ) * ttt - 0.00121197 ) *... */
  /* '<S112>:1:71'                         ttt - 2.3814292 ) * ttt +   10.556403 ) * ttt; */
  /* '<S112>:1:73' zeta =  (((( - 0.0000003173 * ttt - 0.000005971 ) * ttt + 0.01801828 ) *... */
  /* '<S112>:1:74'                 ttt + 0.2988499 ) * ttt + 2306.083227 ) * ttt + 2.650545; */
  /*  " */
  /* '<S112>:1:75' theta=  (((( - 0.0000001274 * ttt - 0.000007089 ) * ttt - 0.04182264 ) *... */
  /* '<S112>:1:76'                 ttt - 0.4294934 ) * ttt + 2004.191903 ) * ttt; */
  /* '<S112>:1:77' z    =  ((((   0.0000002904 * ttt - 0.000028596 ) * ttt + 0.01826837 ) *... */
  /* '<S112>:1:78'                 ttt + 1.0927348 ) * ttt + 2306.077181 ) * ttt - 2.650545; */
  /*  convert all units to rad */
  /* '<S112>:1:81' psia = psia  * convrt; */
  c_c = ((((-9.51E-8 * rtb_T_ut1_J2000 + 0.000132851) * rtb_T_ut1_J2000 -
           0.00114045) * rtb_T_ut1_J2000 - 1.0790069) * rtb_T_ut1_J2000 +
         5038.481507) * rtb_T_ut1_J2000 * 4.84813681109536E-6;

  /*  rad */
  /* '<S112>:1:82' wa   = wa    * convrt; */
  b_c = (((((3.337E-7 * rtb_T_ut1_J2000 - 4.67E-7) * rtb_T_ut1_J2000 -
            0.00772503) * rtb_T_ut1_J2000 + 0.0512623) * rtb_T_ut1_J2000 -
          0.025754) * rtb_T_ut1_J2000 + 84381.406) * 4.84813681109536E-6;

  /* '<S112>:1:83' ea   = ea    * convrt; */
  /* '<S112>:1:84' xa   = xa    * convrt; */
  c = ((((-5.6E-8 * rtb_T_ut1_J2000 + 0.000170663) * rtb_T_ut1_J2000 -
         0.00121197) * rtb_T_ut1_J2000 - 2.3814292) * rtb_T_ut1_J2000 +
       10.556403) * rtb_T_ut1_J2000 * 4.84813681109536E-6;

  /* '<S112>:1:86' oblo = oblo * convrt; */
  /*  " to rad */
  /* '<S112>:1:87' a4  = rot3mat(-xa); */
  /* '<S112>:1:108' s   = sin( z_rad ); */
  s = sin(-c);

  /* '<S112>:1:109' c   = cos( z_rad ); */
  c = cos(-c);

  /* '<S112>:1:111' DCMz    = [ c   s   0; */
  /* '<S112>:1:112'            -s   c   0; */
  /* '<S112>:1:113'             0   0   1 ]; */
  /* '<S112>:1:88' a5  = rot1mat(wa); */
  /*  precess */
  /* '<S112>:1:97' s   = sin( x_rad ); */
  b_s = sin(b_c);

  /* '<S112>:1:98' c   = cos( x_rad ); */
  b_c = cos(b_c);

  /* '<S112>:1:100' DCMx    = [ 1   0   0 */
  /* '<S112>:1:101'             0   c   s; */
  /* '<S112>:1:102'             0  -s   c ]; */
  /* '<S112>:1:89' a6  = rot3mat(psia); */
  /* '<S112>:1:108' s   = sin( z_rad ); */
  c_s = sin(c_c);

  /* '<S112>:1:109' c   = cos( z_rad ); */
  c_c = cos(c_c);

  /* '<S112>:1:111' DCMz    = [ c   s   0; */
  /* '<S112>:1:112'            -s   c   0; */
  /* '<S112>:1:113'             0   0   1 ]; */
  /* '<S112>:1:90' a7  = rot1mat(-oblo); */
  /* '<S112>:1:91' prec = a7*a6*a5*a4; */
  /* '<S112>:1:52' ~ */
  /* '<S112>:1:54' vec_eci = prec*vec_mod; */
  rtb_mod_to_gcrf[0] = c_c;
  rtb_mod_to_gcrf[3] = c_s;
  rtb_mod_to_gcrf[6] = 0.0;
  rtb_mod_to_gcrf[1] = -c_s;
  rtb_mod_to_gcrf[4] = c_c;
  rtb_mod_to_gcrf[7] = 0.0;
  rtb_mod_to_gcrf[2] = 0.0;
  rtb_mod_to_gcrf[5] = 0.0;
  rtb_mod_to_gcrf[8] = 1.0;
  for (idx2 = 0; idx2 < 3; idx2++) {
    for (sigIdx = 0; sigIdx < 3; sigIdx++) {
      a_2[idx2 + 3 * sigIdx] = 0.0;
      a_2[idx2 + 3 * sigIdx] += rtb_mod_to_gcrf[3 * sigIdx] * a[idx2];
      a_2[idx2 + 3 * sigIdx] += rtb_mod_to_gcrf[3 * sigIdx + 1] * a[idx2 + 3];
      a_2[idx2 + 3 * sigIdx] += rtb_mod_to_gcrf[3 * sigIdx + 2] * a[idx2 + 6];
    }

    b_2[3 * idx2] = b[idx2];
  }

  b_2[1] = 0.0;
  b_2[4] = b_c;
  b_2[7] = b_s;
  b_2[2] = 0.0;
  b_2[5] = -b_s;
  b_2[8] = b_c;
  rtb_mod_to_gcrf[0] = c;
  rtb_mod_to_gcrf[3] = s;
  rtb_mod_to_gcrf[6] = 0.0;
  rtb_mod_to_gcrf[1] = -s;
  rtb_mod_to_gcrf[4] = c;
  rtb_mod_to_gcrf[7] = 0.0;
  for (idx2 = 0; idx2 < 3; idx2++) {
    for (sigIdx = 0; sigIdx < 3; sigIdx++) {
      a_3[idx2 + 3 * sigIdx] = 0.0;
      a_3[idx2 + 3 * sigIdx] += b_2[3 * sigIdx] * a_2[idx2];
      a_3[idx2 + 3 * sigIdx] += b_2[3 * sigIdx + 1] * a_2[idx2 + 3];
      a_3[idx2 + 3 * sigIdx] += b_2[3 * sigIdx + 2] * a_2[idx2 + 6];
    }

    rtb_mod_to_gcrf[2 + 3 * idx2] = d[idx2];
  }

  mean_anom_sun_rad_0[0] = mean_anom_sun_rad * cos(long_eclp_rad) *
    1.495978707E+8;
  mean_anom_sun_rad_0[1] = mean_anom_sun_rad * cos(oblq_rad) * sin(long_eclp_rad)
    * 1.495978707E+8;
  mean_anom_sun_rad_0[2] = mean_anom_sun_rad * sin(oblq_rad) * sin(long_eclp_rad)
    * 1.495978707E+8;
  for (idx2 = 0; idx2 < 3; idx2++) {
    rtb_sun_vector_eci_km[idx2] = 0.0;
    for (sigIdx = 0; sigIdx < 3; sigIdx++) {
      a_2[idx2 + 3 * sigIdx] = 0.0;
      a_2[idx2 + 3 * sigIdx] += rtb_mod_to_gcrf[3 * sigIdx] * a_3[idx2];
      a_2[idx2 + 3 * sigIdx] += rtb_mod_to_gcrf[3 * sigIdx + 1] * a_3[idx2 + 3];
      a_2[idx2 + 3 * sigIdx] += rtb_mod_to_gcrf[3 * sigIdx + 2] * a_3[idx2 + 6];
      rtb_sun_vector_eci_km[idx2] += a_2[3 * sigIdx + idx2] *
        mean_anom_sun_rad_0[sigIdx];
    }
  }

  /* End of MATLAB Function: '<S66>/MATLAB Function' */

  /* MATLAB Function: '<S114>/MATLAB Function' */
  /*  */
  /*  UW HuskySat-1, ADCS Subsystem */
  /*    Courtesy: Krish Kaycee 9.11.17 */
  /*    Updated: T. Reynolds 2.10.18 */
  /*  */
  /*  COORD_ROTATIONS excludes the polar motion transformation. Hence it */
  /*  includes the Precession, Nutation, and Sidereal Time rotation matrices. */
  /* MATLAB Function 'coord_rotations_lib/MATLAB Function': '<S116>:1' */
  /*  UPDATED: Excluding polar motion since it would need to be updated ~1 per */
  /*  week to keep accurate. For our mission duration and requirements, */
  /*  accounting for polar motion is not necessary. -T. Reynolds, 9.11.17 */
  /*  Constants */
  /*  Everything should be precomputed in radians */
  /* '<S116>:1:17' deg2rad     = pi/180; */
  /* '<S116>:1:18' twopi       = 2*pi; */
  /* '<S116>:1:19' asec2rad    = 1/3600*deg2rad; */
  /* '<S116>:1:20' o_prec      = 7.292115146706979e-5; */
  /*  Evaluate Delaunay parameters */
  /* '<S116>:1:23' epsb_1980 = deg2rad * ( 23.439291 ... */
  /* '<S116>:1:24'                         - 0.0130042 * jd_tt_j2000_century ... */
  /* '<S116>:1:25'                         - 1.64e-7 * jd_tt_j2000_century^2 ... */
  /* '<S116>:1:26'                         + 5.04e-7 * jd_tt_j2000_century^3); */
  long_eclp_rad = (((23.439291 - 0.0130042 * rtb_T_TT_J2000) - rtb_T_TT_J2000 *
                    rtb_T_TT_J2000 * 1.64E-7) + 5.04E-7 * rt_powd_snf
                   (rtb_T_TT_J2000, 3.0)) * 0.017453292519943295;

  /*  Evaluate Delaunay parameters (correct equations from 4e errata) */
  /* '<S116>:1:29' M_moon	=   deg2rad * ( 134.96298139 ... */
  /* '<S116>:1:30'                         + (1325 * 360 + 198.8673981) * jd_tt_j2000_century ... */
  /* '<S116>:1:31'                       	+ 0.0086972 * jd_tt_j2000_century^2 ... */
  /* '<S116>:1:32'                        	+ 1.78e-5 * jd_tt_j2000_century^3); */
  b_c = (((477198.8673981 * rtb_T_TT_J2000 + 134.96298139) + rtb_T_TT_J2000 *
          rtb_T_TT_J2000 * 0.0086972) + 1.78E-5 * rt_powd_snf(rtb_T_TT_J2000,
          3.0)) * 0.017453292519943295;

  /* '<S116>:1:34' M_sun	=   deg2rad * ( 357.52772333 ... */
  /* '<S116>:1:35'                         + (99 * 360 + 359.0503400) * jd_tt_j2000_century ... */
  /* '<S116>:1:36'                       	- 0.0001603 * jd_tt_j2000_century^2 ... */
  /* '<S116>:1:37'                      	- 3.3e-6 * jd_tt_j2000_century^3); */
  c_c = (((35999.05034 * rtb_T_TT_J2000 + 357.52772333) - rtb_T_TT_J2000 *
          rtb_T_TT_J2000 * 0.0001603) - 3.3E-6 * rt_powd_snf(rtb_T_TT_J2000, 3.0))
    * 0.017453292519943295;

  /* '<S116>:1:39' u_moon	=   deg2rad * ( 93.27191028 ... */
  /* '<S116>:1:40'                         + (1342 * 360 + 82.0175381) * jd_tt_j2000_century ... */
  /* '<S116>:1:41'                       	- 0.0036825 * jd_tt_j2000_century^2 ... */
  /* '<S116>:1:42'                         + 3.1e-6 * jd_tt_j2000_century^3); */
  oblq_rad = (((483202.0175381 * rtb_T_TT_J2000 + 93.27191028) - rtb_T_TT_J2000 *
               rtb_T_TT_J2000 * 0.0036825) + 3.1E-6 * rt_powd_snf(rtb_T_TT_J2000,
    3.0)) * 0.017453292519943295;

  /* '<S116>:1:44' D_sun	=   deg2rad * ( 297.85036306 ... */
  /* '<S116>:1:45'                         + (1236 * 360 + 307.1114800) * jd_tt_j2000_century ... */
  /* '<S116>:1:46'                         - 0.0019142 * jd_tt_j2000_century^2 ... */
  /* '<S116>:1:47'                      	+ 5.3e-6 * jd_tt_j2000_century^3); */
  s = (((445267.11148 * rtb_T_TT_J2000 + 297.85036306) - rtb_T_TT_J2000 *
        rtb_T_TT_J2000 * 0.0019142) + 5.3E-6 * rt_powd_snf(rtb_T_TT_J2000, 3.0))
    * 0.017453292519943295;

  /* '<S116>:1:49' O_moon	=   deg2rad * ( 125.04452222 ... */
  /* '<S116>:1:50'                         - (5 * 360 + 134.1362608) * jd_tt_j2000_century ... */
  /* '<S116>:1:51'                     	+ 0.0020708 * jd_tt_j2000_century^2 ... */
  /* '<S116>:1:52'                         + 2.2e-6 * jd_tt_j2000_century^3); */
  mean_anom_sun_rad = (((125.04452222 - 1934.1362608 * rtb_T_TT_J2000) +
                        rtb_T_TT_J2000 * rtb_T_TT_J2000 * 0.0020708) + 2.2E-6 *
                       rt_powd_snf(rtb_T_TT_J2000, 3.0)) * 0.017453292519943295;

  /*  Largest Nutation coefficents (out of 106)                     */
  /* '<S116>:1:55' nc = [ ... */
  /* '<S116>:1:56' 1   0   0   0   0   1   -171996 -174.2  92025   8.9 */
  /* '<S116>:1:57' 9   0   0   2   -2  2   -13187  -1.6    5736    -3.1 */
  /* '<S116>:1:58' 31  0   0   2   0   2   -2274   -0.2    977     -0.5 */
  /* '<S116>:1:59' 2   0   0   0   0   2   2062    0.2     -895    0.5 */
  /* '<S116>:1:60' 10  0   1   0  	0   0   1426    -3.4    54      -0.1 */
  /* '<S116>:1:61' 32  1   0   0   0   0   712     0.1     -7      0.0 */
  /* '<S116>:1:62' 11  0   1   2   -2  2   -517    1.2     224     -0.6 */
  /* '<S116>:1:63' 33  0   0   2   0   1   -386    -0.4    200     0.0 */
  /* '<S116>:1:64' 34  1   0   2   0   2   -301    0.0     129     -0.1 */
  /* '<S116>:1:65' 12  0   -1  2   -2  2   217     -0.5    -95     0.3 */
  /* '<S116>:1:66' 35  1   0   0   -2  0   -158    0.0     -1      0.0 */
  /* '<S116>:1:67' 13  0   0   2   -2  1   129     0.1     -70     0.0  */
  /* '<S116>:1:68' 36  -1  0   2   0   2   123     0.0     -53     0.0  */
  /* '<S116>:1:69' 38  1   0   0   0   1   63      0.1     -33     0.0 */
  /* '<S116>:1:70' 37  0   0   0   2   0   63      0.0     -2      0.0 */
  /* '<S116>:1:71' 40  -1  0   2   2   2   -59     0.0     26      0.0 */
  /* '<S116>:1:72' 39  -1  0   0   0   1   -58     -0.1    32      0.0 */
  /* '<S116>:1:73' 41  1   0   2   0   1   -51     0.0     27      0.0 */
  /* '<S116>:1:74' 14  2   0   0   -2  0   48      0.0     1       0.0 */
  /* '<S116>:1:75' 3   -2  0   2   0   1   46      0.0     -24     0.0 */
  /* '<S116>:1:76' 42  0   0   2   2   2   -38     0.0     16      0.0 */
  /* '<S116>:1:77' 45  2   0   2   0   2   -31     0.0     13      0.0 */
  /* '<S116>:1:78' 43  2   0   0   0   0   29      0.0     -1      0.0 */
  /* '<S116>:1:79' 44  1   0   2   -2  2   29      0.0     -12     0.0 */
  /* '<S116>:1:80' 46  0   0   2   0   0   26      0.0     -1      0.0 */
  /* '<S116>:1:81' 15  0   0   2   -2  0   -22     0.0     0       0.0 */
  /* '<S116>:1:82' 47  -1  0   2   0   1   21      0.0     -10     0.0 */
  /* '<S116>:1:83' 16  0   2   0   0   0   17      -0.1    0       0.0 */
  /* '<S116>:1:84' 18  0   2   2   -2  2   -16     0.1     7       0.0 */
  /* '<S116>:1:85' 48  -1  0   0   2   1   16      0.0     -8      0.0 ... */
  /* '<S116>:1:86' ]; */
  /*  Map coefficients to radians (this should be embedded in the data) */
  /*  nc(:,end-3:end) = nc(:,end-3:end) * 0.0001 * asec2rad; */
  /*  Compute nutation in longitude (psi), and latitude (eps) */
  /* '<S116>:1:92' dpsi_1980 = 0; */
  c = 0.0;

  /* '<S116>:1:92' deps_1980 = 0; */
  b_s = 0.0;

  /* '<S116>:1:93' for i = 1:size(nc,1) */
  for (idx2 = 0; idx2 < 30; idx2++) {
    /* '<S116>:1:94' api         =   nc(i,2) * M_moon + nc(i,3) * M_sun + nc(i,4) * u_moon + nc(i,5) * D_sun + nc(i,6) * O_moon; */
    c_s = (((nc[30 + idx2] * b_c + nc[60 + idx2] * c_c) + nc[90 + idx2] *
            oblq_rad) + nc[120 + idx2] * s) + nc[150 + idx2] * mean_anom_sun_rad;

    /* '<S116>:1:95' dpsi_1980   =   0.0001 * (nc(i,7) + nc(i,8) * jd_tt_j2000_century) * sin(api) + dpsi_1980; */
    c += (nc[210 + idx2] * rtb_T_TT_J2000 + nc[180 + idx2]) * 0.0001 * sin(c_s);

    /* '<S116>:1:96' deps_1980   =   0.0001 * (nc(i,9) + nc(i,10) * jd_tt_j2000_century) * cos(api) + deps_1980; */
    b_s += (nc[270 + idx2] * rtb_T_TT_J2000 + nc[240 + idx2]) * 0.0001 * cos(c_s);
  }

  /* '<S116>:1:99' eps_1980 = epsb_1980 + asec2rad * deps_1980; */
  c_c = 4.84813681109536E-6 * b_s + long_eclp_rad;

  /* '<S116>:1:100' tod_to_mod = rot1(-epsb_1980) * rot3(asec2rad * dpsi_1980) * rot1(eps_1980); */
  /* '<S116>:1:149' y = [1 0 0; 0 cos(u) sin(u); 0 -sin(u) cos(u)]; */
  b_c = 4.84813681109536E-6 * c;

  /* '<S116>:1:157' y = [cos(u) sin(u) 0; -sin(u) cos(u) 0; 0 0 1]; */
  /* '<S116>:1:149' y = [1 0 0; 0 cos(u) sin(u); 0 -sin(u) cos(u)]; */
  rtb_teme_to_gcrf[1] = 0.0;
  rtb_teme_to_gcrf[4] = cos(-long_eclp_rad);
  rtb_teme_to_gcrf[7] = sin(-long_eclp_rad);
  rtb_teme_to_gcrf[2] = 0.0;
  rtb_teme_to_gcrf[5] = -sin(-long_eclp_rad);
  rtb_teme_to_gcrf[8] = cos(-long_eclp_rad);
  rtb_MatrixMultiply[0] = cos(b_c);
  rtb_MatrixMultiply[3] = sin(b_c);
  rtb_MatrixMultiply[6] = 0.0;
  rtb_MatrixMultiply[1] = -sin(b_c);
  rtb_MatrixMultiply[4] = cos(b_c);
  rtb_MatrixMultiply[7] = 0.0;
  rtb_teme_to_gcrf[0] = 1.0;
  rtb_MatrixMultiply[2] = 0.0;
  rtb_teme_to_gcrf[3] = 0.0;
  rtb_MatrixMultiply[5] = 0.0;
  rtb_teme_to_gcrf[6] = 0.0;
  rtb_MatrixMultiply[8] = 1.0;
  for (idx2 = 0; idx2 < 3; idx2++) {
    for (sigIdx = 0; sigIdx < 3; sigIdx++) {
      rtb_mod_to_gcrf[idx2 + 3 * sigIdx] = 0.0;
      rtb_mod_to_gcrf[idx2 + 3 * sigIdx] += rtb_MatrixMultiply[3 * sigIdx] *
        rtb_teme_to_gcrf[idx2];
      rtb_mod_to_gcrf[idx2 + 3 * sigIdx] += rtb_MatrixMultiply[3 * sigIdx + 1] *
        rtb_teme_to_gcrf[idx2 + 3];
      rtb_mod_to_gcrf[idx2 + 3 * sigIdx] += rtb_MatrixMultiply[3 * sigIdx + 2] *
        rtb_teme_to_gcrf[idx2 + 6];
    }

    a_2[3 * idx2] = c_0[idx2];
  }

  a_2[1] = 0.0;
  a_2[4] = cos(c_c);
  a_2[7] = sin(c_c);
  a_2[2] = 0.0;
  a_2[5] = -sin(c_c);
  a_2[8] = cos(c_c);

  /*  Generate Precession matrix */
  /* '<S116>:1:103' zeta    =   asec2rad * (2306.2181 * jd_tt_j2000_century + 0.30188 * jd_tt_j2000_century^2 + 0.017998 * jd_tt_j2000_century^3); */
  b_c = ((rtb_T_TT_J2000 * rtb_T_TT_J2000 * 0.30188 + 2306.2181 * rtb_T_TT_J2000)
         + 0.017998 * rt_powd_snf(rtb_T_TT_J2000, 3.0)) * 4.84813681109536E-6;

  /* '<S116>:1:104' theta   =   asec2rad * (2004.3109 * jd_tt_j2000_century - 0.42665 * jd_tt_j2000_century^2 - 0.041833 * jd_tt_j2000_century^3); */
  /* '<S116>:1:105' z       =   asec2rad * (2306.2181 * jd_tt_j2000_century + 1.09468 * jd_tt_j2000_century^2 + 0.018203 * jd_tt_j2000_century^3); */
  c_c = ((rtb_T_TT_J2000 * rtb_T_TT_J2000 * 1.09468 + 2306.2181 * rtb_T_TT_J2000)
         + 0.018203 * rt_powd_snf(rtb_T_TT_J2000, 3.0)) * 4.84813681109536E-6;

  /* '<S116>:1:107' mod_to_gcrf = rot3(zeta) * rot2(-theta) * rot3(z); */
  /* '<S116>:1:157' y = [cos(u) sin(u) 0; -sin(u) cos(u) 0; 0 0 1]; */
  rtb_T_TT_J2000 = -(((2004.3109 * rtb_T_TT_J2000 - rtb_T_TT_J2000 *
                       rtb_T_TT_J2000 * 0.42665) - 0.041833 * rt_powd_snf
                      (rtb_T_TT_J2000, 3.0)) * 4.84813681109536E-6);

  /* '<S116>:1:153' y = [cos(u) 0 -sin(u); 0 1 0; sin(u) 0 cos(u)]; */
  /* '<S116>:1:157' y = [cos(u) sin(u) 0; -sin(u) cos(u) 0; 0 0 1]; */
  rtb_MatrixMultiply[0] = cos(b_c);
  rtb_MatrixMultiply[3] = sin(b_c);
  rtb_MatrixMultiply[6] = 0.0;
  rtb_MatrixMultiply[1] = -sin(b_c);
  rtb_MatrixMultiply[4] = cos(b_c);
  rtb_MatrixMultiply[7] = 0.0;
  rtb_teme_to_gcrf[0] = cos(rtb_T_TT_J2000);
  rtb_teme_to_gcrf[3] = 0.0;
  rtb_teme_to_gcrf[6] = -sin(rtb_T_TT_J2000);
  for (idx2 = 0; idx2 < 3; idx2++) {
    for (sigIdx = 0; sigIdx < 3; sigIdx++) {
      tod_to_mod[idx2 + 3 * sigIdx] = 0.0;
      tod_to_mod[idx2 + 3 * sigIdx] += a_2[3 * sigIdx] * rtb_mod_to_gcrf[idx2];
      tod_to_mod[idx2 + 3 * sigIdx] += a_2[3 * sigIdx + 1] *
        rtb_mod_to_gcrf[idx2 + 3];
      tod_to_mod[idx2 + 3 * sigIdx] += a_2[3 * sigIdx + 2] *
        rtb_mod_to_gcrf[idx2 + 6];
    }

    rtb_MatrixMultiply[2 + 3 * idx2] = d_0[idx2];
    rtb_teme_to_gcrf[1 + 3 * idx2] = e[idx2];
  }

  rtb_teme_to_gcrf[2] = sin(rtb_T_TT_J2000);
  rtb_teme_to_gcrf[5] = 0.0;
  rtb_teme_to_gcrf[8] = cos(rtb_T_TT_J2000);
  b_2[0] = cos(c_c);
  b_2[3] = sin(c_c);
  b_2[6] = 0.0;
  b_2[1] = -sin(c_c);
  b_2[4] = cos(c_c);
  b_2[7] = 0.0;
  for (idx2 = 0; idx2 < 3; idx2++) {
    for (sigIdx = 0; sigIdx < 3; sigIdx++) {
      a_2[idx2 + 3 * sigIdx] = 0.0;
      a_2[idx2 + 3 * sigIdx] += rtb_teme_to_gcrf[3 * sigIdx] *
        rtb_MatrixMultiply[idx2];
      a_2[idx2 + 3 * sigIdx] += rtb_teme_to_gcrf[3 * sigIdx + 1] *
        rtb_MatrixMultiply[idx2 + 3];
      a_2[idx2 + 3 * sigIdx] += rtb_teme_to_gcrf[3 * sigIdx + 2] *
        rtb_MatrixMultiply[idx2 + 6];
    }

    b_2[2 + 3 * idx2] = d_0[idx2];
  }

  for (idx2 = 0; idx2 < 3; idx2++) {
    for (sigIdx = 0; sigIdx < 3; sigIdx++) {
      rtb_mod_to_gcrf[sigIdx + 3 * idx2] = 0.0;
      rtb_mod_to_gcrf[sigIdx + 3 * idx2] += b_2[3 * idx2] * a_2[sigIdx];
      rtb_mod_to_gcrf[sigIdx + 3 * idx2] += b_2[3 * idx2 + 1] * a_2[sigIdx + 3];
      rtb_mod_to_gcrf[sigIdx + 3 * idx2] += b_2[3 * idx2 + 2] * a_2[sigIdx + 6];
    }
  }

  /*  Compute equation of Equinoxes */
  /* '<S116>:1:110' eqe_1980 = asec2rad * (dpsi_1980  * cos(epsb_1980) + 0.00264 * sin(O_moon) + 0.000063 * sin(2 * O_moon)); */
  rtb_T_TT_J2000 = ((c * cos(long_eclp_rad) + 0.00264 * sin(mean_anom_sun_rad))
                    + sin(2.0 * mean_anom_sun_rad) * 6.3E-5) *
    4.84813681109536E-6;

  /* '<S116>:1:111' teme_to_tod = rot3(-eqe_1980); */
  /* '<S116>:1:157' y = [cos(u) sin(u) 0; -sin(u) cos(u) 0; 0 0 1]; */
  /*  % Compute sidereal rotation */
  /*  GMST_1982 = asec2rad * (67310.54841 ... */
  /*                          + (876600 * 3600 + 8640184.812866) * jd_ut1_j2000_century ... */
  /*                          + 0.093104 * jd_ut1_j2000_century^2 ... */
  /*                          - 6.2e-6 * jd_ut1_j2000_century^3); */
  /* '<S116>:1:118' GMST_1982 = (67310.54841 ... */
  /* '<S116>:1:119'                         + (876600 * 3600 + 8640184.812866) * jd_ut1_j2000_century ... */
  /* '<S116>:1:120'                         + 0.093104 * jd_ut1_j2000_century^2 ... */
  /* '<S116>:1:121'                         - 6.2e-6 * jd_ut1_j2000_century^3); */
  rtb_T_ut1_J2000 = ((3.1644001848128662E+9 * rtb_T_ut1_J2000 + 67310.54841) +
                     rtb_T_ut1_J2000 * rtb_T_ut1_J2000 * 0.093104) - 6.2E-6 *
    rt_powd_snf(rtb_T_ut1_J2000, 3.0);

  /* '<S116>:1:122' GMST_1982 = mod(GMST_1982,sign(GMST_1982)*86400) / 240; */
  if (rtb_T_ut1_J2000 < 0.0) {
    long_eclp_rad = -1.0;
  } else if (rtb_T_ut1_J2000 > 0.0) {
    long_eclp_rad = 1.0;
  } else if (rtb_T_ut1_J2000 == 0.0) {
    long_eclp_rad = 0.0;
  } else {
    long_eclp_rad = rtb_T_ut1_J2000;
  }

  mean_anom_sun_rad = long_eclp_rad * 86400.0;
  if (!(mean_anom_sun_rad == 0.0)) {
    if (mean_anom_sun_rad == mean_anom_sun_rad) {
      rtb_T_ut1_J2000 -= floor(rtb_T_ut1_J2000 / mean_anom_sun_rad) *
        mean_anom_sun_rad;
    } else {
      rtb_T_ut1_J2000 /= mean_anom_sun_rad;
      if (fabs(rtb_T_ut1_J2000 - rt_roundd_snf(rtb_T_ut1_J2000)) <=
          2.2204460492503131E-16 * fabs(rtb_T_ut1_J2000)) {
        rtb_T_ut1_J2000 = 0.0;
      } else {
        rtb_T_ut1_J2000 = (rtb_T_ut1_J2000 - floor(rtb_T_ut1_J2000)) *
          mean_anom_sun_rad;
      }
    }
  }

  rtb_T_ut1_J2000 /= 240.0;

  /* '<S116>:1:123' GMST_1982 = deg2rad * mod(GMST_1982, 360); */
  rtb_T_ut1_J2000 = (rtb_T_ut1_J2000 - floor(rtb_T_ut1_J2000 / 360.0) * 360.0) *
    0.017453292519943295;

  /* '<S116>:1:124' GAST_1982 = GMST_1982 + eqe_1980; */
  /*  Compute sidereal rotation */
  /*  GMST_1982 = asec2rad * (67310.54841 ... */
  /*                          + (876600 * 3600 + 8640184.812866) * jd_ut1_j2000_century ... */
  /*                          + 0.093104 * jd_ut1_j2000_century^2 ... */
  /*                          - 6.2e-6 * jd_ut1_j2000_century^3); */
  /*  GMST_1982 = mod(GMST_1982, 2*pi); */
  /*  GAST_1982 = GMST_1982 + eqe_1980; */
  /*  Compute rotation from pseudo-Earth fixed frame (does not include polar */
  /*  motion) */
  /* '<S116>:1:136' pef_to_tod = rot3(-GAST_1982); */
  rtb_T_ut1_J2000 = -(rtb_T_ut1_J2000 + rtb_T_TT_J2000);

  /* '<S116>:1:157' y = [cos(u) sin(u) 0; -sin(u) cos(u) 0; 0 0 1]; */
  /*  % Compute polar motion (small angle approximation is assumed) */
  /*  itrf_to_pef = polar(polar_motion_rad(1), polar_motion_rad(2)); */
  /*  Compute composite rotations */
  /* '<S116>:1:142' teme_to_gcrf = mod_to_gcrf * tod_to_mod * teme_to_tod; */
  /* '<S116>:1:143' itrf_to_gcrf = mod_to_gcrf * tod_to_mod * pef_to_tod; */
  /*  * itrf_to_pef;   % for vecef */
  /* '<S116>:1:144' ppef_to_vgcrf = itrf_to_gcrf * skew([0; 0; o_prec]); */
  /*  for w x recef */
  rtb_MatrixMultiply[0] = cos(-rtb_T_TT_J2000);
  rtb_MatrixMultiply[3] = sin(-rtb_T_TT_J2000);
  rtb_MatrixMultiply[6] = 0.0;
  rtb_MatrixMultiply[1] = -sin(-rtb_T_TT_J2000);
  rtb_MatrixMultiply[4] = cos(-rtb_T_TT_J2000);
  rtb_MatrixMultiply[7] = 0.0;
  for (idx2 = 0; idx2 < 3; idx2++) {
    for (sigIdx = 0; sigIdx < 3; sigIdx++) {
      a_2[idx2 + 3 * sigIdx] = 0.0;
      a_2[idx2 + 3 * sigIdx] += tod_to_mod[3 * sigIdx] * rtb_mod_to_gcrf[idx2];
      a_2[idx2 + 3 * sigIdx] += tod_to_mod[3 * sigIdx + 1] *
        rtb_mod_to_gcrf[idx2 + 3];
      a_2[idx2 + 3 * sigIdx] += tod_to_mod[3 * sigIdx + 2] *
        rtb_mod_to_gcrf[idx2 + 6];
    }

    rtb_MatrixMultiply[2 + 3 * idx2] = d_0[idx2];
  }

  for (idx2 = 0; idx2 < 3; idx2++) {
    for (sigIdx = 0; sigIdx < 3; sigIdx++) {
      rtb_teme_to_gcrf[sigIdx + 3 * idx2] = 0.0;
      rtb_teme_to_gcrf[sigIdx + 3 * idx2] += rtb_MatrixMultiply[3 * idx2] *
        a_2[sigIdx];
      rtb_teme_to_gcrf[sigIdx + 3 * idx2] += rtb_MatrixMultiply[3 * idx2 + 1] *
        a_2[sigIdx + 3];
      rtb_teme_to_gcrf[sigIdx + 3 * idx2] += rtb_MatrixMultiply[3 * idx2 + 2] *
        a_2[sigIdx + 6];
    }
  }

  /* MATLAB Function: '<S65>/MATLAB Function' incorporates:
   *  Inport: '<Root>/orbit_tle'
   *  MATLAB Function: '<S115>/time-conversion-lib'
   */
  /*  ----------------------------------------------------------------------- % */
  /*  LOAD CONSTANTS */
  /*  ----------------------------------------------------------------------- % */
  /* MATLAB Function 'sgp4_lib_fsw/MATLAB Function': '<S111>:1' */
  /*  SGP4 Orbit Propagator */
  /*  UW Husky-Sat1 - ADCS Subsystem team */
  /*    Author:     Taylor Reynolds */
  /*    Updated:    7/3/18 */
  /*  Based on "SpaceTrack Report #3: Models for Propagation of NORAD Element */
  /*  Sets", Hoots & Roerhrich, 1980. */
  /*  */
  /*  TLE Format: */
  /*    Line 1: Column | Description */
  /*            01          line number of element data */
  /*            03-07       satellite number */
  /*            08          classification (u = unclassified) */
  /*            10-11       last two digits of launch year */
  /*            12-14       launch number of year */
  /*            15-17       piece of launch */
  /*            19-20       epoch year (last two digits) */
  /*            21-32       epoch (DOY and fractional portion of the day) */
  /*            34-43       first derivative of the mean motion */
  /*            45-52       second time derivative of mean motion (decimal */
  /*                            assumed) */
  /*            54-61       BS drag term (decimal point assumed) */
  /*            63          ephemeris type */
  /*            65-68       element number */
  /*            69          checksum (mod 10) */
  /*     */
  /*    Line 2: Column  | Description */
  /*            01          line number of element data */
  /*            03-07       satellite number */
  /*            09-16       inclination (degrees) */
  /*            18-25       right ascension of the ascending node (degrees) */
  /*            27-33       eccentricity (decimal assumed) */
  /*            35-42       argument of perigee (degrees) */
  /*            44-51       mean anomaly (degrees) */
  /*            53-63       mean motion (revs per day) */
  /*            64-68       revolution number at epoch (revs) */
  /*            69          checksum (mod 10) */
  /*  */
  /*  ----------------------------------------------------------------------- % */
  /*  Inputs: */
  /*    - orbit_tle: NORAD two line element set containing orbit info */
  /*    - tsince: Time since epoch of TLE in MINUTES */
  /*  Outputs: */
  /*    - pos_frame: Position vector in the TEME frame   */
  /*    - vel_frame: Velocity vector in the TEME frame */
  /*  */
  /*  Variables: */
  /*    - n_o = SGP type "mean" mean motion at epoch */
  /*    - e_o = the "mean" eccentricity at epoch */
  /*    - i_o = the "mean" inclination at epoch */
  /*    - M_o = the "mean" mean anomaly at epoch */
  /*    - w_o = the "mean" argument of perigee at epoch */
  /*    - Om_o = the "mean" longitude of ascending node at epoch */
  /*    - nd_o  = the TRoC of n_o */
  /*    - ndd_o = the TRoC of nd_o */
  /*    - Bs = the SGP4 type drag coefficient */
  /*    - k_e = gravitational constant of Earth, sqrt(GM_e) */
  /*    - a_E = the equatorial radius of Earth in ER */
  /*    - J_2 = the second gravitation zonal harmonic of Earth */
  /*    - J_3 = the third gravitational zonal harmonic of Earth */
  /*    - J_4 = the fourth gravitational zonal harmonic of Earth */
  /*    - (t-t_0) = time since epoch */
  /*    - k_2   = 0.5*J_2*a_E^2 */
  /*    - k_4   = -(3/8)*J_4*a_E^4 */
  /*    - A_30  = -J_3*a_E^3 */
  /*    - q_0   = parameter for the SGP4 density function */
  /*    - s     = parameter for the SGP4 density function */
  /*  ----------------------------------------------------------------------- % */
  /*  Function Body */
  /* '<S111>:1:75' k_2     = 5.413080e-4; */
  /*  CK2 = 0.5*J_2*a_E^2 */
  /* '<S111>:1:76' k_4     = 0.62098875e-6; */
  /*  CK4 = -3/8*J_4*a_E^4 */
  /* '<S111>:1:77' QOMS4   = 1.88027916e-9; */
  b_c = 1.88027916E-9;

  /*  QOMS2T = (q_0 - s)^4 * ER^4 */
  /* '<S111>:1:78' s       = 1.01222928; */
  long_eclp_rad = 1.01222928;

  /*  S = s*ER */
  /* '<S111>:1:79' XJ3     = -0.2538815e-5; */
  /*  J_3 */
  /* '<S111>:1:80' XKE     = 0.743669161e-1; */
  /*  XKE = k_e*(ER/min)^{3/2} */
  /* '<S111>:1:81' XKMPER  = 6378.137; */
  /*  km/ER */
  /* '<S111>:1:82' XMNPDA  = 1440; */
  /*  time_units/day */
  /* '<S111>:1:83' a_E     = 1; */
  /*  distance units/ER */
  /* '<S111>:1:84' DE2RA   = 0.174532925e-1; */
  /*  radians/degree */
  /* '<S111>:1:85' TRUE    = 1; */
  /* '<S111>:1:86' FALSE   = 0; */
  /* '<S111>:1:87' r_E     = 6378.137; */
  /*  Earth's equatorial radius [km] */
  /* '<S111>:1:88' A_30    = -XJ3*a_E^3; */
  /*  see nomenclature */
  /* '<S111>:1:89' VKMPS   = XKMPER/60; */
  /*  Convert ER/min velocities to km/s */
  /* '<S111>:1:90' J2000   = 2451545.0; */
  /*  Julian date for J2000 */
  /* '<S111>:1:91' FLAG    = 0; */
  /* '<S111>:1:92' pos_invalid     = [ XKMPER; XKMPER; XKMPER + 500 ]; */
  /* '<S111>:1:93' vel_invalid     = [ 0.0; 0.0; 0.0 ]; */
  /*  ----------------------------------------------------------------------- % */
  /*  Line 1 */
  /* '<S111>:1:98' epoch_year  = orbit_tle(1); */
  /* '<S111>:1:99' epoch_JD    = orbit_tle(2); */
  /* '<S111>:1:100' BS          = orbit_tle(3); */
  /*  Line 2 */
  /* '<S111>:1:103' i_o     = orbit_tle(4)*DE2RA; */
  rtb_T_TT_J2000 = rtU.orbit_tle[3] * 0.0174532925;

  /*  Radians (INC) */
  /* '<S111>:1:104' Om_o    = orbit_tle(5)*DE2RA; */
  /*  Radians (RAAN) */
  /* '<S111>:1:105' e_o     = orbit_tle(6); */
  /*  Non-dimensional (ECC) */
  /* '<S111>:1:106' w_o     = orbit_tle(7)*DE2RA; */
  oblq_rad = rtU.orbit_tle[6] * 0.0174532925;

  /*  Radians (AOP) */
  /* '<S111>:1:107' M_o     = orbit_tle(8)*DE2RA; */
  c = rtU.orbit_tle[7] * 0.0174532925;

  /*  Radians (MNA) */
  /* '<S111>:1:108' n_o     = orbit_tle(9)*2*pi/XMNPDA; */
  c_c = rtU.orbit_tle[8] * 2.0 * 3.1415926535897931 / 1440.0;

  /*  Revs per time unit (MNM)    */
  /*  Hooks on orbital elements (catch #1) */
  /*  eccentricity */
  /* '<S111>:1:112' if( (e_o >= 1) || (e_o <= 0) ) */
  if ((rtU.orbit_tle[5] >= 1.0) || (rtU.orbit_tle[5] <= 0.0)) {
    /* '<S111>:1:113' pos_teme_km       = pos_invalid; */
    /* '<S111>:1:114' vel_teme_kmps     = vel_invalid; */
    rtb_pos_teme_km[0] = 6378.137;
    c_s = 0.0;
    rtb_pos_teme_km[1] = 6378.137;
    xi = 0.0;
    rtb_pos_teme_km[2] = 6878.137;
    b_o = 0.0;

    /* '<S111>:1:115' FLAG = -1; */
  } else {
    /*  mean motion (catch #1) */
    /* '<S111>:1:119' if( n_o == 0 ) */
    if (c_c == 0.0) {
      /* '<S111>:1:120' pos_teme_km       = pos_invalid; */
      /* '<S111>:1:121' vel_teme_kmps     = vel_invalid; */
      rtb_pos_teme_km[0] = 6378.137;
      c_s = 0.0;
      rtb_pos_teme_km[1] = 6378.137;
      xi = 0.0;
      rtb_pos_teme_km[2] = 6878.137;
      b_o = 0.0;

      /* '<S111>:1:122' FLAG = -1; */
    } else {
      /*  Time since epoch (catch #1)                              */
      /* '<S111>:1:127' tsince_JD      = (JD_J2000_cur - epoch_JD); */
      JD_days_gps = ((JD_days_gps + -0.00020833333333333332) - 2.451545E+6) -
        rtU.orbit_tle[1];

      /* '<S111>:1:128' if( abs(tsince_JD) < 1e-8 || tsince_JD < 0) */
      if ((fabs(JD_days_gps) < 1.0E-8) || (JD_days_gps < 0.0)) {
        /* '<S111>:1:129' tsince_JD   = 0; */
        JD_days_gps = 0.0;
      }

      /* '<S111>:1:132' tsince  = XMNPDA*tsince_JD; */
      mean_anom_sun_rad = 1440.0 * JD_days_gps;

      /* '<S111>:1:134' a_1  = (XKE/n_o)^(2/3); */
      s = rt_powd_snf(0.0743669161 / c_c, 0.66666666666666663);

      /* '<S111>:1:135' d_1  = 1.5*(k_2/(a_1^2))*((3*cos(i_o)^2 - 1)/(1 - e_o^2)^(3/2)); */
      JD_days_gps = cos(rtb_T_TT_J2000);
      JD_days_gps = (JD_days_gps * JD_days_gps * 3.0 - 1.0) / rt_powd_snf(1.0 -
        rtU.orbit_tle[5] * rtU.orbit_tle[5], 1.5) * (0.000541308 / (s * s) * 1.5);

      /* '<S111>:1:136' a_o  = a_1*(1 - (1/3)*d_1 - d_1^2 - (134/81)*d_1^3); */
      JD_days_gps = (((1.0 - 0.33333333333333331 * JD_days_gps) - JD_days_gps *
                      JD_days_gps) - 1.654320987654321 * rt_powd_snf(JD_days_gps,
        3.0)) * s;

      /* '<S111>:1:137' d_o  = (3/2)*(k_2/(a_o^2))*((3*cos(i_o)^2 - 1)/(1 - e_o^2)^(3/2)); */
      b_s = cos(rtb_T_TT_J2000);
      b_s = (b_s * b_s * 3.0 - 1.0) / rt_powd_snf(1.0 - rtU.orbit_tle[5] *
        rtU.orbit_tle[5], 1.5) * (0.000541308 / (JD_days_gps * JD_days_gps) *
        1.5);

      /* '<S111>:1:138' n_o_pp   = n_o/(1 + d_o); */
      s = c_c / (1.0 + b_s);

      /* '<S111>:1:139' a_o_pp   = a_o/(1 - d_o); */
      b_s = JD_days_gps / (1.0 - b_s);

      /* '<S111>:1:141' r_p     = r_E*(a_o_pp*(1 - e_o) - a_E); */
      JD_days_gps = ((1.0 - rtU.orbit_tle[5]) * b_s - 1.0) * 6378.137;

      /*  Radius of perigee */
      /*  Check low altitude condition                                     */
      /* '<S111>:1:144' if( a_o_pp*(1-e_o)/a_E < (220/XKMPER + a_E) ) */
      if ((1.0 - rtU.orbit_tle[5]) * b_s < 1.0344928307435228) {
        /* '<S111>:1:145' lowAlt  = TRUE; */
        lowAlt = 1;

        /* '<S111>:1:146' FLAG    = 1; */
      } else {
        /* '<S111>:1:147' else */
        /* '<S111>:1:148' lowAlt  = FALSE; */
        lowAlt = 0;
      }

      /*  Check if perigee is between [98,156]km or below 98km and adjust the */
      /*  constant s accordingly. */
      /* '<S111>:1:153' if( (r_p >= 98) && (r_p <= 156) ) */
      if ((JD_days_gps >= 98.0) && (JD_days_gps <= 156.0)) {
        /* '<S111>:1:154' s_star  = a_o_pp*(1 - e_o) - s + a_E; */
        long_eclp_rad = ((1.0 - rtU.orbit_tle[5]) * b_s - 1.01222928) + 1.0;

        /* '<S111>:1:155' QOMS4   = (QOMS4^(0.25) + s - s_star)^4; */
        b_c = rt_powd_snf(1.0188142770258546 - long_eclp_rad, 4.0);

        /* '<S111>:1:156' s       = s_star; */
      } else {
        if (JD_days_gps < 98.0) {
          /* '<S111>:1:157' elseif( r_p < 98 ) */
          /* '<S111>:1:158' s_star  = 20/XKMPER + a_E; */
          /* '<S111>:1:159' QOMS4   = (QOMS4^(0.25) + s - s_star)^4; */
          b_c = 6.0426196528035638E-8;

          /* '<S111>:1:160' s       = s_star; */
          long_eclp_rad = 1.0031357118857749;
        }
      }

      /*  Constants */
      /* '<S111>:1:164' tht     = cos(i_o); */
      JD_days_gps = cos(rtb_T_TT_J2000);

      /* '<S111>:1:165' xi      = 1/(a_o_pp - s); */
      xi = 1.0 / (b_s - long_eclp_rad);

      /*  cannot be zero since s_star = s ~= a_o_pp */
      /* '<S111>:1:166' b_o     = (1 - e_o^2)^(0.5); */
      b_o = sqrt(1.0 - rtU.orbit_tle[5] * rtU.orbit_tle[5]);

      /* '<S111>:1:167' eta     = a_o_pp*e_o*xi; */
      eta = b_s * rtU.orbit_tle[5] * xi;

      /*  cannot be zero, but could be 1. */
      /* '<S111>:1:168' if( eta == 1 ) */
      if (eta == 1.0) {
        /*  check that (1-eta^2) cannot be zero (catch #2) */
        /* '<S111>:1:169' pos_teme_km     = pos_invalid; */
        /* '<S111>:1:170' vel_teme_kmps   = vel_invalid; */
        rtb_pos_teme_km[0] = 6378.137;
        c_s = 0.0;
        rtb_pos_teme_km[1] = 6378.137;
        xi = 0.0;
        rtb_pos_teme_km[2] = 6878.137;
        b_o = 0.0;

        /* '<S111>:1:171' FLAG = -1; */
      } else {
        /* '<S111>:1:174' C_2     = QOMS4*xi^4*n_o_pp*(1-eta^2)^(-7/2)*((a_o_pp*(1 + ... */
        /* '<S111>:1:175'             (3/2)*eta^2 + 4*e_o*eta + e_o*eta^3)) + ... */
        /* '<S111>:1:176'             (3/2)*k_2*xi*(-0.5+1.5*tht^2)*(8+24*eta^2+3*eta^4)/(1-eta^2)); */
        /* '<S111>:1:177' C_1     = BS*C_2; */
        C_1 = ((((eta * eta * 1.5 + 1.0) + 4.0 * rtU.orbit_tle[5] * eta) +
                rtU.orbit_tle[5] * rt_powd_snf(eta, 3.0)) * b_s + (JD_days_gps *
                JD_days_gps * 1.5 + -0.5) * (0.00081196200000000006 * xi) *
               ((eta * eta * 24.0 + 8.0) + 3.0 * rt_powd_snf(eta, 4.0)) / (1.0 -
                eta * eta)) * (b_c * rt_powd_snf(xi, 4.0) * s * rt_powd_snf(1.0
          - eta * eta, -3.5)) * rtU.orbit_tle[2];

        /* '<S111>:1:178' C_3     = (QOMS4*xi^5*A_30*n_o_pp*a_E*sin(i_o))/(k_2*e_o); */
        /* '<S111>:1:179' C_4     = 2*n_o_pp*QOMS4*xi^4*a_o_pp*b_o^2*(1-eta^2)^(-7/2)* ... */
        /* '<S111>:1:180'             ((2*eta*(1+e_o*eta) + 0.5*e_o + 0.5*eta^3) - ... */
        /* '<S111>:1:181'             (2*k_2*xi)/(a_o_pp*(1-eta^2)) * (3*(1-3*tht^2)* ... */
        /* '<S111>:1:182'             (1-(3/2)*eta^2-2*e_o*eta-0.5*e_o*eta^3) + (3/4)*(1-tht^2)* ... */
        /* '<S111>:1:183'             (2*eta^2-e_o*eta-e_o*eta^3)*cos(2*w_o))); */
        C_4 = ((((rtU.orbit_tle[5] * eta + 1.0) * (2.0 * eta) + 0.5 *
                 rtU.orbit_tle[5]) + 0.5 * rt_powd_snf(eta, 3.0)) - ((((1.0 -
                   eta * eta * 1.5) - 2.0 * rtU.orbit_tle[5] * eta) - 0.5 *
                 rtU.orbit_tle[5] * rt_powd_snf(eta, 3.0)) * ((1.0 - JD_days_gps
                  * JD_days_gps * 3.0) * 3.0) + ((eta * eta * 2.0 -
                  rtU.orbit_tle[5] * eta) - rtU.orbit_tle[5] * rt_powd_snf(eta,
                  3.0)) * ((1.0 - JD_days_gps * JD_days_gps) * 0.75) * cos(2.0 *
                 oblq_rad)) * (0.001082616 * xi / ((1.0 - eta * eta) * b_s))) *
          (2.0 * s * b_c * rt_powd_snf(xi, 4.0) * b_s * (b_o * b_o) *
           rt_powd_snf(1.0 - eta * eta, -3.5));

        /* '<S111>:1:184' C_5     = 0; */
        C_5 = 0.0;

        /* '<S111>:1:185' D_2     = 0; */
        D_2 = 0.0;

        /* '<S111>:1:186' D_3     = 0; */
        D_3 = 0.0;

        /* '<S111>:1:187' D_4     = 0; */
        D_4 = 0.0;

        /* '<S111>:1:188' IL2     = 1.5*C_1; */
        c_s = 1.5 * C_1;

        /* '<S111>:1:189' IL3     = 0; */
        IL3 = 0.0;

        /* '<S111>:1:190' IL4     = 0; */
        IL4 = 0.0;

        /* '<S111>:1:191' IL5     = 0; */
        IL5 = 0.0;

        /* '<S111>:1:193' if( lowAlt  == FALSE ) */
        if (lowAlt == 0) {
          /* '<S111>:1:194' C_5     = 2*QOMS4*xi^4*a_o_pp*b_o^2*(1-eta^2)^(-7/2)*... */
          /* '<S111>:1:195'                                     (1+(11/4)*eta*(eta+e_o) + e_o*eta^3); */
          C_5 = 2.0 * b_c * rt_powd_snf(xi, 4.0) * b_s * (b_o * b_o) *
            rt_powd_snf(1.0 - eta * eta, -3.5) * ((2.75 * eta * (eta +
            rtU.orbit_tle[5]) + 1.0) + rtU.orbit_tle[5] * rt_powd_snf(eta, 3.0));

          /* '<S111>:1:196' D_2     = 4*a_o_pp*xi*C_1^2; */
          D_2 = 4.0 * b_s * xi * (C_1 * C_1);

          /* '<S111>:1:197' D_3     = (4/3)*a_o_pp*xi^2*(17*a_o_pp + s)*C_1^3; */
          D_3 = 1.3333333333333333 * b_s * (xi * xi) * (17.0 * b_s +
            long_eclp_rad) * rt_powd_snf(C_1, 3.0);

          /* '<S111>:1:198' D_4     = (2/3)*a_o_pp*xi^3*(221*a_o_pp + 31*s)*C_1^4; */
          D_4 = 0.66666666666666663 * b_s * rt_powd_snf(xi, 3.0) * (221.0 * b_s
            + 31.0 * long_eclp_rad) * rt_powd_snf(C_1, 4.0);

          /* '<S111>:1:199' IL3     = D_2 + 2*C_1^2; */
          IL3 = C_1 * C_1 * 2.0 + D_2;

          /* '<S111>:1:200' IL4     = 0.25*(3*D_3 + 12*C_1*D_2 + 10*C_1^3); */
          IL4 = ((12.0 * C_1 * D_2 + 3.0 * D_3) + 10.0 * rt_powd_snf(C_1, 3.0)) *
            0.25;

          /* '<S111>:1:201' IL5     = 0.2*(3*D_4 + 12*C_1*D_3 + 6*D_2^2 + 30*C_1^2*D_2 + 15*C_1^4); */
          IL5 = ((((12.0 * C_1 * D_3 + 3.0 * D_4) + D_2 * D_2 * 6.0) + C_1 * C_1
                  * 30.0 * D_2) + 15.0 * rt_powd_snf(C_1, 4.0)) * 0.2;
        }

        /*  Secular effects of atm drag and gravitation. Note that a_o_pp ~= 0 and */
        /*  b_o ~= 0 so no denoms here are zero. */
        /* '<S111>:1:206' M_DF    = M_o + ( 1 + (3*k_2*(3*tht^2-1))/(2*a_o_pp^2*b_o^3) + ... */
        /* '<S111>:1:207'             (3*k_2^2*(13-78*tht^2+137*tht^4))/(16*a_o_pp^4*b_o^7) )* ... */
        /* '<S111>:1:208'             n_o_pp*tsince; */
        M_DF = (((JD_days_gps * JD_days_gps * 3.0 - 1.0) * 0.0016239240000000001
                 / (b_s * b_s * 2.0 * rt_powd_snf(b_o, 3.0)) + 1.0) + ((13.0 -
                  JD_days_gps * JD_days_gps * 78.0) + 137.0 * rt_powd_snf
                 (JD_days_gps, 4.0)) * 8.7904305259200008E-7 / (16.0 *
                 rt_powd_snf(b_s, 4.0) * rt_powd_snf(b_o, 7.0))) * s *
          mean_anom_sun_rad + c;

        /* '<S111>:1:209' w_DF    = w_o + ( (-3*k_2*(1-5*tht^2))/(2*a_o_pp^2*b_o^3) + ... */
        /* '<S111>:1:210'             (3*k_2^2*(7-114*tht^2+395*tht^4))/(16*a_o_pp^4*b_o^8) + ... */
        /* '<S111>:1:211'             (5*k_4*(3-36*tht^2+49*tht^4))/(4*a_o_pp^4*b_o^8) )*n_o_pp*tsince; */
        c_c = ((((7.0 - JD_days_gps * JD_days_gps * 114.0) + 395.0 * rt_powd_snf
                 (JD_days_gps, 4.0)) * 8.7904305259200008E-7 / (16.0 *
                 rt_powd_snf(b_s, 4.0) * rt_powd_snf(b_o, 8.0)) + (1.0 -
                 JD_days_gps * JD_days_gps * 5.0) * -0.0016239240000000001 /
                (b_s * b_s * 2.0 * rt_powd_snf(b_o, 3.0))) + ((3.0 - JD_days_gps
                 * JD_days_gps * 36.0) + 49.0 * rt_powd_snf(JD_days_gps, 4.0)) *
               3.1049437500000002E-6 / (4.0 * rt_powd_snf(b_s, 4.0) *
                rt_powd_snf(b_o, 8.0))) * s * mean_anom_sun_rad + oblq_rad;

        /* '<S111>:1:212' Om_DF   = Om_o + ( (-3*k_2*tht)/(a_o_pp^2*b_o^4) +... */
        /* '<S111>:1:213'             (3*k_2^2*(4*tht-19*tht^3))/(2*a_o_pp^4*b_o^8) +... */
        /* '<S111>:1:214'             (5*k_4*tht*(3-7*tht^2))/(2*a_o_pp^4*b_o^8) )*n_o_pp*tsince; */
        /* '<S111>:1:216' Om      = Om_DF - (21/2)*( (n_o_pp*k_2*tht)/(a_o_pp^2*b_o^2) )*C_1*tsince^2; */
        long_eclp_rad = ((((4.0 * JD_days_gps - 19.0 * rt_powd_snf(JD_days_gps,
          3.0)) * 8.7904305259200008E-7 / (2.0 * rt_powd_snf(b_s, 4.0) *
          rt_powd_snf(b_o, 8.0)) + -0.0016239240000000001 * JD_days_gps / (b_s *
          b_s * rt_powd_snf(b_o, 4.0))) + (3.0 - JD_days_gps * JD_days_gps * 7.0)
                          * (3.1049437500000002E-6 * JD_days_gps) / (2.0 *
          rt_powd_snf(b_s, 4.0) * rt_powd_snf(b_o, 8.0))) * s *
                         mean_anom_sun_rad + rtU.orbit_tle[4] * 0.0174532925) -
          s * 0.000541308 * JD_days_gps / (b_s * b_s * (b_o * b_o)) * 10.5 * C_1
          * (mean_anom_sun_rad * mean_anom_sun_rad);

        /* '<S111>:1:218' if( lowAlt == FALSE ) */
        if (lowAlt == 0) {
          /*  #5 %     */
          /* '<S111>:1:219' d_w     = BS*C_3*cos(w_o)*tsince; */
          oblq_rad = b_c * rt_powd_snf(xi, 5.0) * 2.538815E-6 * s * sin
            (rtb_T_TT_J2000) / (0.000541308 * rtU.orbit_tle[5]) * rtU.orbit_tle
            [2] * cos(oblq_rad) * mean_anom_sun_rad;

          /* '<S111>:1:220' d_M     = -(2/3)*QOMS4*BS*xi^4*(a_E/(e_o*eta))* ... */
          /* '<S111>:1:221'                 ( (1+eta*cos(M_DF))^3 - (1 + eta*cos(M_o))^3 ); */
          b_c = -0.66666666666666663 * b_c * rtU.orbit_tle[2] * rt_powd_snf(xi,
            4.0) * (1.0 / (rtU.orbit_tle[5] * eta)) * (rt_powd_snf(eta * cos
            (M_DF) + 1.0, 3.0) - rt_powd_snf(eta * cos(c) + 1.0, 3.0));

          /* '<S111>:1:222' M_p     = M_DF + d_w + d_M; */
          eta = (M_DF + oblq_rad) + b_c;

          /* '<S111>:1:223' w       = w_DF - d_w - d_M; */
          c_c = (c_c - oblq_rad) - b_c;

          /* '<S111>:1:224' e       = e_o - BS*C_4*tsince - BS*C_5*( sin(M_p) - sin(M_o) ); */
          b_c = (rtU.orbit_tle[5] - rtU.orbit_tle[2] * C_4 * mean_anom_sun_rad)
            - rtU.orbit_tle[2] * C_5 * (sin(eta) - sin(c));

          /* '<S111>:1:225' a       = a_o_pp*( 1 - C_1*tsince - D_2*tsince^2 - D_3*tsince^3 - ... */
          /* '<S111>:1:226'                 D_4*tsince^4 )^2; */
          c = (((1.0 - C_1 * mean_anom_sun_rad) - mean_anom_sun_rad *
                mean_anom_sun_rad * D_2) - D_3 * rt_powd_snf(mean_anom_sun_rad,
                3.0)) - D_4 * rt_powd_snf(mean_anom_sun_rad, 4.0);
          c = c * c * b_s;

          /* '<S111>:1:227' L       = M_p + w + Om + n_o_pp*( IL2*tsince^2 + IL3*tsince^3 +... */
          /* '<S111>:1:228'             IL4*tsince^4 + IL5*tsince^5 ); */
          mean_anom_sun_rad = (((mean_anom_sun_rad * mean_anom_sun_rad * c_s +
            IL3 * rt_powd_snf(mean_anom_sun_rad, 3.0)) + IL4 * rt_powd_snf
                                (mean_anom_sun_rad, 4.0)) + IL5 * rt_powd_snf
                               (mean_anom_sun_rad, 5.0)) * s + ((eta + c_c) +
            long_eclp_rad);
        } else {
          /* '<S111>:1:229' else */
          /* '<S111>:1:230' M_p     = M_DF; */
          /* '<S111>:1:231' w       = w_DF; */
          /* '<S111>:1:232' a       = a_o_pp*(1 - C_1*tsince)^2; */
          b_c = 1.0 - C_1 * mean_anom_sun_rad;
          c = b_c * b_c * b_s;

          /* '<S111>:1:233' e       = e_o - BS*C_4*tsince; */
          b_c = rtU.orbit_tle[5] - rtU.orbit_tle[2] * C_4 * mean_anom_sun_rad;

          /* '<S111>:1:234' L       = M_p + w + Om + n_o_pp*IL2*tsince^2; */
          mean_anom_sun_rad = ((M_DF + c_c) + long_eclp_rad) + s * c_s *
            (mean_anom_sun_rad * mean_anom_sun_rad);
        }

        /* '<S111>:1:237' if( (a == 0) || (e >= 1) ) */
        if ((c == 0.0) || (b_c >= 1.0)) {
          /*  catch divide by zero conditions (catch #3) */
          /* '<S111>:1:238' pos_teme_km       = pos_invalid; */
          /* '<S111>:1:239' vel_teme_kmps     = vel_invalid; */
          rtb_pos_teme_km[0] = 6378.137;
          c_s = 0.0;
          rtb_pos_teme_km[1] = 6378.137;
          xi = 0.0;
          rtb_pos_teme_km[2] = 6878.137;
          b_o = 0.0;

          /* '<S111>:1:240' FLAG = -1; */
        } else {
          /* '<S111>:1:243' b       = sqrt(1-e^2); */
          s = sqrt(1.0 - b_c * b_c);

          /* '<S111>:1:244' n       = XKE/(a^(3/2)); */
          oblq_rad = 0.0743669161 / rt_powd_snf(c, 1.5);

          /*  Add the long-period periodic terms */
          /* '<S111>:1:247' a_xN    = e*cos(w); */
          b_s = b_c * cos(c_c);

          /* '<S111>:1:248' L_L     = (A_30*sin(i_o)/(8*k_2*a*b^2))*e*cos(w)*((3+5*tht)/(1+tht)); */
          /* '<S111>:1:249' a_yNL   = A_30*sin(i_o)/(4*k_2*a*b^2); */
          /* '<S111>:1:250' L_T     = L + L_L; */
          /* '<S111>:1:251' a_yN    = e*sin(w) + a_yNL; */
          c_s = 2.538815E-6 * sin(rtb_T_TT_J2000) / (0.002165232 * c * (s * s))
            + b_c * sin(c_c);

          /* '<S111>:1:253' U       = mod(L_T - Om,2*pi); */
          mean_anom_sun_rad = ((2.538815E-6 * sin(rtb_T_TT_J2000) / (0.004330464
            * c * (s * s)) * b_c * cos(c_c) * ((5.0 * JD_days_gps + 3.0) / (1.0
            + JD_days_gps)) + mean_anom_sun_rad) - long_eclp_rad) /
            6.2831853071795862;
          if (fabs(mean_anom_sun_rad - rt_roundd_snf(mean_anom_sun_rad)) <=
              2.2204460492503131E-16 * fabs(mean_anom_sun_rad)) {
            mean_anom_sun_rad = 0.0;
          } else {
            mean_anom_sun_rad = (mean_anom_sun_rad - floor(mean_anom_sun_rad)) *
              6.2831853071795862;
          }

          /* '<S111>:1:254' Epw     = kepler(U,a_yN,a_xN); */
          /*  Solves Kepler's equation for Epw = E + w using iterative method */
          /* '<S111>:1:304' tol         = 1e-8; */
          /* '<S111>:1:305' iter_max    = 10; */
          /* '<S111>:1:306' Epw         = U; */
          c_c = mean_anom_sun_rad;

          /* '<S111>:1:307' Epw_new     = 0; */
          b_c = 0.0;

          /* '<S111>:1:308' iter        = 0; */
          lowAlt = 0;

          /* '<S111>:1:310' while( (abs(Epw - Epw_new) > tol) && (iter < iter_max) ) */
          while ((fabs(c_c - b_c) > 1.0E-8) && (lowAlt < 10)) {
            /* '<S111>:1:311' Epw     = Epw_new; */
            c_c = b_c;

            /* '<S111>:1:312' dEpw    = (U-a_yN*cos(Epw) + a_xN*sin(Epw) - Epw)/ ... */
            /* '<S111>:1:313'                     (-a_yN*sin(Epw) - a_xN*cos(Epw) + 1); */
            /* '<S111>:1:314' Epw_new = Epw + dEpw; */
            b_c += (((mean_anom_sun_rad - c_s * cos(b_c)) + b_s * sin(b_c)) -
                    b_c) / ((-c_s * sin(b_c) - b_s * cos(b_c)) + 1.0);

            /* '<S111>:1:315' iter    = iter +1; */
            lowAlt++;
          }

          /* '<S111>:1:318' Epw = Epw_new; */
          /*  Preliminary quantities for short-period periodics */
          /* '<S111>:1:257' ecE     = a_xN*cos(Epw) + a_yN*sin(Epw); */
          /* '<S111>:1:258' esE     = a_xN*sin(Epw) - a_yN*cos(Epw); */
          IL3 = b_s * sin(b_c) - c_s * cos(b_c);

          /* '<S111>:1:259' e_L     = (a_xN^2 + a_yN^2)^(1/2); */
          c_c = sqrt(b_s * b_s + c_s * c_s);

          /* '<S111>:1:260' p_L     = a*(1 - e_L^2); */
          s = (1.0 - c_c * c_c) * c;

          /* '<S111>:1:261' r       = a*(1 - ecE); */
          mean_anom_sun_rad = (1.0 - (b_s * cos(b_c) + c_s * sin(b_c))) * c;

          /* '<S111>:1:262' if( (r == 0) || (p_L == 0) ) */
          if ((mean_anom_sun_rad == 0.0) || (s == 0.0)) {
            /*  (catch #4) */
            /* '<S111>:1:263' pos_teme_km       = pos_invalid; */
            /* '<S111>:1:264' vel_teme_kmps     = vel_invalid; */
            rtb_pos_teme_km[0] = 6378.137;
            c_s = 0.0;
            rtb_pos_teme_km[1] = 6378.137;
            xi = 0.0;
            rtb_pos_teme_km[2] = 6878.137;
            b_o = 0.0;

            /* '<S111>:1:265' FLAG = -1; */
          } else {
            /* '<S111>:1:268' r_dot   = XKE*sqrt(a)*esE/r; */
            /* '<S111>:1:269' r_f_dot = XKE*sqrt(p_L)/r; */
            /* '<S111>:1:270' cosu    = (a/r)*( cos(Epw) - a_xN + ((a_yN*esE)/(1+sqrt(1 - e_L^2))) ); */
            /* '<S111>:1:271' sinu    = (a/r)*( sin(Epw) - a_yN - ((a_xN*esE)/(1 + sqrt(1 - e_L^2))) ); */
            /* '<S111>:1:272' u       = atan2(sinu,cosu); */
            b_c = rt_atan2d_snf(((sin(b_c) - c_s) - b_s * IL3 / (sqrt(1.0 - c_c *
              c_c) + 1.0)) * (c / mean_anom_sun_rad), (c_s * IL3 / (sqrt(1.0 -
              c_c * c_c) + 1.0) + (cos(b_c) - b_s)) * (c / mean_anom_sun_rad));

            /* '<S111>:1:273' dr      = (k_2/(2*p_L))*(1 - tht^2)*cos(2*u); */
            /* '<S111>:1:274' du      = -(k_2/(4*p_L^2))*(7*tht^2 - 1)*sin(2*u); */
            /* '<S111>:1:275' dOm     = (3*k_2*tht/(2*p_L^2))*sin(2*u); */
            /* '<S111>:1:276' di      = (3*k_2*tht/(2*p_L^2))*sin(i_o)*cos(2*u); */
            /* '<S111>:1:277' dr_dot  = -((k_2*n)/p_L)*(1-tht^2)*sin(2*u); */
            /* '<S111>:1:278' dr_f_dot    = (k_2*n/p_L)*( (1-tht^2)*cos(2*u) - (3/2)*(1-3*tht^2) ); */
            /*  Add the short-period periodics to get osculating elements */
            /* '<S111>:1:281' r_k     = r*(1 - (3/2)*k_2*sqrt(1 - e_L^2)*(3*tht^2 - 1)/p_L^2) + dr; */
            c_c = (1.0 - sqrt(1.0 - c_c * c_c) * 0.00081196200000000006 *
                   (JD_days_gps * JD_days_gps * 3.0 - 1.0) / (s * s)) *
              mean_anom_sun_rad + 0.000541308 / (2.0 * s) * (1.0 - JD_days_gps *
              JD_days_gps) * cos(2.0 * b_c);

            /* '<S111>:1:282' u_k     = u + du; */
            b_s = -(0.000541308 / (s * s * 4.0)) * (JD_days_gps * JD_days_gps *
              7.0 - 1.0) * sin(2.0 * b_c) + b_c;

            /* '<S111>:1:283' Om_k    = Om + dOm; */
            long_eclp_rad += 0.0016239240000000001 * JD_days_gps / (s * s * 2.0)
              * sin(2.0 * b_c);

            /* '<S111>:1:284' i_k     = i_o + di; */
            c_s = 0.0016239240000000001 * JD_days_gps / (s * s * 2.0) * sin
              (rtb_T_TT_J2000) * cos(2.0 * b_c) + rtb_T_TT_J2000;

            /* '<S111>:1:285' r_dot_k     = r_dot + dr_dot; */
            rtb_T_TT_J2000 = -(0.000541308 * oblq_rad / s) * (1.0 - JD_days_gps *
              JD_days_gps) * sin(2.0 * b_c) + 0.0743669161 * sqrt(c) * IL3 /
              mean_anom_sun_rad;

            /* '<S111>:1:286' r_f_dot_k   = r_f_dot + dr_f_dot; */
            JD_days_gps = ((1.0 - JD_days_gps * JD_days_gps) * cos(2.0 * b_c) -
                           (1.0 - JD_days_gps * JD_days_gps * 3.0) * 1.5) *
              (0.000541308 * oblq_rad / s) + 0.0743669161 * sqrt(s) /
              mean_anom_sun_rad;

            /*  Create unit orientation vectors */
            /* '<S111>:1:289' M       = [ -sin(Om_k)*cos(i_k); cos(Om_k)*cos(i_k); sin(i_k)]; */
            M[0] = -sin(long_eclp_rad) * cos(c_s);
            M[1] = cos(long_eclp_rad) * cos(c_s);
            M[2] = sin(c_s);

            /* '<S111>:1:290' N       = [ cos(Om_k); sin(Om_k); 0 ]; */
            N[0] = cos(long_eclp_rad);
            N[1] = sin(long_eclp_rad);

            /* '<S111>:1:292' U       = M.*sin(u_k) + N.*cos(u_k); */
            long_eclp_rad = sin(b_s);
            mean_anom_sun_rad = cos(b_s);

            /* '<S111>:1:293' V       = M.*cos(u_k) - N.*sin(u_k); */
            IL4 = M[0] * long_eclp_rad + N[0] * mean_anom_sun_rad;
            rtb_pos_teme_km[0] = c_c * IL4 * 6378.137;
            c_s = IL4;
            IL4 = M[1] * long_eclp_rad + N[1] * mean_anom_sun_rad;
            rtb_pos_teme_km[1] = c_c * IL4 * 6378.137;
            xi = IL4;
            IL4 = M[2] * long_eclp_rad + 0.0 * mean_anom_sun_rad;
            rtb_pos_teme_km[2] = c_c * IL4 * 6378.137;
            long_eclp_rad = cos(b_s);
            mean_anom_sun_rad = sin(b_s);

            /*  Find position and velocity in km & km/s */
            /* '<S111>:1:296' pos_teme_km     = r_k.*U.*XKMPER; */
            /* '<S111>:1:297' vel_teme_kmps   = (r_dot_k.*U + r_f_dot_k.*V).*(VKMPS); */
            c_s = ((M[0] * long_eclp_rad - N[0] * mean_anom_sun_rad) *
                   JD_days_gps + rtb_T_TT_J2000 * c_s) * 106.30228333333334;
            xi = ((M[1] * long_eclp_rad - N[1] * mean_anom_sun_rad) *
                  JD_days_gps + rtb_T_TT_J2000 * xi) * 106.30228333333334;
            b_o = ((M[2] * long_eclp_rad - 0.0 * mean_anom_sun_rad) *
                   JD_days_gps + rtb_T_TT_J2000 * IL4) * 106.30228333333334;
          }
        }
      }
    }
  }

  /* End of MATLAB Function: '<S65>/MATLAB Function' */
  for (idx2 = 0; idx2 < 3; idx2++) {
    /* Gain: '<S65>/Gain' incorporates:
     *  Product: '<S65>/Product'
     */
    M[idx2] = 1000.0 * (rtb_teme_to_gcrf[idx2 + 6] * rtb_pos_teme_km[2] +
                        (rtb_teme_to_gcrf[idx2 + 3] * rtb_pos_teme_km[1] +
                         rtb_teme_to_gcrf[idx2] * rtb_pos_teme_km[0]));
  }

  /* MATLAB Function: '<S66>/MATLAB Function1' */
  /*  Constants */
  /* MATLAB Function 'sun_vector_lib/MATLAB Function1': '<S113>:1' */
  /* '<S113>:1:4' M2KM        = 1e-3; */
  /* '<S113>:1:5' ECCE2       = 0.006694385000; */
  /* '<S113>:1:6' RE          = 6378.137; */
  /* '<S113>:1:7' TRUE        = 1; */
  /* '<S113>:1:8' FALSE       = 0; */
  /*  ----- */
  /*  Convert to sc position vector to km if necessary */
  /* '<S113>:1:12' sc_pos_eci_km   = sc_pos_eci_m*M2KM; */
  rtb_pos_teme_km[0] = M[0] * 0.001;
  rtb_pos_teme_km[1] = M[1] * 0.001;
  rtb_pos_teme_km[2] = M[2] * 0.001;

  /* ----- */
  /*  Main Function */
  /* '<S113>:1:16' LOS     = FALSE; */
  lowAlt = 0;

  /* '<S113>:1:18' sun_vector_eci_km(3)    = sun_vector_eci_km(3)/(sqrt(1 - ECCE2)); */
  rtb_sun_vector_eci_km[2] /= 0.99664718682189635;

  /* '<S113>:1:19' sc_pos_eci_km(3)        = sc_pos_eci_km(3)/(sqrt(1 - ECCE2)); */
  rtb_pos_teme_km[2] /= 0.99664718682189635;

  /* '<S113>:1:21' sun_vec     = sun_vector_eci_km; */
  /* '<S113>:1:22' sc_vec      = sc_pos_eci_km; */
  /* '<S113>:1:24' sc2sun_unit  = (sun_vec - sc_vec)/norm(sun_vec - sc_vec); */
  rtb_sun_vector_eci_km_0[0] = rtb_sun_vector_eci_km[0] - rtb_pos_teme_km[0];
  rtb_sun_vector_eci_km_0[1] = rtb_sun_vector_eci_km[1] - rtb_pos_teme_km[1];
  rtb_sun_vector_eci_km_0[2] = rtb_sun_vector_eci_km[2] - rtb_pos_teme_km[2];
  mean_anom_sun_rad = norm_c(rtb_sun_vector_eci_km_0);

  /*  Determine if the sc is in the light or shadow */
  /*    Call vector 1 the sun, vector 2 the sc */
  /* '<S113>:1:29' mag1    = norm(sun_vec); */
  JD_days_gps = norm_c(rtb_sun_vector_eci_km);

  /* '<S113>:1:30' mag2    = norm(sc_vec); */
  rtb_T_TT_J2000 = norm_c(rtb_pos_teme_km);

  /* '<S113>:1:32' mag1_sq     = mag1*mag1; */
  JD_days_gps *= JD_days_gps;

  /* '<S113>:1:33' mag2_sq     = mag2*mag2; */
  /* '<S113>:1:35' sun_sc_dot  = dot(sun_vec,sc_vec); */
  long_eclp_rad = (rtb_sun_vector_eci_km[0] * rtb_pos_teme_km[0] +
                   rtb_sun_vector_eci_km[1] * rtb_pos_teme_km[1]) +
    rtb_sun_vector_eci_km[2] * rtb_pos_teme_km[2];

  /*  Find t_min */
  /* '<S113>:1:38' t_min_num   = mag1_sq - sun_sc_dot; */
  /* '<S113>:1:39' t_min_den   = mag1_sq + mag2_sq - 2*sun_sc_dot; */
  rtb_T_TT_J2000 = (rtb_T_TT_J2000 * rtb_T_TT_J2000 + JD_days_gps) - 2.0 *
    long_eclp_rad;

  /* '<S113>:1:41' if ( t_min_den < 0.0001  ) */
  if (rtb_T_TT_J2000 < 0.0001) {
    /* '<S113>:1:42' t_min = 0.0; */
    rtb_T_TT_J2000 = 0.0;
  } else {
    /* '<S113>:1:43' else */
    /* '<S113>:1:44' t_min = ( t_min_num ) / ( t_min_den ); */
    rtb_T_TT_J2000 = (JD_days_gps - long_eclp_rad) / rtb_T_TT_J2000;
  }

  /* '<S113>:1:47' c_t_min_sq  = ((1-t_min)*mag1_sq + sun_sc_dot*t_min)/RE^2; */
  /*  Check LoS */
  /* '<S113>:1:50' if( t_min < 0 || t_min > 0.999979 ) */
  if ((rtb_T_TT_J2000 < 0.0) || (rtb_T_TT_J2000 > 0.999979)) {
    /* '<S113>:1:51' LOS     = TRUE; */
    lowAlt = 1;
  }

  /* '<S113>:1:56' sc_in_sun   = LOS; */
  rtb_sun_vector_eci_km[0] = (rtb_sun_vector_eci_km[0] - rtb_pos_teme_km[0]) /
    mean_anom_sun_rad;
  rtb_sun_vector_eci_km[1] = (rtb_sun_vector_eci_km[1] - rtb_pos_teme_km[1]) /
    mean_anom_sun_rad;
  C_1 = (rtb_sun_vector_eci_km[2] - rtb_pos_teme_km[2]) / mean_anom_sun_rad;

  /* Gain: '<S63>/day2sec' incorporates:
   *  MATLAB Function: '<S115>/time-conversion-lib'
   *  Sum: '<S63>/Sum'
   */
  mean_anom_sun_rad = ((rtb_TrigonometricFunction1_o1 - 2.451545E+6) - 6939.5) *
    86400.0;

  /* Product: '<S63>/Product' incorporates:
   *  Constant: '<S63>/o_prec'
   */
  rtb_T_TT_J2000 = 0.0011432818469647177 * mean_anom_sun_rad;

  /* Trigonometry: '<S63>/Trigonometric Function1' */
  rtb_TrigonometricFunction1_o1 = sin(rtb_T_TT_J2000);
  rtb_T_TT_J2000 = cos(rtb_T_TT_J2000);

  /* Product: '<S63>/Product2' incorporates:
   *  Constant: '<S63>/o_prec1'
   *  Gain: '<S63>/Gain'
   */
  long_eclp_rad = 2.0 * mean_anom_sun_rad * 0.0011432818469647177;

  /* Trigonometry: '<S63>/Trigonometric Function3' */
  JD_days_gps = sin(long_eclp_rad);
  long_eclp_rad = cos(long_eclp_rad);

  /* Product: '<S63>/Product6' incorporates:
   *  Constant: '<S63>/o_prec2'
   *  Gain: '<S63>/Gain1'
   */
  c = 3.0 * mean_anom_sun_rad * 0.0011432818469647177;

  /* Trigonometry: '<S63>/Trigonometric Function2' */
  mean_anom_sun_rad = sin(c);
  c = cos(c);

  /* Sum: '<S63>/Add' incorporates:
   *  Product: '<S63>/Product1'
   *  Product: '<S63>/Product3'
   *  Product: '<S63>/Product4'
   *  Product: '<S63>/Product7'
   *  Product: '<S63>/Product8'
   *  Product: '<S63>/Product9'
   */
  rtb_Sum_o[0] = (((((6.91379616095366E-7 * rtb_TrigonometricFunction1_o1 +
                      -3.1026951075018163E-6) + 2.9104511018230211E-6 *
                     rtb_T_TT_J2000) + 3.8241562712542387E-6 * JD_days_gps) +
                   -1.1869102846245769E-5 * long_eclp_rad) +
                  -2.2530640096590495E-6 * mean_anom_sun_rad) +
    2.1929753673351795E-7 * c;
  rtb_Sum_o[1] = (((((-1.2831543857309969E-6 * rtb_TrigonometricFunction1_o1 +
                      3.722221729683332E-6) + 4.8221621875746385E-7 *
                     rtb_T_TT_J2000) + 1.8595023245999862E-5 * JD_days_gps) +
                   -2.5166190729574583E-5 * long_eclp_rad) +
                  -5.2045517041145835E-6 * mean_anom_sun_rad) +
    -1.7289538390470034E-6 * c;
  rtb_Sum_o[2] = (((((-1.0091052857023282E-6 * rtb_TrigonometricFunction1_o1 +
                      -1.034525887746725E-5) + 1.519520402880094E-6 *
                     rtb_T_TT_J2000) + -2.7220644638230336E-5 * JD_days_gps) +
                   -1.8107441912348641E-5 * long_eclp_rad) +
                  -1.7140462354677309E-6 * mean_anom_sun_rad) +
    5.5535077057277425E-6 * c;

  /* S-Function (sdsp2norm2): '<S63>/Normalization' */
  IL4 = 1.0 / (sqrt((rtb_Sum_o[0] * rtb_Sum_o[0] + rtb_Sum_o[1] * rtb_Sum_o[1])
                    + rtb_Sum_o[2] * rtb_Sum_o[2]) + 1.0E-10);
  rtb_Normalization[0] = rtb_Sum_o[0] * IL4;
  rtb_Normalization[1] = rtb_Sum_o[1] * IL4;
  rtb_Normalization[2] = rtb_Sum_o[2] * IL4;

  /* If: '<S12>/If' incorporates:
   *  Inport: '<Root>/mag_vec_body_T'
   *  Inport: '<Root>/sun_vec_body_sunsensor'
   *  Inport: '<S19>/bias_min'
   *  Inport: '<S19>/cov_min'
   *  Inport: '<S19>/q_min'
   *  Logic: '<S9>/Logical Operator'
   *  Logic: '<S9>/Logical Operator1'
   *  Logic: '<S9>/Logical Operator2'
   *  MATLAB Function: '<S18>/update_state '
   *  MATLAB Function: '<S66>/MATLAB Function1'
   *  UnitDelay: '<S9>/Unit Delay'
   *  UnitDelay: '<S9>/Unit Delay1'
   *  UnitDelay: '<S9>/Unit Delay2'
   */
  if ((rtU.mag_vec_body_T[3] != 0.0) && rtb_LogicalOperator_m &&
      ((rtU.sun_vec_body_sunsensor[3] != 0.0) && (lowAlt != 0))) {
    /* Outputs for IfAction SubSystem: '<S12>/If Action Subsystem' incorporates:
     *  ActionPort: '<S18>/Action Port'
     */
    /* MATLAB Function: '<S18>/convert_inertial_body' incorporates:
     *  SignalConversion: '<S20>/TmpSignal ConversionAt SFunction Inport2'
     *  UnitDelay: '<S9>/Unit Delay'
     */
    /* MATLAB Function 'Estimation_EKF /Update Step /If Action Subsystem/convert_inertial_body': '<S20>:1' */
    /* '<S20>:1:3' rotation_matrix = att(q_min); */
    /* '<S20>:1:10' q0 = q(1); */
    /* '<S20>:1:11' qv = q(2:4); */
    /* '<S20>:1:13' dcm = (2*q0^2-1)*eye(3) + 2*(qv*qv') - 2*q0*skew(qv); */
    c = rtDW.UnitDelay_DSTATE[0] * rtDW.UnitDelay_DSTATE[0] * 2.0 - 1.0;

    /* '<S20>:1:21' X = [ 0    -x(3)   x(2); */
    /* '<S20>:1:22'      x(3)   0     -x(1); */
    /* '<S20>:1:23'     -x(2)   x(1)   0 ]; */
    b_c = 2.0 * rtDW.UnitDelay_DSTATE[0];
    for (idx2 = 0; idx2 < 3; idx2++) {
      rtb_MatrixMultiply[idx2] = rtDW.UnitDelay_DSTATE[1 + idx2] *
        rtDW.UnitDelay_DSTATE[1];
      rtb_MatrixMultiply[idx2 + 3] = rtDW.UnitDelay_DSTATE[1 + idx2] *
        rtDW.UnitDelay_DSTATE[2];
      rtb_MatrixMultiply[idx2 + 6] = rtDW.UnitDelay_DSTATE[1 + idx2] *
        rtDW.UnitDelay_DSTATE[3];
    }

    rotation_matrix_0[0] = 0.0;
    rotation_matrix_0[3] = -rtDW.UnitDelay_DSTATE[3];
    rotation_matrix_0[6] = rtDW.UnitDelay_DSTATE[2];
    rotation_matrix_0[1] = rtDW.UnitDelay_DSTATE[3];
    rotation_matrix_0[4] = 0.0;
    rotation_matrix_0[7] = -rtDW.UnitDelay_DSTATE[1];
    rotation_matrix_0[2] = -rtDW.UnitDelay_DSTATE[2];
    rotation_matrix_0[5] = rtDW.UnitDelay_DSTATE[1];
    rotation_matrix_0[8] = 0.0;
    for (idx2 = 0; idx2 < 3; idx2++) {
      rotation_matrix[3 * idx2] = ((real_T)b_1[3 * idx2] * c +
        rtb_MatrixMultiply[3 * idx2] * 2.0) - rotation_matrix_0[3 * idx2] * b_c;
      rotation_matrix[1 + 3 * idx2] = ((real_T)b_1[3 * idx2 + 1] * c +
        rtb_MatrixMultiply[3 * idx2 + 1] * 2.0) - rotation_matrix_0[3 * idx2 + 1]
        * b_c;
      rotation_matrix[2 + 3 * idx2] = ((real_T)b_1[3 * idx2 + 2] * c +
        rtb_MatrixMultiply[3 * idx2 + 2] * 2.0) - rotation_matrix_0[3 * idx2 + 2]
        * b_c;
    }

    /*  dcm = [q(1)^2 + q(2)^2 - q(3)^2 - q(4)^2,   2*(q(2)*q(3)+q(1)*q(4)),    2*(q(2)*q(4) - q(1)*q(3)); */
    /*          2*(q(2)*q(3) - q(1)*q(4)),          q(1)^2-q(2)^2+q(3)^2-q(4)^2,    2*(q(3)*q(4) + q(1)*q(2)); */
    /*          2*(q(2)*q(4)+q(1)*q(3)),            2*(q(3)*q(4)-q(1)*q(2)),        q(1)^2-q(2)^2-q(3)^2+q(4)^2]; */
    /* '<S20>:1:4' body_est = blkdiag(rotation_matrix,rotation_matrix)*meas_eci; */
    memset(&KHI[0], 0, 36U * sizeof(real_T));
    for (idx2 = 0; idx2 < 3; idx2++) {
      KHI[6 * idx2] = rotation_matrix[3 * idx2];
      KHI[3 + 6 * (3 + idx2)] = rotation_matrix[3 * idx2];
      KHI[1 + 6 * idx2] = rotation_matrix[3 * idx2 + 1];
      KHI[4 + 6 * (3 + idx2)] = rotation_matrix[3 * idx2 + 1];
      KHI[2 + 6 * idx2] = rotation_matrix[3 * idx2 + 2];
      KHI[5 + 6 * (3 + idx2)] = rotation_matrix[3 * idx2 + 2];

      /* SignalConversion: '<S20>/TmpSignal ConversionAt SFunction Inport2' */
      rtb_Normalization_0[idx2] = rtb_Normalization[idx2];
      rtb_Normalization_0[idx2 + 3] = rtDW.u1[idx2];
    }

    for (idx2 = 0; idx2 < 6; idx2++) {
      rtb_body_est[idx2] = 0.0;
      for (sigIdx = 0; sigIdx < 6; sigIdx++) {
        rtb_body_est[idx2] += KHI[6 * sigIdx + idx2] *
          rtb_Normalization_0[sigIdx];
      }
    }

    /* End of MATLAB Function: '<S18>/convert_inertial_body' */

    /* MATLAB Function: '<S18>/observation_matrix' */
    /* MATLAB Function 'Estimation_EKF /Update Step /If Action Subsystem/observation_matrix': '<S23>:1' */
    /* '<S23>:1:3' H = [  skew(body_est(1:3))     zeros(3); */
    /* '<S23>:1:4'        skew(body_est(4:6))     zeros(3)]; */
    /* '<S23>:1:9' S = [0  -v(3)   v(2); */
    /* '<S23>:1:10'     v(3)    0   -v(1); */
    /* '<S23>:1:11'     -v(2)   v(1)    0]; */
    /* '<S23>:1:9' S = [0  -v(3)   v(2); */
    /* '<S23>:1:10'     v(3)    0   -v(1); */
    /* '<S23>:1:11'     -v(2)   v(1)    0]; */
    rtb_Merge2[0] = 0.0;
    rtb_Merge2[6] = -rtb_body_est[2];
    rtb_Merge2[12] = rtb_body_est[1];
    rtb_Merge2[1] = rtb_body_est[2];
    rtb_Merge2[7] = 0.0;
    rtb_Merge2[13] = -rtb_body_est[0];
    rtb_Merge2[2] = -rtb_body_est[1];
    rtb_Merge2[8] = rtb_body_est[0];
    rtb_Merge2[14] = 0.0;
    rtb_Merge2[3] = 0.0;
    rtb_Merge2[9] = -rtb_body_est[5];
    rtb_Merge2[15] = rtb_body_est[4];
    rtb_Merge2[4] = rtb_body_est[5];
    rtb_Merge2[10] = 0.0;
    rtb_Merge2[16] = -rtb_body_est[3];
    rtb_Merge2[5] = -rtb_body_est[4];
    rtb_Merge2[11] = rtb_body_est[3];
    rtb_Merge2[17] = 0.0;
    for (idx2 = 0; idx2 < 3; idx2++) {
      rtb_Merge2[6 * (idx2 + 3)] = 0.0;
      rtb_Merge2[3 + 6 * (idx2 + 3)] = 0.0;
      rtb_Merge2[1 + 6 * (idx2 + 3)] = 0.0;
      rtb_Merge2[4 + 6 * (idx2 + 3)] = 0.0;
      rtb_Merge2[2 + 6 * (idx2 + 3)] = 0.0;
      rtb_Merge2[5 + 6 * (idx2 + 3)] = 0.0;
    }

    /* End of MATLAB Function: '<S18>/observation_matrix' */

    /* MATLAB Function: '<S18>/kalman_gain' incorporates:
     *  Inport: '<Root>/gyro_omega_body_radps'
     *  UnitDelay: '<S9>/Unit Delay2'
     */
    /* MATLAB Function 'Estimation_EKF /Update Step /If Action Subsystem/kalman_gain': '<S22>:1' */
    /* '<S22>:1:3' K = cov_min*H'/(H*cov_min*H' + meas_cov); */
    for (idx2 = 0; idx2 < 6; idx2++) {
      for (sigIdx = 0; sigIdx < 6; sigIdx++) {
        rtb_K[idx2 + 6 * sigIdx] = 0.0;
        rtb_Merge2_1[idx2 + 6 * sigIdx] = 0.0;
        for (ABOVE = 0; ABOVE < 6; ABOVE++) {
          rtb_K[idx2 + 6 * sigIdx] += rtDW.UnitDelay2_DSTATE[6 * ABOVE + idx2] *
            rtb_Merge2[6 * ABOVE + sigIdx];
          rtb_Merge2_1[idx2 + 6 * sigIdx] += rtb_Merge2[6 * ABOVE + idx2] *
            rtDW.UnitDelay2_DSTATE[6 * sigIdx + ABOVE];
        }
      }

      for (sigIdx = 0; sigIdx < 6; sigIdx++) {
        IL3 = 0.0;
        for (ABOVE = 0; ABOVE < 6; ABOVE++) {
          IL3 += rtb_Merge2_1[6 * ABOVE + idx2] * rtb_Merge2[6 * ABOVE + sigIdx];
        }

        rtb_Merge2_0[idx2 + 6 * sigIdx] = rtDW.u0[6 * sigIdx + idx2] + IL3;
      }
    }

    mrdivide(rtb_K, rtb_Merge2_0);

    /*  zero off part of gain if gyro reading is invalid */
    /* '<S22>:1:7' if( valid_gyro == 0 ) */
    if (rtU.gyro_omega_body_radps[3] == 0.0) {
      /* '<S22>:1:8' K(4:6,:) = zeros(3,6); */
      for (idx2 = 0; idx2 < 6; idx2++) {
        rtb_K[3 + 6 * idx2] = 0.0;
        rtb_K[4 + 6 * idx2] = 0.0;
        rtb_K[5 + 6 * idx2] = 0.0;
      }
    }

    /* End of MATLAB Function: '<S18>/kalman_gain' */

    /* Sum: '<S18>/Sum' incorporates:
     *  Product: '<S18>/Matrix Multiply'
     */
    tmp[0] = rtU.mag_vec_body_T[0];
    tmp[3] = rtU.sun_vec_body_sunsensor[0];
    tmp[1] = rtU.mag_vec_body_T[1];
    tmp[4] = rtU.sun_vec_body_sunsensor[1];
    tmp[2] = rtU.mag_vec_body_T[2];
    tmp[5] = rtU.sun_vec_body_sunsensor[2];
    for (idx2 = 0; idx2 < 6; idx2++) {
      rtb_Normalization_0[idx2] = tmp[idx2] - rtb_body_est[idx2];
    }

    /* End of Sum: '<S18>/Sum' */

    /* Product: '<S18>/Matrix Multiply' */
    for (idx2 = 0; idx2 < 6; idx2++) {
      rtb_MatrixMultiply_p[idx2] = 0.0;
      for (sigIdx = 0; sigIdx < 6; sigIdx++) {
        rtb_MatrixMultiply_p[idx2] += rtb_K[6 * sigIdx + idx2] *
          rtb_Normalization_0[sigIdx];
      }
    }

    /* MATLAB Function: '<S18>/update_state ' incorporates:
     *  UnitDelay: '<S9>/Unit Delay'
     */
    /*  select out bias */
    /* MATLAB Function 'Estimation_EKF /Update Step /If Action Subsystem/update_state ': '<S24>:1' */
    /* '<S24>:1:5' bias_plu = bias_min + del_x_plu(4:6); */
    /* '<S24>:1:7' q_plu = quat_update(del_x_plu(1:3),q_min); */
    /* '<S24>:1:16' XI = [ -q_hat_mk(2) -q_hat_mk(3) -q_hat_mk(4); */
    /* '<S24>:1:17'         q_hat_mk(1) -q_hat_mk(4)  q_hat_mk(3); */
    /* '<S24>:1:18'         q_hat_mk(4)  q_hat_mk(1) -q_hat_mk(2); */
    /* '<S24>:1:19'        -q_hat_mk(3)  q_hat_mk(2)  q_hat_mk(1) ]; */
    /* '<S24>:1:21' q_hat_pk = q_hat_mk + 0.5*XI*del_apk; */
    tmp_0[0] = -rtDW.UnitDelay_DSTATE[1];
    tmp_0[4] = -rtDW.UnitDelay_DSTATE[2];
    tmp_0[8] = -rtDW.UnitDelay_DSTATE[3];
    tmp_0[1] = rtDW.UnitDelay_DSTATE[0];
    tmp_0[5] = -rtDW.UnitDelay_DSTATE[3];
    tmp_0[9] = rtDW.UnitDelay_DSTATE[2];
    tmp_0[2] = rtDW.UnitDelay_DSTATE[3];
    tmp_0[6] = rtDW.UnitDelay_DSTATE[0];
    tmp_0[10] = -rtDW.UnitDelay_DSTATE[1];
    tmp_0[3] = -rtDW.UnitDelay_DSTATE[2];
    tmp_0[7] = rtDW.UnitDelay_DSTATE[1];
    tmp_0[11] = rtDW.UnitDelay_DSTATE[0];
    for (idx2 = 0; idx2 < 3; idx2++) {
      tmp_1[idx2 << 2] = tmp_0[idx2 << 2] * 0.5;
      tmp_1[1 + (idx2 << 2)] = tmp_0[(idx2 << 2) + 1] * 0.5;
      tmp_1[2 + (idx2 << 2)] = tmp_0[(idx2 << 2) + 2] * 0.5;
      tmp_1[3 + (idx2 << 2)] = tmp_0[(idx2 << 2) + 3] * 0.5;
    }

    /* '<S24>:1:8' q_plu = q_plu/norm(q_plu); */
    mean_anom_sun_rad = 0.0;
    rtb_T_TT_J2000 = 2.2250738585072014E-308;
    for (sigIdx = 0; sigIdx < 4; sigIdx++) {
      rtb_TrigonometricFunction1_o1 = ((tmp_1[sigIdx + 4] *
        rtb_MatrixMultiply_p[1] + tmp_1[sigIdx] * rtb_MatrixMultiply_p[0]) +
        tmp_1[sigIdx + 8] * rtb_MatrixMultiply_p[2]) +
        rtDW.UnitDelay_DSTATE[sigIdx];
      JD_days_gps = fabs(rtb_TrigonometricFunction1_o1);
      if (JD_days_gps > rtb_T_TT_J2000) {
        long_eclp_rad = rtb_T_TT_J2000 / JD_days_gps;
        mean_anom_sun_rad = mean_anom_sun_rad * long_eclp_rad * long_eclp_rad +
          1.0;
        rtb_T_TT_J2000 = JD_days_gps;
      } else {
        long_eclp_rad = JD_days_gps / rtb_T_TT_J2000;
        mean_anom_sun_rad += long_eclp_rad * long_eclp_rad;
      }

      rtb_q_plu[sigIdx] = rtb_TrigonometricFunction1_o1;
    }

    mean_anom_sun_rad = rtb_T_TT_J2000 * sqrt(mean_anom_sun_rad);
    rtb_q_plu[0] /= mean_anom_sun_rad;
    rtb_q_plu[1] /= mean_anom_sun_rad;
    rtb_q_plu[2] /= mean_anom_sun_rad;
    rtb_q_plu[3] /= mean_anom_sun_rad;

    /* SignalConversion: '<S18>/OutportBufferForbias_plus' incorporates:
     *  MATLAB Function: '<S18>/update_state '
     *  UnitDelay: '<S9>/Unit Delay1'
     */
    rtb_pos_teme_km[0] = rtDW.UnitDelay1_DSTATE[0] + rtb_MatrixMultiply_p[3];
    rtb_pos_teme_km[1] = rtDW.UnitDelay1_DSTATE[1] + rtb_MatrixMultiply_p[4];
    rtb_pos_teme_km[2] = rtDW.UnitDelay1_DSTATE[2] + rtb_MatrixMultiply_p[5];

    /* MATLAB Function: '<S18>/covariance_update' incorporates:
     *  UnitDelay: '<S9>/Unit Delay2'
     */
    /* MATLAB Function 'Estimation_EKF /Update Step /If Action Subsystem/covariance_update': '<S21>:1' */
    /* '<S21>:1:3' KHI = (K*H - eye(6)); */
    for (idx2 = 0; idx2 < 36; idx2++) {
      I_0[idx2] = 0;
    }

    for (sigIdx = 0; sigIdx < 6; sigIdx++) {
      I_0[sigIdx + 6 * sigIdx] = 1;
    }

    /* '<S21>:1:4' cov_plus = KHI*cov_min*KHI' + K*meas_cov*K'; */
    for (idx2 = 0; idx2 < 6; idx2++) {
      for (sigIdx = 0; sigIdx < 6; sigIdx++) {
        IL3 = 0.0;
        for (ABOVE = 0; ABOVE < 6; ABOVE++) {
          IL3 += rtb_K[6 * ABOVE + idx2] * rtb_Merge2[6 * sigIdx + ABOVE];
        }

        KHI[idx2 + 6 * sigIdx] = IL3 - (real_T)I_0[6 * sigIdx + idx2];
      }

      for (sigIdx = 0; sigIdx < 6; sigIdx++) {
        rtb_Merge2_0[idx2 + 6 * sigIdx] = 0.0;
        rtb_Merge2_1[idx2 + 6 * sigIdx] = 0.0;
        for (ABOVE = 0; ABOVE < 6; ABOVE++) {
          rtb_Merge2_0[idx2 + 6 * sigIdx] += KHI[6 * ABOVE + idx2] *
            rtDW.UnitDelay2_DSTATE[6 * sigIdx + ABOVE];
          rtb_Merge2_1[idx2 + 6 * sigIdx] += rtb_K[6 * ABOVE + idx2] * rtDW.u0[6
            * sigIdx + ABOVE];
        }
      }
    }

    for (idx2 = 0; idx2 < 6; idx2++) {
      for (sigIdx = 0; sigIdx < 6; sigIdx++) {
        KHI_0[idx2 + 6 * sigIdx] = 0.0;
        rtb_K_0[idx2 + 6 * sigIdx] = 0.0;
        for (ABOVE = 0; ABOVE < 6; ABOVE++) {
          KHI_0[idx2 + 6 * sigIdx] += rtb_Merge2_0[6 * ABOVE + idx2] * KHI[6 *
            ABOVE + sigIdx];
          rtb_K_0[idx2 + 6 * sigIdx] += rtb_Merge2_1[6 * ABOVE + idx2] * rtb_K[6
            * ABOVE + sigIdx];
        }
      }
    }

    /* SignalConversion: '<S18>/OutportBufferForcov_plus' incorporates:
     *  MATLAB Function: '<S18>/covariance_update'
     */
    for (idx2 = 0; idx2 < 6; idx2++) {
      for (sigIdx = 0; sigIdx < 6; sigIdx++) {
        rtb_Merge2[sigIdx + 6 * idx2] = KHI_0[6 * idx2 + sigIdx] + rtb_K_0[6 *
          idx2 + sigIdx];
      }
    }

    /* End of SignalConversion: '<S18>/OutportBufferForcov_plus' */
    /* End of Outputs for SubSystem: '<S12>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S12>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S19>/Action Port'
     */
    rtb_q_plu[0] = rtDW.UnitDelay_DSTATE[0];
    rtb_q_plu[1] = rtDW.UnitDelay_DSTATE[1];
    rtb_q_plu[2] = rtDW.UnitDelay_DSTATE[2];
    rtb_q_plu[3] = rtDW.UnitDelay_DSTATE[3];
    rtb_pos_teme_km[0] = rtDW.UnitDelay1_DSTATE[0];
    rtb_pos_teme_km[1] = rtDW.UnitDelay1_DSTATE[1];
    rtb_pos_teme_km[2] = rtDW.UnitDelay1_DSTATE[2];
    memcpy(&rtb_Merge2[0], &rtDW.UnitDelay2_DSTATE[0], 36U * sizeof(real_T));

    /* End of Outputs for SubSystem: '<S12>/If Action Subsystem1' */
  }

  /* End of If: '<S12>/If' */

  /* Switch: '<S11>/Switch' incorporates:
   *  Inport: '<Root>/gyro_omega_body_radps'
   *  Sum: '<S11>/Sum'
   */
  if (rtU.gyro_omega_body_radps[3] >= 0.0) {
    N[0] = rtU.gyro_omega_body_radps[0] - rtb_pos_teme_km[0];
    N[1] = rtU.gyro_omega_body_radps[1] - rtb_pos_teme_km[1];
    N[2] = rtU.gyro_omega_body_radps[2] - rtb_pos_teme_km[2];
  } else {
    N[0] = 0.0;
    N[1] = 0.0;
    N[2] = 0.0;
  }

  /* End of Switch: '<S11>/Switch' */

  /* MATLAB Function: '<S11>/propagate_quat' incorporates:
   *  Constant: '<S11>/Constant1'
   */
  /* MATLAB Function 'Estimation_EKF /Propagate Step /propagate_quat': '<S14>:1' */
  /* '<S14>:1:4' w_n = norm(w_plu); */
  rtb_T_TT_J2000 = 2.2250738585072014E-308;
  JD_days_gps = fabs(N[0]);
  if (JD_days_gps > 2.2250738585072014E-308) {
    rtb_TrigonometricFunction1_o1 = 1.0;
    rtb_T_TT_J2000 = JD_days_gps;
  } else {
    long_eclp_rad = JD_days_gps / 2.2250738585072014E-308;
    rtb_TrigonometricFunction1_o1 = long_eclp_rad * long_eclp_rad;
  }

  JD_days_gps = fabs(N[1]);
  if (JD_days_gps > rtb_T_TT_J2000) {
    long_eclp_rad = rtb_T_TT_J2000 / JD_days_gps;
    rtb_TrigonometricFunction1_o1 = rtb_TrigonometricFunction1_o1 *
      long_eclp_rad * long_eclp_rad + 1.0;
    rtb_T_TT_J2000 = JD_days_gps;
  } else {
    long_eclp_rad = JD_days_gps / rtb_T_TT_J2000;
    rtb_TrigonometricFunction1_o1 += long_eclp_rad * long_eclp_rad;
  }

  JD_days_gps = fabs(N[2]);
  if (JD_days_gps > rtb_T_TT_J2000) {
    long_eclp_rad = rtb_T_TT_J2000 / JD_days_gps;
    rtb_TrigonometricFunction1_o1 = rtb_TrigonometricFunction1_o1 *
      long_eclp_rad * long_eclp_rad + 1.0;
    rtb_T_TT_J2000 = JD_days_gps;
  } else {
    long_eclp_rad = JD_days_gps / rtb_T_TT_J2000;
    rtb_TrigonometricFunction1_o1 += long_eclp_rad * long_eclp_rad;
  }

  rtb_TrigonometricFunction1_o1 = rtb_T_TT_J2000 * sqrt
    (rtb_TrigonometricFunction1_o1);

  /* '<S14>:1:6' if( w_n < 1e-10 ) */
  if (rtb_TrigonometricFunction1_o1 < 1.0E-10) {
    /* '<S14>:1:7' Psi = zeros(3,1); */
    rtb_Sum_o[0] = 0.0;
    rtb_Sum_o[1] = 0.0;
    rtb_Sum_o[2] = 0.0;
  } else {
    /* '<S14>:1:8' else */
    /* '<S14>:1:9' Psi = (sin(0.5*w_n*dt)/w_n).*w_plu; */
    mean_anom_sun_rad = sin(0.5 * rtb_TrigonometricFunction1_o1 * 0.1) /
      rtb_TrigonometricFunction1_o1;
    rtb_Sum_o[0] = mean_anom_sun_rad * N[0];
    rtb_Sum_o[1] = mean_anom_sun_rad * N[1];
    rtb_Sum_o[2] = mean_anom_sun_rad * N[2];
  }

  /* '<S14>:1:12' Psi_skew = skew(Psi); */
  /* '<S14>:1:23' S = [ 0    -v(3)  v(2); */
  /* '<S14>:1:24'       v(3)  0    -v(1); */
  /* '<S14>:1:25'      -v(2)  v(1)  0 ]; */
  /* '<S14>:1:14' OmegaB = [ cos(0.5*w_n*dt)  -Psi'; */
  /* '<S14>:1:15'             Psi             cos(0.5*w_n*dt)*eye(3) - Psi_skew ]; */
  JD_days_gps = cos(0.5 * rtb_TrigonometricFunction1_o1 * 0.1);

  /* '<S14>:1:17' q_min_k1 = OmegaB*q_plu; */
  tmp_2[0] = 0.0;
  tmp_2[3] = -rtb_Sum_o[2];
  tmp_2[6] = rtb_Sum_o[1];
  tmp_2[1] = rtb_Sum_o[2];
  tmp_2[4] = 0.0;
  tmp_2[7] = -rtb_Sum_o[0];
  tmp_2[2] = -rtb_Sum_o[1];
  tmp_2[5] = rtb_Sum_o[0];
  tmp_2[8] = 0.0;
  tmp_3[0] = cos(0.5 * rtb_TrigonometricFunction1_o1 * 0.1);
  for (idx2 = 0; idx2 < 3; idx2++) {
    tmp_3[(idx2 + 1) << 2] = -rtb_Sum_o[idx2];
    tmp_3[idx2 + 1] = rtb_Sum_o[idx2];
    tmp_3[1 + ((idx2 + 1) << 2)] = (real_T)b_0[3 * idx2] * JD_days_gps - tmp_2[3
      * idx2];
    tmp_3[2 + ((idx2 + 1) << 2)] = (real_T)b_0[3 * idx2 + 1] * JD_days_gps -
      tmp_2[3 * idx2 + 1];
    tmp_3[3 + ((idx2 + 1) << 2)] = (real_T)b_0[3 * idx2 + 2] * JD_days_gps -
      tmp_2[3 * idx2 + 2];
  }

  for (idx2 = 0; idx2 < 4; idx2++) {
    JD_days_gps = tmp_3[idx2 + 12] * rtb_q_plu[3] + (tmp_3[idx2 + 8] *
      rtb_q_plu[2] + (tmp_3[idx2 + 4] * rtb_q_plu[1] + tmp_3[idx2] * rtb_q_plu[0]));
    rtb_q_min_k1[idx2] = JD_days_gps;
  }

  /* End of MATLAB Function: '<S11>/propagate_quat' */

  /* MATLAB Function: '<S11>/state_transition' incorporates:
   *  Constant: '<S11>/Constant4'
   */
  /* MATLAB Function 'Estimation_EKF /Propagate Step /state_transition': '<S15>:1' */
  /* '<S15>:1:3' w_n     = norm(w_plus); */
  rtb_T_TT_J2000 = 2.2250738585072014E-308;
  JD_days_gps = fabs(N[0]);
  if (JD_days_gps > 2.2250738585072014E-308) {
    rtb_TrigonometricFunction1_o1 = 1.0;
    rtb_T_TT_J2000 = JD_days_gps;
  } else {
    long_eclp_rad = JD_days_gps / 2.2250738585072014E-308;
    rtb_TrigonometricFunction1_o1 = long_eclp_rad * long_eclp_rad;
  }

  JD_days_gps = fabs(N[1]);
  if (JD_days_gps > rtb_T_TT_J2000) {
    long_eclp_rad = rtb_T_TT_J2000 / JD_days_gps;
    rtb_TrigonometricFunction1_o1 = rtb_TrigonometricFunction1_o1 *
      long_eclp_rad * long_eclp_rad + 1.0;
    rtb_T_TT_J2000 = JD_days_gps;
  } else {
    long_eclp_rad = JD_days_gps / rtb_T_TT_J2000;
    rtb_TrigonometricFunction1_o1 += long_eclp_rad * long_eclp_rad;
  }

  JD_days_gps = fabs(N[2]);
  if (JD_days_gps > rtb_T_TT_J2000) {
    long_eclp_rad = rtb_T_TT_J2000 / JD_days_gps;
    rtb_TrigonometricFunction1_o1 = rtb_TrigonometricFunction1_o1 *
      long_eclp_rad * long_eclp_rad + 1.0;
    rtb_T_TT_J2000 = JD_days_gps;
  } else {
    long_eclp_rad = JD_days_gps / rtb_T_TT_J2000;
    rtb_TrigonometricFunction1_o1 += long_eclp_rad * long_eclp_rad;
  }

  rtb_TrigonometricFunction1_o1 = rtb_T_TT_J2000 * sqrt
    (rtb_TrigonometricFunction1_o1);

  /* '<S15>:1:4' w_skew  = skew(w_plus); */
  /* '<S15>:1:23' S = [ 0   -v(3)   v(2); */
  /* '<S15>:1:24'       v(3) 0     -v(1); */
  /* '<S15>:1:25'      -v(2) v(1)   0 ]; */
  rotation_matrix[0] = 0.0;
  rotation_matrix[3] = -N[2];
  rotation_matrix[6] = N[1];
  rotation_matrix[1] = N[2];
  rotation_matrix[4] = 0.0;
  rotation_matrix[7] = -N[0];
  rotation_matrix[2] = -N[1];
  rotation_matrix[5] = N[0];
  rotation_matrix[8] = 0.0;

  /* '<S15>:1:6' if( w_n < 1e-10 ) */
  if (rtb_TrigonometricFunction1_o1 < 1.0E-10) {
    /* '<S15>:1:7' Phi = [ eye(3)     -eye(3)*dt; */
    /* '<S15>:1:8'             zeros(3,3)  eye(3) ]; */
    memset(&rotation_matrix[0], 0, 9U * sizeof(real_T));
    for (idx2 = 0; idx2 < 9; idx2++) {
      I[idx2] = 0;
    }

    I[0] = 1;
    I[4] = 1;
    I[8] = 1;
    for (sigIdx = 0; sigIdx < 3; sigIdx++) {
      rotation_matrix[sigIdx + 3 * sigIdx] = 1.0;
      rtb_K[6 * sigIdx] = I[3 * sigIdx];
      rtb_K[6 * (sigIdx + 3)] = (real_T)a_0[3 * sigIdx] * 0.1;
      rtb_K[3 + 6 * sigIdx] = 0.0;
      rtb_K[1 + 6 * sigIdx] = I[3 * sigIdx + 1];
      rtb_K[1 + 6 * (sigIdx + 3)] = (real_T)a_0[3 * sigIdx + 1] * 0.1;
      rtb_K[4 + 6 * sigIdx] = 0.0;
      rtb_K[2 + 6 * sigIdx] = I[3 * sigIdx + 2];
      rtb_K[2 + 6 * (sigIdx + 3)] = (real_T)a_0[3 * sigIdx + 2] * 0.1;
      rtb_K[5 + 6 * sigIdx] = 0.0;
    }

    for (idx2 = 0; idx2 < 3; idx2++) {
      rtb_K[3 + 6 * (idx2 + 3)] = rotation_matrix[3 * idx2];
      rtb_K[4 + 6 * (idx2 + 3)] = rotation_matrix[3 * idx2 + 1];
      rtb_K[5 + 6 * (idx2 + 3)] = rotation_matrix[3 * idx2 + 2];
    }
  } else {
    /* '<S15>:1:9' else */
    /* '<S15>:1:10' Phi_11  = eye(3) - w_skew*(sin(w_n*dt)/w_n) + ... */
    /* '<S15>:1:11'                                         w_skew^2*(1 - cos(w_n*dt))/w_n^2; */
    for (idx2 = 0; idx2 < 9; idx2++) {
      I[idx2] = 0;
      Phi_22[idx2] = 0;
    }

    I[0] = 1;
    I[4] = 1;
    I[8] = 1;
    mean_anom_sun_rad = sin(rtb_TrigonometricFunction1_o1 * 0.1) /
      rtb_TrigonometricFunction1_o1;
    JD_days_gps = cos(rtb_TrigonometricFunction1_o1 * 0.1);
    c = rtb_TrigonometricFunction1_o1 * rtb_TrigonometricFunction1_o1;

    /* '<S15>:1:12' Phi_12  = w_skew*(1 - cos(w_n*dt))/w_n^2 - eye(3)*dt - ... */
    /* '<S15>:1:13'                                     w_skew^2*(w_n*dt - sin(w_n*dt))/w_n^3; */
    b_s = cos(rtb_TrigonometricFunction1_o1 * 0.1);
    b_c = rtb_TrigonometricFunction1_o1 * rtb_TrigonometricFunction1_o1;
    s = rtb_TrigonometricFunction1_o1 * 0.1 - sin(rtb_TrigonometricFunction1_o1 *
      0.1);
    c_c = rt_powd_snf(rtb_TrigonometricFunction1_o1, 3.0);

    /* '<S15>:1:14' Phi_21  = zeros(3,3); */
    /* '<S15>:1:15' Phi_22  = eye(3); */
    /* '<S15>:1:16' Phi     = [ Phi_11 Phi_12; */
    /* '<S15>:1:17'                 Phi_21 Phi_22 ]; */
    for (sigIdx = 0; sigIdx < 3; sigIdx++) {
      Phi_22[sigIdx + 3 * sigIdx] = 1;
      for (idx2 = 0; idx2 < 3; idx2++) {
        rtb_MatrixMultiply[sigIdx + 3 * idx2] = 0.0;
        rotation_matrix_0[sigIdx + 3 * idx2] = 0.0;
        rtb_MatrixMultiply[sigIdx + 3 * idx2] += rotation_matrix[3 * idx2] *
          rotation_matrix[sigIdx];
        rotation_matrix_0[sigIdx + 3 * idx2] += rotation_matrix[3 * idx2] *
          rotation_matrix[sigIdx];
        rtb_MatrixMultiply[sigIdx + 3 * idx2] += rotation_matrix[3 * idx2 + 1] *
          rotation_matrix[sigIdx + 3];
        rotation_matrix_0[sigIdx + 3 * idx2] += rotation_matrix[3 * idx2 + 1] *
          rotation_matrix[sigIdx + 3];
        rtb_MatrixMultiply[sigIdx + 3 * idx2] += rotation_matrix[3 * idx2 + 2] *
          rotation_matrix[sigIdx + 6];
        rotation_matrix_0[sigIdx + 3 * idx2] += rotation_matrix[3 * idx2 + 2] *
          rotation_matrix[sigIdx + 6];
      }
    }

    for (idx2 = 0; idx2 < 3; idx2++) {
      rtb_K[6 * idx2] = ((real_T)I[3 * idx2] - rotation_matrix[3 * idx2] *
                         mean_anom_sun_rad) + rtb_MatrixMultiply[3 * idx2] *
        (1.0 - JD_days_gps) / c;
      rtb_K[6 * (idx2 + 3)] = (rotation_matrix[3 * idx2] * (1.0 - b_s) / b_c -
        (real_T)b_a[3 * idx2] * 0.1) - rotation_matrix_0[3 * idx2] * s / c_c;
      rtb_K[3 + 6 * idx2] = 0.0;
      rtb_K[3 + 6 * (idx2 + 3)] = Phi_22[3 * idx2];
      rtb_K[1 + 6 * idx2] = ((real_T)I[3 * idx2 + 1] - rotation_matrix[3 * idx2
        + 1] * mean_anom_sun_rad) + rtb_MatrixMultiply[3 * idx2 + 1] * (1.0 -
        JD_days_gps) / c;
      rtb_K[1 + 6 * (idx2 + 3)] = (rotation_matrix[3 * idx2 + 1] * (1.0 - b_s) /
        b_c - (real_T)b_a[3 * idx2 + 1] * 0.1) - rotation_matrix_0[3 * idx2 + 1]
        * s / c_c;
      rtb_K[4 + 6 * idx2] = 0.0;
      rtb_K[4 + 6 * (idx2 + 3)] = Phi_22[3 * idx2 + 1];
      rtb_K[2 + 6 * idx2] = ((real_T)I[3 * idx2 + 2] - rotation_matrix[3 * idx2
        + 2] * mean_anom_sun_rad) + rtb_MatrixMultiply[3 * idx2 + 2] * (1.0 -
        JD_days_gps) / c;
      rtb_K[2 + 6 * (idx2 + 3)] = (rotation_matrix[3 * idx2 + 2] * (1.0 - b_s) /
        b_c - (real_T)b_a[3 * idx2 + 2] * 0.1) - rotation_matrix_0[3 * idx2 + 2]
        * s / c_c;
      rtb_K[5 + 6 * idx2] = 0.0;
      rtb_K[5 + 6 * (idx2 + 3)] = Phi_22[3 * idx2 + 2];
    }
  }

  /* End of MATLAB Function: '<S11>/state_transition' */

  /* Sqrt: '<S16>/sqrt' incorporates:
   *  Product: '<S17>/Product'
   *  Product: '<S17>/Product1'
   *  Product: '<S17>/Product2'
   *  Product: '<S17>/Product3'
   *  Sum: '<S17>/Sum'
   */
  mean_anom_sun_rad = sqrt(((rtb_q_min_k1[0] * rtb_q_min_k1[0] + rtb_q_min_k1[1]
    * rtb_q_min_k1[1]) + rtb_q_min_k1[2] * rtb_q_min_k1[2]) + rtb_q_min_k1[3] *
    rtb_q_min_k1[3]);

  /* Product: '<S13>/Product' */
  rtb_TrigonometricFunction1_o1 = rtb_q_min_k1[0] / mean_anom_sun_rad;

  /* Product: '<S13>/Product1' */
  rtb_T_TT_J2000 = rtb_q_min_k1[1] / mean_anom_sun_rad;

  /* Product: '<S13>/Product2' */
  JD_days_gps = rtb_q_min_k1[2] / mean_anom_sun_rad;

  /* Product: '<S13>/Product3' */
  long_eclp_rad = rtb_q_min_k1[3] / mean_anom_sun_rad;

  /* If: '<S10>/If' incorporates:
   *  Inport: '<Root>/mag_vec_body_T'
   *  Inport: '<Root>/sun_vec_body_sunsensor'
   *  Inport: '<S25>/quat_old'
   *  Logic: '<S10>/Logical Operator'
   *  UnitDelay: '<S10>/Unit Delay'
   */
  if ((rtU.mag_vec_body_T[3] != 0.0) && (rtU.sun_vec_body_sunsensor[3] != 0.0))
  {
    /* Outputs for IfAction SubSystem: '<S10>/TRIAD ' incorporates:
     *  ActionPort: '<S26>/Action Port'
     */
    /* S-Function (sdsp2norm2): '<S26>/Normalization2' */
    IL4 = 1.0 / (sqrt((rtU.mag_vec_body_T[0] * rtU.mag_vec_body_T[0] +
                       rtU.mag_vec_body_T[1] * rtU.mag_vec_body_T[1]) +
                      rtU.mag_vec_body_T[2] * rtU.mag_vec_body_T[2]) + 1.0E-10);
    rtb_s[0] = rtU.mag_vec_body_T[0] * IL4;
    rtb_s[1] = rtU.mag_vec_body_T[1] * IL4;
    rtb_s[2] = rtU.mag_vec_body_T[2] * IL4;

    /* SignalConversion: '<S26>/ConcatBufferAtMatrix Concatenate1In1' */
    rtb_MathFunction_n[0] = rtb_s[0];
    rtb_MathFunction_n[1] = rtb_s[1];
    rtb_MathFunction_n[2] = rtb_s[2];

    /* S-Function (sdsp2norm2): '<S26>/Normalization3' */
    IL4 = 1.0 / (sqrt((rtU.sun_vec_body_sunsensor[0] *
                       rtU.sun_vec_body_sunsensor[0] +
                       rtU.sun_vec_body_sunsensor[1] *
                       rtU.sun_vec_body_sunsensor[1]) +
                      rtU.sun_vec_body_sunsensor[2] *
                      rtU.sun_vec_body_sunsensor[2]) + 1.0E-10);
    rtb_m[0] = rtU.sun_vec_body_sunsensor[0] * IL4;
    rtb_m[1] = rtU.sun_vec_body_sunsensor[1] * IL4;
    rtb_m[2] = rtU.sun_vec_body_sunsensor[2] * IL4;

    /* Product: '<S28>/Element product' */
    rtb_body_est[1] = rtb_s[2] * rtb_m[0];
    rtb_body_est[2] = rtb_s[0] * rtb_m[1];
    rtb_body_est[5] = rtb_s[1] * rtb_m[0];

    /* Sum: '<S28>/Add3' incorporates:
     *  Product: '<S28>/Element product'
     */
    rtb_m[0] = rtb_s[1] * rtb_m[2] - rtb_s[2] * rtb_m[1];
    rtb_m[1] = rtb_body_est[1] - rtb_s[0] * rtb_m[2];
    rtb_m[2] = rtb_body_est[2] - rtb_body_est[5];

    /* S-Function (sdsp2norm2): '<S26>/Normalization5' */
    IL4 = 1.0 / (sqrt((rtb_m[0] * rtb_m[0] + rtb_m[1] * rtb_m[1]) + rtb_m[2] *
                      rtb_m[2]) + 1.0E-10);
    rtb_m[0] *= IL4;
    rtb_m[1] *= IL4;
    rtb_m[2] *= IL4;

    /* SignalConversion: '<S26>/ConcatBufferAtMatrix Concatenate1In2' */
    rtb_MathFunction_n[3] = rtb_m[0];
    rtb_MathFunction_n[4] = rtb_m[1];
    rtb_MathFunction_n[5] = rtb_m[2];

    /* S-Function (sdsp2norm2): '<S26>/Normalization' */
    IL4 = 1.0 / (sqrt((rtb_Normalization[0] * rtb_Normalization[0] +
                       rtb_Normalization[1] * rtb_Normalization[1]) +
                      rtb_Normalization[2] * rtb_Normalization[2]) + 1.0E-10);
    rtb_S[0] = rtb_Normalization[0] * IL4;
    rtb_S[1] = rtb_Normalization[1] * IL4;
    rtb_S[2] = rtb_Normalization[2] * IL4;

    /* SignalConversion: '<S26>/ConcatBufferAtMatrix ConcatenateIn1' */
    rtb_MatrixConcatenate[0] = rtb_S[0];
    rtb_MatrixConcatenate[1] = rtb_S[1];
    rtb_MatrixConcatenate[2] = rtb_S[2];

    /* S-Function (sdsp2norm2): '<S26>/Normalization1' */
    IL4 = 1.0 / (sqrt((rtDW.u1_f[0] * rtDW.u1_f[0] + rtDW.u1_f[1] * rtDW.u1_f[1])
                      + rtDW.u1_f[2] * rtDW.u1_f[2]) + 1.0E-10);
    c_c = rtDW.u1_f[0] * IL4;
    c = rtDW.u1_f[1] * IL4;
    mean_anom_sun_rad = rtDW.u1_f[2] * IL4;

    /* Product: '<S27>/Element product' */
    rtb_body_est[1] = rtb_S[2] * c_c;
    rtb_body_est[2] = rtb_S[0] * c;
    rtb_body_est[5] = rtb_S[1] * c_c;

    /* Sum: '<S27>/Add3' incorporates:
     *  Product: '<S27>/Element product'
     */
    c_c = rtb_S[1] * mean_anom_sun_rad - rtb_S[2] * c;
    c = rtb_body_est[1] - rtb_S[0] * mean_anom_sun_rad;
    mean_anom_sun_rad = rtb_body_est[2] - rtb_body_est[5];

    /* S-Function (sdsp2norm2): '<S26>/Normalization4' */
    IL4 = 1.0 / (sqrt((c_c * c_c + c * c) + mean_anom_sun_rad *
                      mean_anom_sun_rad) + 1.0E-10);
    c_c *= IL4;
    c *= IL4;
    mean_anom_sun_rad *= IL4;

    /* SignalConversion: '<S26>/ConcatBufferAtMatrix ConcatenateIn2' */
    rtb_MatrixConcatenate[3] = c_c;

    /* Sum: '<S29>/Add3' incorporates:
     *  Product: '<S29>/Element product'
     */
    rtb_MatrixConcatenate[6] = rtb_S[1] * mean_anom_sun_rad - rtb_S[2] * c;

    /* SignalConversion: '<S26>/ConcatBufferAtMatrix ConcatenateIn2' */
    rtb_MatrixConcatenate[4] = c;

    /* Sum: '<S29>/Add3' incorporates:
     *  Product: '<S29>/Element product'
     */
    rtb_MatrixConcatenate[7] = rtb_S[2] * c_c - rtb_S[0] * mean_anom_sun_rad;

    /* SignalConversion: '<S26>/ConcatBufferAtMatrix ConcatenateIn2' */
    rtb_MatrixConcatenate[5] = mean_anom_sun_rad;

    /* Sum: '<S29>/Add3' incorporates:
     *  Product: '<S29>/Element product'
     */
    rtb_MatrixConcatenate[8] = rtb_S[0] * c - rtb_S[1] * c_c;

    /* Sum: '<S30>/Add3' incorporates:
     *  Product: '<S30>/Element product'
     */
    rtb_MathFunction_n[6] = rtb_s[1] * rtb_m[2] - rtb_s[2] * rtb_m[1];
    rtb_MathFunction_n[7] = rtb_s[2] * rtb_m[0] - rtb_s[0] * rtb_m[2];
    rtb_MathFunction_n[8] = rtb_s[0] * rtb_m[1] - rtb_s[1] * rtb_m[0];

    /* Math: '<S26>/Math Function' */
    for (idx2 = 0; idx2 < 3; idx2++) {
      rotation_matrix[3 * idx2] = rtb_MathFunction_n[idx2];
      rotation_matrix[1 + 3 * idx2] = rtb_MathFunction_n[idx2 + 3];
      rotation_matrix[2 + 3 * idx2] = rtb_MathFunction_n[idx2 + 6];
    }

    for (idx2 = 0; idx2 < 3; idx2++) {
      rtb_MathFunction_n[3 * idx2] = rotation_matrix[3 * idx2];
      rtb_MathFunction_n[1 + 3 * idx2] = rotation_matrix[3 * idx2 + 1];
      rtb_MathFunction_n[2 + 3 * idx2] = rotation_matrix[3 * idx2 + 2];

      /* Product: '<S26>/Matrix Multiply' */
      for (sigIdx = 0; sigIdx < 3; sigIdx++) {
        rtb_MatrixMultiply[sigIdx + 3 * idx2] = 0.0;
        rtb_MatrixMultiply[sigIdx + 3 * idx2] += rtb_MathFunction_n[3 * idx2] *
          rtb_MatrixConcatenate[sigIdx];
        rtb_MatrixMultiply[sigIdx + 3 * idx2] += rtb_MathFunction_n[3 * idx2 + 1]
          * rtb_MatrixConcatenate[sigIdx + 3];
        rtb_MatrixMultiply[sigIdx + 3 * idx2] += rtb_MathFunction_n[3 * idx2 + 2]
          * rtb_MatrixConcatenate[sigIdx + 6];
      }

      /* End of Product: '<S26>/Matrix Multiply' */
    }

    /* End of Math: '<S26>/Math Function' */

    /* MATLAB Function: '<S26>/MATLAB Function3' */
    /*  ----------------------------------------------------------------------- % */
    /*  UW HuskySat-1, ADCS Team */
    /*  */
    /*  DCM to Quaternion conversion assuming positive scalar part */
    /*  */
    /*  T. Reynolds 1.15.18 */
    /*  #codegen */
    /*  ----------------------------------------------------------------------- % */
    /* MATLAB Function 'TRIAD_coarse_estimator/TRIAD /MATLAB Function3': '<S31>:1' */
    /* '<S31>:1:10' q   = zeros(4,1); */
    /* '<S31>:1:12' tr  = trace(DCM); */
    /* '<S31>:1:14' q(1)    = 0.5*sqrt(tr + 1); */
    b_s = sqrt(((rtb_MatrixMultiply[0] + rtb_MatrixMultiply[4]) +
                rtb_MatrixMultiply[8]) + 1.0) * 0.5;

    /* '<S31>:1:16' if( q(1) ~= 0 ) */
    if (b_s != 0.0) {
      /* '<S31>:1:17' eta     = 1/(4*q(1)); */
      eta = 1.0 / (4.0 * b_s);

      /* '<S31>:1:18' q(2)    = eta*(DCM(2,3) - DCM(3,2)); */
      C_4 = (rtb_MatrixMultiply[7] - rtb_MatrixMultiply[5]) * eta;

      /* '<S31>:1:19' q(3)    = eta*(DCM(3,1) - DCM(1,3)); */
      C_5 = (rtb_MatrixMultiply[2] - rtb_MatrixMultiply[6]) * eta;

      /* '<S31>:1:20' q(4)    = eta*(DCM(1,2) - DCM(2,1)); */
      eta *= rtb_MatrixMultiply[3] - rtb_MatrixMultiply[1];
    } else {
      /* '<S31>:1:21' else */
      /* '<S31>:1:22' q(2)  = sqrt(0.5*(DCM(1,1) + 1)); */
      C_4 = sqrt((rtb_MatrixMultiply[0] + 1.0) * 0.5);

      /* '<S31>:1:23' q(3)  = sign(DCM(1,2))*sqrt(0.5*(DCM(2,2) + 1)); */
      if (rtb_MatrixMultiply[3] < 0.0) {
        IL4 = -1.0;
      } else if (rtb_MatrixMultiply[3] > 0.0) {
        IL4 = 1.0;
      } else if (rtb_MatrixMultiply[3] == 0.0) {
        IL4 = 0.0;
      } else {
        IL4 = rtb_MatrixMultiply[3];
      }

      C_5 = sqrt((rtb_MatrixMultiply[4] + 1.0) * 0.5) * IL4;

      /* '<S31>:1:24' q(4)  = sign(DCM(1,3))*sqrt(0.5*(DCM(3,3) + 1)); */
      if (rtb_MatrixMultiply[6] < 0.0) {
        IL4 = -1.0;
      } else if (rtb_MatrixMultiply[6] > 0.0) {
        IL4 = 1.0;
      } else if (rtb_MatrixMultiply[6] == 0.0) {
        IL4 = 0.0;
      } else {
        IL4 = rtb_MatrixMultiply[6];
      }

      eta = sqrt((rtb_MatrixMultiply[8] + 1.0) * 0.5) * IL4;
    }

    /* End of MATLAB Function: '<S26>/MATLAB Function3' */
    /* End of Outputs for SubSystem: '<S10>/TRIAD ' */
  } else {
    /* Outputs for IfAction SubSystem: '<S10>/Passthrough' incorporates:
     *  ActionPort: '<S25>/Action Port'
     */
    b_s = rtDW.UnitDelay_DSTATE_n[0];
    C_4 = rtDW.UnitDelay_DSTATE_n[1];
    C_5 = rtDW.UnitDelay_DSTATE_n[2];
    eta = rtDW.UnitDelay_DSTATE_n[3];

    /* End of Outputs for SubSystem: '<S10>/Passthrough' */
  }

  /* End of If: '<S10>/If' */

  /* MultiPortSwitch: '<S3>/Multiport Switch' incorporates:
   *  Inport: '<Root>/gyro_omega_body_radps'
   */
  if ((int32_T)rtU.gyro_omega_body_radps[3] == 0) {
    rtb_q_plu[0] = b_s;
    rtb_q_plu[1] = C_4;
    rtb_q_plu[2] = C_5;
    rtb_q_plu[3] = eta;
  } else {
    rtb_q_plu[0] = rtb_TrigonometricFunction1_o1;
    rtb_q_plu[1] = rtb_T_TT_J2000;
    rtb_q_plu[2] = JD_days_gps;
    rtb_q_plu[3] = long_eclp_rad;
  }

  /* End of MultiPortSwitch: '<S3>/Multiport Switch' */

  /* UnitDelay: '<S6>/Unit Delay' */
  rtb_UnitDelay_d = rtDW.UnitDelay_DSTATE_g;

  /* UnaryMinus: '<S87>/Unary Minus' incorporates:
   *  Product: '<S87>/u(1)*u(4)'
   */
  /* Unit Conversion - from: deg to: rad
     Expression: output = (0.0174533*input) + (0) */
  /* Unit Conversion - from: rad to: deg
     Expression: output = (57.2958*input) + (0) */
  /* Unit Conversion - from: deg to: rad
     Expression: output = (0.0174533*input) + (0) */
  /* Unit Conversion - from: rad to: deg
     Expression: output = (57.2958*input) + (0) */
  /* Unit Conversion - from: deg to: rad
     Expression: output = (0.0174533*input) + (0) */
  rtb_VectorConcatenate[0] = 0.39377477022454854;

  /* UnaryMinus: '<S90>/Unary Minus' */
  rtb_VectorConcatenate[1] = 0.84522918991728324;

  /* UnaryMinus: '<S93>/Unary Minus' incorporates:
   *  Product: '<S93>/u(3)*u(4)'
   */
  rtb_VectorConcatenate[2] = 0.361288038615143;

  /* UnaryMinus: '<S88>/Unary Minus' incorporates:
   *  Product: '<S88>/u(1)*u(2)'
   */
  rtb_VectorConcatenate[3] = 0.62280585651662945;

  /* SignalConversion: '<S97>/ConcatBufferAtVector ConcatenateIn5' */
  rtb_VectorConcatenate[4] = -0.53440398249991838;

  /* UnaryMinus: '<S94>/Unary Minus' incorporates:
   *  Product: '<S94>/u(2)*u(3)'
   */
  rtb_VectorConcatenate[5] = 0.57142387819972529;

  /* SignalConversion: '<S97>/ConcatBufferAtVector ConcatenateIn7' */
  rtb_VectorConcatenate[6] = 0.67605790833566293;

  /* SignalConversion: '<S97>/ConcatBufferAtVector ConcatenateIn8' incorporates:
   *  Constant: '<S92>/Constant'
   */
  rtb_VectorConcatenate[7] = 0.0;

  /* UnaryMinus: '<S95>/Unary Minus' */
  rtb_VectorConcatenate[8] = -0.73684849499527949;

  /* SignalConversion: '<S69>/TmpSignal ConversionAtProduct1Inport2' incorporates:
   *  Constant: '<S69>/Constant'
   *  Constant: '<S75>/Constant'
   *  Constant: '<S75>/Re'
   *  Product: '<S75>/Product2'
   *  Product: '<S75>/Product3'
   *  Sqrt: '<S75>/sqrt'
   *  Sum: '<S75>/Sum2'
   *  UnaryMinus: '<S69>/Unary Minus'
   */
  /* Unit Conversion - from: deg to: rad
     Expression: output = (0.0174533*input) + (0) */
  tmp_4[0] = 0.0;
  tmp_4[1] = 0.0;
  tmp_4[2] = -6.3664995496819746E+6;

  /* MATLAB Function: '<S114>/MATLAB Function' */
  rtb_MatrixMultiply[0] = cos(rtb_T_ut1_J2000);
  rtb_MatrixMultiply[3] = sin(rtb_T_ut1_J2000);
  rtb_MatrixMultiply[6] = 0.0;
  rtb_MatrixMultiply[1] = -sin(rtb_T_ut1_J2000);
  rtb_MatrixMultiply[4] = cos(rtb_T_ut1_J2000);
  rtb_MatrixMultiply[7] = 0.0;
  for (idx2 = 0; idx2 < 3; idx2++) {
    /* Product: '<S69>/Product1' incorporates:
     *  MATLAB Function: '<S114>/MATLAB Function'
     *  Math: '<S69>/Math Function1'
     *  Sum: '<S69>/Sum'
     */
    rtb_Sum_o[idx2] = 0.0;
    for (sigIdx = 0; sigIdx < 3; sigIdx++) {
      /* MATLAB Function: '<S114>/MATLAB Function' */
      a_2[idx2 + 3 * sigIdx] = 0.0;
      a_2[idx2 + 3 * sigIdx] += tod_to_mod[3 * sigIdx] * rtb_mod_to_gcrf[idx2];
      a_2[idx2 + 3 * sigIdx] += tod_to_mod[3 * sigIdx + 1] *
        rtb_mod_to_gcrf[idx2 + 3];
      a_2[idx2 + 3 * sigIdx] += tod_to_mod[3 * sigIdx + 2] *
        rtb_mod_to_gcrf[idx2 + 6];
      rtb_Sum_o[idx2] += rtb_VectorConcatenate[3 * idx2 + sigIdx] * tmp_4[sigIdx];
    }

    /* End of Product: '<S69>/Product1' */

    /* Sum: '<S69>/Sum' */
    rtb_m[idx2] = rtb_Sum_o[idx2];

    /* MATLAB Function: '<S114>/MATLAB Function' */
    rtb_MatrixMultiply[2 + 3 * idx2] = d_0[idx2];
  }

  /*  Constants */
  /* MATLAB Function 'gs_prediction/gs_prediction_lib/MATLAB Function1': '<S70>:1' */
  /* '<S70>:1:4' M2KM        = 1000; */
  /* '<S70>:1:5' ECCE2       = 0.006694385000; */
  /* '<S70>:1:6' RE          = 6378.137; */
  /* '<S70>:1:7' TRUE        = 1; */
  /* '<S70>:1:8' FALSE       = 0; */
  /*  ----- */
  /*  Main Function */
  /*  Remnant from sun_vector, may not be relevant here? */
  /*  gs_eci_km(3)  = gs_eci_km(3)/(sqrt(1 - ECCE2)); */
  /*  sc_pos_eci_km(3)        = sc_pos_eci_km(3)/(sqrt(1 - ECCE2)); */
  /* '<S70>:1:17' gs_vec     = gs_ecef_m; */
  /* '<S70>:1:18' sc_vec      = sc_pos_ecef_m; */
  /* In ECI coordinates */
  /* '<S70>:1:21' sc2gs_unit  = (gs_vec - sc_vec)/norm(gs_vec - sc_vec); */
  for (idx2 = 0; idx2 < 3; idx2++) {
    /* Product: '<S62>/Product3' */
    rtb_s[idx2] = 0.0;
    for (sigIdx = 0; sigIdx < 3; sigIdx++) {
      /* Math: '<S62>/Math Function1' incorporates:
       *  MATLAB Function: '<S114>/MATLAB Function'
       *  Product: '<S62>/Product3'
       */
      rtb_mod_to_gcrf[idx2 + 3 * sigIdx] = 0.0;
      rtb_mod_to_gcrf[idx2 + 3 * sigIdx] += rtb_MatrixMultiply[3 * idx2] *
        a_2[sigIdx];
      rtb_mod_to_gcrf[idx2 + 3 * sigIdx] += rtb_MatrixMultiply[3 * idx2 + 1] *
        a_2[sigIdx + 3];
      rtb_mod_to_gcrf[idx2 + 3 * sigIdx] += rtb_MatrixMultiply[3 * idx2 + 2] *
        a_2[sigIdx + 6];

      /* Product: '<S62>/Product3' */
      rtb_s[idx2] += rtb_mod_to_gcrf[3 * sigIdx + idx2] * M[sigIdx];
    }

    /* MATLAB Function: '<S68>/MATLAB Function1' */
    rtb_Sum_o[idx2] = rtb_m[idx2] - rtb_s[idx2];
  }

  /* MATLAB Function: '<S68>/MATLAB Function1' */
  mean_anom_sun_rad = norm(rtb_Sum_o);

  /*  Determine if the sc is above the horizon in Seattle */
  /* '<S70>:1:25' sc2gs_gs_dot  = dot(sc2gs_unit,gs_vec)/norm(gs_vec); */
  IL4 = (rtb_m[0] - rtb_s[0]) / mean_anom_sun_rad;
  c = IL4 * rtb_m[0];
  rtb_s[0] = IL4;
  IL4 = (rtb_m[1] - rtb_s[1]) / mean_anom_sun_rad;
  c += IL4 * rtb_m[1];
  rtb_s[1] = IL4;
  IL4 = (rtb_m[2] - rtb_s[2]) / mean_anom_sun_rad;
  c += IL4 * rtb_m[2];
  rtb_s[2] = IL4;

  /*  Check LoS */
  /* '<S70>:1:28' if sc2gs_gs_dot < 0 */
  if (c / norm(rtb_m) < 0.0) {
    /* '<S70>:1:29' ABOVE     = TRUE; */
    ABOVE = 1;
  } else {
    /* '<S70>:1:30' else */
    /* '<S70>:1:31' ABOVE     = FALSE; */
    ABOVE = 0;
  }

  /* MATLAB Function: '<S7>/MATLAB Function2' */
  /* '<S70>:1:34' sc_above_gs = ABOVE; */
  /* '<S70>:1:36' pr = sc_vec - gs_vec; */
  /* '<S70>:1:37' fs = norm(pr)*cosd(fov_ang) - gs_vec'*pr/norm(gs_vec); */
  /* '<S70>:1:38' if (fs < 0) */
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
  /* MATLAB Function 'target_generation_lib/MATLAB Function2': '<S121>:1' */
  /*  Constants */
  /* '<S121>:1:16' COM2    = [ 0.0; -1.0; 0.0 ]; */
  /*  COMM antenna boresight vector (F_body) */
  /* '<S121>:1:17' PPT     = [ 0.0; 0.0; -1.0 ]; */
  /*  thruster boresight vector (F_body) */
  /* '<S121>:1:18' SP      = [ 0.0; 1.0; 0.0 ]; */
  /*  solar panel boresight vector (F_body) */
  /* '<S121>:1:19' flag    = 0; */
  idx2 = 0;

  /* '<S121>:1:20' tol     = 1e-3; */
  /* '<S121>:1:21' Cx5     = [ 1 0 0; 0 cosd(5) sind(5); 0 -sind(5) cosd(5)]; */
  /*  Uncomment for testing only % */
  /*  PPT     = [0;1;2];     */
  /*  SP      = [1;3;0]; */
  /*  -------------------------- % */
  /*  Validity Checks */
  /* '<S121>:1:29' if( norm(vel_eci_kmps) < tol || norm(sc2sun_eci) < tol ... */
  /* '<S121>:1:30'                                                 || norm(sc2gs_eci) < tol ) */
  if ((norm_o(rtDW.RateTransition2_b) < 0.001) || (norm_o(rtDW.RateTransition1) <
       0.001) || (norm_o(rtb_s) < 0.001)) {
    /* '<S121>:1:31' vel_unit        = zeros(3,1); */
    /* '<S121>:1:32' sc2sun_unit     = zeros(3,1); */
    /* '<S121>:1:33' sc2gs_unit      = zeros(3,1); */
    rtb_m[0] = 0.0;
    rtb_S[0] = 0.0;
    rtb_s[0] = 0.0;
    rtb_m[1] = 0.0;
    rtb_S[1] = 0.0;
    rtb_s[1] = 0.0;
    rtb_m[2] = 0.0;
    rtb_S[2] = 0.0;
    rtb_s[2] = 0.0;

    /* '<S121>:1:34' flag = -1; */
    idx2 = -1;
  } else {
    /* '<S121>:1:35' else */
    /*  Compute unit vectors */
    /* '<S121>:1:37' vel_unit    = vel_eci_kmps./norm(vel_eci_kmps); */
    mean_anom_sun_rad = norm_o(rtDW.RateTransition2_b);

    /* '<S121>:1:38' sc2sun_unit = sc2sun_eci./norm(sc2sun_eci); */
    rtb_T_ut1_J2000 = norm_o(rtDW.RateTransition1);
    rtb_m[0] = rtDW.RateTransition2_b[0] / mean_anom_sun_rad;
    rtb_S[0] = rtDW.RateTransition1[0] / rtb_T_ut1_J2000;
    rtb_m[1] = rtDW.RateTransition2_b[1] / mean_anom_sun_rad;
    rtb_S[1] = rtDW.RateTransition1[1] / rtb_T_ut1_J2000;
    rtb_m[2] = rtDW.RateTransition2_b[2] / mean_anom_sun_rad;
    rtb_S[2] = rtDW.RateTransition1[2] / rtb_T_ut1_J2000;

    /* '<S121>:1:39' sc2gs_unit  = sc2gs_eci./norm(sc2gs_eci); */
    rtb_T_ut1_J2000 = norm_o(rtb_s);

    /*  Check for parallel unit vectors */
    /* '<S121>:1:41' if ( abs(dot(vel_unit,sc2sun_unit)) > 1-tol ... */
    /* '<S121>:1:42'                             || abs(dot(vel_unit,sc2gs_unit)) > 1-tol ... */
    /* '<S121>:1:43'                             || abs(dot(sc2sun_unit,sc2gs_unit)) > 1-tol ) */
    rtb_s[0] /= rtb_T_ut1_J2000;
    rtb_s[1] /= rtb_T_ut1_J2000;
    IL4 /= rtb_T_ut1_J2000;
    rtb_s[2] = IL4;
    if ((fabs((rtb_m[0] * rtb_S[0] + rtb_m[1] * rtb_S[1]) + rtb_m[2] * rtb_S[2])
         > 0.999) || (fabs((rtb_m[0] * rtb_s[0] + rtb_m[1] * rtb_s[1]) + rtb_m[2]
          * IL4) > 0.999) || (fabs((rtb_S[0] * rtb_s[0] + rtb_S[1] * rtb_s[1]) +
          rtb_S[2] * IL4) > 0.999)) {
      /* '<S121>:1:44' flag = -1; */
      idx2 = -1;
    }
  }

  /*  Main Code */
  /* '<S121>:1:49' if( sc_mode == 31 && flag == 0 ) */
  if ((rtb_UnitDelay_d == 31) && (idx2 == 0)) {
    /*  Body vectors */
    /* '<S121>:1:52' B1      = PPT; */
    /* '<S121>:1:53' B2      = SP; */
    /* '<S121>:1:54' Xtb     = B1; */
    /* '<S121>:1:55' Ytb     = cross(B1,B2)/norm(cross(B1,B2)); */
    /* '<S121>:1:56' Ztb     = cross(B1,Ytb)/norm(cross(B1,Ytb)); */
    /*  Inertial vectors */
    /* '<S121>:1:59' S1      = vel_unit; */
    /* '<S121>:1:60' S2      = sc2sun_unit; */
    /* '<S121>:1:61' Xti     = S1; */
    /* '<S121>:1:62' Yti     = cross(S1,S2)/norm(cross(S1,S2)); */
    rtb_s_1[0] = rtb_m[1] * rtb_S[2] - rtb_m[2] * rtb_S[1];
    rtb_s_1[1] = rtb_m[2] * rtb_S[0] - rtb_m[0] * rtb_S[2];
    rtb_s_1[2] = rtb_m[0] * rtb_S[1] - rtb_m[1] * rtb_S[0];
    rtb_T_ut1_J2000 = norm_o(rtb_s_1);
    c_c = (rtb_m[1] * rtb_S[2] - rtb_m[2] * rtb_S[1]) / rtb_T_ut1_J2000;
    c = (rtb_m[2] * rtb_S[0] - rtb_m[0] * rtb_S[2]) / rtb_T_ut1_J2000;
    mean_anom_sun_rad = (rtb_m[0] * rtb_S[1] - rtb_m[1] * rtb_S[0]) /
      rtb_T_ut1_J2000;

    /* '<S121>:1:63' Zti     = cross(S1,Yti)/norm(cross(S1,Yti)); */
    rtb_s_0[0] = rtb_m[1] * mean_anom_sun_rad - rtb_m[2] * c;
    rtb_s_0[1] = rtb_m[2] * c_c - rtb_m[0] * mean_anom_sun_rad;
    rtb_s_0[2] = rtb_m[0] * c - rtb_m[1] * c_c;
    rtb_T_ut1_J2000 = norm_o(rtb_s_0);

    /*  Stack vectors */
    /* '<S121>:1:66' Cb  = [Xtb, Ytb, Ztb]; */
    /* '<S121>:1:67' Ci  = [Xti, Yti, Zti]; */
    /*  Commanded DCM ( body to inertial ) */
    /* '<S121>:1:70' C_cmd   = Cb*Ci'; */
    rtb_s_2[0] = rtb_m[0];
    rtb_s_2[1] = c_c;
    rtb_s_2[2] = (rtb_m[1] * mean_anom_sun_rad - rtb_m[2] * c) / rtb_T_ut1_J2000;
    rtb_s_2[3] = rtb_m[1];
    rtb_s_2[4] = c;
    rtb_s_2[5] = (rtb_m[2] * c_c - rtb_m[0] * mean_anom_sun_rad) /
      rtb_T_ut1_J2000;
    rtb_s_2[6] = rtb_m[2];
    rtb_s_2[7] = mean_anom_sun_rad;
    rtb_s_2[8] = (rtb_m[0] * c - rtb_m[1] * c_c) / rtb_T_ut1_J2000;
    for (idx2 = 0; idx2 < 3; idx2++) {
      for (sigIdx = 0; sigIdx < 3; sigIdx++) {
        tod_to_mod[sigIdx + 3 * idx2] = 0.0;
        tod_to_mod[sigIdx + 3 * idx2] += rtb_s_2[3 * idx2] * (real_T)a_1[sigIdx];
        tod_to_mod[sigIdx + 3 * idx2] += rtb_s_2[3 * idx2 + 1] * (real_T)
          a_1[sigIdx + 3];
        tod_to_mod[sigIdx + 3 * idx2] += rtb_s_2[3 * idx2 + 2] * (real_T)
          a_1[sigIdx + 6];
      }
    }
  } else if ((rtb_UnitDelay_d == 32) && (idx2 == 0)) {
    /* '<S121>:1:72' elseif( sc_mode == 32 && flag == 0 ) */
    /*  Tilted so doesn't aling with COM2 -- chose a 5[deg] roll. */
    /* '<S121>:1:75' SP      = Cx5*[0;1;0]; */
    /*  Body */
    /* '<S121>:1:78' B1      = COM2; */
    /* '<S121>:1:79' B2      = SP./norm(SP); */
    /* '<S121>:1:80' Xtb     = B1; */
    /* '<S121>:1:81' Ytb     = cross(B1,B2)/norm(cross(B1,B2)); */
    /* '<S121>:1:82' Ztb     = cross(B1,Ytb)/norm(cross(B1,Ytb)); */
    /*  Inertial */
    /* '<S121>:1:85' S1      = sc2gs_unit; */
    /* '<S121>:1:86' S2      = sc2sun_unit; */
    /* '<S121>:1:87' Xti     = S1; */
    /* '<S121>:1:88' Yti     = cross(S1,S2)/norm(cross(S1,S2)); */
    rtb_s_1[0] = rtb_s[1] * rtb_S[2] - rtb_s[2] * rtb_S[1];
    rtb_s_1[1] = rtb_s[2] * rtb_S[0] - rtb_s[0] * rtb_S[2];
    rtb_s_1[2] = rtb_s[0] * rtb_S[1] - rtb_s[1] * rtb_S[0];
    mean_anom_sun_rad = norm_o(rtb_s_1);
    c_c = (rtb_s[1] * rtb_S[2] - rtb_s[2] * rtb_S[1]) / mean_anom_sun_rad;
    c = (rtb_s[2] * rtb_S[0] - rtb_s[0] * rtb_S[2]) / mean_anom_sun_rad;
    mean_anom_sun_rad = (rtb_s[0] * rtb_S[1] - rtb_s[1] * rtb_S[0]) /
      mean_anom_sun_rad;

    /* '<S121>:1:89' Zti     = cross(S1,Yti)/norm(cross(S1,Yti)); */
    rtb_s_0[0] = rtb_s[1] * mean_anom_sun_rad - rtb_s[2] * c;
    rtb_s_0[1] = rtb_s[2] * c_c - rtb_s[0] * mean_anom_sun_rad;
    rtb_s_0[2] = rtb_s[0] * c - rtb_s[1] * c_c;
    rtb_T_ut1_J2000 = norm_o(rtb_s_0);

    /*  Stack vectors */
    /* '<S121>:1:92' Cb  = [Xtb, Ytb, Ztb]; */
    /* '<S121>:1:93' Ci  = [Xti, Yti, Zti]; */
    /*  Commanded DCM ( body to inertial ) */
    /* '<S121>:1:96' C_cmd   = Cb*Ci'; */
    rtb_s_2[0] = rtb_s[0];
    rtb_s_2[1] = c_c;
    rtb_s_2[2] = (rtb_s[1] * mean_anom_sun_rad - rtb_s[2] * c) / rtb_T_ut1_J2000;
    rtb_s_2[3] = rtb_s[1];
    rtb_s_2[4] = c;
    rtb_s_2[5] = (rtb_s[2] * c_c - rtb_s[0] * mean_anom_sun_rad) /
      rtb_T_ut1_J2000;
    rtb_s_2[6] = rtb_s[2];
    rtb_s_2[7] = mean_anom_sun_rad;
    rtb_s_2[8] = (rtb_s[0] * c - rtb_s[1] * c_c) / rtb_T_ut1_J2000;
    for (idx2 = 0; idx2 < 3; idx2++) {
      for (sigIdx = 0; sigIdx < 3; sigIdx++) {
        tod_to_mod[sigIdx + 3 * idx2] = 0.0;
        tod_to_mod[sigIdx + 3 * idx2] += rtb_s_2[3 * idx2] * (real_T)
          b_a_0[sigIdx];
        tod_to_mod[sigIdx + 3 * idx2] += rtb_s_2[3 * idx2 + 1] * (real_T)
          b_a_0[sigIdx + 3];
        tod_to_mod[sigIdx + 3 * idx2] += rtb_s_2[3 * idx2 + 2] * (real_T)
          b_a_0[sigIdx + 6];
      }
    }
  } else {
    /* '<S121>:1:98' else */
    /* '<S121>:1:100' C_cmd   = eye(3); */
    memset(&tod_to_mod[0], 0, 9U * sizeof(real_T));
    tod_to_mod[0] = 1.0;
    tod_to_mod[4] = 1.0;
    tod_to_mod[8] = 1.0;
  }

  /*  Compute commanded quaternion from DCM */
  /* '<S121>:1:105' q_cmd   = myDCM2quat( C_cmd ); */
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
  /* '<S121>:1:130' q  = zeros(4,1); */
  /* '<S121>:1:131' tr = trace(DCM); */
  mean_anom_sun_rad = (tod_to_mod[0] + tod_to_mod[4]) + tod_to_mod[8];

  /* '<S121>:1:133' if (tr > 0) */
  if (mean_anom_sun_rad > 0.0) {
    /* '<S121>:1:134' sqtrp1 = sqrt( tr + 1.0 ); */
    rtb_T_ut1_J2000 = sqrt(mean_anom_sun_rad + 1.0);

    /* '<S121>:1:136' q(1) = 0.5*sqtrp1; */
    rtb_q_cmd[0] = 0.5 * rtb_T_ut1_J2000;

    /* '<S121>:1:137' q(2) = (DCM(2, 3) - DCM(3, 2))/(2.0*sqtrp1); */
    rtb_q_cmd[1] = (tod_to_mod[7] - tod_to_mod[5]) / (2.0 * rtb_T_ut1_J2000);

    /* '<S121>:1:138' q(3) = (DCM(3, 1) - DCM(1, 3))/(2.0*sqtrp1); */
    rtb_q_cmd[2] = (tod_to_mod[2] - tod_to_mod[6]) / (2.0 * rtb_T_ut1_J2000);

    /* '<S121>:1:139' q(4) = (DCM(1, 2) - DCM(2, 1))/(2.0*sqtrp1); */
    rtb_q_cmd[3] = (tod_to_mod[3] - tod_to_mod[1]) / (2.0 * rtb_T_ut1_J2000);
  } else {
    /* '<S121>:1:140' else */
    /* '<S121>:1:141' d = diag(DCM); */
    /* '<S121>:1:142' if ((d(2) > d(1)) && (d(2) > d(3))) */
    if ((tod_to_mod[4] > tod_to_mod[0]) && (tod_to_mod[4] > tod_to_mod[8])) {
      /* '<S121>:1:143' sqdip1 = sqrt(d(2) - d(1) - d(3) + 1.0 ); */
      rtb_T_ut1_J2000 = sqrt(((tod_to_mod[4] - tod_to_mod[0]) - tod_to_mod[8]) +
        1.0);

      /* '<S121>:1:145' q(3) = 0.5*sqdip1; */
      rtb_q_cmd[2] = 0.5 * rtb_T_ut1_J2000;

      /* '<S121>:1:147' if ( sqdip1 ~= 0 ) */
      if (rtb_T_ut1_J2000 != 0.0) {
        /* '<S121>:1:148' sqdip1 = 0.5/sqdip1; */
        rtb_T_ut1_J2000 = 0.5 / rtb_T_ut1_J2000;
      }

      /* '<S121>:1:151' q(1) = (DCM(3, 1) - DCM(1, 3))*sqdip1; */
      rtb_q_cmd[0] = (tod_to_mod[2] - tod_to_mod[6]) * rtb_T_ut1_J2000;

      /* '<S121>:1:152' q(2) = (DCM(1, 2) + DCM(2, 1))*sqdip1; */
      rtb_q_cmd[1] = (tod_to_mod[3] + tod_to_mod[1]) * rtb_T_ut1_J2000;

      /* '<S121>:1:153' q(4) = (DCM(2, 3) + DCM(3, 2))*sqdip1; */
      rtb_q_cmd[3] = (tod_to_mod[7] + tod_to_mod[5]) * rtb_T_ut1_J2000;
    } else if (tod_to_mod[8] > tod_to_mod[0]) {
      /* '<S121>:1:154' elseif (d(3) > d(1)) */
      /* '<S121>:1:155' sqdip1 = sqrt(d(3) - d(1) - d(2) + 1.0 ); */
      rtb_T_ut1_J2000 = sqrt(((tod_to_mod[8] - tod_to_mod[0]) - tod_to_mod[4]) +
        1.0);

      /* '<S121>:1:157' q(4) = 0.5*sqdip1; */
      rtb_q_cmd[3] = 0.5 * rtb_T_ut1_J2000;

      /* '<S121>:1:159' if ( sqdip1 ~= 0 ) */
      if (rtb_T_ut1_J2000 != 0.0) {
        /* '<S121>:1:160' sqdip1 = 0.5/sqdip1; */
        rtb_T_ut1_J2000 = 0.5 / rtb_T_ut1_J2000;
      }

      /* '<S121>:1:163' q(1) = (DCM(1, 2) - DCM(2, 1))*sqdip1; */
      rtb_q_cmd[0] = (tod_to_mod[3] - tod_to_mod[1]) * rtb_T_ut1_J2000;

      /* '<S121>:1:164' q(2) = (DCM(3, 1) + DCM(1, 3))*sqdip1; */
      rtb_q_cmd[1] = (tod_to_mod[2] + tod_to_mod[6]) * rtb_T_ut1_J2000;

      /* '<S121>:1:165' q(3) = (DCM(2, 3) + DCM(3, 2))*sqdip1; */
      rtb_q_cmd[2] = (tod_to_mod[7] + tod_to_mod[5]) * rtb_T_ut1_J2000;
    } else {
      /* '<S121>:1:166' else */
      /* '<S121>:1:167' sqdip1 = sqrt(d(1) - d(2) - d(3) + 1.0 ); */
      rtb_T_ut1_J2000 = sqrt(((tod_to_mod[0] - tod_to_mod[4]) - tod_to_mod[8]) +
        1.0);

      /* '<S121>:1:169' q(2) = 0.5*sqdip1; */
      rtb_q_cmd[1] = 0.5 * rtb_T_ut1_J2000;

      /* '<S121>:1:171' if ( sqdip1 ~= 0 ) */
      if (rtb_T_ut1_J2000 != 0.0) {
        /* '<S121>:1:172' sqdip1 = 0.5/sqdip1; */
        rtb_T_ut1_J2000 = 0.5 / rtb_T_ut1_J2000;
      }

      /* '<S121>:1:175' q(1) = (DCM(2, 3) - DCM(3, 2))*sqdip1; */
      rtb_q_cmd[0] = (tod_to_mod[7] - tod_to_mod[5]) * rtb_T_ut1_J2000;

      /* '<S121>:1:176' q(3) = (DCM(1, 2) + DCM(2, 1))*sqdip1; */
      rtb_q_cmd[2] = (tod_to_mod[3] + tod_to_mod[1]) * rtb_T_ut1_J2000;

      /* '<S121>:1:177' q(4) = (DCM(3, 1) + DCM(1, 3))*sqdip1; */
      rtb_q_cmd[3] = (tod_to_mod[2] + tod_to_mod[6]) * rtb_T_ut1_J2000;
    }
  }

  /* End of MATLAB Function: '<S7>/MATLAB Function2' */

  /* Sum: '<S44>/Sum' incorporates:
   *  Product: '<S44>/Product'
   *  Product: '<S44>/Product1'
   *  Product: '<S44>/Product2'
   *  Product: '<S44>/Product3'
   */
  c_c = ((rtb_q_cmd[0] * rtb_q_cmd[0] + rtb_q_cmd[1] * rtb_q_cmd[1]) +
         rtb_q_cmd[2] * rtb_q_cmd[2]) + rtb_q_cmd[3] * rtb_q_cmd[3];

  /* Product: '<S41>/Divide' */
  b_c = rtb_q_cmd[0] / c_c;

  /* Product: '<S41>/Divide1' incorporates:
   *  UnaryMinus: '<S43>/Unary Minus'
   */
  c = -rtb_q_cmd[1] / c_c;

  /* Product: '<S41>/Divide2' incorporates:
   *  UnaryMinus: '<S43>/Unary Minus1'
   */
  mean_anom_sun_rad = -rtb_q_cmd[2] / c_c;

  /* Product: '<S41>/Divide3' incorporates:
   *  UnaryMinus: '<S43>/Unary Minus2'
   */
  c_c = -rtb_q_cmd[3] / c_c;

  /* Sum: '<S45>/Sum' incorporates:
   *  Product: '<S45>/Product'
   *  Product: '<S45>/Product1'
   *  Product: '<S45>/Product2'
   *  Product: '<S45>/Product3'
   */
  rtb_T_ut1_J2000 = ((b_c * rtb_q_plu[0] - c * rtb_q_plu[1]) - mean_anom_sun_rad
                     * rtb_q_plu[2]) - c_c * rtb_q_plu[3];

  /* Signum: '<S34>/Sign' */
  if (rtb_T_ut1_J2000 < 0.0) {
    rtb_T_ut1_J2000 = -1.0;
  } else if (rtb_T_ut1_J2000 > 0.0) {
    rtb_T_ut1_J2000 = 1.0;
  } else {
    if (rtb_T_ut1_J2000 == 0.0) {
      rtb_T_ut1_J2000 = 0.0;
    }
  }

  /* End of Signum: '<S34>/Sign' */

  /* Sum: '<S46>/Sum' incorporates:
   *  Product: '<S46>/Product'
   *  Product: '<S46>/Product1'
   *  Product: '<S46>/Product2'
   *  Product: '<S46>/Product3'
   */
  oblq_rad = ((b_c * rtb_q_plu[1] + c * rtb_q_plu[0]) + mean_anom_sun_rad *
              rtb_q_plu[3]) - c_c * rtb_q_plu[2];

  /* Sum: '<S47>/Sum' incorporates:
   *  Product: '<S47>/Product'
   *  Product: '<S47>/Product1'
   *  Product: '<S47>/Product2'
   *  Product: '<S47>/Product3'
   */
  s = ((b_c * rtb_q_plu[2] - c * rtb_q_plu[3]) + mean_anom_sun_rad * rtb_q_plu[0])
    + c_c * rtb_q_plu[1];

  /* Sum: '<S48>/Sum' incorporates:
   *  Product: '<S48>/Product'
   *  Product: '<S48>/Product1'
   *  Product: '<S48>/Product2'
   *  Product: '<S48>/Product3'
   */
  c_c = ((b_c * rtb_q_plu[3] + c * rtb_q_plu[2]) - mean_anom_sun_rad *
         rtb_q_plu[1]) + c_c * rtb_q_plu[0];

  /* Product: '<S34>/Product2' */
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
  /* MATLAB Function 'target_generation_lib/MATLAB Function': '<S120>:1' */
  /*  Constants */
  /* '<S120>:1:17' XSPDA   = 86400; */
  /*  seconds per day */
  /* '<S120>:1:18' DE2RA   = 0.174532925e-1; */
  /*  radians/degree */
  /* '<S120>:1:19' n_orb   = [ 0.0; 0.0; orbit_tle(9)*2*pi/XSPDA ]; */
  /*  mean motion [rad/s] */
  /* '<S120>:1:20' INC     = orbit_tle(4)*DE2RA; */
  /*  inclination [rad] */
  /* '<S120>:1:21' RAAN    = orbit_tle(5)*DE2RA; */
  /*  right ascension of ascending node [rad] */
  /* '<S120>:1:22' AOP     = orbit_tle(7)*DE2RA; */
  /*  argument of perigee [rad] */
  /* '<S120>:1:24' C_orb2eci   = rot3(-RAAN)*rot1(-INC)*rot3(-AOP); */
  /* '<S120>:1:25' n_eci       = C_orb2eci*n_orb; */
  /* '<S120>:1:27' C_eci2body  = quat2DCM(sc_quat); */
  /* '<S120>:1:55' q0  = q(1); */
  /* '<S120>:1:56' qv  = reshape(q(2:4),3,1); */
  /* '<S120>:1:58' DCM     = (2*q0^2 - 1)*eye(3) + 2*(qv*qv') - 2*q0*skew(qv); */
  /* 'skew:4' cross = [0 -a(3) a(2); */
  /* 'skew:5'          a(3) 0 -a(1); */
  /* 'skew:6'         -a(2) a(1) 0]; */
  /* '<S120>:1:28' n_body      = C_eci2body'*n_eci; */
  /* '<S120>:1:30' if( sc_mode == 31 || sc_mode == 32 ) */
  IL4 = rtb_T_ut1_J2000 * oblq_rad;

  /* Sum: '<S34>/Sum1' */
  rtb_omega_cmd[0] = N[0];

  /* Product: '<S34>/Product2' */
  IL3 = rtb_T_ut1_J2000 * s;

  /* Sum: '<S34>/Sum1' */
  rtb_omega_cmd[1] = N[1];

  /* Product: '<S34>/Product2' */
  mean_anom_sun_rad = rtb_T_ut1_J2000 * c_c;

  /* Sum: '<S34>/Sum1' */
  rtb_omega_cmd[2] = N[2];
  for (idx2 = 0; idx2 < 3; idx2++) {
    /* Saturate: '<S34>/Saturation' incorporates:
     *  Constant: '<S34>/Constant'
     *  Constant: '<S34>/Constant1'
     *  Product: '<S34>/Product'
     *  Product: '<S34>/Product1'
     *  Sum: '<S34>/Sum'
     *  Sum: '<S34>/Sum1'
     */
    rtb_T_ut1_J2000 = (rtConstP.Constant_Value_p[idx2 + 6] * mean_anom_sun_rad +
                       (rtConstP.Constant_Value_p[idx2 + 3] * IL3 +
                        rtConstP.Constant_Value_p[idx2] * IL4)) +
      (rtConstP.Constant1_Value_l[idx2 + 6] * N[2] +
       (rtConstP.Constant1_Value_l[idx2 + 3] * rtb_omega_cmd[1] +
        rtConstP.Constant1_Value_l[idx2] * rtb_omega_cmd[0]));
    if (rtb_T_ut1_J2000 > 0.005) {
      rtb_s[idx2] = 0.005;
    } else if (rtb_T_ut1_J2000 < -0.005) {
      rtb_s[idx2] = -0.005;
    } else {
      rtb_s[idx2] = rtb_T_ut1_J2000;
    }

    /* End of Saturate: '<S34>/Saturation' */
  }

  /* MultiPortSwitch: '<S33>/Multiport Switch' incorporates:
   *  Inport: '<Root>/mag_vec_body_T'
   *  UnitDelay: '<S33>/Unit Delay'
   */
  if ((int32_T)rtU.mag_vec_body_T[3] == 0) {
    rtb_m[0] = rtDW.UnitDelay_DSTATE_b[0];
    rtb_m[1] = rtDW.UnitDelay_DSTATE_b[1];
    rtb_m[2] = rtDW.UnitDelay_DSTATE_b[2];
  } else {
    rtb_m[0] = rtU.mag_vec_body_T[0];
    rtb_m[1] = rtU.mag_vec_body_T[1];
    rtb_m[2] = rtU.mag_vec_body_T[2];
  }

  /* End of MultiPortSwitch: '<S33>/Multiport Switch' */

  /* S-Function (sdsp2norm2): '<S33>/Normalization' */
  idx2 = 0;
  IL4 = 1.0 / (((rtb_m[0] * rtb_m[0] + rtb_m[1] * rtb_m[1]) + rtb_m[2] * rtb_m[2])
               + 1.0E-10);

  /* Signum: '<S40>/Sign2' incorporates:
   *  Inport: '<Root>/RW_rpm'
   */
  if (rtU.RW_rpm[0] < 0.0) {
    IL3 = -1.0;
  } else if (rtU.RW_rpm[0] > 0.0) {
    IL3 = 1.0;
  } else if (rtU.RW_rpm[0] == 0.0) {
    IL3 = 0.0;
  } else {
    IL3 = rtU.RW_rpm[0];
  }

  /* End of Signum: '<S40>/Sign2' */

  /* Gain: '<S40>/rpm2radps' incorporates:
   *  Gain: '<S40>/Gain'
   */
  rtb_Gain1_a[0] = 1000.0 * IL3;

  /* Signum: '<S40>/Sign1' incorporates:
   *  Inport: '<Root>/RW_rpm'
   */
  if (rtU.RW_rpm[1] < 0.0) {
    IL3 = -1.0;
  } else if (rtU.RW_rpm[1] > 0.0) {
    IL3 = 1.0;
  } else if (rtU.RW_rpm[1] == 0.0) {
    IL3 = 0.0;
  } else {
    IL3 = rtU.RW_rpm[1];
  }

  /* End of Signum: '<S40>/Sign1' */

  /* Gain: '<S40>/rpm2radps' incorporates:
   *  Gain: '<S40>/Gain1'
   */
  rtb_Gain1_a[1] = 1000.0 * IL3;

  /* Signum: '<S40>/Sign' incorporates:
   *  Inport: '<Root>/RW_rpm'
   */
  if (rtU.RW_rpm[2] < 0.0) {
    IL3 = -1.0;
  } else if (rtU.RW_rpm[2] > 0.0) {
    IL3 = 1.0;
  } else if (rtU.RW_rpm[2] == 0.0) {
    IL3 = 0.0;
  } else {
    IL3 = rtU.RW_rpm[2];
  }

  /* End of Signum: '<S40>/Sign' */

  /* Gain: '<S40>/rpm2radps' incorporates:
   *  Gain: '<S40>/Gain2'
   */
  rtb_Gain1_a[2] = 1000.0 * IL3;
  for (sigIdx = 0; sigIdx < 3; sigIdx++) {
    /* S-Function (sdsp2norm2): '<S33>/Normalization' */
    rtb_omega_cmd[idx2] = rtb_m[idx2] * IL4;
    idx2++;

    /* Gain: '<S40>/rpm2radps' incorporates:
     *  Product: '<S40>/Product'
     */
    tmp_4[sigIdx] = 0.10471975511965977 * rtb_Gain1_a[sigIdx];

    /* Product: '<S33>/Matrix Multiply' incorporates:
     *  Constant: '<S33>/RW_inertia'
     *  Gain: '<S33>/rpm2radps'
     *  Inport: '<Root>/RW_rpm'
     *  Sum: '<S33>/Sum'
     */
    rtb_S[sigIdx] = rtConstP.pooled23[sigIdx + 6] * (0.10471975511965977 *
      rtU.RW_rpm[2]) + (rtConstP.pooled23[sigIdx + 3] * (0.10471975511965977 *
      rtU.RW_rpm[1]) + 0.10471975511965977 * rtU.RW_rpm[0] *
                        rtConstP.pooled23[sigIdx]);
  }

  for (idx2 = 0; idx2 < 3; idx2++) {
    /* Sum: '<S33>/Sum' incorporates:
     *  Constant: '<S40>/wheel_inertia'
     *  Product: '<S40>/Product'
     */
    rtb_Sum_o[idx2] = rtb_S[idx2] - (rtConstP.pooled23[idx2 + 6] * tmp_4[2] +
      (rtConstP.pooled23[idx2 + 3] * tmp_4[1] + rtConstP.pooled23[idx2] * tmp_4
       [0]));
  }

  /* Saturate: '<S33>/Sat2' incorporates:
   *  Gain: '<S33>/-gain'
   *  Product: '<S39>/Element product'
   *  Sum: '<S39>/Add3'
   */
  rtb_T_ut1_J2000 = (rtb_omega_cmd[1] * rtb_Sum_o[2] - rtb_omega_cmd[2] *
                     rtb_Sum_o[1]) * -0.5;

  /* Saturate: '<S33>/Sat' incorporates:
   *  Gain: '<S33>/-gain'
   *  Product: '<S39>/Element product'
   *  Sum: '<S39>/Add3'
   */
  s = (rtb_omega_cmd[2] * rtb_Sum_o[0] - rtb_omega_cmd[0] * rtb_Sum_o[2]) * -0.5;

  /* Saturate: '<S33>/Sat1' incorporates:
   *  Gain: '<S33>/-gain'
   *  Product: '<S39>/Element product'
   *  Sum: '<S39>/Add3'
   */
  oblq_rad = (rtb_omega_cmd[0] * rtb_Sum_o[1] - rtb_omega_cmd[1] * rtb_Sum_o[0])
    * -0.5;

  /* SampleTimeMath: '<S49>/TSamp' incorporates:
   *  DiscreteTransferFcn: '<S35>/Discrete Transfer Fcn'
   *
   * About '<S49>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  c_c = 0.060898632575707344 * rtDW.DiscreteTransferFcn_states[0] * 10.0;
  c = 0.060898632575707344 * rtDW.DiscreteTransferFcn_states[1] * 10.0;
  mean_anom_sun_rad = 0.060898632575707344 * rtDW.DiscreteTransferFcn_states[2] *
    10.0;

  /* MultiPortSwitch: '<S35>/Multiport Switch1' incorporates:
   *  Inport: '<Root>/mag_vec_body_T'
   *  Sum: '<S49>/Diff'
   *  UnitDelay: '<S35>/Unit Delay'
   *  UnitDelay: '<S49>/UD'
   *
   * Block description for '<S49>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S49>/UD':
   *
   *  Store in Global RAM
   */
  if ((int32_T)rtU.mag_vec_body_T[3] == 0) {
    rtb_Sum_o[0] = rtDW.UnitDelay_DSTATE_o[0];
    rtb_Sum_o[1] = rtDW.UnitDelay_DSTATE_o[1];
    rtb_Sum_o[2] = rtDW.UnitDelay_DSTATE_o[2];
  } else {
    rtb_Sum_o[0] = c_c - rtDW.UD_DSTATE[0];
    rtb_Sum_o[1] = c - rtDW.UD_DSTATE[1];
    rtb_Sum_o[2] = mean_anom_sun_rad - rtDW.UD_DSTATE[2];
  }

  /* End of MultiPortSwitch: '<S35>/Multiport Switch1' */

  /* Product: '<S35>/Product' incorporates:
   *  Constant: '<S35>/gain matrix'
   */
  for (idx2 = 0; idx2 < 3; idx2++) {
    rtb_S[idx2] = rtConstP.gainmatrix_Value[idx2 + 6] * rtb_Sum_o[2] +
      (rtConstP.gainmatrix_Value[idx2 + 3] * rtb_Sum_o[1] +
       rtConstP.gainmatrix_Value[idx2] * rtb_Sum_o[0]);
  }

  /* End of Product: '<S35>/Product' */

  /* Outputs for Atomic SubSystem: '<S4>/sun_point_lib' */
  /* MultiPortSwitch: '<S37>/Multiport Switch' incorporates:
   *  Constant: '<S56>/Constant'
   *  Constant: '<S57>/Constant'
   *  Inport: '<Root>/faceinsun_body_unit'
   *  Inport: '<Root>/sun_vec_body_sunsensor'
   *  Logic: '<S37>/Logical Operator'
   *  RelationalOperator: '<S56>/Compare'
   *  RelationalOperator: '<S57>/Compare'
   */
  if (!((rtU.sun_vec_body_sunsensor[3] <= 1.5) && (rtU.sun_vec_body_sunsensor[3]
        >= 0.5))) {
    rtb_omega_cmd[0] = rtU.faceinsun_body_unit[0];
    rtb_omega_cmd[1] = rtU.faceinsun_body_unit[1];
    rtb_omega_cmd[2] = rtU.faceinsun_body_unit[2];
  } else {
    rtb_omega_cmd[0] = rtU.sun_vec_body_sunsensor[0];
    rtb_omega_cmd[1] = rtU.sun_vec_body_sunsensor[1];
    rtb_omega_cmd[2] = rtU.sun_vec_body_sunsensor[2];
  }

  /* End of MultiPortSwitch: '<S37>/Multiport Switch' */

  /* S-Function (sdsp2norm2): '<S58>/Normalization1' */
  IL4 = 1.0 / (sqrt((rtb_omega_cmd[0] * rtb_omega_cmd[0] + rtb_omega_cmd[1] *
                     rtb_omega_cmd[1]) + rtb_omega_cmd[2] * rtb_omega_cmd[2]) +
               1.0E-10);
  rtb_omega_cmd[0] *= IL4;
  rtb_omega_cmd[1] *= IL4;
  rtb_omega_cmd[2] *= IL4;

  /* DotProduct: '<S58>/Dot Product' */
  IL3 = (rtb_omega_cmd[0] * 0.0 + rtb_omega_cmd[1] * 0.9999999999) +
    rtb_omega_cmd[2] * 0.0;

  /* Saturate: '<S58>/Saturation' */
  if (IL3 > 1.0) {
    IL3 = 1.0;
  } else {
    if (IL3 < -1.0) {
      IL3 = -1.0;
    }
  }

  /* End of Saturate: '<S58>/Saturation' */

  /* Trigonometry: '<S58>/Trigonometric Function2' incorporates:
   *  Gain: '<S58>/Gain1'
   *  Trigonometry: '<S58>/Trigonometric Function'
   */
  IL3 = sin(0.5 * acos(IL3));

  /* Sum: '<S59>/Sum' incorporates:
   *  Product: '<S60>/i x j'
   *  Product: '<S60>/j x k'
   *  Product: '<S60>/k x i'
   *  Product: '<S61>/i x k'
   *  Product: '<S61>/j x i'
   *  Product: '<S61>/k x j'
   */
  rtb_Sum_d[0] = rtb_omega_cmd[1] * 0.0 - rtb_omega_cmd[2] * 0.9999999999;
  rtb_Sum_d[1] = rtb_omega_cmd[2] * 0.0 - rtb_omega_cmd[0] * 0.0;
  rtb_Sum_d[2] = rtb_omega_cmd[0] * 0.9999999999 - rtb_omega_cmd[1] * 0.0;

  /* S-Function (sdsp2norm2): '<S58>/Normalization' */
  IL4 = 1.0 / (sqrt((rtb_Sum_d[0] * rtb_Sum_d[0] + rtb_Sum_d[1] * rtb_Sum_d[1])
                    + rtb_Sum_d[2] * rtb_Sum_d[2]) + 1.0E-10);

  /* Switch: '<S58>/Switch' incorporates:
   *  DotProduct: '<S58>/Dot Product1'
   *  Product: '<S58>/Product'
   *  S-Function (sdsp2norm2): '<S58>/Normalization'
   *  Sqrt: '<S58>/Sqrt'
   *  UnitDelay: '<S58>/Unit Delay'
   */
  rtb_Switch_p = (sqrt((rtb_Sum_d[0] * rtb_Sum_d[0] + rtb_Sum_d[1] * rtb_Sum_d[1])
                       + rtb_Sum_d[2] * rtb_Sum_d[2]) != 0.0);
  if (rtb_Switch_p) {
    b_c = rtb_Sum_d[0] * IL4 * IL3;
  } else {
    b_c = rtDW.UnitDelay_DSTATE_k[0];
  }

  /* Update for UnitDelay: '<S58>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_k[0] = b_c;

  /* Switch: '<S58>/Switch' incorporates:
   *  Product: '<S58>/Product'
   *  S-Function (sdsp2norm2): '<S58>/Normalization'
   *  UnitDelay: '<S58>/Unit Delay'
   */
  rtb_omega_cmd[0] = b_c;
  if (rtb_Switch_p) {
    b_c = rtb_Sum_d[1] * IL4 * IL3;
  } else {
    b_c = rtDW.UnitDelay_DSTATE_k[1];
  }

  /* Update for UnitDelay: '<S58>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_k[1] = b_c;

  /* Switch: '<S58>/Switch' incorporates:
   *  Product: '<S58>/Product'
   *  S-Function (sdsp2norm2): '<S58>/Normalization'
   *  UnitDelay: '<S58>/Unit Delay'
   */
  rtb_omega_cmd[1] = b_c;
  if (rtb_Switch_p) {
    b_c = rtb_Sum_d[2] * IL4 * IL3;
  } else {
    b_c = rtDW.UnitDelay_DSTATE_k[2];
  }

  /* Update for UnitDelay: '<S58>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_k[2] = b_c;

  /* End of Outputs for SubSystem: '<S4>/sun_point_lib' */

  /* Saturate: '<S33>/Sat2' */
  if (rtb_T_ut1_J2000 > 0.2) {
    /* SignalConversion: '<S38>/TmpSignal ConversionAt SFunction Inport3' incorporates:
     *  MATLAB Function: '<S32>/MATLAB Function'
     */
    rtb_TmpSignalConversionAtSFunct[0] = 0.2;
  } else if (rtb_T_ut1_J2000 < -0.2) {
    /* SignalConversion: '<S38>/TmpSignal ConversionAt SFunction Inport3' incorporates:
     *  MATLAB Function: '<S32>/MATLAB Function'
     */
    rtb_TmpSignalConversionAtSFunct[0] = -0.2;
  } else {
    /* SignalConversion: '<S38>/TmpSignal ConversionAt SFunction Inport3' incorporates:
     *  MATLAB Function: '<S32>/MATLAB Function'
     */
    rtb_TmpSignalConversionAtSFunct[0] = rtb_T_ut1_J2000;
  }

  /* Saturate: '<S33>/Sat' */
  if (s > 0.2) {
    /* SignalConversion: '<S38>/TmpSignal ConversionAt SFunction Inport3' incorporates:
     *  MATLAB Function: '<S32>/MATLAB Function'
     */
    rtb_TmpSignalConversionAtSFunct[1] = 0.2;
  } else if (s < -0.2) {
    /* SignalConversion: '<S38>/TmpSignal ConversionAt SFunction Inport3' incorporates:
     *  MATLAB Function: '<S32>/MATLAB Function'
     */
    rtb_TmpSignalConversionAtSFunct[1] = -0.2;
  } else {
    /* SignalConversion: '<S38>/TmpSignal ConversionAt SFunction Inport3' incorporates:
     *  MATLAB Function: '<S32>/MATLAB Function'
     */
    rtb_TmpSignalConversionAtSFunct[1] = s;
  }

  /* Saturate: '<S33>/Sat1' */
  if (oblq_rad > 0.2) {
    /* SignalConversion: '<S38>/TmpSignal ConversionAt SFunction Inport3' incorporates:
     *  MATLAB Function: '<S32>/MATLAB Function'
     */
    rtb_TmpSignalConversionAtSFunct[2] = 0.2;
  } else if (oblq_rad < -0.2) {
    /* SignalConversion: '<S38>/TmpSignal ConversionAt SFunction Inport3' incorporates:
     *  MATLAB Function: '<S32>/MATLAB Function'
     */
    rtb_TmpSignalConversionAtSFunct[2] = -0.2;
  } else {
    /* SignalConversion: '<S38>/TmpSignal ConversionAt SFunction Inport3' incorporates:
     *  MATLAB Function: '<S32>/MATLAB Function'
     */
    rtb_TmpSignalConversionAtSFunct[2] = oblq_rad;
  }

  /* MATLAB Function: '<S32>/MATLAB Function' */
  /*  Control Selection Logic */
  /*  */
  /*  Selects which command gets passed to the actuators based on the mode */
  /*  provided by upstream mode selection. Current modes are: */
  /*    mode_logic.bdot             = 1; */
  /*    mode_logic.desat_eclipse    = 2; */
  /*    mode_logic.point            = 3; */
  /*        point.velocity          = 31; */
  /*        point.ground            = 32; */
  /*    mode_logic.low_power        = 4; */
  /*    mode_logic.sun_seek         = 5; */
  /*  */
  /*  FLAG output can be used to make sure the control output matches up with */
  /*  what is being commanded, before commands are passed to actuators. FLAG */
  /*  should match mode, unless something is wrong. */
  /*  */
  /*  RAIN-SAT: T. Reynolds 7.7.18 */
  /* MATLAB Function 'command_generation/Control Selection/MATLAB Function': '<S38>:1' */
  /* '<S38>:1:20' FLAG    = 1; */
  /* '<S38>:1:22' if( mode == 1 ) */
  switch (rtb_UnitDelay_d) {
   case 1:
    /* '<S38>:1:23' cmd_RW_out  = zeros(3,1); */
    rtb_s[0] = 0.0;
    rtb_s[1] = 0.0;
    rtb_s[2] = 0.0;

    /* Saturate: '<S35>/Saturation1' */
    /* '<S38>:1:24' cmd_MT_out  = cmd_MT_bDot; */
    if (rtb_S[0] > 0.2) {
      rtb_TmpSignalConversionAtSFunct[0] = 0.2;
    } else if (rtb_S[0] < -0.2) {
      rtb_TmpSignalConversionAtSFunct[0] = -0.2;
    } else {
      rtb_TmpSignalConversionAtSFunct[0] = rtb_S[0];
    }

    /* End of Saturate: '<S35>/Saturation1' */

    /* Saturate: '<S35>/Saturation2' */
    if (rtb_S[1] > 0.2) {
      rtb_TmpSignalConversionAtSFunct[1] = 0.2;
    } else if (rtb_S[1] < -0.2) {
      rtb_TmpSignalConversionAtSFunct[1] = -0.2;
    } else {
      rtb_TmpSignalConversionAtSFunct[1] = rtb_S[1];
    }

    /* End of Saturate: '<S35>/Saturation2' */

    /* Saturate: '<S35>/Saturation3' */
    if (rtb_S[2] > 0.2) {
      rtb_TmpSignalConversionAtSFunct[2] = 0.2;
    } else if (rtb_S[2] < -0.2) {
      rtb_TmpSignalConversionAtSFunct[2] = -0.2;
    } else {
      rtb_TmpSignalConversionAtSFunct[2] = rtb_S[2];
    }

    /* End of Saturate: '<S35>/Saturation3' */
    break;

   case 2:
    /* '<S38>:1:25' elseif( mode == 2 ) */
    /* '<S38>:1:26' cmd_RW_out  = cmd_RW; */
    /* '<S38>:1:27' cmd_MT_out  = cmd_MT_pDump; */
    break;

   default:
    if (!((rtb_UnitDelay_d == 31) || (rtb_UnitDelay_d == 32) || (rtb_UnitDelay_d
          == 33))) {
      switch (rtb_UnitDelay_d) {
       case 4:
        /* '<S38>:1:31' elseif( mode == 4 ) */
        /* '<S38>:1:32' cmd_RW_out  = zeros(3,1); */
        /* '<S38>:1:33' cmd_MT_out  = zeros(3,1); */
        rtb_s[0] = 0.0;
        rtb_TmpSignalConversionAtSFunct[0] = 0.0;
        rtb_s[1] = 0.0;
        rtb_TmpSignalConversionAtSFunct[1] = 0.0;
        rtb_s[2] = 0.0;
        rtb_TmpSignalConversionAtSFunct[2] = 0.0;
        break;

       case 5:
        /* Outputs for Atomic SubSystem: '<S4>/sun_point_lib' */
        /* '<S38>:1:34' elseif( mode == 5 ) */
        /* '<S38>:1:35' cmd_RW_out  = cmd_RW_ss; */
        /* '<S38>:1:36' cmd_MT_out  = zeros(3,1); */
        for (idx2 = 0; idx2 < 3; idx2++) {
          /* Saturate: '<S37>/Saturation' incorporates:
           *  Gain: '<S37>/drv_gain'
           *  Gain: '<S37>/prop_gain'
           *  Sum: '<S37>/Sum'
           */
          rtb_T_ut1_J2000 = (rtConstP.prop_gain_Gain[idx2 + 6] * b_c +
                             (rtConstP.prop_gain_Gain[idx2 + 3] * rtb_omega_cmd
                              [1] + rtConstP.prop_gain_Gain[idx2] *
                              rtb_omega_cmd[0])) + (rtConstP.drv_gain_Gain[idx2
            + 6] * N[2] + (rtConstP.drv_gain_Gain[idx2 + 3] * N[1] +
                           rtConstP.drv_gain_Gain[idx2] * N[0]));
          if (rtb_T_ut1_J2000 > 0.005) {
            rtb_s[idx2] = 0.005;
          } else if (rtb_T_ut1_J2000 < -0.005) {
            rtb_s[idx2] = -0.005;
          } else {
            rtb_s[idx2] = rtb_T_ut1_J2000;
          }

          /* End of Saturate: '<S37>/Saturation' */
          rtb_TmpSignalConversionAtSFunct[idx2] = 0.0;
        }

        /* End of Outputs for SubSystem: '<S4>/sun_point_lib' */
        break;

       default:
        /* '<S38>:1:37' else */
        /* '<S38>:1:38' FLAG = -1; */
        /* '<S38>:1:39' cmd_RW_out  = zeros(3,1); */
        /* '<S38>:1:40' cmd_MT_out  = zeros(3,1); */
        rtb_s[0] = 0.0;
        rtb_TmpSignalConversionAtSFunct[0] = 0.0;
        rtb_s[1] = 0.0;
        rtb_TmpSignalConversionAtSFunct[1] = 0.0;
        rtb_s[2] = 0.0;
        rtb_TmpSignalConversionAtSFunct[2] = 0.0;
        break;
      }
    } else {
      /* '<S38>:1:28' elseif( mode == 31 || mode == 32 || mode == 33 ) */
      /* '<S38>:1:29' cmd_RW_out  = cmd_RW; */
      /* '<S38>:1:30' cmd_MT_out  = cmd_MT_pDump; */
    }
    break;
  }

  /* Product: '<S50>/Product' incorporates:
   *  Constant: '<S50>/Constant1'
   *  Inport: '<Root>/mag_vec_body_T'
   *  Sum: '<S50>/Sum'
   */
  for (idx2 = 0; idx2 < 3; idx2++) {
    rtb_Sum_d[idx2] = rtConstP.Constant1_Value_o[idx2 + 6] * rtU.mag_vec_body_T
      [2] + (rtConstP.Constant1_Value_o[idx2 + 3] * rtU.mag_vec_body_T[1] +
             rtConstP.Constant1_Value_o[idx2] * rtU.mag_vec_body_T[0]);
  }

  /* End of Product: '<S50>/Product' */

  /* RateTransition: '<S36>/Rate Transition' */
  if (rtM->Timing.RateInteraction.TID2_3 == 1) {
    rtDW.RateTransition = rtDW.RateTransition_Buffer0;
  }

  /* End of RateTransition: '<S36>/Rate Transition' */

  /* Switch: '<S36>/Switch' incorporates:
   *  Constant: '<S51>/Constant'
   *  RelationalOperator: '<S51>/Compare'
   */
  if (rtDW.RateTransition <= 0.5) {
    /* Gain: '<S52>/To DigVal1' */
    rtb_T_ut1_J2000 = 500.0 * rtb_TmpSignalConversionAtSFunct[0];

    /* DataTypeConversion: '<S52>/Data Type Conversion' */
    IL4 = fabs(rtb_T_ut1_J2000);
    if (IL4 < 4.503599627370496E+15) {
      if (IL4 >= 0.5) {
        rtb_Switch_j[0] = (int8_T)floor(rtb_T_ut1_J2000 + 0.5);
      } else {
        rtb_Switch_j[0] = (int8_T)(rtb_T_ut1_J2000 * 0.0);
      }
    } else {
      rtb_Switch_j[0] = (int8_T)rtb_T_ut1_J2000;
    }

    /* End of DataTypeConversion: '<S52>/Data Type Conversion' */

    /* Gain: '<S52>/To DigVal2' */
    rtb_T_ut1_J2000 = 500.0 * rtb_TmpSignalConversionAtSFunct[1];

    /* DataTypeConversion: '<S52>/Data Type Conversion1' */
    IL4 = fabs(rtb_T_ut1_J2000);
    if (IL4 < 4.503599627370496E+15) {
      if (IL4 >= 0.5) {
        rtb_Switch_j[1] = (int8_T)floor(rtb_T_ut1_J2000 + 0.5);
      } else {
        rtb_Switch_j[1] = (int8_T)(rtb_T_ut1_J2000 * 0.0);
      }
    } else {
      rtb_Switch_j[1] = (int8_T)rtb_T_ut1_J2000;
    }

    /* End of DataTypeConversion: '<S52>/Data Type Conversion1' */

    /* Gain: '<S52>/To DigVal3' */
    rtb_T_ut1_J2000 = 500.0 * rtb_TmpSignalConversionAtSFunct[2];

    /* DataTypeConversion: '<S52>/Data Type Conversion2' */
    IL4 = fabs(rtb_T_ut1_J2000);
    if (IL4 < 4.503599627370496E+15) {
      if (IL4 >= 0.5) {
        rtb_Switch_j[2] = (int8_T)floor(rtb_T_ut1_J2000 + 0.5);
      } else {
        rtb_Switch_j[2] = (int8_T)(rtb_T_ut1_J2000 * 0.0);
      }
    } else {
      rtb_Switch_j[2] = (int8_T)rtb_T_ut1_J2000;
    }

    /* End of DataTypeConversion: '<S52>/Data Type Conversion2' */
  } else {
    rtb_Switch_j[0] = 0;
    rtb_Switch_j[1] = 0;
    rtb_Switch_j[2] = 0;
  }

  /* End of Switch: '<S36>/Switch' */

  /* Assertion: '<S54>/Assertion' incorporates:
   *  Sum: '<S55>/Sum'
   */
  utAssert(true);

  /* Product: '<S54>/Product' incorporates:
   *  Constant: '<S53>/Constant'
   */
  rt_invd3x3_snf(rtConstP.pooled23, rtb_MatrixMultiply);
  for (idx2 = 0; idx2 < 3; idx2++) {
    /* Saturate: '<S53>/Saturation' incorporates:
     *  DiscreteIntegrator: '<S53>/Discrete-Time Integrator'
     *  Gain: '<S53>/radps_2_rpm'
     *  Product: '<S53>/Product'
     */
    rtb_T_ut1_J2000 = 9.5492965855137211 * (rtb_MatrixMultiply[idx2 + 6] *
      rtDW.DiscreteTimeIntegrator_DSTATE[2] + (rtb_MatrixMultiply[idx2 + 3] *
      rtDW.DiscreteTimeIntegrator_DSTATE[1] + rtb_MatrixMultiply[idx2] *
      rtDW.DiscreteTimeIntegrator_DSTATE[0]));
    if (rtb_T_ut1_J2000 > 13500.0) {
      rtb_TmpSignalConversionAtSFunct[idx2] = 13500.0;
    } else if (rtb_T_ut1_J2000 < -13500.0) {
      rtb_TmpSignalConversionAtSFunct[idx2] = -13500.0;
    } else {
      rtb_TmpSignalConversionAtSFunct[idx2] = rtb_T_ut1_J2000;
    }

    /* End of Saturate: '<S53>/Saturation' */

    /* Gain: '<S65>/Gain1' incorporates:
     *  Product: '<S65>/Product1'
     */
    rtb_Gain1_a[idx2] = 1000.0 * (rtb_teme_to_gcrf[idx2 + 6] * b_o +
      (rtb_teme_to_gcrf[idx2 + 3] * xi + rtb_teme_to_gcrf[idx2] * c_s));

    /* Abs: '<S6>/Abs' */
    rtb_S[idx2] = fabs(N[idx2]);

    /* Abs: '<S6>/Abs1' incorporates:
     *  Inport: '<Root>/RW_rpm'
     */
    rtb_omega_cmd[idx2] = fabs(rtU.RW_rpm[idx2]);
  }

  /* MinMax: '<S6>/MinMax' */
  if ((rtb_S[0] >= rtb_S[1]) || rtIsNaN(rtb_S[1])) {
    rtb_T_ut1_J2000 = rtb_S[0];
  } else {
    rtb_T_ut1_J2000 = rtb_S[1];
  }

  if (!((rtb_T_ut1_J2000 >= rtb_S[2]) || rtIsNaN(rtb_S[2]))) {
    rtb_T_ut1_J2000 = rtb_S[2];
  }

  /* Relay: '<S6>/Relay' incorporates:
   *  MinMax: '<S6>/MinMax'
   */
  if (rtb_T_ut1_J2000 >= 0.12) {
    rtDW.Relay_Mode = true;
  } else {
    if (rtb_T_ut1_J2000 <= 0.00436) {
      rtDW.Relay_Mode = false;
    }
  }

  /* MinMax: '<S6>/MinMax1' */
  if ((rtb_omega_cmd[0] >= rtb_omega_cmd[1]) || rtIsNaN(rtb_omega_cmd[1])) {
    rtb_T_ut1_J2000 = rtb_omega_cmd[0];
  } else {
    rtb_T_ut1_J2000 = rtb_omega_cmd[1];
  }

  if (!((rtb_T_ut1_J2000 >= rtb_omega_cmd[2]) || rtIsNaN(rtb_omega_cmd[2]))) {
    rtb_T_ut1_J2000 = rtb_omega_cmd[2];
  }

  /* Relay: '<S6>/Relay1' incorporates:
   *  MinMax: '<S6>/MinMax1'
   */
  if (rtb_T_ut1_J2000 >= 10000.0) {
    rtDW.Relay1_Mode = true;
  } else {
    if (rtb_T_ut1_J2000 <= 2000.0) {
      rtDW.Relay1_Mode = false;
    }
  }

  /* MATLAB Function: '<S6>/MATLAB Function' incorporates:
   *  Constant: '<S118>/Constant'
   *  Inport: '<Root>/RW_valid'
   *  Inport: '<Root>/sun_vec_body_sunsensor'
   *  Inport: '<Root>/telecom'
   *  Logic: '<S2>/Logical Operator1'
   *  Logic: '<S6>/Logical Operator'
   *  MATLAB Function: '<S66>/MATLAB Function1'
   *  MATLAB Function: '<S68>/MATLAB Function1'
   *  RelationalOperator: '<S118>/Compare'
   *  Relay: '<S6>/Relay'
   *  Relay: '<S6>/Relay1'
   */
  /* GNC_MODE_LOGIC    GNC Mode Selector */
  /*  */
  /*  Chooses control mode based on sensor and actuator data. */
  /*    mode_logic.bdot             = 1; */
  /*    mode_logic.desat            = 2; */
  /*    mode_logic.point            = 3; */
  /*        point.velocity          = 31; */
  /*        point.ground            = 32; */
  /*        point.MPC               = 33; */
  /*    mode_logic.low_power        = 4; */
  /*    mode_logic.sun_seek         = 5; */
  /*  */
  /*  ----- INPUTS ----- */
  /*  */
  /*  1. telecom - Data coming from the bus. Parsed according to: */
  /*  */
  /*    telecom(1) == Override the autonomous mode selection and command the mode */
  /*                corresponding to this number. Set to 0 if the autonomous  */
  /*                selection is to go ahead. Type: int8 */
  /*    telecom(2) == Reboot just occured OR we just exited a detumble.  */
  /*                s/c will sit in this mode until either pointing takes over */
  /*                or body rates rise again. Type: int8 */
  /*    telecom(3) == Go ahead for the pointing mode. One means the s/c */
  /*                is go for pointing of any kind. Type: int8 */
  /*  */
  /*  2. sc_in_sun: - Tells us if the s/c is in eclipse. Type: boolean. */
  /*  3. ss_valid:  - validity bit from the sun_sensor. Used to decide if we */
  /*                    need to enter sun_seek mode */
  /*  4. gs_appraoch: - Tells us if the ground station is approaching based on */
  /*                    reorientation criteria. Type: boolean. */
  /*  */
  /*  bdot_flag: - Output from the relay block. Goes high when thresh_max is */
  /*  hit, and does not go low until thresh_min is hit (hysteresis). */
  /*  */
  /*  desat_flag: - Same as bdot_flag but with reaction wheel RPM thresholds. */
  /*  */
  /*  sc_mode_old - Previous spacecraft state, used to test exit conditions for */
  /*                    each mode. */
  /*  */
  /*  ----- OUTPUTS ----- */
  /*  */
  /*  sc_mode - Spacecraft state determined. Type: double. */
  /*  */
  /*  sc_exp - Extra state corresponding to what type of experimental control */
  /*            is engaged. Only nonzero if sc_mode == 33. */
  /*     */
  /*  RAIN-SAT -- T. Reynolds 2.15.18 */
  /* MATLAB Function 'mode_selecction/MATLAB Function': '<S119>:1' */
  /*  Default to last known condition and no experimental control */
  /* '<S119>:1:51' sc_mode     = sc_mode_last; */
  rtb_sc_mode = rtb_UnitDelay_d;

  /* '<S119>:1:53' if( telecom(1) == 0 ) */
  if (rtU.telecom[0] == 0) {
    /*  Check for bdot condition */
    /* '<S119>:1:56' if( bdot_flag == 1 ) */
    if (rtDW.Relay_Mode) {
      /* '<S119>:1:57' sc_mode     = int8(1.0); */
      rtb_sc_mode = 1;

      /*  If Bdot is triggered, return immediately since control has high  */
      /*  priority and control will be handed off. */
    } else {
      /*  Bdot flag will go low once omega_radps drops below the lower */
      /*  threshold. Accounted for in the relay block -- so won't proceed to  */
      /*  conditions below until this is met. */
      /*  Check for low power condition or recent boot up */
      /* '<S119>:1:68' if( telecom(2) == 1 || (sc_mode == 1 && bdot_flag == 0) || (~act_valid) ) */
      if ((rtU.telecom[1] == 1) || ((rtb_UnitDelay_d == 1) ||
           (!(rtb_LogicalOperator_m && (rtU.RW_valid[0] && rtU.RW_valid[1] &&
              rtU.RW_valid[2]))))) {
        /*  If reboot/bdot just occured and we are not tumbling, enter low */
        /*  power/estimate mode. */
        /* '<S119>:1:71' sc_mode     = int8(4.0); */
        rtb_sc_mode = 4;
      }

      /*  Check for desat conditions. This is for dedicated desat */
      /*  event. The PPT should be off before we initiate a desat.  */
      /* '<S119>:1:76' if( (desat_flag == 1) || (sc_mode_last == 2) ) */
      if (rtDW.Relay1_Mode || (rtb_UnitDelay_d == 2)) {
        /* '<S119>:1:77' sc_mode     = int8(2.0); */
        rtb_sc_mode = 2;
      } else {
        /*  If we are not in Earth's shadow but the sun_sensor is reporting */
        /*  invalid, then we need to move to acquire the sun in the FoV of the */
        /*  sun_sensor. Hence enter sun_seek mode. */
        /* '<S119>:1:84' if( sc_in_sun && ~ss_valid ) */
        if ((lowAlt != 0) && (!(rtU.sun_vec_body_sunsensor[3] == 1.0))) {
          /* '<S119>:1:85' sc_mode  = int8(5.0); */
          rtb_sc_mode = 5;
        } else {
          /*  If all cases upstream have been passed, then enter pointing mode if */
          /*  allowed to do so. Check for pointing condition from CAN */
          /* '<S119>:1:91' if( telecom(3) == 1 ) */
          if (rtU.telecom[2] == 1) {
            /*  Default to velocity pointing mode */
            /* '<S119>:1:93' sc_mode     = int8(31.0); */
            rtb_sc_mode = 31;

            /*  Check to see if entering GS range and not in eclipse */
            /* '<S119>:1:96' if( GS_approach && sc_in_sun ) */
            if ((ABOVE != 0) && (lowAlt != 0)) {
              /* '<S119>:1:97' sc_mode  = int8(32.0); */
              rtb_sc_mode = 32;
            }
          }

          /*  If signal received to override the autonomous mode selection, set mode  */
          /*  based on CAN(1) value. */
        }
      }
    }
  } else {
    if (rtU.telecom[0] != 0) {
      /* '<S119>:1:104' elseif( telecom(1) ~= 0 ) */
      /* '<S119>:1:106' sc_mode = telecom(1); */
      rtb_sc_mode = rtU.telecom[0];
    }
  }

  /* End of MATLAB Function: '<S6>/MATLAB Function' */

  /* DataTypeConversion: '<S8>/Data Type Conversion2' incorporates:
   *  MATLAB Function: '<S66>/MATLAB Function1'
   */
  rtb_LogicalOperator_m = (lowAlt != 0);

  /* Sum: '<S126>/Sum' incorporates:
   *  Product: '<S126>/Product'
   *  Product: '<S126>/Product1'
   *  Product: '<S126>/Product2'
   *  Product: '<S126>/Product3'
   *  UnaryMinus: '<S124>/Unary Minus'
   *  UnaryMinus: '<S124>/Unary Minus1'
   *  UnaryMinus: '<S124>/Unary Minus2'
   */
  rtb_T_ut1_J2000 = ((rtb_q_plu[0] * rtb_q_cmd[0] - -rtb_q_plu[1] * rtb_q_cmd[1])
                     - -rtb_q_plu[2] * rtb_q_cmd[2]) - -rtb_q_plu[3] *
    rtb_q_cmd[3];

  /* Saturate: '<S123>/Saturation' */
  if (rtb_T_ut1_J2000 > 1.0) {
    rtb_T_ut1_J2000 = 1.0;
  } else {
    if (rtb_T_ut1_J2000 < -1.0) {
      rtb_T_ut1_J2000 = -1.0;
    }
  }

  /* End of Saturate: '<S123>/Saturation' */

  /* Switch: '<S123>/Switch' incorporates:
   *  Gain: '<S123>/Gain'
   *  Gain: '<S123>/rad2deg'
   *  Trigonometry: '<S123>/Trigonometric Function'
   */
  rtb_Switch_p = !(2.0 * acos(rtb_T_ut1_J2000) * 57.295779513082323 >= 12.0);

  /* Update for RateTransition: '<S1>/Rate Transition7' */
  rtDW.RateTransition7_1_Buffer0[0] = rtb_q_plu[0];
  rtDW.RateTransition7_1_Buffer0[1] = rtb_q_plu[1];
  rtDW.RateTransition7_1_Buffer0[2] = rtb_q_plu[2];
  rtDW.RateTransition7_1_Buffer0[3] = rtb_q_plu[3];

  /* Update for RateTransition: '<S1>/Rate Transition7' */
  rtDW.RateTransition7_2_Buffer0[0] = N[0];
  rtDW.RateTransition7_2_Buffer0[1] = N[1];
  rtDW.RateTransition7_2_Buffer0[2] = N[2];

  /* Update for RateTransition: '<S1>/Rate Transition7' */
  rtDW.RateTransition7_3_Buffer0 = rtb_UnitDelay_d;

  /* Update for RateTransition: '<S1>/Rate Transition7' */
  rtDW.RateTransition7_4_Buffer0 = rtb_Switch_p;

  /* Update for RateTransition: '<S1>/Rate Transition7' */
  rtDW.RateTransition7_5_Buffer0[0] = rtb_q_cmd[0];
  rtDW.RateTransition7_5_Buffer0[1] = rtb_q_cmd[1];
  rtDW.RateTransition7_5_Buffer0[2] = rtb_q_cmd[2];
  rtDW.RateTransition7_5_Buffer0[3] = rtb_q_cmd[3];

  /* Update for RateTransition: '<S1>/Rate Transition7' incorporates:
   *  DataTypeConversion: '<S8>/Data Type Conversion'
   *  MATLAB Function: '<S68>/MATLAB Function1'
   */
  rtDW.RateTransition7_6_Buffer0 = (ABOVE != 0);

  /* Update for RateTransition: '<S1>/Rate Transition7' */
  rtDW.RateTransition7_7_Buffer0 = rtb_LogicalOperator_m;

  /* Update for RateTransition: '<S1>/Rate Transition7' */
  rtDW.RateTransition7_8_Buffer0[0] = rtb_Normalization[0];
  rtDW.RateTransition7_8_Buffer0[1] = rtb_Normalization[1];
  rtDW.RateTransition7_8_Buffer0[2] = rtb_Normalization[2];

  /* Update for RateTransition: '<S1>/Rate Transition7' incorporates:
   *  DataTypeConversion: '<S8>/Data Type Conversion1'
   *  Inport: '<Root>/gyro_omega_body_radps'
   */
  rtDW.RateTransition7_11_Buffer0 = (rtU.gyro_omega_body_radps[3] != 0.0);

  /* Update for RateTransition: '<S1>/Rate Transition4' */
  rtDW.RateTransition4_Buffer0[0] = rtb_TmpSignalConversionAtSFunct[0];
  rtDW.RateTransition4_Buffer0[1] = rtb_TmpSignalConversionAtSFunct[1];
  rtDW.RateTransition4_Buffer0[2] = rtb_TmpSignalConversionAtSFunct[2];

  /* Update for RateTransition: '<S1>/Rate Transition1' */
  rtDW.RateTransition1_Buffer0[0] = rtb_Switch_j[0];
  rtDW.RateTransition1_Buffer0[1] = rtb_Switch_j[1];
  rtDW.RateTransition1_Buffer0[2] = rtb_Switch_j[2];

  /* Update for UnitDelay: '<S9>/Unit Delay' */
  rtDW.UnitDelay_DSTATE[0] = rtb_TrigonometricFunction1_o1;
  rtDW.UnitDelay_DSTATE[1] = rtb_T_TT_J2000;
  rtDW.UnitDelay_DSTATE[2] = JD_days_gps;
  rtDW.UnitDelay_DSTATE[3] = long_eclp_rad;

  /* Update for UnitDelay: '<S9>/Unit Delay1' */
  rtDW.UnitDelay1_DSTATE[0] = rtb_pos_teme_km[0];
  rtDW.UnitDelay1_DSTATE[1] = rtb_pos_teme_km[1];
  rtDW.UnitDelay1_DSTATE[2] = rtb_pos_teme_km[2];

  /* Product: '<S11>/Product' incorporates:
   *  Math: '<S11>/Math Function'
   */
  for (idx2 = 0; idx2 < 6; idx2++) {
    for (sigIdx = 0; sigIdx < 6; sigIdx++) {
      rtb_Merge2_0[idx2 + 6 * sigIdx] = 0.0;
      for (ABOVE = 0; ABOVE < 6; ABOVE++) {
        rtb_Merge2_0[idx2 + 6 * sigIdx] += rtb_Merge2[6 * ABOVE + idx2] * rtb_K
          [6 * ABOVE + sigIdx];
      }
    }
  }

  /* Update for UnitDelay: '<S9>/Unit Delay2' incorporates:
   *  Product: '<S11>/Product'
   *  Sum: '<S11>/Add'
   */
  for (idx2 = 0; idx2 < 6; idx2++) {
    for (sigIdx = 0; sigIdx < 6; sigIdx++) {
      IL3 = 0.0;
      for (ABOVE = 0; ABOVE < 6; ABOVE++) {
        IL3 += rtb_K[6 * ABOVE + sigIdx] * rtb_Merge2_0[6 * idx2 + ABOVE];
      }

      rtDW.UnitDelay2_DSTATE[sigIdx + 6 * idx2] = rtConstB.Product1[6 * idx2 +
        sigIdx] + IL3;
    }
  }

  /* End of Update for UnitDelay: '<S9>/Unit Delay2' */

  /* Update for RateTransition: '<S5>/Rate Transition7' */
  rtDW.RateTransition7_Buffer0[0] = rtb_sun_vector_eci_km[0];
  rtDW.RateTransition7_Buffer0[1] = rtb_sun_vector_eci_km[1];
  rtDW.RateTransition7_Buffer0[2] = C_1;

  /* Update for RateTransition: '<S5>/Rate Transition2' */
  rtDW.RateTransition2_Buffer0[0] = rtb_Gain1_a[0];
  rtDW.RateTransition2_Buffer0[1] = rtb_Gain1_a[1];
  rtDW.RateTransition2_Buffer0[2] = rtb_Gain1_a[2];

  /* Update for RateTransition: '<S5>/Rate Transition11' */
  rtDW.RateTransition11_Buffer0[0] = M[0];
  rtDW.RateTransition11_Buffer0[1] = M[1];
  rtDW.RateTransition11_Buffer0[2] = M[2];

  /* Update for UnitDelay: '<S10>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_n[0] = b_s;
  rtDW.UnitDelay_DSTATE_n[1] = C_4;
  rtDW.UnitDelay_DSTATE_n[2] = C_5;
  rtDW.UnitDelay_DSTATE_n[3] = eta;

  /* Update for UnitDelay: '<S6>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_g = rtb_sc_mode;

  /* Update for UnitDelay: '<S33>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_b[0] = rtb_m[0];

  /* Update for UnitDelay: '<S35>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_o[0] = rtb_Sum_o[0];

  /* Update for DiscreteTransferFcn: '<S35>/Discrete Transfer Fcn' */
  rtDW.DiscreteTransferFcn_states[0] = rtb_Sum_d[0] - -0.93910136742429262 *
    rtDW.DiscreteTransferFcn_states[0];

  /* Update for UnitDelay: '<S49>/UD'
   *
   * Block description for '<S49>/UD':
   *
   *  Store in Global RAM
   */
  rtDW.UD_DSTATE[0] = c_c;

  /* Update for DiscreteIntegrator: '<S53>/Discrete-Time Integrator' */
  rtDW.DiscreteTimeIntegrator_DSTATE[0] += 0.1 * rtb_s[0];

  /* Update for UnitDelay: '<S33>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_b[1] = rtb_m[1];

  /* Update for UnitDelay: '<S35>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_o[1] = rtb_Sum_o[1];

  /* Update for DiscreteTransferFcn: '<S35>/Discrete Transfer Fcn' */
  rtDW.DiscreteTransferFcn_states[1] = rtb_Sum_d[1] - -0.93910136742429262 *
    rtDW.DiscreteTransferFcn_states[1];

  /* Update for UnitDelay: '<S49>/UD'
   *
   * Block description for '<S49>/UD':
   *
   *  Store in Global RAM
   */
  rtDW.UD_DSTATE[1] = c;

  /* Update for DiscreteIntegrator: '<S53>/Discrete-Time Integrator' */
  rtDW.DiscreteTimeIntegrator_DSTATE[1] += 0.1 * rtb_s[1];

  /* Update for UnitDelay: '<S33>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_b[2] = rtb_m[2];

  /* Update for UnitDelay: '<S35>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_o[2] = rtb_Sum_o[2];

  /* Update for DiscreteTransferFcn: '<S35>/Discrete Transfer Fcn' */
  rtDW.DiscreteTransferFcn_states[2] = rtb_Sum_d[2] - -0.93910136742429262 *
    rtDW.DiscreteTransferFcn_states[2];

  /* Update for UnitDelay: '<S49>/UD'
   *
   * Block description for '<S49>/UD':
   *
   *  Store in Global RAM
   */
  rtDW.UD_DSTATE[2] = mean_anom_sun_rad;

  /* Update for DiscreteIntegrator: '<S53>/Discrete-Time Integrator' */
  rtDW.DiscreteTimeIntegrator_DSTATE[2] += 0.1 * rtb_s[2];
}

/* Model step function for TID3 */
void fsw_lib_step3(void)               /* Sample time: [0.39999999999999997s, 0.0s] */
{
  int32_T rtb_PulseGenerator;

  /* DiscretePulseGenerator: '<S36>/Pulse Generator' */
  rtb_PulseGenerator = ((rtDW.clockTickCounter < 3) && (rtDW.clockTickCounter >=
    0));
  if (rtDW.clockTickCounter >= 4) {
    rtDW.clockTickCounter = 0;
  } else {
    rtDW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<S36>/Pulse Generator' */

  /* Update for RateTransition: '<S36>/Rate Transition' */
  rtDW.RateTransition_Buffer0 = rtb_PulseGenerator;
}

/* Model initialize function */
void fsw_lib_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* InitializeConditions for UnitDelay: '<S9>/Unit Delay' */
  rtDW.UnitDelay_DSTATE[0] = 1.0;
  rtDW.UnitDelay_DSTATE[1] = 0.0;
  rtDW.UnitDelay_DSTATE[2] = 0.0;
  rtDW.UnitDelay_DSTATE[3] = 0.0;

  /* InitializeConditions for UnitDelay: '<S9>/Unit Delay2' */
  memcpy(&rtDW.UnitDelay2_DSTATE[0], &rtConstP.UnitDelay2_InitialCondition[0],
         36U * sizeof(real_T));

  /* InitializeConditions for UnitDelay: '<S10>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_n[0] = 1.0;
  rtDW.UnitDelay_DSTATE_n[1] = 0.0;
  rtDW.UnitDelay_DSTATE_n[2] = 0.0;
  rtDW.UnitDelay_DSTATE_n[3] = 0.0;

  /* InitializeConditions for UnitDelay: '<S6>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_g = 1;
}

/* Model terminate function */
void fsw_lib_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
