/* Include files */

#include "gnc2_lib_sfun.h"
#include "c2_gnc2_lib.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "gnc2_lib_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c2_debug_family_names[59] = { "N", "Nx", "Nu", "iter_max",
  "c_size", "b_size", "h_size", "q_size", "Air_size", "Ajc_size", "Apr_size",
  "Gir_size", "Gjc_size", "Gpr_size", "l_dim", "soc_dim", "n", "m", "p", "l",
  "ncones", "q", "xi", "xf", "k", "EH", "BE", "ES", "AR", "c", "G", "h", "A",
  "b", "Air", "Ajc", "Apr", "Gir", "Gjc", "Gpr", "y", "diff", "V", "soac_params",
  "nargin", "nargout", "X", "U", "s", "J", "ME", "MI", "T_max", "w_max", "s_max",
  "s_min", "w_v", "exitcode", "time" };

static const char * c2_b_debug_family_names[4] = { "nargin", "nargout", "a",
  "cross" };

static const char * c2_c_debug_family_names[29] = { "B", "q", "q0", "qv", "hb",
  "hw", "w", "dfq_dq", "dfq_dhb", "dfq_dhw", "dfhb_dq", "dfhb_dhb", "dfhb_dhw",
  "dfhw_dq", "dfhw_dhb", "dfhw_dhw", "dfq_du", "dfhb_du", "dfhw_du", "fq", "fhb",
  "fhw", "nargin", "nargout", "x", "u", "J", "A", "f" };

static const char * c2_d_debug_family_names[18] = { "tkm", "tkp", "lam_km",
  "lam_kp", "u_tau", "B", "nargin", "nargout", "t", "x", "u", "tspan", "J", "f",
  "A", "Bp", "Bm", "Z" };

static const char * c2_e_debug_family_names[23] = { "Nx", "x", "f", "A", "Bp",
  "Bm", "Z", "Phi", "xdot", "Phi_dot", "Bdp_dot", "Bdm_dot", "Sd_dot", "Zd_dot",
  "nargin", "nargout", "t", "X", "u", "tspan", "s", "J", "DX" };

static const char * c2_f_debug_family_names[42] = { "len", "tau", "Nsub", "A0",
  "B0p", "B0m", "S0", "R0", "k", "xF", "P0", "um", "up", "u", "tspan", "k_",
  "tk", "tkp1", "h", "k1", "k2", "k3", "k4", "AF", "BFp", "BFm", "SF", "RF",
  "Ad", "N", "Nx", "Nu", "nargin", "nargout", "X", "U", "s", "J", "EH", "BE",
  "ES", "AR" };

static const char * c2_g_debug_family_names[33] = { "u_max", "Nx", "Nu", "Hw",
  "Hu", "Hv", "Hg", "Hs", "Hev", "Glin", "Gquad", "hlin", "hquad", "w_max", "N",
  "nargin", "nargout", "xi", "xf", "J", "EH", "BE", "ES", "AR", "T_max", "s_max",
  "s_min", "w_v", "c", "G", "h", "A", "b" };

static const char * c2_h_debug_family_names[12] = { "n", "m", "X_nnz", "id",
  "col", "row", "Xir_size", "nargin", "nargout", "X", "Xir", "Xpr" };

static const char * c2_i_debug_family_names[8] = { "col", "Xir_size", "nargin",
  "nargout", "X", "Xir", "Xjc", "Xpr" };

static const char * c2_j_debug_family_names[12] = { "n", "m", "X_nnz", "id",
  "col", "row", "Xir_size", "nargin", "nargout", "X", "Xir", "Xpr" };

static const char * c2_k_debug_family_names[8] = { "col", "Xir_size", "nargin",
  "nargout", "X", "Xir", "Xjc", "Xpr" };

/* Function Declarations */
static void initialize_c2_gnc2_lib(SFc2_gnc2_libInstanceStruct *chartInstance);
static void initialize_params_c2_gnc2_lib(SFc2_gnc2_libInstanceStruct
  *chartInstance);
static void enable_c2_gnc2_lib(SFc2_gnc2_libInstanceStruct *chartInstance);
static void disable_c2_gnc2_lib(SFc2_gnc2_libInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_gnc2_lib(SFc2_gnc2_libInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_gnc2_lib(SFc2_gnc2_libInstanceStruct
  *chartInstance);
static void set_sim_state_c2_gnc2_lib(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_st);
static void finalize_c2_gnc2_lib(SFc2_gnc2_libInstanceStruct *chartInstance);
static void sf_gateway_c2_gnc2_lib(SFc2_gnc2_libInstanceStruct *chartInstance);
static void mdl_start_c2_gnc2_lib(SFc2_gnc2_libInstanceStruct *chartInstance);
static void c2_chartstep_c2_gnc2_lib(SFc2_gnc2_libInstanceStruct *chartInstance);
static void initSimStructsc2_gnc2_lib(SFc2_gnc2_libInstanceStruct *chartInstance);
static void c2_run_ecos(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_n,
  real_T c2_m, real_T c2_p, real_T c2_l, real_T c2_ncones, real_T c2_c[332],
  real_T c2_Gjc[333], real_T c2_Gir[674], real_T c2_Gpr[674], real_T c2_h[354],
  real_T c2_q, real_T c2_Ajc[333], real_T c2_Air[1278], real_T c2_Apr[1278],
  real_T c2_b[117], real_T c2_e_y[334]);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_b_time, const char_T *c2_identifier, real_T c2_e_y[10]);
static void c2_b_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[10]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_c_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_b_exitcode, const char_T *c2_identifier, real_T c2_e_y[11]);
static void c2_d_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[11]);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_e_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_g_s, const char_T *c2_identifier);
static real_T c2_f_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_g_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_c_U, const char_T *c2_identifier, real_T c2_e_y[30]);
static void c2_h_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[30]);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_i_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_X, const char_T *c2_identifier, real_T c2_e_y[100]);
static void c2_j_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [100]);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_k_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[99]);
static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_j_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_l_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [334]);
static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_k_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_m_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [674]);
static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_l_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_n_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [333]);
static void c2_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_m_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_o_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [1278]);
static void c2_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_n_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_p_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [117]);
static void c2_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_o_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_q_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [38844]);
static void c2_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_p_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_r_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [354]);
static void c2_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_q_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_s_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [117528]);
static void c2_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_r_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_t_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [332]);
static void c2_o_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_s_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_u_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [3000]);
static void c2_p_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_t_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_v_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [10000]);
static void c2_q_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_u_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_w_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[7]);
static void c2_r_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_x_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[9]);
static void c2_s_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_v_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_y_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[3]);
static void c2_t_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_w_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_ab_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [100]);
static void c2_u_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_x_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_bb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[4]);
static void c2_v_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_y_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_ab_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_cb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[12]);
static void c2_w_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_db_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[16]);
static void c2_x_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_bb_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_eb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[30]);
static void c2_y_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_cb_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_fb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[10]);
static void c2_ab_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_db_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_gb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[6]);
static void c2_bb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_eb_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_hb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [190]);
static void c2_cb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_fb_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_gb_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_ib_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [322]);
static void c2_db_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_hb_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_jb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [10624]);
static void c2_eb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_ib_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_kb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [106904]);
static void c2_fb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_jb_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_lb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [33200]);
static void c2_gb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_kb_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_mb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [332]);
static void c2_hb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_lb_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_nb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [9960]);
static void c2_ib_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_linspace(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_d1,
  real_T c2_d2, real_T c2_e_y[10]);
static void c2_foh(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_e_X[100],
                   real_T c2_c_U[30], real_T c2_g_s, real_T c2_b_J[9], real_T
                   c2_d_EH[10000], real_T c2_d_BE[3000], real_T c2_ES[100],
                   real_T c2_AR[100]);
static void c2_eye(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_I[100]);
static void c2_deriv(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_t,
                     real_T c2_e_X[190], real_T c2_e_u[6], real_T c2_tspan[10],
                     real_T c2_g_s, real_T c2_b_J[9], real_T c2_DX[190]);
static void c2_get_f_vals(SFc2_gnc2_libInstanceStruct *chartInstance, real_T
  c2_t, real_T c2_x[10], real_T c2_e_u[6], real_T c2_tspan[10], real_T c2_b_J[9],
  real_T c2_f[10], real_T c2_d_A[100], real_T c2_Bp[30], real_T c2_Bm[30],
  real_T c2_Z[10]);
static void c2_Q_linearize(SFc2_gnc2_libInstanceStruct *chartInstance, real_T
  c2_x[10], real_T c2_e_u[3], real_T c2_b_J[9], real_T c2_d_A[100], real_T c2_f
  [10]);
static void c2_warning(SFc2_gnc2_libInstanceStruct *chartInstance);
static void c2_mrdivide(SFc2_gnc2_libInstanceStruct *chartInstance, real_T
  c2_d_A[9], real_T c2_B[9], real_T c2_e_y[9]);
static void c2_mldivide(SFc2_gnc2_libInstanceStruct *chartInstance, real_T
  c2_d_A[100], real_T c2_B[30], real_T c2_Y[30]);
static void c2_xgetrf(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_d_A
                      [100], real_T c2_e_A[100], int32_T c2_ipiv[10], int32_T
                      *c2_info);
static void c2_check_forloop_overflow_error(SFc2_gnc2_libInstanceStruct
  *chartInstance, boolean_T c2_overflow);
static void c2_b_mldivide(SFc2_gnc2_libInstanceStruct *chartInstance, real_T
  c2_d_A[100], real_T c2_B[10], real_T c2_Y[10]);
static void c2_parse_ecos(SFc2_gnc2_libInstanceStruct *chartInstance, real_T
  c2_xi[10], real_T c2_xf[7], real_T c2_b_J[9], real_T c2_d_EH[10000], real_T
  c2_d_BE[3000], real_T c2_ES[100], real_T c2_AR[100], real_T c2_b_T_max, real_T
  c2_b_w_max, real_T c2_b_s_max, real_T c2_b_s_min, real_T c2_b_w_v, real_T
  c2_c[332], real_T c2_d_G[117528], real_T c2_h[354], real_T c2_d_A[38844],
  real_T c2_b[117]);
static void c2_inv(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_x[9],
                   real_T c2_e_y[9]);
static real_T c2_norm(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_x[9]);
static void c2_b_warning(SFc2_gnc2_libInstanceStruct *chartInstance, char_T
  c2_varargin_1[14]);
static void c2_kron(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_d_A
                    [100], real_T c2_B[30], real_T c2_K[3000]);
static void c2_b_eye(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_I[900]);
static void c2_c_eye(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_I
                     [10000]);
static void c2_d_eye(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_I
                     [10000]);
static void c2_convert_to_CCS(SFc2_gnc2_libInstanceStruct *chartInstance, real_T
  c2_e_X[38844], real_T c2_Xir[1278], real_T c2_Xjc[333], real_T c2_Xpr[1278]);
static void c2_my_find(SFc2_gnc2_libInstanceStruct *chartInstance, real_T
  c2_e_X[38844], real_T c2_Xir[1278], real_T c2_Xpr[1278]);
static void c2_b_convert_to_CCS(SFc2_gnc2_libInstanceStruct *chartInstance,
  real_T c2_e_X[117528], real_T c2_Xir[674], real_T c2_Xjc[333], real_T c2_Xpr
  [674]);
static void c2_b_my_find(SFc2_gnc2_libInstanceStruct *chartInstance, real_T
  c2_e_X[117528], real_T c2_Xir[674], real_T c2_Xpr[674]);
static real_T c2_b_norm(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_x
  [100]);
static real_T c2_c_norm(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_x
  [99]);
static void c2_ob_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_sprintf, const char_T *c2_identifier, char_T c2_e_y[14]);
static void c2_pb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, char_T c2_e_y[14]);
static const mxArray *c2_mb_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_qb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_jb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_rb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId,
  c2_saot08BhBJej868PSk74SzB *c2_e_y);
static void c2_sb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId,
  c2_sKpQB9jVSEZrFP5iOeb0DOE *c2_e_y);
static void c2_tb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[2]);
static void c2_kb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_ub_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_gnc2_lib, const char_T *c2_identifier);
static uint8_T c2_vb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_xgetrf(SFc2_gnc2_libInstanceStruct *chartInstance, real_T
  c2_d_A[100], int32_T c2_ipiv[10], int32_T *c2_info);
static void init_dsm_address_info(SFc2_gnc2_libInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc2_gnc2_libInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_gnc2_lib(SFc2_gnc2_libInstanceStruct *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc2_gnc2_lib(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_is_active_c2_gnc2_lib = 0U;
}

static void initialize_params_c2_gnc2_lib(SFc2_gnc2_libInstanceStruct
  *chartInstance)
{
  const mxArray *c2_m0 = NULL;
  static const char * c2_fieldNames[17] = { "ic", "sample_time_s", "N", "dt",
    "c_size", "Air_size", "Ajc_size", "Apr_size", "b_size", "Gir_size",
    "Gjc_size", "Gpr_size", "h_size", "q_size", "y_size", "l_dim", "soc_dim" };

  const mxArray *c2_mxField;
  const mxArray *c2_m1 = NULL;
  static const char * c2_b_fieldNames[11] = { "sc_mode", "quat_in",
    "w_body_radps", "hw_Nms", "quat_cmd", "w_body_cmd_radps",
    "sun_inertial_unit", "gps_epoch_s", "gps_time_s", "cmd_torque", "cmd_state"
  };

  const mxArray *c2_b_mxField;
  c2_saot08BhBJej868PSk74SzB c2_r0;
  c2_m0 = sf_mex_get_sfun_param(chartInstance->S, 0, 1);
  sf_mex_check_bus_parameter(c2_m0, 17, c2_fieldNames, "saot08BhBJej868PSk74SzB");
  c2_mxField = sf_mex_getfield(c2_m0, "ic", "soac_params", 0);
  c2_m1 = sf_mex_dup(c2_mxField);
  sf_mex_check_bus_parameter(c2_m1, 11, c2_b_fieldNames,
    "sKpQB9jVSEZrFP5iOeb0DOE");
  c2_b_mxField = sf_mex_getfield(c2_m1, "sc_mode", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_b_mxField), &c2_r0.ic.sc_mode,
                      1, 0, 0U, 0, 0U, 0);
  c2_b_mxField = sf_mex_getfield(c2_m1, "quat_in", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_b_mxField), c2_r0.ic.quat_in,
                      1, 0, 0U, 1, 0U, 1, 4);
  c2_b_mxField = sf_mex_getfield(c2_m1, "w_body_radps", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_b_mxField),
                      c2_r0.ic.w_body_radps, 1, 0, 0U, 1, 0U, 1, 3);
  c2_b_mxField = sf_mex_getfield(c2_m1, "hw_Nms", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_b_mxField), c2_r0.ic.hw_Nms,
                      1, 0, 0U, 1, 0U, 1, 3);
  c2_b_mxField = sf_mex_getfield(c2_m1, "quat_cmd", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_b_mxField), c2_r0.ic.quat_cmd,
                      1, 0, 0U, 1, 0U, 1, 4);
  c2_b_mxField = sf_mex_getfield(c2_m1, "w_body_cmd_radps", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_b_mxField),
                      c2_r0.ic.w_body_cmd_radps, 1, 0, 0U, 1, 0U, 1, 3);
  c2_b_mxField = sf_mex_getfield(c2_m1, "sun_inertial_unit", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_b_mxField),
                      c2_r0.ic.sun_inertial_unit, 1, 0, 0U, 1, 0U, 1, 3);
  c2_b_mxField = sf_mex_getfield(c2_m1, "gps_epoch_s", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_b_mxField),
                      c2_r0.ic.gps_epoch_s, 1, 0, 0U, 1, 0U, 1, 2);
  c2_b_mxField = sf_mex_getfield(c2_m1, "gps_time_s", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_b_mxField),
                      c2_r0.ic.gps_time_s, 1, 0, 0U, 1, 0U, 1, 2);
  c2_b_mxField = sf_mex_getfield(c2_m1, "cmd_torque", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_b_mxField),
                      c2_r0.ic.cmd_torque, 1, 0, 0U, 1, 0U, 1, 3);
  c2_b_mxField = sf_mex_getfield(c2_m1, "cmd_state", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_b_mxField),
                      c2_r0.ic.cmd_state, 1, 0, 0U, 1, 0U, 1, 10);
  sf_mex_destroy(&c2_m1);
  c2_mxField = sf_mex_getfield(c2_m0, "sample_time_s", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_mxField),
                      &c2_r0.sample_time_s, 1, 0, 0U, 0, 0U, 0);
  c2_mxField = sf_mex_getfield(c2_m0, "N", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_mxField), &c2_r0.N, 1, 0, 0U,
                      0, 0U, 0);
  c2_mxField = sf_mex_getfield(c2_m0, "dt", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_mxField), &c2_r0.dt, 1, 0, 0U,
                      0, 0U, 0);
  c2_mxField = sf_mex_getfield(c2_m0, "c_size", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_mxField), &c2_r0.c_size, 1, 0,
                      0U, 0, 0U, 0);
  c2_mxField = sf_mex_getfield(c2_m0, "Air_size", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_mxField), &c2_r0.Air_size, 1,
                      0, 0U, 0, 0U, 0);
  c2_mxField = sf_mex_getfield(c2_m0, "Ajc_size", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_mxField), &c2_r0.Ajc_size, 1,
                      0, 0U, 0, 0U, 0);
  c2_mxField = sf_mex_getfield(c2_m0, "Apr_size", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_mxField), &c2_r0.Apr_size, 1,
                      0, 0U, 0, 0U, 0);
  c2_mxField = sf_mex_getfield(c2_m0, "b_size", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_mxField), &c2_r0.b_size, 1, 0,
                      0U, 0, 0U, 0);
  c2_mxField = sf_mex_getfield(c2_m0, "Gir_size", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_mxField), &c2_r0.Gir_size, 1,
                      0, 0U, 0, 0U, 0);
  c2_mxField = sf_mex_getfield(c2_m0, "Gjc_size", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_mxField), &c2_r0.Gjc_size, 1,
                      0, 0U, 0, 0U, 0);
  c2_mxField = sf_mex_getfield(c2_m0, "Gpr_size", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_mxField), &c2_r0.Gpr_size, 1,
                      0, 0U, 0, 0U, 0);
  c2_mxField = sf_mex_getfield(c2_m0, "h_size", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_mxField), &c2_r0.h_size, 1, 0,
                      0U, 0, 0U, 0);
  c2_mxField = sf_mex_getfield(c2_m0, "q_size", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_mxField), &c2_r0.q_size, 1, 0,
                      0U, 0, 0U, 0);
  c2_mxField = sf_mex_getfield(c2_m0, "y_size", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_mxField), &c2_r0.y_size, 1, 0,
                      0U, 0, 0U, 0);
  c2_mxField = sf_mex_getfield(c2_m0, "l_dim", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_mxField), &c2_r0.l_dim, 1, 0,
                      0U, 0, 0U, 0);
  c2_mxField = sf_mex_getfield(c2_m0, "soc_dim", "soac_params", 0);
  sf_mex_import_named("soac_params", sf_mex_dup(c2_mxField), &c2_r0.soc_dim, 1,
                      0, 0U, 0, 0U, 0);
  sf_mex_destroy(&c2_m0);
  chartInstance->c2_soac_params = c2_r0;
}

static void enable_c2_gnc2_lib(SFc2_gnc2_libInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_gnc2_lib(SFc2_gnc2_libInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_gnc2_lib(SFc2_gnc2_libInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c2_gnc2_lib(SFc2_gnc2_libInstanceStruct
  *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_e_y = NULL;
  const mxArray *c2_f_y = NULL;
  const mxArray *c2_g_y = NULL;
  const mxArray *c2_h_y = NULL;
  real_T c2_hoistedGlobal;
  const mxArray *c2_i_y = NULL;
  const mxArray *c2_j_y = NULL;
  uint8_T c2_b_hoistedGlobal;
  const mxArray *c2_k_y = NULL;
  c2_st = NULL;
  c2_st = NULL;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_createcellmatrix(6, 1), false);
  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", *chartInstance->c2_b_U, 0, 0U, 1U,
    0U, 1, 30), false);
  sf_mex_setcell(c2_e_y, 0, c2_f_y);
  c2_g_y = NULL;
  sf_mex_assign(&c2_g_y, sf_mex_create("y", *chartInstance->c2_d_X, 0, 0U, 1U,
    0U, 1, 100), false);
  sf_mex_setcell(c2_e_y, 1, c2_g_y);
  c2_h_y = NULL;
  sf_mex_assign(&c2_h_y, sf_mex_create("y", *chartInstance->c2_exitcode, 0, 0U,
    1U, 0U, 1, 11), false);
  sf_mex_setcell(c2_e_y, 2, c2_h_y);
  c2_hoistedGlobal = *chartInstance->c2_f_s;
  c2_i_y = NULL;
  sf_mex_assign(&c2_i_y, sf_mex_create("y", &c2_hoistedGlobal, 0, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c2_e_y, 3, c2_i_y);
  c2_j_y = NULL;
  sf_mex_assign(&c2_j_y, sf_mex_create("y", *chartInstance->c2_time, 0, 0U, 1U,
    0U, 1, 10), false);
  sf_mex_setcell(c2_e_y, 4, c2_j_y);
  c2_b_hoistedGlobal = chartInstance->c2_is_active_c2_gnc2_lib;
  c2_k_y = NULL;
  sf_mex_assign(&c2_k_y, sf_mex_create("y", &c2_b_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c2_e_y, 5, c2_k_y);
  sf_mex_assign(&c2_st, c2_e_y, false);
  return c2_st;
}

static void set_sim_state_c2_gnc2_lib(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_st)
{
  const mxArray *c2_e_u;
  real_T c2_dv0[30];
  int32_T c2_i0;
  real_T c2_dv1[100];
  int32_T c2_i1;
  real_T c2_dv2[11];
  int32_T c2_i2;
  real_T c2_dv3[10];
  int32_T c2_i3;
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_e_u = sf_mex_dup(c2_st);
  c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("U", c2_e_u, 0)),
                        "U", c2_dv0);
  for (c2_i0 = 0; c2_i0 < 30; c2_i0++) {
    (*chartInstance->c2_b_U)[c2_i0] = c2_dv0[c2_i0];
  }

  c2_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("X", c2_e_u, 1)),
                        "X", c2_dv1);
  for (c2_i1 = 0; c2_i1 < 100; c2_i1++) {
    (*chartInstance->c2_d_X)[c2_i1] = c2_dv1[c2_i1];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("exitcode",
    c2_e_u, 2)), "exitcode", c2_dv2);
  for (c2_i2 = 0; c2_i2 < 11; c2_i2++) {
    (*chartInstance->c2_exitcode)[c2_i2] = c2_dv2[c2_i2];
  }

  *chartInstance->c2_f_s = c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("s", c2_e_u, 3)), "s");
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("time", c2_e_u, 4)),
                      "time", c2_dv3);
  for (c2_i3 = 0; c2_i3 < 10; c2_i3++) {
    (*chartInstance->c2_time)[c2_i3] = c2_dv3[c2_i3];
  }

  chartInstance->c2_is_active_c2_gnc2_lib = c2_ub_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("is_active_c2_gnc2_lib", c2_e_u, 5)),
    "is_active_c2_gnc2_lib");
  sf_mex_destroy(&c2_e_u);
  c2_update_debugger_state_c2_gnc2_lib(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_gnc2_lib(SFc2_gnc2_libInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c2_gnc2_lib(SFc2_gnc2_libInstanceStruct *chartInstance)
{
  int32_T c2_i4;
  int32_T c2_i5;
  int32_T c2_i6;
  int32_T c2_i7;
  int32_T c2_i8;
  int32_T c2_i9;
  int32_T c2_i10;
  int32_T c2_i11;
  int32_T c2_i12;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_w_v, 10U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_s_min, 9U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_s_max, 8U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_w_max, 7U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_T_max, 6U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  for (c2_i4 = 0; c2_i4 < 16; c2_i4++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_MI)[c2_i4], 5U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i5 = 0; c2_i5 < 16; c2_i5++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_ME)[c2_i5], 4U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i6 = 0; c2_i6 < 9; c2_i6++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_J)[c2_i6], 3U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_e_s, 2U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  for (c2_i7 = 0; c2_i7 < 30; c2_i7++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_U)[c2_i7], 1U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i8 = 0; c2_i8 < 100; c2_i8++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_c_X)[c2_i8], 0U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_gnc2_lib(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_gnc2_libMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c2_i9 = 0; c2_i9 < 100; c2_i9++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_d_X)[c2_i9], 11U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i10 = 0; c2_i10 < 30; c2_i10++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_b_U)[c2_i10], 12U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_f_s, 13U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  for (c2_i11 = 0; c2_i11 < 11; c2_i11++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_exitcode)[c2_i11], 14U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }

  for (c2_i12 = 0; c2_i12 < 10; c2_i12++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_time)[c2_i12], 15U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }
}

static void mdl_start_c2_gnc2_lib(SFc2_gnc2_libInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_chartstep_c2_gnc2_lib(SFc2_gnc2_libInstanceStruct *chartInstance)
{
  real_T c2_hoistedGlobal;
  real_T c2_b_hoistedGlobal;
  real_T c2_c_hoistedGlobal;
  real_T c2_d_hoistedGlobal;
  real_T c2_e_hoistedGlobal;
  real_T c2_f_hoistedGlobal;
  int32_T c2_i13;
  int32_T c2_i14;
  real_T c2_e_X[100];
  real_T c2_g_s;
  real_T c2_c_U[30];
  int32_T c2_i15;
  int32_T c2_i16;
  real_T c2_b_J[9];
  int32_T c2_i17;
  real_T c2_b_ME[16];
  real_T c2_b_T_max;
  real_T c2_b_MI[16];
  real_T c2_b_w_max;
  real_T c2_b_s_max;
  real_T c2_b_s_min;
  real_T c2_b_w_v;
  uint32_T c2_debug_family_var_map[59];
  real_T c2_N;
  real_T c2_Nx;
  real_T c2_Nu;
  real_T c2_iter_max;
  real_T c2_c_size;
  real_T c2_b_size;
  real_T c2_h_size;
  real_T c2_q_size;
  real_T c2_Air_size;
  real_T c2_Ajc_size;
  real_T c2_Apr_size;
  real_T c2_Gir_size;
  real_T c2_Gjc_size;
  real_T c2_Gpr_size;
  real_T c2_l_dim;
  real_T c2_soc_dim;
  real_T c2_n;
  real_T c2_m;
  real_T c2_p;
  real_T c2_l;
  real_T c2_ncones;
  real_T c2_q;
  real_T c2_xi[10];
  real_T c2_xf[7];
  real_T c2_k;
  real_T c2_ES[100];
  real_T c2_AR[100];
  real_T c2_c[332];
  real_T c2_h[354];
  real_T c2_b[117];
  real_T c2_Air[1278];
  real_T c2_Ajc[333];
  real_T c2_Apr[1278];
  real_T c2_Gir[674];
  real_T c2_Gjc[333];
  real_T c2_Gpr[674];
  real_T c2_e_y[334];
  real_T c2_diff;
  real_T c2_V[99];
  c2_saot08BhBJej868PSk74SzB c2_b_soac_params;
  real_T c2_nargin = 12.0;
  real_T c2_nargout = 5.0;
  real_T c2_f_X[100];
  real_T c2_d_U[30];
  real_T c2_h_s;
  real_T c2_b_exitcode[11];
  real_T c2_b_time[10];
  static c2_saot08BhBJej868PSk74SzB c2_r1 = { { 0.0,/* sc_mode */
      { 1.0, 0.0, 0.0, 0.0 },          /* quat_in */
      { 0.0, 0.0, 0.0 },               /* w_body_radps */
      { 0.0, 0.0, 0.0 },               /* hw_Nms */
      { 1.0, 0.0, 0.0, 0.0 },          /* quat_cmd */
      { 0.0, 0.0, 0.0 },               /* w_body_cmd_radps */
      { 0.0, 0.0, 0.0 },               /* sun_inertial_unit */
      { 0.0, 0.0 },                    /* gps_epoch_s */
      { 0.0, 0.0 },                    /* gps_time_s */
      { 0.0, 0.0, 0.0 },               /* cmd_torque */
      { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }/* cmd_state */
    },                                 /* ic */
    0.1,                               /* sample_time_s */
    10.0,                              /* N */
    0.1111111111111111,                /* dt */
    332.0,                             /* c_size */
    1278.0,                            /* Air_size */
    333.0,                             /* Ajc_size */
    1278.0,                            /* Apr_size */
    117.0,                             /* b_size */
    674.0,                             /* Gir_size */
    333.0,                             /* Gjc_size */
    674.0,                             /* Gpr_size */
    354.0,                             /* h_size */
    1.0,                               /* q_size */
    334.0,                             /* y_size */
    322.0,                             /* l_dim */
    32.0                               /* soc_dim */
  };

  int32_T c2_i18;
  int32_T c2_i19;
  int32_T c2_i20;
  int32_T c2_i21;
  int32_T c2_i22;
  int32_T c2_i23;
  int32_T c2_b_k;
  int32_T c2_i24;
  int32_T c2_i25;
  real_T c2_g_X[100];
  int32_T c2_i26;
  int32_T c2_i27;
  int32_T c2_i28;
  real_T c2_e_U[30];
  int32_T c2_i29;
  int32_T c2_i30;
  real_T c2_b_V[99];
  real_T c2_c_J[9];
  real_T c2_b_ES[100];
  real_T c2_b_AR[100];
  real_T c2_c_V[99];
  int32_T c2_i31;
  int32_T c2_i32;
  int32_T c2_i33;
  int32_T c2_i34;
  int32_T c2_i35;
  int32_T c2_i36;
  int32_T c2_i37;
  int32_T c2_i38;
  real_T c2_b_xi[10];
  int32_T c2_i39;
  real_T c2_b_xf[7];
  int32_T c2_i40;
  real_T c2_d_J[9];
  int32_T c2_i41;
  int32_T c2_i42;
  int32_T c2_i43;
  real_T c2_c_ES[100];
  real_T c2_c_AR[100];
  real_T c2_b_c[332];
  real_T c2_b_h[354];
  real_T c2_b_b[117];
  int32_T c2_i44;
  int32_T c2_i45;
  int32_T c2_i46;
  int32_T c2_i47;
  int32_T c2_i48;
  int32_T c2_i49;
  real_T c2_b_Air[1278];
  real_T c2_b_Ajc[333];
  real_T c2_b_Apr[1278];
  int32_T c2_i50;
  int32_T c2_i51;
  int32_T c2_i52;
  int32_T c2_i53;
  real_T c2_b_Gir[674];
  real_T c2_b_Gpr[674];
  int32_T c2_i54;
  int32_T c2_i55;
  int32_T c2_i56;
  int32_T c2_i57;
  int32_T c2_i58;
  real_T c2_c_c[332];
  int32_T c2_i59;
  real_T c2_b_Gjc[333];
  int32_T c2_i60;
  real_T c2_c_Gir[674];
  int32_T c2_i61;
  real_T c2_c_Gpr[674];
  int32_T c2_i62;
  real_T c2_c_h[354];
  int32_T c2_i63;
  real_T c2_c_Ajc[333];
  int32_T c2_i64;
  real_T c2_c_Air[1278];
  int32_T c2_i65;
  real_T c2_c_Apr[1278];
  real_T c2_c_b[117];
  real_T c2_dv4[334];
  int32_T c2_i66;
  int32_T c2_i67;
  real_T c2_h_X[100];
  int32_T c2_i68;
  int32_T c2_i69;
  int32_T c2_i70;
  real_T c2_d0;
  int32_T c2_i71;
  int32_T c2_i72;
  real_T c2_d_V[99];
  real_T c2_e_V[99];
  int32_T exitg1;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *chartInstance->c2_e_s;
  c2_b_hoistedGlobal = *chartInstance->c2_T_max;
  c2_c_hoistedGlobal = *chartInstance->c2_w_max;
  c2_d_hoistedGlobal = *chartInstance->c2_s_max;
  c2_e_hoistedGlobal = *chartInstance->c2_s_min;
  c2_f_hoistedGlobal = *chartInstance->c2_w_v;
  for (c2_i13 = 0; c2_i13 < 100; c2_i13++) {
    c2_e_X[c2_i13] = (*chartInstance->c2_c_X)[c2_i13];
  }

  for (c2_i14 = 0; c2_i14 < 30; c2_i14++) {
    c2_c_U[c2_i14] = (*chartInstance->c2_U)[c2_i14];
  }

  c2_g_s = c2_hoistedGlobal;
  for (c2_i15 = 0; c2_i15 < 9; c2_i15++) {
    c2_b_J[c2_i15] = (*chartInstance->c2_J)[c2_i15];
  }

  for (c2_i16 = 0; c2_i16 < 16; c2_i16++) {
    c2_b_ME[c2_i16] = (*chartInstance->c2_ME)[c2_i16];
  }

  for (c2_i17 = 0; c2_i17 < 16; c2_i17++) {
    c2_b_MI[c2_i17] = (*chartInstance->c2_MI)[c2_i17];
  }

  c2_b_T_max = c2_b_hoistedGlobal;
  c2_b_w_max = c2_c_hoistedGlobal;
  c2_b_s_max = c2_d_hoistedGlobal;
  c2_b_s_min = c2_e_hoistedGlobal;
  c2_b_w_v = c2_f_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 59U, 62U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_N, 0U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Nx, 1U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Nu, 2U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_iter_max, 3U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_c_size, 4U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_size, 5U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_h_size, 6U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_q_size, 7U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Air_size, 8U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Ajc_size, 9U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Apr_size, 10U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Gir_size, 11U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Gjc_size, 12U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Gpr_size, 13U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_l_dim, 14U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_soc_dim, 15U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_n, 16U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_m, 17U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_p, 18U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_l, 19U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_ncones, 20U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_q, 21U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_xi, 22U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_xf, 23U, c2_u_sf_marshallOut,
    c2_r_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_k, 24U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_EH, 25U,
    c2_t_sf_marshallOut, c2_q_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_BE, 26U,
    c2_s_sf_marshallOut, c2_p_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_ES, 27U, c2_e_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_AR, 28U, c2_e_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_c, 29U, c2_r_sf_marshallOut,
    c2_o_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_G, 30U,
    c2_q_sf_marshallOut, c2_n_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_h, 31U, c2_p_sf_marshallOut,
    c2_m_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_A, 32U,
    c2_o_sf_marshallOut, c2_l_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b, 33U, c2_n_sf_marshallOut,
    c2_k_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Air, 34U, c2_m_sf_marshallOut,
    c2_j_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Ajc, 35U, c2_l_sf_marshallOut,
    c2_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Apr, 36U, c2_m_sf_marshallOut,
    c2_j_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Gir, 37U, c2_k_sf_marshallOut,
    c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Gjc, 38U, c2_l_sf_marshallOut,
    c2_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Gpr, 39U, c2_k_sf_marshallOut,
    c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_e_y, 40U, c2_j_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_diff, 41U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_V, 42U, c2_i_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_soac_params, 43U, c2_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 44U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 45U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_e_X, 46U, c2_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_c_U, 47U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_g_s, 48U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_J, 49U, c2_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_ME, 50U, c2_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_MI, 51U, c2_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_T_max, 52U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_w_max, 53U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_s_max, 54U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_s_min, 55U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_w_v, 56U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_f_X, MAX_uint32_T, c2_e_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_d_U, MAX_uint32_T, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_h_s, MAX_uint32_T,
    c2_c_sf_marshallOut, c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_exitcode, 57U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_time, 58U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  c2_b_soac_params = c2_r1;
  c2_h_s = c2_g_s;
  _SFD_SYMBOL_SWITCH(48U, 59U);
  for (c2_i18 = 0; c2_i18 < 30; c2_i18++) {
    c2_d_U[c2_i18] = c2_c_U[c2_i18];
  }

  _SFD_SYMBOL_SWITCH(47U, 58U);
  for (c2_i19 = 0; c2_i19 < 100; c2_i19++) {
    c2_f_X[c2_i19] = c2_e_X[c2_i19];
  }

  _SFD_SYMBOL_SWITCH(46U, 57U);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 13);
  c2_N = 10.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 14);
  c2_Nx = 10.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 15);
  c2_Nu = 3.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 16);
  c2_iter_max = 10.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 19);
  c2_c_size = 332.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 20);
  c2_b_size = 117.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 21);
  c2_h_size = 354.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 22);
  c2_q_size = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 23);
  c2_Air_size = 1278.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 24);
  c2_Ajc_size = 333.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 25);
  c2_Apr_size = 1278.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 26);
  c2_Gir_size = 674.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 27);
  c2_Gjc_size = 333.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 28);
  c2_Gpr_size = 674.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 29);
  c2_l_dim = 322.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 30);
  c2_soc_dim = 32.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 31);
  c2_n = c2_c_size;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 32);
  c2_m = c2_h_size;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 33);
  c2_p = c2_b_size;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 34);
  c2_l = c2_l_dim;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 35);
  c2_ncones = c2_q_size;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 36);
  c2_q = c2_soc_dim;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 37);
  for (c2_i20 = 0; c2_i20 < 11; c2_i20++) {
    c2_b_exitcode[c2_i20] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 38);
  for (c2_i21 = 0; c2_i21 < 10; c2_i21++) {
    c2_b_time[c2_i21] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 41);
  for (c2_i22 = 0; c2_i22 < 10; c2_i22++) {
    c2_xi[c2_i22] = c2_f_X[c2_i22];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 42);
  for (c2_i23 = 0; c2_i23 < 7; c2_i23++) {
    c2_xf[c2_i23] = c2_f_X[c2_i23 + 90];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 44);
  c2_k = 1.0;
  c2_b_k = 0;
  do {
    exitg1 = 0;
    if (c2_b_k < 10) {
      c2_k = 1.0 + (real_T)c2_b_k;
      CV_EML_FOR(0, 1, 0, 1);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 47);
      for (c2_i24 = 0; c2_i24 < 100; c2_i24++) {
        c2_g_X[c2_i24] = c2_f_X[c2_i24];
      }

      for (c2_i25 = 0; c2_i25 < 30; c2_i25++) {
        c2_e_U[c2_i25] = c2_d_U[c2_i25];
      }

      for (c2_i28 = 0; c2_i28 < 9; c2_i28++) {
        c2_c_J[c2_i28] = c2_b_J[c2_i28];
      }

      c2_foh(chartInstance, c2_g_X, c2_e_U, c2_h_s, c2_c_J,
             chartInstance->c2_b_EH, chartInstance->c2_b_BE, c2_b_ES, c2_b_AR);
      for (c2_i31 = 0; c2_i31 < 10000; c2_i31++) {
        chartInstance->c2_EH[c2_i31] = chartInstance->c2_b_EH[c2_i31];
      }

      for (c2_i33 = 0; c2_i33 < 3000; c2_i33++) {
        chartInstance->c2_BE[c2_i33] = chartInstance->c2_b_BE[c2_i33];
      }

      for (c2_i35 = 0; c2_i35 < 100; c2_i35++) {
        c2_ES[c2_i35] = c2_b_ES[c2_i35];
      }

      for (c2_i36 = 0; c2_i36 < 100; c2_i36++) {
        c2_AR[c2_i36] = c2_b_AR[c2_i36];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 50);
      for (c2_i37 = 0; c2_i37 < 10; c2_i37++) {
        c2_b_xi[c2_i37] = c2_xi[c2_i37];
      }

      for (c2_i38 = 0; c2_i38 < 7; c2_i38++) {
        c2_b_xf[c2_i38] = c2_xf[c2_i38];
      }

      for (c2_i39 = 0; c2_i39 < 9; c2_i39++) {
        c2_d_J[c2_i39] = c2_b_J[c2_i39];
      }

      for (c2_i40 = 0; c2_i40 < 10000; c2_i40++) {
        chartInstance->c2_c_EH[c2_i40] = chartInstance->c2_EH[c2_i40];
      }

      for (c2_i41 = 0; c2_i41 < 3000; c2_i41++) {
        chartInstance->c2_c_BE[c2_i41] = chartInstance->c2_BE[c2_i41];
      }

      for (c2_i42 = 0; c2_i42 < 100; c2_i42++) {
        c2_c_ES[c2_i42] = c2_ES[c2_i42];
      }

      for (c2_i43 = 0; c2_i43 < 100; c2_i43++) {
        c2_c_AR[c2_i43] = c2_AR[c2_i43];
      }

      c2_parse_ecos(chartInstance, c2_b_xi, c2_b_xf, c2_d_J,
                    chartInstance->c2_c_EH, chartInstance->c2_c_BE, c2_c_ES,
                    c2_c_AR, c2_b_T_max, c2_b_w_max, c2_b_s_max, c2_b_s_min,
                    c2_b_w_v, c2_b_c, chartInstance->c2_b_G, c2_b_h,
                    chartInstance->c2_b_A, c2_b_b);
      for (c2_i44 = 0; c2_i44 < 332; c2_i44++) {
        c2_c[c2_i44] = c2_b_c[c2_i44];
      }

      for (c2_i45 = 0; c2_i45 < 117528; c2_i45++) {
        chartInstance->c2_G[c2_i45] = chartInstance->c2_b_G[c2_i45];
      }

      for (c2_i46 = 0; c2_i46 < 354; c2_i46++) {
        c2_h[c2_i46] = c2_b_h[c2_i46];
      }

      for (c2_i47 = 0; c2_i47 < 38844; c2_i47++) {
        chartInstance->c2_A[c2_i47] = chartInstance->c2_b_A[c2_i47];
      }

      for (c2_i48 = 0; c2_i48 < 117; c2_i48++) {
        c2_b[c2_i48] = c2_b_b[c2_i48];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 54);
      for (c2_i49 = 0; c2_i49 < 38844; c2_i49++) {
        chartInstance->c2_c_A[c2_i49] = chartInstance->c2_A[c2_i49];
      }

      c2_convert_to_CCS(chartInstance, chartInstance->c2_c_A, c2_b_Air, c2_b_Ajc,
                        c2_b_Apr);
      for (c2_i50 = 0; c2_i50 < 1278; c2_i50++) {
        c2_Air[c2_i50] = c2_b_Air[c2_i50];
      }

      for (c2_i51 = 0; c2_i51 < 333; c2_i51++) {
        c2_Ajc[c2_i51] = c2_b_Ajc[c2_i51];
      }

      for (c2_i52 = 0; c2_i52 < 1278; c2_i52++) {
        c2_Apr[c2_i52] = c2_b_Apr[c2_i52];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 55);
      for (c2_i53 = 0; c2_i53 < 117528; c2_i53++) {
        chartInstance->c2_c_G[c2_i53] = chartInstance->c2_G[c2_i53];
      }

      c2_b_convert_to_CCS(chartInstance, chartInstance->c2_c_G, c2_b_Gir,
                          c2_b_Ajc, c2_b_Gpr);
      for (c2_i54 = 0; c2_i54 < 674; c2_i54++) {
        c2_Gir[c2_i54] = c2_b_Gir[c2_i54];
      }

      for (c2_i55 = 0; c2_i55 < 333; c2_i55++) {
        c2_Gjc[c2_i55] = c2_b_Ajc[c2_i55];
      }

      for (c2_i56 = 0; c2_i56 < 674; c2_i56++) {
        c2_Gpr[c2_i56] = c2_b_Gpr[c2_i56];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 58);
      for (c2_i57 = 0; c2_i57 < 332; c2_i57++) {
        c2_c_c[c2_i57] = c2_c[c2_i57];
      }

      for (c2_i58 = 0; c2_i58 < 333; c2_i58++) {
        c2_b_Gjc[c2_i58] = c2_Gjc[c2_i58];
      }

      for (c2_i59 = 0; c2_i59 < 674; c2_i59++) {
        c2_c_Gir[c2_i59] = c2_Gir[c2_i59];
      }

      for (c2_i60 = 0; c2_i60 < 674; c2_i60++) {
        c2_c_Gpr[c2_i60] = c2_Gpr[c2_i60];
      }

      for (c2_i61 = 0; c2_i61 < 354; c2_i61++) {
        c2_c_h[c2_i61] = c2_h[c2_i61];
      }

      for (c2_i62 = 0; c2_i62 < 333; c2_i62++) {
        c2_c_Ajc[c2_i62] = c2_Ajc[c2_i62];
      }

      for (c2_i63 = 0; c2_i63 < 1278; c2_i63++) {
        c2_c_Air[c2_i63] = c2_Air[c2_i63];
      }

      for (c2_i64 = 0; c2_i64 < 1278; c2_i64++) {
        c2_c_Apr[c2_i64] = c2_Apr[c2_i64];
      }

      for (c2_i65 = 0; c2_i65 < 117; c2_i65++) {
        c2_c_b[c2_i65] = c2_b[c2_i65];
      }

      c2_run_ecos(chartInstance, c2_n, c2_m, c2_p, c2_l, c2_ncones, c2_c_c,
                  c2_b_Gjc, c2_c_Gir, c2_c_Gpr, c2_c_h, c2_q, c2_c_Ajc, c2_c_Air,
                  c2_c_Apr, c2_c_b, c2_dv4);
      for (c2_i66 = 0; c2_i66 < 334; c2_i66++) {
        c2_e_y[c2_i66] = c2_dv4[c2_i66];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 65);
      for (c2_i67 = 0; c2_i67 < 100; c2_i67++) {
        c2_h_X[c2_i67] = c2_f_X[c2_i67] - c2_e_y[c2_i67];
      }

      c2_diff = c2_b_norm(chartInstance, c2_h_X);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 66);
      for (c2_i68 = 0; c2_i68 < 100; c2_i68++) {
        c2_f_X[c2_i68] = c2_e_y[c2_i68];
      }

      _SFD_SYMBOL_SWITCH(46U, 57U);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 67);
      for (c2_i69 = 0; c2_i69 < 30; c2_i69++) {
        c2_d_U[c2_i69] = c2_e_y[c2_i69 + 100];
      }

      _SFD_SYMBOL_SWITCH(47U, 58U);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 68);
      c2_h_s = c2_e_y[131];
      _SFD_SYMBOL_SWITCH(48U, 59U);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 69);
      for (c2_i70 = 0; c2_i70 < 99; c2_i70++) {
        c2_V[c2_i70] = c2_e_y[c2_i70 + 132];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 70);
      c2_b_exitcode[sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
        chartInstance->S, 1U, 2405, 11, MAX_uint32_T, (int32_T)sf_integer_check
        (chartInstance->S, 1U, 2405U, 11U, c2_k), 1, 11) - 1] = c2_e_y[332];
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 71);
      c2_b_time[sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
        chartInstance->S, 1U, 2436, 7, MAX_uint32_T, (int32_T)sf_integer_check
        (chartInstance->S, 1U, 2436U, 7U, c2_k), 1, 10) - 1] = c2_e_y[333];
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 75);
      c2_d0 = c2_b_exitcode[sf_eml_array_bounds_check
        (sfGlobalDebugInstanceStruct, chartInstance->S, 1U, 2626, 11,
         MAX_uint32_T, (int32_T)sf_integer_check(chartInstance->S, 1U, 2626U,
          11U, c2_k), 1, 11) - 1];
      if (CV_EML_IF(0, 1, 0, CV_RELATIONAL_EVAL(4U, 0U, 0, c2_d0, 0.0, -1, 1U,
            c2_d0 != 0.0))) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 76);
        c2_b_exitcode[10] = -1.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 79);
      for (c2_i71 = 0; c2_i71 < 99; c2_i71++) {
        c2_d_V[c2_i71] = c2_V[c2_i71];
      }

      for (c2_i72 = 0; c2_i72 < 99; c2_i72++) {
        c2_e_V[c2_i72] = c2_V[c2_i72];
      }

      if (CV_EML_COND(0, 1, 0, CV_RELATIONAL_EVAL(4U, 0U, 1, c2_c_norm
            (chartInstance, c2_d_V), 1.0E-5, -1, 2U, c2_c_norm(chartInstance,
             c2_e_V) < 1.0E-5)) && CV_EML_COND(0, 1, 1, CV_RELATIONAL_EVAL(4U,
            0U, 2, c2_diff, 0.1, -1, 2U, c2_diff < 0.1))) {
        CV_EML_MCDC(0, 1, 0, true);
        CV_EML_IF(0, 1, 1, true);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 81);
        exitg1 = 1;
      } else {
        CV_EML_MCDC(0, 1, 0, false);
        CV_EML_IF(0, 1, 1, false);
        c2_b_k++;
        _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
      }
    } else {
      CV_EML_FOR(0, 1, 0, 0);
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 87);
  if (CV_EML_IF(0, 1, 2, CV_RELATIONAL_EVAL(4U, 0U, 3, c2_k, c2_iter_max, -1, 0U,
        c2_k == c2_iter_max))) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 88);
    if (CV_EML_IF(0, 1, 3, CV_RELATIONAL_EVAL(4U, 0U, 4, c2_b_exitcode[10], -1.0,
          -1, 1U, c2_b_exitcode[10] != -1.0))) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 89);
      for (c2_i27 = 0; c2_i27 < 99; c2_i27++) {
        c2_b_V[c2_i27] = c2_V[c2_i27];
      }

      for (c2_i30 = 0; c2_i30 < 99; c2_i30++) {
        c2_c_V[c2_i30] = c2_V[c2_i30];
      }

      if (CV_EML_IF(0, 1, 4, CV_RELATIONAL_EVAL(4U, 0U, 5, c2_c_norm
            (chartInstance, c2_b_V), 1.0E-5, -1, 4U, c2_c_norm(chartInstance,
             c2_c_V) > 1.0E-5))) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 90);
        c2_b_exitcode[10] = 3.0;
      } else {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 91);
        if (CV_EML_IF(0, 1, 5, CV_RELATIONAL_EVAL(4U, 0U, 6, c2_diff, 1.0E-5, -1,
              4U, c2_diff > 1.0E-5))) {
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 92);
          c2_b_exitcode[10] = 4.0;
        }
      }
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -92);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i26 = 0; c2_i26 < 100; c2_i26++) {
    (*chartInstance->c2_d_X)[c2_i26] = c2_f_X[c2_i26];
  }

  for (c2_i29 = 0; c2_i29 < 30; c2_i29++) {
    (*chartInstance->c2_b_U)[c2_i29] = c2_d_U[c2_i29];
  }

  *chartInstance->c2_f_s = c2_h_s;
  for (c2_i32 = 0; c2_i32 < 11; c2_i32++) {
    (*chartInstance->c2_exitcode)[c2_i32] = c2_b_exitcode[c2_i32];
  }

  for (c2_i34 = 0; c2_i34 < 10; c2_i34++) {
    (*chartInstance->c2_time)[c2_i34] = c2_b_time[c2_i34];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_gnc2_lib(SFc2_gnc2_libInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_run_ecos(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_n,
  real_T c2_m, real_T c2_p, real_T c2_l, real_T c2_ncones, real_T c2_c[332],
  real_T c2_Gjc[333], real_T c2_Gir[674], real_T c2_Gpr[674], real_T c2_h[354],
  real_T c2_q, real_T c2_Ajc[333], real_T c2_Air[1278], real_T c2_Apr[1278],
  real_T c2_b[117], real_T c2_e_y[334])
{
  void *c2_inputVarPtrs[15];
  int32_T c2_inputVarSizes[15];
  void *c2_outputVarPtrs[1];
  int32_T c2_outputVarSizes[1];
  c2_inputVarPtrs[0U] = (void *)&c2_n;
  c2_inputVarSizes[0U] = (int32_T)sizeof(real_T);
  c2_inputVarPtrs[1U] = (void *)&c2_m;
  c2_inputVarSizes[1U] = (int32_T)sizeof(real_T);
  c2_inputVarPtrs[2U] = (void *)&c2_p;
  c2_inputVarSizes[2U] = (int32_T)sizeof(real_T);
  c2_inputVarPtrs[3U] = (void *)&c2_l;
  c2_inputVarSizes[3U] = (int32_T)sizeof(real_T);
  c2_inputVarPtrs[4U] = (void *)&c2_ncones;
  c2_inputVarSizes[4U] = (int32_T)sizeof(real_T);
  c2_inputVarPtrs[5U] = (void *)c2_c;
  c2_inputVarSizes[5U] = (int32_T)sizeof(real_T [332]);
  c2_inputVarPtrs[6U] = (void *)c2_Gjc;
  c2_inputVarSizes[6U] = (int32_T)sizeof(real_T [333]);
  c2_inputVarPtrs[7U] = (void *)c2_Gir;
  c2_inputVarSizes[7U] = (int32_T)sizeof(real_T [674]);
  c2_inputVarPtrs[8U] = (void *)c2_Gpr;
  c2_inputVarSizes[8U] = (int32_T)sizeof(real_T [674]);
  c2_inputVarPtrs[9U] = (void *)c2_h;
  c2_inputVarSizes[9U] = (int32_T)sizeof(real_T [354]);
  c2_inputVarPtrs[10U] = (void *)&c2_q;
  c2_inputVarSizes[10U] = (int32_T)sizeof(real_T);
  c2_inputVarPtrs[11U] = (void *)c2_Ajc;
  c2_inputVarSizes[11U] = (int32_T)sizeof(real_T [333]);
  c2_inputVarPtrs[12U] = (void *)c2_Air;
  c2_inputVarSizes[12U] = (int32_T)sizeof(real_T [1278]);
  c2_inputVarPtrs[13U] = (void *)c2_Apr;
  c2_inputVarSizes[13U] = (int32_T)sizeof(real_T [1278]);
  c2_inputVarPtrs[14U] = (void *)c2_b;
  c2_inputVarSizes[14U] = (int32_T)sizeof(real_T [117]);
  c2_outputVarPtrs[0U] = (void *)c2_e_y;
  c2_outputVarSizes[0U] = (int32_T)sizeof(real_T [334]);
  sfcs_request_service(chartInstance->S, "run_ecos", 15, (void *)c2_inputVarPtrs,
                       (void *)c2_inputVarSizes, 1, (void *)c2_outputVarPtrs,
                       (void *)c2_outputVarSizes);
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber)
{
  (void)c2_machineNumber;
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, c2_instanceNumber, 0U,
    sf_debug_get_script_id(
    "/Users/Taylor/uw_cubesat_adcs/adcs/sw/components/adcs_fsw/matlab/test/triad_test/fcns/skew.m"));
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i73;
  const mxArray *c2_e_y = NULL;
  real_T c2_e_u[10];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i73 = 0; c2_i73 < 10; c2_i73++) {
    c2_e_u[c2_i73] = (*(real_T (*)[10])c2_inData)[c2_i73];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 1, 10), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_b_time, const char_T *c2_identifier, real_T c2_e_y[10])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_time), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_b_time);
}

static void c2_b_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[10])
{
  real_T c2_dv5[10];
  int32_T c2_i74;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv5, 1, 0, 0U, 1, 0U, 1, 10);
  for (c2_i74 = 0; c2_i74 < 10; c2_i74++) {
    c2_e_y[c2_i74] = c2_dv5[c2_i74];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_time;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[10];
  int32_T c2_i75;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_b_time = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_time), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_b_time);
  for (c2_i75 = 0; c2_i75 < 10; c2_i75++) {
    (*(real_T (*)[10])c2_outData)[c2_i75] = c2_e_y[c2_i75];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i76;
  const mxArray *c2_e_y = NULL;
  real_T c2_e_u[11];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i76 = 0; c2_i76 < 11; c2_i76++) {
    c2_e_u[c2_i76] = (*(real_T (*)[11])c2_inData)[c2_i76];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 1, 11), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_c_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_b_exitcode, const char_T *c2_identifier, real_T c2_e_y[11])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_exitcode), &c2_thisId,
                        c2_e_y);
  sf_mex_destroy(&c2_b_exitcode);
}

static void c2_d_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[11])
{
  real_T c2_dv6[11];
  int32_T c2_i77;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv6, 1, 0, 0U, 1, 0U, 1, 11);
  for (c2_i77 = 0; c2_i77 < 11; c2_i77++) {
    c2_e_y[c2_i77] = c2_dv6[c2_i77];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_exitcode;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[11];
  int32_T c2_i78;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_b_exitcode = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_exitcode), &c2_thisId,
                        c2_e_y);
  sf_mex_destroy(&c2_b_exitcode);
  for (c2_i78 = 0; c2_i78 < 11; c2_i78++) {
    (*(real_T (*)[11])c2_outData)[c2_i78] = c2_e_y[c2_i78];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  real_T c2_e_u;
  const mxArray *c2_e_y = NULL;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_e_u = *(real_T *)c2_inData;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_e_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_g_s, const char_T *c2_identifier)
{
  real_T c2_e_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_e_y = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_g_s), &c2_thisId);
  sf_mex_destroy(&c2_g_s);
  return c2_e_y;
}

static real_T c2_f_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_e_y;
  real_T c2_d1;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), &c2_d1, 1, 0, 0U, 0, 0U, 0);
  c2_e_y = c2_d1;
  sf_mex_destroy(&c2_e_u);
  return c2_e_y;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_g_s;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_g_s = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_e_y = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_g_s), &c2_thisId);
  sf_mex_destroy(&c2_g_s);
  *(real_T *)c2_outData = c2_e_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i79;
  const mxArray *c2_e_y = NULL;
  real_T c2_e_u[30];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i79 = 0; c2_i79 < 30; c2_i79++) {
    c2_e_u[c2_i79] = (*(real_T (*)[30])c2_inData)[c2_i79];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 1, 30), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_g_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_c_U, const char_T *c2_identifier, real_T c2_e_y[30])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_c_U), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_c_U);
}

static void c2_h_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[30])
{
  real_T c2_dv7[30];
  int32_T c2_i80;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv7, 1, 0, 0U, 1, 0U, 1, 30);
  for (c2_i80 = 0; c2_i80 < 30; c2_i80++) {
    c2_e_y[c2_i80] = c2_dv7[c2_i80];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_c_U;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[30];
  int32_T c2_i81;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_c_U = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_c_U), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_c_U);
  for (c2_i81 = 0; c2_i81 < 30; c2_i81++) {
    (*(real_T (*)[30])c2_outData)[c2_i81] = c2_e_y[c2_i81];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i82;
  const mxArray *c2_e_y = NULL;
  real_T c2_e_u[100];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i82 = 0; c2_i82 < 100; c2_i82++) {
    c2_e_u[c2_i82] = (*(real_T (*)[100])c2_inData)[c2_i82];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 1, 100),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_i_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_X, const char_T *c2_identifier, real_T c2_e_y[100])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_e_X), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_e_X);
}

static void c2_j_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [100])
{
  real_T c2_dv8[100];
  int32_T c2_i83;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv8, 1, 0, 0U, 1, 0U, 1, 100);
  for (c2_i83 = 0; c2_i83 < 100; c2_i83++) {
    c2_e_y[c2_i83] = c2_dv8[c2_i83];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_e_X;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[100];
  int32_T c2_i84;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_e_X = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_e_X), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_e_X);
  for (c2_i84 = 0; c2_i84 < 100; c2_i84++) {
    (*(real_T (*)[100])c2_outData)[c2_i84] = c2_e_y[c2_i84];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i85;
  int32_T c2_i86;
  const mxArray *c2_e_y = NULL;
  int32_T c2_i87;
  real_T c2_e_u[16];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_i85 = 0;
  for (c2_i86 = 0; c2_i86 < 4; c2_i86++) {
    for (c2_i87 = 0; c2_i87 < 4; c2_i87++) {
      c2_e_u[c2_i87 + c2_i85] = (*(real_T (*)[16])c2_inData)[c2_i87 + c2_i85];
    }

    c2_i85 += 4;
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 2, 4, 4),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i88;
  int32_T c2_i89;
  const mxArray *c2_e_y = NULL;
  int32_T c2_i90;
  real_T c2_e_u[9];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_i88 = 0;
  for (c2_i89 = 0; c2_i89 < 3; c2_i89++) {
    for (c2_i90 = 0; c2_i90 < 3; c2_i90++) {
      c2_e_u[c2_i90 + c2_i88] = (*(real_T (*)[9])c2_inData)[c2_i90 + c2_i88];
    }

    c2_i88 += 3;
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 2, 3, 3),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  c2_saot08BhBJej868PSk74SzB c2_e_u;
  const mxArray *c2_e_y = NULL;
  c2_sKpQB9jVSEZrFP5iOeb0DOE c2_f_u;
  const mxArray *c2_f_y = NULL;
  real_T c2_g_u;
  const mxArray *c2_g_y = NULL;
  int32_T c2_i91;
  const mxArray *c2_h_y = NULL;
  real_T c2_h_u[4];
  int32_T c2_i92;
  const mxArray *c2_i_y = NULL;
  real_T c2_i_u[3];
  int32_T c2_i93;
  const mxArray *c2_j_y = NULL;
  int32_T c2_i94;
  const mxArray *c2_k_y = NULL;
  int32_T c2_i95;
  const mxArray *c2_l_y = NULL;
  int32_T c2_i96;
  const mxArray *c2_m_y = NULL;
  int32_T c2_i97;
  const mxArray *c2_n_y = NULL;
  real_T c2_j_u[2];
  int32_T c2_i98;
  const mxArray *c2_o_y = NULL;
  int32_T c2_i99;
  const mxArray *c2_p_y = NULL;
  int32_T c2_i100;
  const mxArray *c2_q_y = NULL;
  real_T c2_k_u[10];
  real_T c2_l_u;
  const mxArray *c2_r_y = NULL;
  real_T c2_m_u;
  const mxArray *c2_s_y = NULL;
  real_T c2_n_u;
  const mxArray *c2_t_y = NULL;
  real_T c2_o_u;
  const mxArray *c2_u_y = NULL;
  real_T c2_p_u;
  const mxArray *c2_v_y = NULL;
  real_T c2_q_u;
  const mxArray *c2_w_y = NULL;
  real_T c2_r_u;
  const mxArray *c2_x_y = NULL;
  real_T c2_s_u;
  const mxArray *c2_y_y = NULL;
  real_T c2_t_u;
  const mxArray *c2_ab_y = NULL;
  real_T c2_u_u;
  const mxArray *c2_bb_y = NULL;
  real_T c2_v_u;
  const mxArray *c2_cb_y = NULL;
  real_T c2_w_u;
  const mxArray *c2_db_y = NULL;
  real_T c2_x_u;
  const mxArray *c2_eb_y = NULL;
  real_T c2_y_u;
  const mxArray *c2_fb_y = NULL;
  real_T c2_ab_u;
  const mxArray *c2_gb_y = NULL;
  real_T c2_bb_u;
  const mxArray *c2_hb_y = NULL;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_e_u = *(c2_saot08BhBJej868PSk74SzB *)c2_inData;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c2_f_u = c2_e_u.ic;
  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c2_g_u = c2_f_u.sc_mode;
  c2_g_y = NULL;
  sf_mex_assign(&c2_g_y, sf_mex_create("y", &c2_g_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_f_y, c2_g_y, "sc_mode", "sc_mode", 0);
  for (c2_i91 = 0; c2_i91 < 4; c2_i91++) {
    c2_h_u[c2_i91] = c2_f_u.quat_in[c2_i91];
  }

  c2_h_y = NULL;
  sf_mex_assign(&c2_h_y, sf_mex_create("y", c2_h_u, 0, 0U, 1U, 0U, 1, 4), false);
  sf_mex_addfield(c2_f_y, c2_h_y, "quat_in", "quat_in", 0);
  for (c2_i92 = 0; c2_i92 < 3; c2_i92++) {
    c2_i_u[c2_i92] = c2_f_u.w_body_radps[c2_i92];
  }

  c2_i_y = NULL;
  sf_mex_assign(&c2_i_y, sf_mex_create("y", c2_i_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_addfield(c2_f_y, c2_i_y, "w_body_radps", "w_body_radps", 0);
  for (c2_i93 = 0; c2_i93 < 3; c2_i93++) {
    c2_i_u[c2_i93] = c2_f_u.hw_Nms[c2_i93];
  }

  c2_j_y = NULL;
  sf_mex_assign(&c2_j_y, sf_mex_create("y", c2_i_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_addfield(c2_f_y, c2_j_y, "hw_Nms", "hw_Nms", 0);
  for (c2_i94 = 0; c2_i94 < 4; c2_i94++) {
    c2_h_u[c2_i94] = c2_f_u.quat_cmd[c2_i94];
  }

  c2_k_y = NULL;
  sf_mex_assign(&c2_k_y, sf_mex_create("y", c2_h_u, 0, 0U, 1U, 0U, 1, 4), false);
  sf_mex_addfield(c2_f_y, c2_k_y, "quat_cmd", "quat_cmd", 0);
  for (c2_i95 = 0; c2_i95 < 3; c2_i95++) {
    c2_i_u[c2_i95] = c2_f_u.w_body_cmd_radps[c2_i95];
  }

  c2_l_y = NULL;
  sf_mex_assign(&c2_l_y, sf_mex_create("y", c2_i_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_addfield(c2_f_y, c2_l_y, "w_body_cmd_radps", "w_body_cmd_radps", 0);
  for (c2_i96 = 0; c2_i96 < 3; c2_i96++) {
    c2_i_u[c2_i96] = c2_f_u.sun_inertial_unit[c2_i96];
  }

  c2_m_y = NULL;
  sf_mex_assign(&c2_m_y, sf_mex_create("y", c2_i_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_addfield(c2_f_y, c2_m_y, "sun_inertial_unit", "sun_inertial_unit", 0);
  for (c2_i97 = 0; c2_i97 < 2; c2_i97++) {
    c2_j_u[c2_i97] = c2_f_u.gps_epoch_s[c2_i97];
  }

  c2_n_y = NULL;
  sf_mex_assign(&c2_n_y, sf_mex_create("y", c2_j_u, 0, 0U, 1U, 0U, 1, 2), false);
  sf_mex_addfield(c2_f_y, c2_n_y, "gps_epoch_s", "gps_epoch_s", 0);
  for (c2_i98 = 0; c2_i98 < 2; c2_i98++) {
    c2_j_u[c2_i98] = c2_f_u.gps_time_s[c2_i98];
  }

  c2_o_y = NULL;
  sf_mex_assign(&c2_o_y, sf_mex_create("y", c2_j_u, 0, 0U, 1U, 0U, 1, 2), false);
  sf_mex_addfield(c2_f_y, c2_o_y, "gps_time_s", "gps_time_s", 0);
  for (c2_i99 = 0; c2_i99 < 3; c2_i99++) {
    c2_i_u[c2_i99] = c2_f_u.cmd_torque[c2_i99];
  }

  c2_p_y = NULL;
  sf_mex_assign(&c2_p_y, sf_mex_create("y", c2_i_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_addfield(c2_f_y, c2_p_y, "cmd_torque", "cmd_torque", 0);
  for (c2_i100 = 0; c2_i100 < 10; c2_i100++) {
    c2_k_u[c2_i100] = c2_f_u.cmd_state[c2_i100];
  }

  c2_q_y = NULL;
  sf_mex_assign(&c2_q_y, sf_mex_create("y", c2_k_u, 0, 0U, 1U, 0U, 1, 10), false);
  sf_mex_addfield(c2_f_y, c2_q_y, "cmd_state", "cmd_state", 0);
  sf_mex_addfield(c2_e_y, c2_f_y, "ic", "ic", 0);
  c2_l_u = c2_e_u.sample_time_s;
  c2_r_y = NULL;
  sf_mex_assign(&c2_r_y, sf_mex_create("y", &c2_l_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_e_y, c2_r_y, "sample_time_s", "sample_time_s", 0);
  c2_m_u = c2_e_u.N;
  c2_s_y = NULL;
  sf_mex_assign(&c2_s_y, sf_mex_create("y", &c2_m_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_e_y, c2_s_y, "N", "N", 0);
  c2_n_u = c2_e_u.dt;
  c2_t_y = NULL;
  sf_mex_assign(&c2_t_y, sf_mex_create("y", &c2_n_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_e_y, c2_t_y, "dt", "dt", 0);
  c2_o_u = c2_e_u.c_size;
  c2_u_y = NULL;
  sf_mex_assign(&c2_u_y, sf_mex_create("y", &c2_o_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_e_y, c2_u_y, "c_size", "c_size", 0);
  c2_p_u = c2_e_u.Air_size;
  c2_v_y = NULL;
  sf_mex_assign(&c2_v_y, sf_mex_create("y", &c2_p_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_e_y, c2_v_y, "Air_size", "Air_size", 0);
  c2_q_u = c2_e_u.Ajc_size;
  c2_w_y = NULL;
  sf_mex_assign(&c2_w_y, sf_mex_create("y", &c2_q_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_e_y, c2_w_y, "Ajc_size", "Ajc_size", 0);
  c2_r_u = c2_e_u.Apr_size;
  c2_x_y = NULL;
  sf_mex_assign(&c2_x_y, sf_mex_create("y", &c2_r_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_e_y, c2_x_y, "Apr_size", "Apr_size", 0);
  c2_s_u = c2_e_u.b_size;
  c2_y_y = NULL;
  sf_mex_assign(&c2_y_y, sf_mex_create("y", &c2_s_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_e_y, c2_y_y, "b_size", "b_size", 0);
  c2_t_u = c2_e_u.Gir_size;
  c2_ab_y = NULL;
  sf_mex_assign(&c2_ab_y, sf_mex_create("y", &c2_t_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_e_y, c2_ab_y, "Gir_size", "Gir_size", 0);
  c2_u_u = c2_e_u.Gjc_size;
  c2_bb_y = NULL;
  sf_mex_assign(&c2_bb_y, sf_mex_create("y", &c2_u_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_e_y, c2_bb_y, "Gjc_size", "Gjc_size", 0);
  c2_v_u = c2_e_u.Gpr_size;
  c2_cb_y = NULL;
  sf_mex_assign(&c2_cb_y, sf_mex_create("y", &c2_v_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_e_y, c2_cb_y, "Gpr_size", "Gpr_size", 0);
  c2_w_u = c2_e_u.h_size;
  c2_db_y = NULL;
  sf_mex_assign(&c2_db_y, sf_mex_create("y", &c2_w_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_e_y, c2_db_y, "h_size", "h_size", 0);
  c2_x_u = c2_e_u.q_size;
  c2_eb_y = NULL;
  sf_mex_assign(&c2_eb_y, sf_mex_create("y", &c2_x_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_e_y, c2_eb_y, "q_size", "q_size", 0);
  c2_y_u = c2_e_u.y_size;
  c2_fb_y = NULL;
  sf_mex_assign(&c2_fb_y, sf_mex_create("y", &c2_y_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_e_y, c2_fb_y, "y_size", "y_size", 0);
  c2_ab_u = c2_e_u.l_dim;
  c2_gb_y = NULL;
  sf_mex_assign(&c2_gb_y, sf_mex_create("y", &c2_ab_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_e_y, c2_gb_y, "l_dim", "l_dim", 0);
  c2_bb_u = c2_e_u.soc_dim;
  c2_hb_y = NULL;
  sf_mex_assign(&c2_hb_y, sf_mex_create("y", &c2_bb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_e_y, c2_hb_y, "soc_dim", "soc_dim", 0);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i101;
  const mxArray *c2_e_y = NULL;
  real_T c2_e_u[99];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i101 = 0; c2_i101 < 99; c2_i101++) {
    c2_e_u[c2_i101] = (*(real_T (*)[99])c2_inData)[c2_i101];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 1, 99), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_k_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[99])
{
  real_T c2_dv9[99];
  int32_T c2_i102;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv9, 1, 0, 0U, 1, 0U, 1, 99);
  for (c2_i102 = 0; c2_i102 < 99; c2_i102++) {
    c2_e_y[c2_i102] = c2_dv9[c2_i102];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_V;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[99];
  int32_T c2_i103;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_V = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_V), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_V);
  for (c2_i103 = 0; c2_i103 < 99; c2_i103++) {
    (*(real_T (*)[99])c2_outData)[c2_i103] = c2_e_y[c2_i103];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_j_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i104;
  const mxArray *c2_e_y = NULL;
  real_T c2_e_u[334];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i104 = 0; c2_i104 < 334; c2_i104++) {
    c2_e_u[c2_i104] = (*(real_T (*)[334])c2_inData)[c2_i104];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 1, 334),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_l_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [334])
{
  real_T c2_dv10[334];
  int32_T c2_i105;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv10, 1, 0, 0U, 1, 0U, 1,
                334);
  for (c2_i105 = 0; c2_i105 < 334; c2_i105++) {
    c2_e_y[c2_i105] = c2_dv10[c2_i105];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_e_y;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_f_y[334];
  int32_T c2_i106;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_e_y = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_e_y), &c2_thisId, c2_f_y);
  sf_mex_destroy(&c2_e_y);
  for (c2_i106 = 0; c2_i106 < 334; c2_i106++) {
    (*(real_T (*)[334])c2_outData)[c2_i106] = c2_f_y[c2_i106];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_k_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i107;
  const mxArray *c2_e_y = NULL;
  real_T c2_e_u[674];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i107 = 0; c2_i107 < 674; c2_i107++) {
    c2_e_u[c2_i107] = (*(real_T (*)[674])c2_inData)[c2_i107];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 1, 674),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_m_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [674])
{
  real_T c2_dv11[674];
  int32_T c2_i108;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv11, 1, 0, 0U, 1, 0U, 1,
                674);
  for (c2_i108 = 0; c2_i108 < 674; c2_i108++) {
    c2_e_y[c2_i108] = c2_dv11[c2_i108];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_Gpr;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[674];
  int32_T c2_i109;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_Gpr = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_Gpr), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_Gpr);
  for (c2_i109 = 0; c2_i109 < 674; c2_i109++) {
    (*(real_T (*)[674])c2_outData)[c2_i109] = c2_e_y[c2_i109];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_l_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i110;
  const mxArray *c2_e_y = NULL;
  real_T c2_e_u[333];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i110 = 0; c2_i110 < 333; c2_i110++) {
    c2_e_u[c2_i110] = (*(real_T (*)[333])c2_inData)[c2_i110];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 1, 333),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_n_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [333])
{
  real_T c2_dv12[333];
  int32_T c2_i111;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv12, 1, 0, 0U, 1, 0U, 1,
                333);
  for (c2_i111 = 0; c2_i111 < 333; c2_i111++) {
    c2_e_y[c2_i111] = c2_dv12[c2_i111];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_Gjc;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[333];
  int32_T c2_i112;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_Gjc = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_Gjc), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_Gjc);
  for (c2_i112 = 0; c2_i112 < 333; c2_i112++) {
    (*(real_T (*)[333])c2_outData)[c2_i112] = c2_e_y[c2_i112];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_m_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i113;
  const mxArray *c2_e_y = NULL;
  real_T c2_e_u[1278];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i113 = 0; c2_i113 < 1278; c2_i113++) {
    c2_e_u[c2_i113] = (*(real_T (*)[1278])c2_inData)[c2_i113];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 1, 1278),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_o_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [1278])
{
  real_T c2_dv13[1278];
  int32_T c2_i114;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv13, 1, 0, 0U, 1, 0U, 1,
                1278);
  for (c2_i114 = 0; c2_i114 < 1278; c2_i114++) {
    c2_e_y[c2_i114] = c2_dv13[c2_i114];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_Apr;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[1278];
  int32_T c2_i115;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_Apr = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_Apr), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_Apr);
  for (c2_i115 = 0; c2_i115 < 1278; c2_i115++) {
    (*(real_T (*)[1278])c2_outData)[c2_i115] = c2_e_y[c2_i115];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_n_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i116;
  const mxArray *c2_e_y = NULL;
  real_T c2_e_u[117];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i116 = 0; c2_i116 < 117; c2_i116++) {
    c2_e_u[c2_i116] = (*(real_T (*)[117])c2_inData)[c2_i116];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 1, 117),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_p_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [117])
{
  real_T c2_dv14[117];
  int32_T c2_i117;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv14, 1, 0, 0U, 1, 0U, 1,
                117);
  for (c2_i117 = 0; c2_i117 < 117; c2_i117++) {
    c2_e_y[c2_i117] = c2_dv14[c2_i117];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[117];
  int32_T c2_i118;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_b = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_b);
  for (c2_i118 = 0; c2_i118 < 117; c2_i118++) {
    (*(real_T (*)[117])c2_outData)[c2_i118] = c2_e_y[c2_i118];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_o_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i119;
  int32_T c2_i120;
  const mxArray *c2_e_y = NULL;
  int32_T c2_i121;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_i119 = 0;
  for (c2_i120 = 0; c2_i120 < 332; c2_i120++) {
    for (c2_i121 = 0; c2_i121 < 117; c2_i121++) {
      chartInstance->c2_c_u[c2_i121 + c2_i119] = (*(real_T (*)[38844])c2_inData)
        [c2_i121 + c2_i119];
    }

    c2_i119 += 117;
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", chartInstance->c2_c_u, 0, 0U, 1U, 0U,
    2, 117, 332), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_q_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [38844])
{
  int32_T c2_i122;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), chartInstance->c2_dv15, 1, 0,
                0U, 1, 0U, 2, 117, 332);
  for (c2_i122 = 0; c2_i122 < 38844; c2_i122++) {
    c2_e_y[c2_i122] = chartInstance->c2_dv15[c2_i122];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_d_A;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_i123;
  int32_T c2_i124;
  int32_T c2_i125;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_d_A = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_q_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_d_A), &c2_thisId,
                        chartInstance->c2_c_y);
  sf_mex_destroy(&c2_d_A);
  c2_i123 = 0;
  for (c2_i124 = 0; c2_i124 < 332; c2_i124++) {
    for (c2_i125 = 0; c2_i125 < 117; c2_i125++) {
      (*(real_T (*)[38844])c2_outData)[c2_i125 + c2_i123] =
        chartInstance->c2_c_y[c2_i125 + c2_i123];
    }

    c2_i123 += 117;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_p_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i126;
  const mxArray *c2_e_y = NULL;
  real_T c2_e_u[354];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i126 = 0; c2_i126 < 354; c2_i126++) {
    c2_e_u[c2_i126] = (*(real_T (*)[354])c2_inData)[c2_i126];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 1, 354),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_r_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [354])
{
  real_T c2_dv16[354];
  int32_T c2_i127;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv16, 1, 0, 0U, 1, 0U, 1,
                354);
  for (c2_i127 = 0; c2_i127 < 354; c2_i127++) {
    c2_e_y[c2_i127] = c2_dv16[c2_i127];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_h;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[354];
  int32_T c2_i128;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_h = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_r_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_h), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_h);
  for (c2_i128 = 0; c2_i128 < 354; c2_i128++) {
    (*(real_T (*)[354])c2_outData)[c2_i128] = c2_e_y[c2_i128];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_q_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i129;
  int32_T c2_i130;
  const mxArray *c2_e_y = NULL;
  int32_T c2_i131;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_i129 = 0;
  for (c2_i130 = 0; c2_i130 < 332; c2_i130++) {
    for (c2_i131 = 0; c2_i131 < 354; c2_i131++) {
      chartInstance->c2_u[c2_i131 + c2_i129] = (*(real_T (*)[117528])c2_inData)
        [c2_i131 + c2_i129];
    }

    c2_i129 += 354;
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", chartInstance->c2_u, 0, 0U, 1U, 0U,
    2, 354, 332), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_s_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [117528])
{
  int32_T c2_i132;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), chartInstance->c2_dv17, 1, 0,
                0U, 1, 0U, 2, 354, 332);
  for (c2_i132 = 0; c2_i132 < 117528; c2_i132++) {
    c2_e_y[c2_i132] = chartInstance->c2_dv17[c2_i132];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_d_G;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_i133;
  int32_T c2_i134;
  int32_T c2_i135;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_d_G = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_s_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_d_G), &c2_thisId,
                        chartInstance->c2_y);
  sf_mex_destroy(&c2_d_G);
  c2_i133 = 0;
  for (c2_i134 = 0; c2_i134 < 332; c2_i134++) {
    for (c2_i135 = 0; c2_i135 < 354; c2_i135++) {
      (*(real_T (*)[117528])c2_outData)[c2_i135 + c2_i133] = chartInstance->
        c2_y[c2_i135 + c2_i133];
    }

    c2_i133 += 354;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_r_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i136;
  const mxArray *c2_e_y = NULL;
  real_T c2_e_u[332];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i136 = 0; c2_i136 < 332; c2_i136++) {
    c2_e_u[c2_i136] = (*(real_T (*)[332])c2_inData)[c2_i136];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 1, 332),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_t_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [332])
{
  real_T c2_dv18[332];
  int32_T c2_i137;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv18, 1, 0, 0U, 1, 0U, 1,
                332);
  for (c2_i137 = 0; c2_i137 < 332; c2_i137++) {
    c2_e_y[c2_i137] = c2_dv18[c2_i137];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_o_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_c;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[332];
  int32_T c2_i138;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_c = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_t_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_c), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_c);
  for (c2_i138 = 0; c2_i138 < 332; c2_i138++) {
    (*(real_T (*)[332])c2_outData)[c2_i138] = c2_e_y[c2_i138];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_s_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i139;
  int32_T c2_i140;
  const mxArray *c2_e_y = NULL;
  int32_T c2_i141;
  real_T c2_e_u[3000];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_i139 = 0;
  for (c2_i140 = 0; c2_i140 < 30; c2_i140++) {
    for (c2_i141 = 0; c2_i141 < 100; c2_i141++) {
      c2_e_u[c2_i141 + c2_i139] = (*(real_T (*)[3000])c2_inData)[c2_i141 +
        c2_i139];
    }

    c2_i139 += 100;
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 2, 100, 30),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_u_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [3000])
{
  real_T c2_dv19[3000];
  int32_T c2_i142;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv19, 1, 0, 0U, 1, 0U, 2,
                100, 30);
  for (c2_i142 = 0; c2_i142 < 3000; c2_i142++) {
    c2_e_y[c2_i142] = c2_dv19[c2_i142];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_p_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_d_BE;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[3000];
  int32_T c2_i143;
  int32_T c2_i144;
  int32_T c2_i145;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_d_BE = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_u_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_d_BE), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_d_BE);
  c2_i143 = 0;
  for (c2_i144 = 0; c2_i144 < 30; c2_i144++) {
    for (c2_i145 = 0; c2_i145 < 100; c2_i145++) {
      (*(real_T (*)[3000])c2_outData)[c2_i145 + c2_i143] = c2_e_y[c2_i145 +
        c2_i143];
    }

    c2_i143 += 100;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_t_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i146;
  int32_T c2_i147;
  const mxArray *c2_e_y = NULL;
  int32_T c2_i148;
  real_T c2_e_u[10000];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_i146 = 0;
  for (c2_i147 = 0; c2_i147 < 100; c2_i147++) {
    for (c2_i148 = 0; c2_i148 < 100; c2_i148++) {
      c2_e_u[c2_i148 + c2_i146] = (*(real_T (*)[10000])c2_inData)[c2_i148 +
        c2_i146];
    }

    c2_i146 += 100;
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 2, 100, 100),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_v_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [10000])
{
  real_T c2_dv20[10000];
  int32_T c2_i149;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv20, 1, 0, 0U, 1, 0U, 2,
                100, 100);
  for (c2_i149 = 0; c2_i149 < 10000; c2_i149++) {
    c2_e_y[c2_i149] = c2_dv20[c2_i149];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_q_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_d_EH;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[10000];
  int32_T c2_i150;
  int32_T c2_i151;
  int32_T c2_i152;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_d_EH = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_v_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_d_EH), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_d_EH);
  c2_i150 = 0;
  for (c2_i151 = 0; c2_i151 < 100; c2_i151++) {
    for (c2_i152 = 0; c2_i152 < 100; c2_i152++) {
      (*(real_T (*)[10000])c2_outData)[c2_i152 + c2_i150] = c2_e_y[c2_i152 +
        c2_i150];
    }

    c2_i150 += 100;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_u_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i153;
  const mxArray *c2_e_y = NULL;
  real_T c2_e_u[7];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i153 = 0; c2_i153 < 7; c2_i153++) {
    c2_e_u[c2_i153] = (*(real_T (*)[7])c2_inData)[c2_i153];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 1, 7), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_w_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[7])
{
  real_T c2_dv21[7];
  int32_T c2_i154;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv21, 1, 0, 0U, 1, 0U, 1, 7);
  for (c2_i154 = 0; c2_i154 < 7; c2_i154++) {
    c2_e_y[c2_i154] = c2_dv21[c2_i154];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_r_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_xf;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[7];
  int32_T c2_i155;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_xf = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_w_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_xf), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_xf);
  for (c2_i155 = 0; c2_i155 < 7; c2_i155++) {
    (*(real_T (*)[7])c2_outData)[c2_i155] = c2_e_y[c2_i155];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static void c2_x_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[9])
{
  real_T c2_dv22[9];
  int32_T c2_i156;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv22, 1, 0, 0U, 1, 0U, 2, 3,
                3);
  for (c2_i156 = 0; c2_i156 < 9; c2_i156++) {
    c2_e_y[c2_i156] = c2_dv22[c2_i156];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_s_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_cross;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[9];
  int32_T c2_i157;
  int32_T c2_i158;
  int32_T c2_i159;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_cross = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_x_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_cross), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_cross);
  c2_i157 = 0;
  for (c2_i158 = 0; c2_i158 < 3; c2_i158++) {
    for (c2_i159 = 0; c2_i159 < 3; c2_i159++) {
      (*(real_T (*)[9])c2_outData)[c2_i159 + c2_i157] = c2_e_y[c2_i159 + c2_i157];
    }

    c2_i157 += 3;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_v_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i160;
  const mxArray *c2_e_y = NULL;
  real_T c2_e_u[3];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i160 = 0; c2_i160 < 3; c2_i160++) {
    c2_e_u[c2_i160] = (*(real_T (*)[3])c2_inData)[c2_i160];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_y_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[3])
{
  real_T c2_dv23[3];
  int32_T c2_i161;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv23, 1, 0, 0U, 1, 0U, 1, 3);
  for (c2_i161 = 0; c2_i161 < 3; c2_i161++) {
    c2_e_y[c2_i161] = c2_dv23[c2_i161];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_t_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_a;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[3];
  int32_T c2_i162;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_a = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_a), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_a);
  for (c2_i162 = 0; c2_i162 < 3; c2_i162++) {
    (*(real_T (*)[3])c2_outData)[c2_i162] = c2_e_y[c2_i162];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_w_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i163;
  int32_T c2_i164;
  const mxArray *c2_e_y = NULL;
  int32_T c2_i165;
  real_T c2_e_u[100];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_i163 = 0;
  for (c2_i164 = 0; c2_i164 < 10; c2_i164++) {
    for (c2_i165 = 0; c2_i165 < 10; c2_i165++) {
      c2_e_u[c2_i165 + c2_i163] = (*(real_T (*)[100])c2_inData)[c2_i165 +
        c2_i163];
    }

    c2_i163 += 10;
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 2, 10, 10),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_ab_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [100])
{
  real_T c2_dv24[100];
  int32_T c2_i166;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv24, 1, 0, 0U, 1, 0U, 2, 10,
                10);
  for (c2_i166 = 0; c2_i166 < 100; c2_i166++) {
    c2_e_y[c2_i166] = c2_dv24[c2_i166];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_u_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_d_A;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[100];
  int32_T c2_i167;
  int32_T c2_i168;
  int32_T c2_i169;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_d_A = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_ab_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_d_A), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_d_A);
  c2_i167 = 0;
  for (c2_i168 = 0; c2_i168 < 10; c2_i168++) {
    for (c2_i169 = 0; c2_i169 < 10; c2_i169++) {
      (*(real_T (*)[100])c2_outData)[c2_i169 + c2_i167] = c2_e_y[c2_i169 +
        c2_i167];
    }

    c2_i167 += 10;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_x_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i170;
  const mxArray *c2_e_y = NULL;
  real_T c2_e_u[4];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i170 = 0; c2_i170 < 4; c2_i170++) {
    c2_e_u[c2_i170] = (*(real_T (*)[4])c2_inData)[c2_i170];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 1, 4), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_bb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[4])
{
  real_T c2_dv25[4];
  int32_T c2_i171;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv25, 1, 0, 0U, 1, 0U, 1, 4);
  for (c2_i171 = 0; c2_i171 < 4; c2_i171++) {
    c2_e_y[c2_i171] = c2_dv25[c2_i171];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_v_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_fq;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[4];
  int32_T c2_i172;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_fq = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_bb_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_fq), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_fq);
  for (c2_i172 = 0; c2_i172 < 4; c2_i172++) {
    (*(real_T (*)[4])c2_outData)[c2_i172] = c2_e_y[c2_i172];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_y_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i173;
  int32_T c2_i174;
  const mxArray *c2_e_y = NULL;
  int32_T c2_i175;
  real_T c2_e_u[12];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_i173 = 0;
  for (c2_i174 = 0; c2_i174 < 3; c2_i174++) {
    for (c2_i175 = 0; c2_i175 < 4; c2_i175++) {
      c2_e_u[c2_i175 + c2_i173] = (*(real_T (*)[12])c2_inData)[c2_i175 + c2_i173];
    }

    c2_i173 += 4;
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 2, 4, 3),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_ab_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i176;
  int32_T c2_i177;
  const mxArray *c2_e_y = NULL;
  int32_T c2_i178;
  real_T c2_e_u[12];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_i176 = 0;
  for (c2_i177 = 0; c2_i177 < 4; c2_i177++) {
    for (c2_i178 = 0; c2_i178 < 3; c2_i178++) {
      c2_e_u[c2_i178 + c2_i176] = (*(real_T (*)[12])c2_inData)[c2_i178 + c2_i176];
    }

    c2_i176 += 3;
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 2, 3, 4),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_cb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[12])
{
  real_T c2_dv26[12];
  int32_T c2_i179;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv26, 1, 0, 0U, 1, 0U, 2, 4,
                3);
  for (c2_i179 = 0; c2_i179 < 12; c2_i179++) {
    c2_e_y[c2_i179] = c2_dv26[c2_i179];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_w_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_dfq_dhb;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[12];
  int32_T c2_i180;
  int32_T c2_i181;
  int32_T c2_i182;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_dfq_dhb = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_cb_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_dfq_dhb), &c2_thisId,
    c2_e_y);
  sf_mex_destroy(&c2_dfq_dhb);
  c2_i180 = 0;
  for (c2_i181 = 0; c2_i181 < 3; c2_i181++) {
    for (c2_i182 = 0; c2_i182 < 4; c2_i182++) {
      (*(real_T (*)[12])c2_outData)[c2_i182 + c2_i180] = c2_e_y[c2_i182 +
        c2_i180];
    }

    c2_i180 += 4;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static void c2_db_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[16])
{
  real_T c2_dv27[16];
  int32_T c2_i183;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv27, 1, 0, 0U, 1, 0U, 2, 4,
                4);
  for (c2_i183 = 0; c2_i183 < 16; c2_i183++) {
    c2_e_y[c2_i183] = c2_dv27[c2_i183];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_x_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_dfq_dq;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[16];
  int32_T c2_i184;
  int32_T c2_i185;
  int32_T c2_i186;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_dfq_dq = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_db_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_dfq_dq), &c2_thisId,
    c2_e_y);
  sf_mex_destroy(&c2_dfq_dq);
  c2_i184 = 0;
  for (c2_i185 = 0; c2_i185 < 4; c2_i185++) {
    for (c2_i186 = 0; c2_i186 < 4; c2_i186++) {
      (*(real_T (*)[16])c2_outData)[c2_i186 + c2_i184] = c2_e_y[c2_i186 +
        c2_i184];
    }

    c2_i184 += 4;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_bb_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i187;
  int32_T c2_i188;
  const mxArray *c2_e_y = NULL;
  int32_T c2_i189;
  real_T c2_e_u[30];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_i187 = 0;
  for (c2_i188 = 0; c2_i188 < 3; c2_i188++) {
    for (c2_i189 = 0; c2_i189 < 10; c2_i189++) {
      c2_e_u[c2_i189 + c2_i187] = (*(real_T (*)[30])c2_inData)[c2_i189 + c2_i187];
    }

    c2_i187 += 10;
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 2, 10, 3),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_eb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[30])
{
  real_T c2_dv28[30];
  int32_T c2_i190;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv28, 1, 0, 0U, 1, 0U, 2, 10,
                3);
  for (c2_i190 = 0; c2_i190 < 30; c2_i190++) {
    c2_e_y[c2_i190] = c2_dv28[c2_i190];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_y_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_B;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[30];
  int32_T c2_i191;
  int32_T c2_i192;
  int32_T c2_i193;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_B = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_eb_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_B), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_B);
  c2_i191 = 0;
  for (c2_i192 = 0; c2_i192 < 3; c2_i192++) {
    for (c2_i193 = 0; c2_i193 < 10; c2_i193++) {
      (*(real_T (*)[30])c2_outData)[c2_i193 + c2_i191] = c2_e_y[c2_i193 +
        c2_i191];
    }

    c2_i191 += 10;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_cb_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i194;
  const mxArray *c2_e_y = NULL;
  real_T c2_e_u[10];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i194 = 0; c2_i194 < 10; c2_i194++) {
    c2_e_u[c2_i194] = (*(real_T (*)[10])c2_inData)[c2_i194];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 2, 1, 10),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_fb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[10])
{
  real_T c2_dv29[10];
  int32_T c2_i195;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv29, 1, 0, 0U, 1, 0U, 2, 1,
                10);
  for (c2_i195 = 0; c2_i195 < 10; c2_i195++) {
    c2_e_y[c2_i195] = c2_dv29[c2_i195];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_ab_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_tspan;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[10];
  int32_T c2_i196;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_tspan = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_fb_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_tspan), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_tspan);
  for (c2_i196 = 0; c2_i196 < 10; c2_i196++) {
    (*(real_T (*)[10])c2_outData)[c2_i196] = c2_e_y[c2_i196];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_db_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i197;
  int32_T c2_i198;
  const mxArray *c2_e_y = NULL;
  int32_T c2_i199;
  real_T c2_e_u[6];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_i197 = 0;
  for (c2_i198 = 0; c2_i198 < 2; c2_i198++) {
    for (c2_i199 = 0; c2_i199 < 3; c2_i199++) {
      c2_e_u[c2_i199 + c2_i197] = (*(real_T (*)[6])c2_inData)[c2_i199 + c2_i197];
    }

    c2_i197 += 3;
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 2, 3, 2),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_gb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[6])
{
  real_T c2_dv30[6];
  int32_T c2_i200;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv30, 1, 0, 0U, 1, 0U, 2, 3,
                2);
  for (c2_i200 = 0; c2_i200 < 6; c2_i200++) {
    c2_e_y[c2_i200] = c2_dv30[c2_i200];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_bb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_e_u;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[6];
  int32_T c2_i201;
  int32_T c2_i202;
  int32_T c2_i203;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_e_u = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_gb_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_e_u), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_e_u);
  c2_i201 = 0;
  for (c2_i202 = 0; c2_i202 < 2; c2_i202++) {
    for (c2_i203 = 0; c2_i203 < 3; c2_i203++) {
      (*(real_T (*)[6])c2_outData)[c2_i203 + c2_i201] = c2_e_y[c2_i203 + c2_i201];
    }

    c2_i201 += 3;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_eb_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i204;
  const mxArray *c2_e_y = NULL;
  real_T c2_e_u[190];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i204 = 0; c2_i204 < 190; c2_i204++) {
    c2_e_u[c2_i204] = (*(real_T (*)[190])c2_inData)[c2_i204];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 1, 190),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_hb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [190])
{
  real_T c2_dv31[190];
  int32_T c2_i205;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv31, 1, 0, 0U, 1, 0U, 1,
                190);
  for (c2_i205 = 0; c2_i205 < 190; c2_i205++) {
    c2_e_y[c2_i205] = c2_dv31[c2_i205];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_cb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_DX;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[190];
  int32_T c2_i206;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_DX = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_hb_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_DX), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_DX);
  for (c2_i206 = 0; c2_i206 < 190; c2_i206++) {
    (*(real_T (*)[190])c2_outData)[c2_i206] = c2_e_y[c2_i206];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_fb_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i207;
  const mxArray *c2_e_y = NULL;
  real_T c2_e_u[32];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i207 = 0; c2_i207 < 32; c2_i207++) {
    c2_e_u[c2_i207] = (*(real_T (*)[32])c2_inData)[c2_i207];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 1, 32), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_gb_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i208;
  const mxArray *c2_e_y = NULL;
  real_T c2_e_u[322];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i208 = 0; c2_i208 < 322; c2_i208++) {
    c2_e_u[c2_i208] = (*(real_T (*)[322])c2_inData)[c2_i208];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 1, 322),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_ib_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [322])
{
  real_T c2_dv32[322];
  int32_T c2_i209;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv32, 1, 0, 0U, 1, 0U, 1,
                322);
  for (c2_i209 = 0; c2_i209 < 322; c2_i209++) {
    c2_e_y[c2_i209] = c2_dv32[c2_i209];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_db_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_hlin;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[322];
  int32_T c2_i210;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_hlin = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_ib_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_hlin), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_hlin);
  for (c2_i210 = 0; c2_i210 < 322; c2_i210++) {
    (*(real_T (*)[322])c2_outData)[c2_i210] = c2_e_y[c2_i210];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_hb_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i211;
  int32_T c2_i212;
  const mxArray *c2_e_y = NULL;
  int32_T c2_i213;
  real_T c2_e_u[10624];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_i211 = 0;
  for (c2_i212 = 0; c2_i212 < 332; c2_i212++) {
    for (c2_i213 = 0; c2_i213 < 32; c2_i213++) {
      c2_e_u[c2_i213 + c2_i211] = (*(real_T (*)[10624])c2_inData)[c2_i213 +
        c2_i211];
    }

    c2_i211 += 32;
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 2, 32, 332),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_jb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [10624])
{
  real_T c2_dv33[10624];
  int32_T c2_i214;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv33, 1, 0, 0U, 1, 0U, 2, 32,
                332);
  for (c2_i214 = 0; c2_i214 < 10624; c2_i214++) {
    c2_e_y[c2_i214] = c2_dv33[c2_i214];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_eb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_Gquad;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[10624];
  int32_T c2_i215;
  int32_T c2_i216;
  int32_T c2_i217;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_b_Gquad = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_jb_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_Gquad), &c2_thisId,
    c2_e_y);
  sf_mex_destroy(&c2_b_Gquad);
  c2_i215 = 0;
  for (c2_i216 = 0; c2_i216 < 332; c2_i216++) {
    for (c2_i217 = 0; c2_i217 < 32; c2_i217++) {
      (*(real_T (*)[10624])c2_outData)[c2_i217 + c2_i215] = c2_e_y[c2_i217 +
        c2_i215];
    }

    c2_i215 += 32;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_ib_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i218;
  int32_T c2_i219;
  const mxArray *c2_e_y = NULL;
  int32_T c2_i220;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_i218 = 0;
  for (c2_i219 = 0; c2_i219 < 332; c2_i219++) {
    for (c2_i220 = 0; c2_i220 < 322; c2_i220++) {
      chartInstance->c2_b_u[c2_i220 + c2_i218] = (*(real_T (*)[106904])c2_inData)
        [c2_i220 + c2_i218];
    }

    c2_i218 += 322;
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", chartInstance->c2_b_u, 0, 0U, 1U, 0U,
    2, 322, 332), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_kb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [106904])
{
  int32_T c2_i221;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), chartInstance->c2_dv34, 1, 0,
                0U, 1, 0U, 2, 322, 332);
  for (c2_i221 = 0; c2_i221 < 106904; c2_i221++) {
    c2_e_y[c2_i221] = chartInstance->c2_dv34[c2_i221];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_fb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_Glin;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_i222;
  int32_T c2_i223;
  int32_T c2_i224;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_b_Glin = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_kb_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_Glin), &c2_thisId,
    chartInstance->c2_b_y);
  sf_mex_destroy(&c2_b_Glin);
  c2_i222 = 0;
  for (c2_i223 = 0; c2_i223 < 332; c2_i223++) {
    for (c2_i224 = 0; c2_i224 < 322; c2_i224++) {
      (*(real_T (*)[106904])c2_outData)[c2_i224 + c2_i222] =
        chartInstance->c2_b_y[c2_i224 + c2_i222];
    }

    c2_i222 += 322;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_jb_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i225;
  int32_T c2_i226;
  const mxArray *c2_e_y = NULL;
  int32_T c2_i227;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_i225 = 0;
  for (c2_i226 = 0; c2_i226 < 332; c2_i226++) {
    for (c2_i227 = 0; c2_i227 < 100; c2_i227++) {
      chartInstance->c2_d_u[c2_i227 + c2_i225] = (*(real_T (*)[33200])c2_inData)
        [c2_i227 + c2_i225];
    }

    c2_i225 += 100;
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", chartInstance->c2_d_u, 0, 0U, 1U, 0U,
    2, 100, 332), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_lb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [33200])
{
  int32_T c2_i228;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), chartInstance->c2_dv35, 1, 0,
                0U, 1, 0U, 2, 100, 332);
  for (c2_i228 = 0; c2_i228 < 33200; c2_i228++) {
    c2_e_y[c2_i228] = chartInstance->c2_dv35[c2_i228];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_gb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_Hev;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_i229;
  int32_T c2_i230;
  int32_T c2_i231;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_b_Hev = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_lb_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_Hev), &c2_thisId,
    chartInstance->c2_d_y);
  sf_mex_destroy(&c2_b_Hev);
  c2_i229 = 0;
  for (c2_i230 = 0; c2_i230 < 332; c2_i230++) {
    for (c2_i231 = 0; c2_i231 < 100; c2_i231++) {
      (*(real_T (*)[33200])c2_outData)[c2_i231 + c2_i229] =
        chartInstance->c2_d_y[c2_i231 + c2_i229];
    }

    c2_i229 += 100;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_kb_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i232;
  const mxArray *c2_e_y = NULL;
  real_T c2_e_u[332];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i232 = 0; c2_i232 < 332; c2_i232++) {
    c2_e_u[c2_i232] = (*(real_T (*)[332])c2_inData)[c2_i232];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 2, 1, 332),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_mb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [332])
{
  real_T c2_dv36[332];
  int32_T c2_i233;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv36, 1, 0, 0U, 1, 0U, 2, 1,
                332);
  for (c2_i233 = 0; c2_i233 < 332; c2_i233++) {
    c2_e_y[c2_i233] = c2_dv36[c2_i233];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_hb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_Hs;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[332];
  int32_T c2_i234;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_Hs = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_mb_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_Hs), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_Hs);
  for (c2_i234 = 0; c2_i234 < 332; c2_i234++) {
    (*(real_T (*)[332])c2_outData)[c2_i234] = c2_e_y[c2_i234];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_lb_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i235;
  int32_T c2_i236;
  const mxArray *c2_e_y = NULL;
  int32_T c2_i237;
  real_T c2_e_u[9960];
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_i235 = 0;
  for (c2_i236 = 0; c2_i236 < 332; c2_i236++) {
    for (c2_i237 = 0; c2_i237 < 30; c2_i237++) {
      c2_e_u[c2_i237 + c2_i235] = (*(real_T (*)[9960])c2_inData)[c2_i237 +
        c2_i235];
    }

    c2_i235 += 30;
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 2, 30, 332),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static void c2_nb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y
  [9960])
{
  real_T c2_dv37[9960];
  int32_T c2_i238;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv37, 1, 0, 0U, 1, 0U, 2, 30,
                332);
  for (c2_i238 = 0; c2_i238 < 9960; c2_i238++) {
    c2_e_y[c2_i238] = c2_dv37[c2_i238];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_ib_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_Hu;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_e_y[9960];
  int32_T c2_i239;
  int32_T c2_i240;
  int32_T c2_i241;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_b_Hu = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_nb_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_Hu), &c2_thisId, c2_e_y);
  sf_mex_destroy(&c2_b_Hu);
  c2_i239 = 0;
  for (c2_i240 = 0; c2_i240 < 332; c2_i240++) {
    for (c2_i241 = 0; c2_i241 < 30; c2_i241++) {
      (*(real_T (*)[9960])c2_outData)[c2_i241 + c2_i239] = c2_e_y[c2_i241 +
        c2_i239];
    }

    c2_i239 += 30;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_gnc2_lib_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  const char * c2_data[4] = {
    "789cc5524b4ec330109d4088600162c51958e18a15dbaa805a09561416201439c994a4f1a78a9d7e5871035870116ec029380f4ed2b4565429c08691c6f69bc9"
    "9bf1f3049cc135183b30feb90de0997dd7f81654b6b3c48ee555dc85fd257e351e4aa171aeaba4a01ca1b648f24450a1878b0942864ab22946656694301c261c",
    "afa405fa8901fcd24aad40912acebd18c3f426e790c56ad506980d4a3d1d58eb711b7a6aabf51cfe90e72c636b9e0b2ac559c13b6be1798d7e5ef93a79c0b0ea"
    "fbd6c2f71bfc023f5c3c925b85992243ba603223f9cc0ff30015d53e8d4245ca45cd4828f9440a14ba0af92313e354331a108d4a139d2534f2cbe32814866244",
    "9d7068eaf236dccbfe2ff656effbf23efef8eafe9dbf9ec77ff3fb2d73396acca5c0f771de61bd408fa3f934edde3d9d9ff2c173afaa776cd57336d4036bffed"
    "f7dfe667609d", "" };

  c2_nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(c2_data, 976U, &c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_linspace(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_d1,
  real_T c2_d2, real_T c2_e_y[10])
{
  real_T c2_d_A;
  real_T c2_x;
  real_T c2_e_A;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_delta1;
  real_T c2_d_x;
  int32_T c2_k;
  real_T c2_f_A;
  real_T c2_e_x;
  real_T c2_b_k;
  real_T c2_f_x;
  real_T c2_delta2;
  int32_T c2_c_k;
  (void)chartInstance;
  c2_e_y[9] = c2_d2;
  c2_e_y[0] = c2_d1;
  if ((c2_d1 < 0.0 != c2_d2 < 0.0) && ((muDoubleScalarAbs(c2_d1) >
        8.9884656743115785E+307) || (muDoubleScalarAbs(c2_d2) >
        8.9884656743115785E+307))) {
    c2_e_A = c2_d1;
    c2_c_x = c2_e_A;
    c2_d_x = c2_c_x;
    c2_delta1 = c2_d_x / 9.0;
    c2_f_A = c2_d2;
    c2_e_x = c2_f_A;
    c2_f_x = c2_e_x;
    c2_delta2 = c2_f_x / 9.0;
    for (c2_c_k = 0; c2_c_k < 8; c2_c_k++) {
      c2_b_k = 1.0 + (real_T)c2_c_k;
      c2_e_y[(int32_T)(c2_b_k + 1.0) - 1] = (c2_d1 + c2_delta2 * c2_b_k) -
        c2_delta1 * c2_b_k;
    }
  } else {
    c2_d_A = c2_d2 - c2_d1;
    c2_x = c2_d_A;
    c2_b_x = c2_x;
    c2_delta1 = c2_b_x / 9.0;
    for (c2_k = 0; c2_k < 8; c2_k++) {
      c2_b_k = 1.0 + (real_T)c2_k;
      c2_e_y[(int32_T)(c2_b_k + 1.0) - 1] = c2_d1 + c2_b_k * c2_delta1;
    }
  }
}

static void c2_foh(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_e_X[100],
                   real_T c2_c_U[30], real_T c2_g_s, real_T c2_b_J[9], real_T
                   c2_d_EH[10000], real_T c2_d_BE[3000], real_T c2_ES[100],
                   real_T c2_AR[100])
{
  uint32_T c2_debug_family_var_map[42];
  real_T c2_len;
  real_T c2_tau[10];
  real_T c2_Nsub;
  real_T c2_A0[100];
  real_T c2_B0p[30];
  real_T c2_B0m[30];
  real_T c2_S0[10];
  real_T c2_R0[10];
  real_T c2_k;
  real_T c2_xF[10];
  real_T c2_P0[190];
  real_T c2_um[3];
  real_T c2_up[3];
  real_T c2_e_u[6];
  real_T c2_tspan[10];
  real_T c2_k_;
  real_T c2_tk;
  real_T c2_tkp1;
  real_T c2_h;
  real_T c2_k1[190];
  real_T c2_k2[190];
  real_T c2_k3[190];
  real_T c2_k4[190];
  real_T c2_AF[100];
  real_T c2_BFp[30];
  real_T c2_BFm[30];
  real_T c2_SF[10];
  real_T c2_RF[10];
  real_T c2_Ad[100];
  real_T c2_N;
  real_T c2_Nx;
  real_T c2_Nu;
  real_T c2_nargin = 7.0;
  real_T c2_nargout = 4.0;
  int32_T c2_i242;
  int32_T c2_i243;
  real_T c2_dv38[100];
  int32_T c2_i244;
  int32_T c2_i245;
  int32_T c2_i246;
  int32_T c2_i247;
  int32_T c2_i248;
  int32_T c2_i249;
  int32_T c2_i250;
  real_T c2_dv39[100];
  int32_T c2_i251;
  int32_T c2_i252;
  int32_T c2_i253;
  int32_T c2_i254;
  int32_T c2_i255;
  int32_T c2_b_k;
  real_T c2_b_Nx;
  int32_T c2_i256;
  int32_T c2_i257;
  int32_T c2_i258;
  int32_T c2_i259;
  int32_T c2_i260;
  int32_T c2_i261;
  int32_T c2_i262;
  real_T c2_b_Nu;
  int32_T c2_i263;
  real_T c2_c_Nu;
  int32_T c2_i264;
  int32_T c2_i265;
  int32_T c2_c_k;
  real_T c2_x[3];
  int32_T c2_i266;
  real_T c2_e_y[3];
  int32_T c2_d_k;
  int32_T c2_i267;
  real_T c2_f_y[3];
  int32_T c2_i268;
  real_T c2_dv40[10];
  int32_T c2_i269;
  int32_T c2_b_k_;
  int32_T c2_i270;
  int32_T c2_i271;
  int32_T c2_i272;
  int32_T c2_i273;
  int32_T c2_i274;
  real_T c2_b_P0[190];
  int32_T c2_i275;
  int32_T c2_i276;
  real_T c2_f_u[6];
  int32_T c2_i277;
  int32_T c2_i278;
  real_T c2_b_tspan[10];
  real_T c2_c_J[9];
  real_T c2_dv41[190];
  int32_T c2_i279;
  int32_T c2_i280;
  int32_T c2_e_k;
  real_T c2_b_x[100];
  real_T c2_d_A;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_c_Nx;
  real_T c2_g_y;
  real_T c2_d_Nx;
  real_T c2_e_A;
  int32_T c2_i281;
  real_T c2_e_x;
  real_T c2_f_x;
  real_T c2_h_y;
  int32_T c2_i282;
  real_T c2_a;
  int32_T c2_i283;
  int32_T c2_i284;
  int32_T c2_f_k;
  real_T c2_g_x[30];
  int32_T c2_i285;
  real_T c2_b[190];
  int32_T c2_i286;
  real_T c2_i_y[30];
  int32_T c2_i287;
  int32_T c2_i288;
  real_T c2_b_a[100];
  int32_T c2_i289;
  real_T c2_c_P0[190];
  real_T c2_e_Nx;
  int32_T c2_i290;
  int32_T c2_i291;
  real_T c2_g_u[6];
  real_T c2_d_Nu;
  int32_T c2_i292;
  int32_T c2_i293;
  int32_T c2_i294;
  real_T c2_c_tspan[10];
  real_T c2_j_y[30];
  int32_T c2_i295;
  int32_T c2_i296;
  int32_T c2_i297;
  int32_T c2_i298;
  real_T c2_d_J[9];
  real_T c2_dv42[190];
  int32_T c2_i299;
  int32_T c2_g_k;
  real_T c2_f_A;
  int32_T c2_i300;
  real_T c2_h_x;
  real_T c2_i_x;
  real_T c2_k_y;
  int32_T c2_i301;
  real_T c2_g_A;
  real_T c2_j_x;
  real_T c2_k_x;
  real_T c2_f_Nx;
  int32_T c2_i302;
  real_T c2_l_y;
  real_T c2_e_Nu;
  int32_T c2_i303;
  real_T c2_c_a;
  int32_T c2_i304;
  int32_T c2_i305;
  int32_T c2_i306;
  int32_T c2_i307;
  int32_T c2_i308;
  int32_T c2_i309;
  int32_T c2_i310;
  int32_T c2_i311;
  int32_T c2_h_k;
  real_T c2_l_x[10];
  int32_T c2_i312;
  real_T c2_d_P0[190];
  int32_T c2_i313;
  real_T c2_m_y[10];
  int32_T c2_i314;
  real_T c2_h_u[6];
  int32_T c2_i315;
  int32_T c2_i316;
  real_T c2_d_tspan[10];
  real_T c2_g_Nx;
  int32_T c2_i317;
  int32_T c2_i318;
  int32_T c2_i319;
  real_T c2_e_J[9];
  real_T c2_dv43[190];
  int32_T c2_i320;
  int32_T c2_i321;
  real_T c2_d_a;
  int32_T c2_i_k;
  int32_T c2_i322;
  int32_T c2_i323;
  int32_T c2_i324;
  int32_T c2_i325;
  int32_T c2_i326;
  real_T c2_h_Nx;
  int32_T c2_i327;
  real_T c2_e_P0[190];
  int32_T c2_i328;
  int32_T c2_i329;
  int32_T c2_i330;
  int32_T c2_i331;
  real_T c2_i_u[6];
  int32_T c2_i332;
  real_T c2_e_tspan[10];
  real_T c2_f_J[9];
  real_T c2_dv44[190];
  int32_T c2_i333;
  real_T c2_h_A;
  real_T c2_m_x;
  real_T c2_n_x;
  real_T c2_n_y;
  int32_T c2_i334;
  int32_T c2_i335;
  int32_T c2_i336;
  int32_T c2_i337;
  real_T c2_b_b[190];
  real_T c2_e_a;
  int32_T c2_i338;
  int32_T c2_i339;
  int32_T c2_i340;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 42U, 42U, c2_f_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_len, 0U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_tau, 1U, c2_cb_sf_marshallOut,
    c2_ab_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Nsub, 2U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_A0, 3U, c2_w_sf_marshallOut,
    c2_u_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_B0p, 4U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_B0m, 5U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_S0, 6U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_R0, 7U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_k, 8U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_xF, 9U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_P0, 10U, c2_eb_sf_marshallOut,
    c2_cb_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_um, 11U, c2_v_sf_marshallOut,
    c2_t_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_up, 12U, c2_v_sf_marshallOut,
    c2_t_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_e_u, 13U, c2_db_sf_marshallOut,
    c2_bb_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_tspan, 14U, c2_cb_sf_marshallOut,
    c2_ab_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_k_, 15U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_tk, 16U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_tkp1, 17U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_h, 18U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_k1, 19U, c2_eb_sf_marshallOut,
    c2_cb_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_k2, 20U, c2_eb_sf_marshallOut,
    c2_cb_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_k3, 21U, c2_eb_sf_marshallOut,
    c2_cb_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_k4, 22U, c2_eb_sf_marshallOut,
    c2_cb_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_AF, 23U, c2_e_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_BFp, 24U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_BFm, 25U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_SF, 26U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_RF, 27U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Ad, 28U, c2_w_sf_marshallOut,
    c2_u_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_N, 29U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Nx, 30U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Nu, 31U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 32U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 33U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_e_X, 34U, c2_e_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_c_U, 35U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_g_s, 36U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_J, 37U, c2_g_sf_marshallOut,
    c2_s_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_d_EH, 38U, c2_t_sf_marshallOut,
    c2_q_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_d_BE, 39U, c2_s_sf_marshallOut,
    c2_p_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_ES, 40U, c2_e_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_AR, 41U, c2_e_sf_marshallOut,
    c2_e_sf_marshallIn);
  c2_Nu = 3.0;
  c2_Nx = 10.0;
  c2_N = 10.0;
  CV_EML_FCN(0, 1);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 129U);
  c2_len = 9.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 130U);
  for (c2_i242 = 0; c2_i242 < 10; c2_i242++) {
    c2_tau[c2_i242] = 0.1111111111111111 * (real_T)c2_i242;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 131U);
  c2_Nsub = 10.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 134U);
  for (c2_i243 = 0; c2_i243 < 10000; c2_i243++) {
    c2_d_EH[c2_i243] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 135U);
  c2_eye(chartInstance, c2_dv38);
  c2_i244 = 0;
  c2_i245 = 0;
  for (c2_i246 = 0; c2_i246 < 10; c2_i246++) {
    for (c2_i247 = 0; c2_i247 < 10; c2_i247++) {
      c2_d_EH[c2_i247 + c2_i244] = c2_dv38[c2_i247 + c2_i245];
    }

    c2_i244 += 100;
    c2_i245 += 10;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 136U);
  for (c2_i248 = 0; c2_i248 < 3000; c2_i248++) {
    c2_d_BE[c2_i248] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 137U);
  for (c2_i249 = 0; c2_i249 < 100; c2_i249++) {
    c2_ES[c2_i249] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 138U);
  for (c2_i250 = 0; c2_i250 < 100; c2_i250++) {
    c2_AR[c2_i250] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 141U);
  c2_eye(chartInstance, c2_dv39);
  for (c2_i251 = 0; c2_i251 < 100; c2_i251++) {
    c2_A0[c2_i251] = c2_dv39[c2_i251];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 142U);
  for (c2_i252 = 0; c2_i252 < 30; c2_i252++) {
    c2_B0p[c2_i252] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 143U);
  for (c2_i253 = 0; c2_i253 < 30; c2_i253++) {
    c2_B0m[c2_i253] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 144U);
  for (c2_i254 = 0; c2_i254 < 10; c2_i254++) {
    c2_S0[c2_i254] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 145U);
  for (c2_i255 = 0; c2_i255 < 10; c2_i255++) {
    c2_R0[c2_i255] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 147U);
  c2_k = 1.0;
  c2_b_k = 0;
  while (c2_b_k < 9) {
    c2_k = 1.0 + (real_T)c2_b_k;
    CV_EML_FOR(0, 1, 1, 1);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 150U);
    c2_b_Nx = c2_Nx * (c2_k - 1.0);
    for (c2_i256 = 0; c2_i256 < 10; c2_i256++) {
      c2_xF[c2_i256] = c2_e_X[sf_eml_array_bounds_check
        (sfGlobalDebugInstanceStruct, chartInstance->S, 1U, 4898, 18,
         MAX_uint32_T, (int32_T)sf_integer_check(chartInstance->S, 1U, 4898U,
          18U, c2_b_Nx + (real_T)(c2_i256 + 1)), 1, 100) - 1];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 151U);
    for (c2_i257 = 0; c2_i257 < 10; c2_i257++) {
      c2_P0[c2_i257] = c2_xF[c2_i257];
    }

    for (c2_i258 = 0; c2_i258 < 100; c2_i258++) {
      c2_P0[c2_i258 + 10] = c2_A0[c2_i258];
    }

    for (c2_i259 = 0; c2_i259 < 30; c2_i259++) {
      c2_P0[c2_i259 + 110] = c2_B0p[c2_i259];
    }

    for (c2_i260 = 0; c2_i260 < 30; c2_i260++) {
      c2_P0[c2_i260 + 140] = c2_B0m[c2_i260];
    }

    for (c2_i261 = 0; c2_i261 < 10; c2_i261++) {
      c2_P0[c2_i261 + 170] = c2_S0[c2_i261];
    }

    for (c2_i262 = 0; c2_i262 < 10; c2_i262++) {
      c2_P0[c2_i262 + 180] = c2_R0[c2_i262];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 153U);
    c2_b_Nu = c2_Nu * (c2_k - 1.0);
    for (c2_i263 = 0; c2_i263 < 3; c2_i263++) {
      c2_um[c2_i263] = c2_c_U[sf_eml_array_bounds_check
        (sfGlobalDebugInstanceStruct, chartInstance->S, 1U, 4987, 18,
         MAX_uint32_T, (int32_T)sf_integer_check(chartInstance->S, 1U, 4987U,
          18U, c2_b_Nu + (real_T)(c2_i263 + 1)), 1, 30) - 1];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 154U);
    c2_c_Nu = c2_Nu * c2_k;
    for (c2_i264 = 0; c2_i264 < 3; c2_i264++) {
      c2_up[c2_i264] = c2_c_U[sf_eml_array_bounds_check
        (sfGlobalDebugInstanceStruct, chartInstance->S, 1U, 5016, 14,
         MAX_uint32_T, (int32_T)sf_integer_check(chartInstance->S, 1U, 5016U,
          14U, c2_c_Nu + (real_T)(c2_i264 + 1)), 1, 30) - 1];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 155U);
    for (c2_i265 = 0; c2_i265 < 3; c2_i265++) {
      c2_x[c2_i265] = c2_um[c2_i265];
    }

    for (c2_c_k = 0; c2_c_k + 1 < 4; c2_c_k++) {
      c2_e_y[c2_c_k] = c2_x[c2_c_k];
    }

    for (c2_i266 = 0; c2_i266 < 3; c2_i266++) {
      c2_x[c2_i266] = c2_up[c2_i266];
    }

    for (c2_d_k = 0; c2_d_k + 1 < 4; c2_d_k++) {
      c2_f_y[c2_d_k] = c2_x[c2_d_k];
    }

    for (c2_i267 = 0; c2_i267 < 3; c2_i267++) {
      c2_e_u[c2_i267] = c2_e_y[c2_i267];
    }

    for (c2_i268 = 0; c2_i268 < 3; c2_i268++) {
      c2_e_u[c2_i268 + 3] = c2_f_y[c2_i268];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 156U);
    c2_linspace(chartInstance, c2_tau[sf_eml_array_bounds_check
                (sfGlobalDebugInstanceStruct, chartInstance->S, 1U, 5099, 6,
                 MAX_uint32_T, (int32_T)sf_integer_check(chartInstance->S, 1U,
      5099U, 6U, c2_k), 1, 10) - 1], c2_tau[sf_eml_array_bounds_check
                (sfGlobalDebugInstanceStruct, chartInstance->S, 1U, 5107, 8,
                 MAX_uint32_T, (int32_T)sf_integer_check(chartInstance->S, 1U,
      5107U, 8U, c2_k + 1.0), 1, 10) - 1], c2_dv40);
    for (c2_i269 = 0; c2_i269 < 10; c2_i269++) {
      c2_tspan[c2_i269] = c2_dv40[c2_i269];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 158U);
    c2_k_ = 1.0;
    c2_b_k_ = 0;
    while (c2_b_k_ < 9) {
      c2_k_ = 1.0 + (real_T)c2_b_k_;
      CV_EML_FOR(0, 1, 2, 1);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 160U);
      c2_tk = c2_tspan[sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
        chartInstance->S, 1U, 5175, 9, MAX_uint32_T, (int32_T)sf_integer_check
        (chartInstance->S, 1U, 5175U, 9U, c2_k_), 1, 10) - 1];
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 161U);
      c2_tkp1 = c2_tspan[sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
        chartInstance->S, 1U, 5204, 11, MAX_uint32_T, (int32_T)sf_integer_check
        (chartInstance->S, 1U, 5204U, 11U, c2_k_ + 1.0), 1, 10) - 1];
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 162U);
      c2_h = c2_tkp1 - c2_tk;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 164U);
      for (c2_i272 = 0; c2_i272 < 190; c2_i272++) {
        c2_b_P0[c2_i272] = c2_P0[c2_i272];
      }

      for (c2_i274 = 0; c2_i274 < 6; c2_i274++) {
        c2_f_u[c2_i274] = c2_e_u[c2_i274];
      }

      for (c2_i276 = 0; c2_i276 < 10; c2_i276++) {
        c2_b_tspan[c2_i276] = c2_tspan[c2_i276];
      }

      for (c2_i278 = 0; c2_i278 < 9; c2_i278++) {
        c2_c_J[c2_i278] = c2_b_J[c2_i278];
      }

      c2_deriv(chartInstance, c2_tk, c2_b_P0, c2_f_u, c2_b_tspan, c2_g_s, c2_c_J,
               c2_dv41);
      for (c2_i280 = 0; c2_i280 < 190; c2_i280++) {
        c2_k1[c2_i280] = c2_dv41[c2_i280];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 165U);
      c2_d_A = c2_h;
      c2_c_x = c2_d_A;
      c2_d_x = c2_c_x;
      c2_g_y = c2_d_x / 2.0;
      c2_e_A = c2_h;
      c2_e_x = c2_e_A;
      c2_f_x = c2_e_x;
      c2_h_y = c2_f_x / 2.0;
      c2_a = c2_h_y;
      for (c2_i284 = 0; c2_i284 < 190; c2_i284++) {
        c2_b[c2_i284] = c2_k1[c2_i284];
      }

      for (c2_i285 = 0; c2_i285 < 190; c2_i285++) {
        c2_b[c2_i285] *= c2_a;
      }

      for (c2_i287 = 0; c2_i287 < 190; c2_i287++) {
        c2_c_P0[c2_i287] = c2_P0[c2_i287] + c2_b[c2_i287];
      }

      for (c2_i289 = 0; c2_i289 < 6; c2_i289++) {
        c2_g_u[c2_i289] = c2_e_u[c2_i289];
      }

      for (c2_i291 = 0; c2_i291 < 10; c2_i291++) {
        c2_c_tspan[c2_i291] = c2_tspan[c2_i291];
      }

      for (c2_i294 = 0; c2_i294 < 9; c2_i294++) {
        c2_d_J[c2_i294] = c2_b_J[c2_i294];
      }

      c2_deriv(chartInstance, c2_tk + c2_g_y, c2_c_P0, c2_g_u, c2_c_tspan,
               c2_g_s, c2_d_J, c2_dv42);
      for (c2_i299 = 0; c2_i299 < 190; c2_i299++) {
        c2_k2[c2_i299] = c2_dv42[c2_i299];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 166U);
      c2_f_A = c2_h;
      c2_h_x = c2_f_A;
      c2_i_x = c2_h_x;
      c2_k_y = c2_i_x / 2.0;
      c2_g_A = c2_h;
      c2_j_x = c2_g_A;
      c2_k_x = c2_j_x;
      c2_l_y = c2_k_x / 2.0;
      c2_c_a = c2_l_y;
      for (c2_i305 = 0; c2_i305 < 190; c2_i305++) {
        c2_b[c2_i305] = c2_k2[c2_i305];
      }

      for (c2_i308 = 0; c2_i308 < 190; c2_i308++) {
        c2_b[c2_i308] *= c2_c_a;
      }

      for (c2_i311 = 0; c2_i311 < 190; c2_i311++) {
        c2_d_P0[c2_i311] = c2_P0[c2_i311] + c2_b[c2_i311];
      }

      for (c2_i312 = 0; c2_i312 < 6; c2_i312++) {
        c2_h_u[c2_i312] = c2_e_u[c2_i312];
      }

      for (c2_i314 = 0; c2_i314 < 10; c2_i314++) {
        c2_d_tspan[c2_i314] = c2_tspan[c2_i314];
      }

      for (c2_i316 = 0; c2_i316 < 9; c2_i316++) {
        c2_e_J[c2_i316] = c2_b_J[c2_i316];
      }

      c2_deriv(chartInstance, c2_tk + c2_k_y, c2_d_P0, c2_h_u, c2_d_tspan,
               c2_g_s, c2_e_J, c2_dv43);
      for (c2_i320 = 0; c2_i320 < 190; c2_i320++) {
        c2_k3[c2_i320] = c2_dv43[c2_i320];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 167U);
      c2_d_a = c2_h;
      for (c2_i322 = 0; c2_i322 < 190; c2_i322++) {
        c2_b[c2_i322] = c2_k3[c2_i322];
      }

      for (c2_i324 = 0; c2_i324 < 190; c2_i324++) {
        c2_b[c2_i324] *= c2_d_a;
      }

      for (c2_i326 = 0; c2_i326 < 190; c2_i326++) {
        c2_e_P0[c2_i326] = c2_P0[c2_i326] + c2_b[c2_i326];
      }

      for (c2_i327 = 0; c2_i327 < 6; c2_i327++) {
        c2_i_u[c2_i327] = c2_e_u[c2_i327];
      }

      for (c2_i331 = 0; c2_i331 < 10; c2_i331++) {
        c2_e_tspan[c2_i331] = c2_tspan[c2_i331];
      }

      for (c2_i332 = 0; c2_i332 < 9; c2_i332++) {
        c2_f_J[c2_i332] = c2_b_J[c2_i332];
      }

      c2_deriv(chartInstance, c2_tk + c2_h, c2_e_P0, c2_i_u, c2_e_tspan, c2_g_s,
               c2_f_J, c2_dv44);
      for (c2_i333 = 0; c2_i333 < 190; c2_i333++) {
        c2_k4[c2_i333] = c2_dv44[c2_i333];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 169U);
      c2_h_A = c2_h;
      c2_m_x = c2_h_A;
      c2_n_x = c2_m_x;
      c2_n_y = c2_n_x / 6.0;
      for (c2_i334 = 0; c2_i334 < 190; c2_i334++) {
        c2_b[c2_i334] = c2_k2[c2_i334];
      }

      for (c2_i335 = 0; c2_i335 < 190; c2_i335++) {
        c2_b[c2_i335] *= 2.0;
      }

      for (c2_i336 = 0; c2_i336 < 190; c2_i336++) {
        c2_b_b[c2_i336] = c2_k3[c2_i336];
      }

      for (c2_i337 = 0; c2_i337 < 190; c2_i337++) {
        c2_b_b[c2_i337] *= 2.0;
      }

      c2_e_a = c2_n_y;
      for (c2_i338 = 0; c2_i338 < 190; c2_i338++) {
        c2_b[c2_i338] = ((c2_k1[c2_i338] + c2_b[c2_i338]) + c2_b_b[c2_i338]) +
          c2_k4[c2_i338];
      }

      for (c2_i339 = 0; c2_i339 < 190; c2_i339++) {
        c2_b[c2_i339] *= c2_e_a;
      }

      for (c2_i340 = 0; c2_i340 < 190; c2_i340++) {
        c2_P0[c2_i340] += c2_b[c2_i340];
      }

      c2_b_k_++;
      _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 2, 0);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 172U);
    for (c2_i270 = 0; c2_i270 < 100; c2_i270++) {
      c2_AF[c2_i270] = c2_P0[c2_i270 + 10];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 173U);
    for (c2_i271 = 0; c2_i271 < 30; c2_i271++) {
      c2_BFp[c2_i271] = c2_P0[c2_i271 + 110];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 174U);
    for (c2_i273 = 0; c2_i273 < 30; c2_i273++) {
      c2_BFm[c2_i273] = c2_P0[c2_i273 + 140];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 175U);
    for (c2_i275 = 0; c2_i275 < 10; c2_i275++) {
      c2_SF[c2_i275] = c2_P0[c2_i275 + 170];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 176U);
    for (c2_i277 = 0; c2_i277 < 10; c2_i277++) {
      c2_RF[c2_i277] = c2_P0[c2_i277 + 180];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 179U);
    for (c2_i279 = 0; c2_i279 < 100; c2_i279++) {
      c2_b_x[c2_i279] = c2_AF[c2_i279];
    }

    for (c2_e_k = 0; c2_e_k + 1 < 101; c2_e_k++) {
      c2_Ad[c2_e_k] = c2_b_x[c2_e_k];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 180U);
    c2_c_Nx = c2_Nx * c2_k;
    c2_d_Nx = c2_Nx * (c2_k - 1.0);
    for (c2_i281 = 0; c2_i281 < 10; c2_i281++) {
      for (c2_i282 = 0; c2_i282 < 10; c2_i282++) {
        c2_d_EH[(sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
                  chartInstance->S, 1U, 5789, 11, MAX_uint32_T, (int32_T)
                  sf_integer_check(chartInstance->S, 1U, 5789U, 11U, c2_c_Nx +
                   (real_T)(c2_i282 + 1)), 1, 100) + 100 *
                 (sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
                   chartInstance->S, 1U, 5801, 15, MAX_uint32_T, (int32_T)
                   sf_integer_check(chartInstance->S, 1U, 5801U, 15U, c2_d_Nx +
                    (real_T)(c2_i281 + 1)), 1, 100) - 1)) - 1] = c2_Ad[c2_i282 +
          10 * c2_i281];
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 181U);
    for (c2_i283 = 0; c2_i283 < 30; c2_i283++) {
      c2_g_x[c2_i283] = c2_BFm[c2_i283];
    }

    for (c2_f_k = 0; c2_f_k + 1 < 31; c2_f_k++) {
      c2_i_y[c2_f_k] = c2_g_x[c2_f_k];
    }

    for (c2_i286 = 0; c2_i286 < 100; c2_i286++) {
      c2_b_a[c2_i286] = c2_Ad[c2_i286];
    }

    for (c2_i288 = 0; c2_i288 < 10; c2_i288++) {
      c2_i290 = 0;
      for (c2_i292 = 0; c2_i292 < 3; c2_i292++) {
        c2_j_y[c2_i290 + c2_i288] = 0.0;
        c2_i296 = 0;
        for (c2_i298 = 0; c2_i298 < 10; c2_i298++) {
          c2_j_y[c2_i290 + c2_i288] += c2_b_a[c2_i296 + c2_i288] *
            c2_i_y[c2_i298 + c2_i290];
          c2_i296 += 10;
        }

        c2_i290 += 10;
      }
    }

    c2_e_Nx = c2_Nx * c2_k;
    c2_d_Nu = c2_Nu * (c2_k - 1.0);
    for (c2_i293 = 0; c2_i293 < 3; c2_i293++) {
      for (c2_i295 = 0; c2_i295 < 10; c2_i295++) {
        c2_d_BE[(sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
                  chartInstance->S, 1U, 5831, 11, MAX_uint32_T, (int32_T)
                  sf_integer_check(chartInstance->S, 1U, 5831U, 11U, c2_e_Nx +
                   (real_T)(c2_i295 + 1)), 1, 100) + 100 *
                 (sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
                   chartInstance->S, 1U, 5843, 15, MAX_uint32_T, (int32_T)
                   sf_integer_check(chartInstance->S, 1U, 5843U, 15U, c2_d_Nu +
                    (real_T)(c2_i293 + 1)), 1, 30) - 1)) - 1] = c2_j_y[c2_i295 +
          10 * c2_i293];
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 182U);
    for (c2_i297 = 0; c2_i297 < 30; c2_i297++) {
      c2_g_x[c2_i297] = c2_BFp[c2_i297];
    }

    for (c2_g_k = 0; c2_g_k + 1 < 31; c2_g_k++) {
      c2_i_y[c2_g_k] = c2_g_x[c2_g_k];
    }

    for (c2_i300 = 0; c2_i300 < 100; c2_i300++) {
      c2_b_a[c2_i300] = c2_Ad[c2_i300];
    }

    for (c2_i301 = 0; c2_i301 < 10; c2_i301++) {
      c2_i302 = 0;
      for (c2_i303 = 0; c2_i303 < 3; c2_i303++) {
        c2_j_y[c2_i302 + c2_i301] = 0.0;
        c2_i307 = 0;
        for (c2_i310 = 0; c2_i310 < 10; c2_i310++) {
          c2_j_y[c2_i302 + c2_i301] += c2_b_a[c2_i307 + c2_i301] *
            c2_i_y[c2_i310 + c2_i302];
          c2_i307 += 10;
        }

        c2_i302 += 10;
      }
    }

    c2_f_Nx = c2_Nx * c2_k;
    c2_e_Nu = c2_Nu * c2_k;
    for (c2_i304 = 0; c2_i304 < 3; c2_i304++) {
      for (c2_i306 = 0; c2_i306 < 10; c2_i306++) {
        c2_d_BE[(sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
                  chartInstance->S, 1U, 5892, 11, MAX_uint32_T, (int32_T)
                  sf_integer_check(chartInstance->S, 1U, 5892U, 11U, c2_f_Nx +
                   (real_T)(c2_i306 + 1)), 1, 100) + 100 *
                 (sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
                   chartInstance->S, 1U, 5904, 11, MAX_uint32_T, (int32_T)
                   sf_integer_check(chartInstance->S, 1U, 5904U, 11U, c2_e_Nu +
                    (real_T)(c2_i304 + 1)), 1, 30) - 1)) - 1] = c2_j_y[c2_i306 +
          10 * c2_i304];
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 183U);
    for (c2_i309 = 0; c2_i309 < 10; c2_i309++) {
      c2_l_x[c2_i309] = c2_SF[c2_i309];
    }

    for (c2_h_k = 0; c2_h_k + 1 < 11; c2_h_k++) {
      c2_m_y[c2_h_k] = c2_l_x[c2_h_k];
    }

    for (c2_i313 = 0; c2_i313 < 100; c2_i313++) {
      c2_b_a[c2_i313] = c2_Ad[c2_i313];
    }

    for (c2_i315 = 0; c2_i315 < 10; c2_i315++) {
      c2_l_x[c2_i315] = 0.0;
      c2_i318 = 0;
      for (c2_i319 = 0; c2_i319 < 10; c2_i319++) {
        c2_l_x[c2_i315] += c2_b_a[c2_i318 + c2_i315] * c2_m_y[c2_i319];
        c2_i318 += 10;
      }
    }

    c2_g_Nx = c2_Nx * c2_k;
    for (c2_i317 = 0; c2_i317 < 10; c2_i317++) {
      c2_ES[sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
        chartInstance->S, 1U, 5950, 15, MAX_uint32_T, (int32_T)sf_integer_check
        (chartInstance->S, 1U, 5950U, 15U, c2_g_Nx + (real_T)(c2_i317 + 1)), 1,
        100) - 1] = c2_l_x[c2_i317];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 184U);
    for (c2_i321 = 0; c2_i321 < 10; c2_i321++) {
      c2_l_x[c2_i321] = c2_RF[c2_i321];
    }

    for (c2_i_k = 0; c2_i_k + 1 < 11; c2_i_k++) {
      c2_m_y[c2_i_k] = c2_l_x[c2_i_k];
    }

    for (c2_i323 = 0; c2_i323 < 100; c2_i323++) {
      c2_b_a[c2_i323] = c2_Ad[c2_i323];
    }

    for (c2_i325 = 0; c2_i325 < 10; c2_i325++) {
      c2_l_x[c2_i325] = 0.0;
      c2_i329 = 0;
      for (c2_i330 = 0; c2_i330 < 10; c2_i330++) {
        c2_l_x[c2_i325] += c2_b_a[c2_i329 + c2_i325] * c2_m_y[c2_i330];
        c2_i329 += 10;
      }
    }

    c2_h_Nx = c2_Nx * c2_k;
    for (c2_i328 = 0; c2_i328 < 10; c2_i328++) {
      c2_AR[sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
        chartInstance->S, 1U, 6009, 15, MAX_uint32_T, (int32_T)sf_integer_check
        (chartInstance->S, 1U, 6009U, 15U, c2_h_Nx + (real_T)(c2_i328 + 1)), 1,
        100) - 1] = c2_l_x[c2_i328];
    }

    c2_b_k++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 1, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -184);
  _SFD_SYMBOL_SCOPE_POP();
}

static void c2_eye(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_I[100])
{
  int32_T c2_i341;
  int32_T c2_k;
  (void)chartInstance;
  for (c2_i341 = 0; c2_i341 < 100; c2_i341++) {
    c2_I[c2_i341] = 0.0;
  }

  for (c2_k = 0; c2_k + 1 < 11; c2_k++) {
    c2_I[c2_k + 10 * c2_k] = 1.0;
  }
}

static void c2_deriv(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_t,
                     real_T c2_e_X[190], real_T c2_e_u[6], real_T c2_tspan[10],
                     real_T c2_g_s, real_T c2_b_J[9], real_T c2_DX[190])
{
  uint32_T c2_debug_family_var_map[23];
  real_T c2_Nx;
  real_T c2_x[10];
  real_T c2_f[10];
  real_T c2_d_A[100];
  real_T c2_Bp[30];
  real_T c2_Bm[30];
  real_T c2_Z[10];
  real_T c2_Phi[100];
  real_T c2_xdot[10];
  real_T c2_Phi_dot[100];
  real_T c2_Bdp_dot[30];
  real_T c2_Bdm_dot[30];
  real_T c2_Sd_dot[10];
  real_T c2_Zd_dot[10];
  real_T c2_nargin = 6.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i342;
  int32_T c2_i343;
  int32_T c2_i344;
  real_T c2_b_x[10];
  int32_T c2_i345;
  real_T c2_f_u[6];
  int32_T c2_i346;
  real_T c2_b_tspan[10];
  real_T c2_c_J[9];
  real_T c2_b_f[10];
  real_T c2_e_A[100];
  real_T c2_b_Bp[30];
  real_T c2_b_Bm[30];
  real_T c2_b_Z[10];
  int32_T c2_i347;
  int32_T c2_i348;
  int32_T c2_i349;
  int32_T c2_i350;
  int32_T c2_i351;
  int32_T c2_i352;
  int32_T c2_k;
  real_T c2_c_x[100];
  real_T c2_a;
  int32_T c2_i353;
  int32_T c2_i354;
  real_T c2_b_a;
  int32_T c2_i355;
  int32_T c2_i356;
  int32_T c2_i357;
  int32_T c2_i358;
  real_T c2_b[100];
  real_T c2_alpha1;
  real_T c2_beta1;
  int32_T c2_i359;
  char_T c2_TRANSB;
  real_T c2_C[100];
  char_T c2_TRANSA;
  int32_T c2_i360;
  ptrdiff_t c2_m_t;
  ptrdiff_t c2_n_t;
  ptrdiff_t c2_k_t;
  ptrdiff_t c2_lda_t;
  ptrdiff_t c2_ldb_t;
  ptrdiff_t c2_ldc_t;
  real_T c2_c_a;
  int32_T c2_i361;
  int32_T c2_i362;
  int32_T c2_i363;
  real_T c2_b_Phi[100];
  real_T c2_dv45[30];
  int32_T c2_i364;
  real_T c2_d_a;
  int32_T c2_i365;
  int32_T c2_i366;
  int32_T c2_i367;
  real_T c2_c_Phi[100];
  real_T c2_dv46[30];
  int32_T c2_i368;
  int32_T c2_i369;
  int32_T c2_i370;
  real_T c2_d_Phi[100];
  real_T c2_c_f[10];
  real_T c2_dv47[10];
  int32_T c2_i371;
  real_T c2_e_a;
  int32_T c2_i372;
  int32_T c2_i373;
  int32_T c2_i374;
  real_T c2_e_Phi[100];
  real_T c2_dv48[10];
  int32_T c2_i375;
  int32_T c2_i376;
  int32_T c2_i377;
  int32_T c2_i378;
  int32_T c2_i379;
  int32_T c2_i380;
  int32_T c2_i381;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 23U, 23U, c2_e_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Nx, 0U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_x, 1U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_f, 2U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_d_A, 3U, c2_w_sf_marshallOut,
    c2_u_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Bp, 4U, c2_bb_sf_marshallOut,
    c2_y_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Bm, 5U, c2_bb_sf_marshallOut,
    c2_y_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Z, 6U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Phi, 7U, c2_w_sf_marshallOut,
    c2_u_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_xdot, 8U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Phi_dot, 9U, c2_w_sf_marshallOut,
    c2_u_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Bdp_dot, 10U, c2_bb_sf_marshallOut,
    c2_y_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Bdm_dot, 11U, c2_bb_sf_marshallOut,
    c2_y_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Sd_dot, 12U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Zd_dot, 13U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 14U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 15U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_t, 16U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_e_X, 17U, c2_eb_sf_marshallOut,
    c2_cb_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_e_u, 18U, c2_db_sf_marshallOut,
    c2_bb_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_tspan, 19U, c2_cb_sf_marshallOut,
    c2_ab_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_g_s, 20U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_J, 21U, c2_g_sf_marshallOut,
    c2_s_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_DX, 22U, c2_eb_sf_marshallOut,
    c2_cb_sf_marshallIn);
  CV_EML_FCN(0, 2);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 192U);
  c2_Nx = 10.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 193U);
  for (c2_i342 = 0; c2_i342 < 10; c2_i342++) {
    c2_x[c2_i342] = c2_e_X[c2_i342];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 195U);
  for (c2_i343 = 0; c2_i343 < 10; c2_i343++) {
    c2_b_x[c2_i343] = c2_x[c2_i343];
  }

  for (c2_i344 = 0; c2_i344 < 6; c2_i344++) {
    c2_f_u[c2_i344] = c2_e_u[c2_i344];
  }

  for (c2_i345 = 0; c2_i345 < 10; c2_i345++) {
    c2_b_tspan[c2_i345] = c2_tspan[c2_i345];
  }

  for (c2_i346 = 0; c2_i346 < 9; c2_i346++) {
    c2_c_J[c2_i346] = c2_b_J[c2_i346];
  }

  c2_get_f_vals(chartInstance, c2_t, c2_b_x, c2_f_u, c2_b_tspan, c2_c_J, c2_b_f,
                c2_e_A, c2_b_Bp, c2_b_Bm, c2_b_Z);
  for (c2_i347 = 0; c2_i347 < 10; c2_i347++) {
    c2_f[c2_i347] = c2_b_f[c2_i347];
  }

  for (c2_i348 = 0; c2_i348 < 100; c2_i348++) {
    c2_d_A[c2_i348] = c2_e_A[c2_i348];
  }

  for (c2_i349 = 0; c2_i349 < 30; c2_i349++) {
    c2_Bp[c2_i349] = c2_b_Bp[c2_i349];
  }

  for (c2_i350 = 0; c2_i350 < 30; c2_i350++) {
    c2_Bm[c2_i350] = c2_b_Bm[c2_i350];
  }

  for (c2_i351 = 0; c2_i351 < 10; c2_i351++) {
    c2_Z[c2_i351] = c2_b_Z[c2_i351];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 197U);
  for (c2_i352 = 0; c2_i352 < 100; c2_i352++) {
    c2_c_x[c2_i352] = c2_e_X[c2_i352 + 10];
  }

  for (c2_k = 0; c2_k + 1 < 101; c2_k++) {
    c2_Phi[c2_k] = c2_c_x[c2_k];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 199U);
  c2_a = c2_g_s;
  for (c2_i353 = 0; c2_i353 < 10; c2_i353++) {
    c2_b_f[c2_i353] = c2_f[c2_i353];
  }

  for (c2_i354 = 0; c2_i354 < 10; c2_i354++) {
    c2_xdot[c2_i354] = c2_a * c2_b_f[c2_i354];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 200U);
  c2_b_a = c2_g_s;
  for (c2_i355 = 0; c2_i355 < 100; c2_i355++) {
    c2_e_A[c2_i355] = c2_d_A[c2_i355];
  }

  for (c2_i356 = 0; c2_i356 < 100; c2_i356++) {
    c2_e_A[c2_i356] *= c2_b_a;
  }

  for (c2_i357 = 0; c2_i357 < 100; c2_i357++) {
    c2_b[c2_i357] = c2_Phi[c2_i357];
  }

  for (c2_i358 = 0; c2_i358 < 100; c2_i358++) {
    c2_Phi_dot[c2_i358] = 0.0;
  }

  c2_alpha1 = 1.0;
  c2_beta1 = 0.0;
  for (c2_i359 = 0; c2_i359 < 100; c2_i359++) {
    c2_C[c2_i359] = c2_Phi_dot[c2_i359];
  }

  c2_TRANSB = 'N';
  c2_TRANSA = 'N';
  for (c2_i360 = 0; c2_i360 < 100; c2_i360++) {
    c2_Phi_dot[c2_i360] = c2_C[c2_i360];
  }

  c2_m_t = (ptrdiff_t)10;
  c2_n_t = (ptrdiff_t)10;
  c2_k_t = (ptrdiff_t)10;
  c2_lda_t = (ptrdiff_t)10;
  c2_ldb_t = (ptrdiff_t)10;
  c2_ldc_t = (ptrdiff_t)10;
  dgemm(&c2_TRANSA, &c2_TRANSB, &c2_m_t, &c2_n_t, &c2_k_t, &c2_alpha1, &c2_e_A[0],
        &c2_lda_t, &c2_b[0], &c2_ldb_t, &c2_beta1, &c2_Phi_dot[0], &c2_ldc_t);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 201U);
  c2_c_a = c2_g_s;
  for (c2_i361 = 0; c2_i361 < 30; c2_i361++) {
    c2_b_Bp[c2_i361] = c2_Bp[c2_i361];
  }

  for (c2_i362 = 0; c2_i362 < 30; c2_i362++) {
    c2_b_Bp[c2_i362] *= c2_c_a;
  }

  for (c2_i363 = 0; c2_i363 < 100; c2_i363++) {
    c2_b_Phi[c2_i363] = c2_Phi[c2_i363];
  }

  c2_mldivide(chartInstance, c2_b_Phi, c2_b_Bp, c2_dv45);
  for (c2_i364 = 0; c2_i364 < 30; c2_i364++) {
    c2_Bdp_dot[c2_i364] = c2_dv45[c2_i364];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 202U);
  c2_d_a = c2_g_s;
  for (c2_i365 = 0; c2_i365 < 30; c2_i365++) {
    c2_b_Bp[c2_i365] = c2_Bm[c2_i365];
  }

  for (c2_i366 = 0; c2_i366 < 30; c2_i366++) {
    c2_b_Bp[c2_i366] *= c2_d_a;
  }

  for (c2_i367 = 0; c2_i367 < 100; c2_i367++) {
    c2_c_Phi[c2_i367] = c2_Phi[c2_i367];
  }

  c2_mldivide(chartInstance, c2_c_Phi, c2_b_Bp, c2_dv46);
  for (c2_i368 = 0; c2_i368 < 30; c2_i368++) {
    c2_Bdm_dot[c2_i368] = c2_dv46[c2_i368];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 203U);
  for (c2_i369 = 0; c2_i369 < 100; c2_i369++) {
    c2_d_Phi[c2_i369] = c2_Phi[c2_i369];
  }

  for (c2_i370 = 0; c2_i370 < 10; c2_i370++) {
    c2_c_f[c2_i370] = c2_f[c2_i370];
  }

  c2_b_mldivide(chartInstance, c2_d_Phi, c2_c_f, c2_dv47);
  for (c2_i371 = 0; c2_i371 < 10; c2_i371++) {
    c2_Sd_dot[c2_i371] = c2_dv47[c2_i371];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 204U);
  c2_e_a = c2_g_s;
  for (c2_i372 = 0; c2_i372 < 10; c2_i372++) {
    c2_b_f[c2_i372] = c2_Z[c2_i372];
  }

  for (c2_i373 = 0; c2_i373 < 10; c2_i373++) {
    c2_b_f[c2_i373] *= c2_e_a;
  }

  for (c2_i374 = 0; c2_i374 < 100; c2_i374++) {
    c2_e_Phi[c2_i374] = c2_Phi[c2_i374];
  }

  c2_b_mldivide(chartInstance, c2_e_Phi, c2_b_f, c2_dv48);
  for (c2_i375 = 0; c2_i375 < 10; c2_i375++) {
    c2_Zd_dot[c2_i375] = c2_dv48[c2_i375];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 206U);
  for (c2_i376 = 0; c2_i376 < 10; c2_i376++) {
    c2_DX[c2_i376] = c2_xdot[c2_i376];
  }

  for (c2_i377 = 0; c2_i377 < 100; c2_i377++) {
    c2_DX[c2_i377 + 10] = c2_Phi_dot[c2_i377];
  }

  for (c2_i378 = 0; c2_i378 < 30; c2_i378++) {
    c2_DX[c2_i378 + 110] = c2_Bdp_dot[c2_i378];
  }

  for (c2_i379 = 0; c2_i379 < 30; c2_i379++) {
    c2_DX[c2_i379 + 140] = c2_Bdm_dot[c2_i379];
  }

  for (c2_i380 = 0; c2_i380 < 10; c2_i380++) {
    c2_DX[c2_i380 + 170] = c2_Sd_dot[c2_i380];
  }

  for (c2_i381 = 0; c2_i381 < 10; c2_i381++) {
    c2_DX[c2_i381 + 180] = c2_Zd_dot[c2_i381];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -206);
  _SFD_SYMBOL_SCOPE_POP();
}

static void c2_get_f_vals(SFc2_gnc2_libInstanceStruct *chartInstance, real_T
  c2_t, real_T c2_x[10], real_T c2_e_u[6], real_T c2_tspan[10], real_T c2_b_J[9],
  real_T c2_f[10], real_T c2_d_A[100], real_T c2_Bp[30], real_T c2_Bm[30],
  real_T c2_Z[10])
{
  uint32_T c2_debug_family_var_map[18];
  real_T c2_tkm;
  real_T c2_tkp;
  real_T c2_lam_km;
  real_T c2_lam_kp;
  real_T c2_u_tau[3];
  real_T c2_B[30];
  real_T c2_nargin = 5.0;
  real_T c2_nargout = 5.0;
  real_T c2_e_A;
  real_T c2_b_B;
  real_T c2_b_x;
  real_T c2_e_y;
  real_T c2_c_x;
  real_T c2_f_y;
  real_T c2_f_A;
  real_T c2_c_B;
  real_T c2_d_x;
  real_T c2_g_y;
  real_T c2_e_x;
  real_T c2_h_y;
  int32_T c2_i382;
  int32_T c2_i383;
  int32_T c2_i384;
  real_T c2_f_x[10];
  int32_T c2_i385;
  real_T c2_b_u_tau[3];
  real_T c2_c_J[9];
  real_T c2_g_A[100];
  real_T c2_b_f[10];
  int32_T c2_i386;
  int32_T c2_i387;
  int32_T c2_i388;
  static real_T c2_b[30] = { 0.0, 0.0, 0.0, 0.0, -1.0, -0.0, -0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, -0.0, -1.0, -0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    -0.0, -0.0, -1.0, 0.0, 0.0, 1.0 };

  real_T c2_a;
  int32_T c2_i389;
  real_T c2_b_a;
  int32_T c2_i390;
  int32_T c2_i391;
  int32_T c2_i392;
  int32_T c2_i393;
  int32_T c2_i394;
  real_T c2_i_y[10];
  int32_T c2_i395;
  int32_T c2_i396;
  int32_T c2_i397;
  real_T c2_b_b[3];
  int32_T c2_i398;
  int32_T c2_i399;
  int32_T c2_i400;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 18U, 18U, c2_d_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_tkm, 0U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_tkp, 1U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_lam_km, 2U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_lam_kp, 3U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_u_tau, 4U, c2_v_sf_marshallOut,
    c2_t_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_B, 5U, c2_bb_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 6U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 7U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_t, 8U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_x, 9U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_e_u, 10U, c2_db_sf_marshallOut,
    c2_bb_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_tspan, 11U, c2_cb_sf_marshallOut,
    c2_ab_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_J, 12U, c2_g_sf_marshallOut,
    c2_s_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_f, 13U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_d_A, 14U, c2_w_sf_marshallOut,
    c2_u_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Bp, 15U, c2_bb_sf_marshallOut,
    c2_y_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Bm, 16U, c2_bb_sf_marshallOut,
    c2_y_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Z, 17U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 3);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 212U);
  c2_tkm = c2_tspan[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 213U);
  c2_tkp = c2_tspan[9];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 214U);
  c2_e_A = c2_tkp - c2_t;
  c2_b_B = c2_tkp - c2_tkm;
  c2_b_x = c2_e_A;
  c2_e_y = c2_b_B;
  c2_c_x = c2_b_x;
  c2_f_y = c2_e_y;
  c2_lam_km = c2_c_x / c2_f_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 215U);
  c2_f_A = c2_t - c2_tkm;
  c2_c_B = c2_tkp - c2_tkm;
  c2_d_x = c2_f_A;
  c2_g_y = c2_c_B;
  c2_e_x = c2_d_x;
  c2_h_y = c2_g_y;
  c2_lam_kp = c2_e_x / c2_h_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 218U);
  for (c2_i382 = 0; c2_i382 < 3; c2_i382++) {
    c2_u_tau[c2_i382] = c2_lam_km * c2_e_u[c2_i382] + c2_lam_kp * c2_e_u[c2_i382
      + 3];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 221U);
  for (c2_i383 = 0; c2_i383 < 10; c2_i383++) {
    c2_f_x[c2_i383] = c2_x[c2_i383];
  }

  for (c2_i384 = 0; c2_i384 < 3; c2_i384++) {
    c2_b_u_tau[c2_i384] = c2_u_tau[c2_i384];
  }

  for (c2_i385 = 0; c2_i385 < 9; c2_i385++) {
    c2_c_J[c2_i385] = c2_b_J[c2_i385];
  }

  c2_Q_linearize(chartInstance, c2_f_x, c2_b_u_tau, c2_c_J, c2_g_A, c2_b_f);
  for (c2_i386 = 0; c2_i386 < 100; c2_i386++) {
    c2_d_A[c2_i386] = c2_g_A[c2_i386];
  }

  for (c2_i387 = 0; c2_i387 < 30; c2_i387++) {
    c2_B[c2_i387] = c2_b[c2_i387];
  }

  for (c2_i388 = 0; c2_i388 < 10; c2_i388++) {
    c2_f[c2_i388] = c2_b_f[c2_i388];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 223U);
  c2_a = c2_lam_kp;
  for (c2_i389 = 0; c2_i389 < 30; c2_i389++) {
    c2_Bp[c2_i389] = c2_a * c2_b[c2_i389];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 224U);
  c2_b_a = c2_lam_km;
  for (c2_i390 = 0; c2_i390 < 30; c2_i390++) {
    c2_Bm[c2_i390] = c2_b_a * c2_b[c2_i390];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 227U);
  for (c2_i391 = 0; c2_i391 < 100; c2_i391++) {
    c2_g_A[c2_i391] = -c2_d_A[c2_i391];
  }

  for (c2_i392 = 0; c2_i392 < 10; c2_i392++) {
    c2_b_f[c2_i392] = c2_x[c2_i392];
  }

  for (c2_i393 = 0; c2_i393 < 10; c2_i393++) {
    c2_i_y[c2_i393] = 0.0;
    c2_i395 = 0;
    for (c2_i396 = 0; c2_i396 < 10; c2_i396++) {
      c2_i_y[c2_i393] += c2_g_A[c2_i395 + c2_i393] * c2_b_f[c2_i396];
      c2_i395 += 10;
    }
  }

  for (c2_i394 = 0; c2_i394 < 3; c2_i394++) {
    c2_b_b[c2_i394] = c2_u_tau[c2_i394];
  }

  for (c2_i397 = 0; c2_i397 < 10; c2_i397++) {
    c2_b_f[c2_i397] = 0.0;
    c2_i399 = 0;
    for (c2_i400 = 0; c2_i400 < 3; c2_i400++) {
      c2_b_f[c2_i397] += c2_b[c2_i399 + c2_i397] * c2_b_b[c2_i400];
      c2_i399 += 10;
    }
  }

  for (c2_i398 = 0; c2_i398 < 10; c2_i398++) {
    c2_Z[c2_i398] = c2_i_y[c2_i398] - c2_b_f[c2_i398];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -227);
  _SFD_SYMBOL_SCOPE_POP();
}

static void c2_Q_linearize(SFc2_gnc2_libInstanceStruct *chartInstance, real_T
  c2_x[10], real_T c2_e_u[3], real_T c2_b_J[9], real_T c2_d_A[100], real_T c2_f
  [10])
{
  uint32_T c2_debug_family_var_map[29];
  real_T c2_B[30];
  real_T c2_q[4];
  real_T c2_q0;
  real_T c2_qv[3];
  real_T c2_hb[3];
  real_T c2_hw[3];
  real_T c2_w[3];
  real_T c2_dfq_dq[16];
  real_T c2_dfq_dhb[12];
  real_T c2_dfq_dhw[12];
  real_T c2_dfhb_dq[12];
  real_T c2_dfhb_dhb[9];
  real_T c2_dfhb_dhw[9];
  real_T c2_dfhw_dq[12];
  real_T c2_dfhw_dhb[9];
  real_T c2_dfhw_dhw[9];
  real_T c2_dfq_du[12];
  real_T c2_dfhb_du[9];
  real_T c2_dfhw_du[9];
  real_T c2_fq[4];
  real_T c2_fhb[3];
  real_T c2_fhw[3];
  real_T c2_nargin = 4.0;
  real_T c2_nargout = 3.0;
  int32_T c2_i401;
  real_T c2_e_y;
  real_T c2_b_x[4];
  real_T c2_scale;
  int32_T c2_k;
  real_T c2_c_x;
  int32_T c2_i402;
  real_T c2_d_x;
  real_T c2_e_x;
  real_T c2_absxk;
  real_T c2_f_y;
  real_T c2_g_y;
  real_T c2_t;
  int32_T c2_i403;
  int32_T c2_i404;
  int32_T c2_i405;
  int32_T c2_i406;
  int32_T c2_i407;
  int32_T c2_i408;
  real_T c2_e_A[9];
  int32_T c2_r1;
  real_T c2_b_B[3];
  int32_T c2_r2;
  int32_T c2_r3;
  real_T c2_f_x;
  real_T c2_g_x;
  real_T c2_h_x;
  real_T c2_i_x;
  real_T c2_h_y;
  real_T c2_j_x;
  real_T c2_k_x;
  real_T c2_l_x;
  real_T c2_i_y;
  real_T c2_maxval;
  real_T c2_m_x;
  real_T c2_n_x;
  real_T c2_o_x;
  real_T c2_p_x;
  real_T c2_j_y;
  real_T c2_q_x;
  real_T c2_r_x;
  real_T c2_s_x;
  real_T c2_k_y;
  real_T c2_a21;
  real_T c2_t_x;
  real_T c2_u_x;
  real_T c2_v_x;
  real_T c2_w_x;
  real_T c2_l_y;
  real_T c2_x_x;
  real_T c2_y_x;
  real_T c2_ab_x;
  real_T c2_m_y;
  real_T c2_d;
  real_T c2_bb_x;
  real_T c2_n_y;
  real_T c2_cb_x;
  real_T c2_o_y;
  real_T c2_z;
  real_T c2_db_x;
  real_T c2_p_y;
  real_T c2_eb_x;
  real_T c2_q_y;
  real_T c2_b_z;
  real_T c2_fb_x;
  real_T c2_gb_x;
  real_T c2_hb_x;
  real_T c2_ib_x;
  real_T c2_r_y;
  real_T c2_jb_x;
  real_T c2_kb_x;
  real_T c2_lb_x;
  real_T c2_s_y;
  real_T c2_b_d;
  real_T c2_mb_x;
  real_T c2_nb_x;
  real_T c2_ob_x;
  real_T c2_pb_x;
  real_T c2_t_y;
  real_T c2_qb_x;
  real_T c2_rb_x;
  real_T c2_sb_x;
  real_T c2_u_y;
  real_T c2_c_d;
  int32_T c2_rtemp;
  real_T c2_tb_x;
  real_T c2_v_y;
  real_T c2_ub_x;
  real_T c2_w_y;
  real_T c2_c_z;
  real_T c2_vb_x;
  real_T c2_x_y;
  real_T c2_wb_x;
  real_T c2_y_y;
  real_T c2_d_z;
  real_T c2_xb_x;
  real_T c2_ab_y;
  real_T c2_yb_x;
  real_T c2_bb_y;
  real_T c2_e_z;
  real_T c2_ac_x;
  real_T c2_cb_y;
  real_T c2_bc_x;
  real_T c2_db_y;
  real_T c2_f_z;
  int32_T c2_i409;
  uint32_T c2_b_debug_family_var_map[4];
  real_T c2_a[3];
  real_T c2_b_nargin = 1.0;
  real_T c2_b_nargout = 1.0;
  real_T c2_cross[9];
  real_T c2_b[16];
  int32_T c2_i410;
  int32_T c2_i411;
  int32_T c2_i412;
  int32_T c2_i413;
  int32_T c2_i414;
  int32_T c2_i415;
  int32_T c2_i416;
  int32_T c2_i417;
  int32_T c2_i418;
  real_T c2_b_a[3];
  real_T c2_c_nargin = 1.0;
  real_T c2_c_nargout = 1.0;
  real_T c2_b_cross[9];
  real_T c2_c_a;
  int32_T c2_i419;
  int32_T c2_i420;
  static real_T c2_b_b[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };

  int32_T c2_i421;
  int32_T c2_i422;
  real_T c2_c_b[12];
  int32_T c2_i423;
  int32_T c2_i424;
  int32_T c2_i425;
  int32_T c2_i426;
  int32_T c2_i427;
  int32_T c2_b_r1;
  int32_T c2_b_r2;
  int32_T c2_b_r3;
  real_T c2_cc_x;
  real_T c2_dc_x;
  real_T c2_ec_x;
  real_T c2_fc_x;
  real_T c2_eb_y;
  real_T c2_gc_x;
  real_T c2_hc_x;
  real_T c2_ic_x;
  real_T c2_fb_y;
  real_T c2_b_maxval;
  real_T c2_jc_x;
  real_T c2_kc_x;
  real_T c2_lc_x;
  real_T c2_mc_x;
  real_T c2_gb_y;
  real_T c2_nc_x;
  real_T c2_oc_x;
  real_T c2_pc_x;
  real_T c2_hb_y;
  real_T c2_b_a21;
  real_T c2_qc_x;
  real_T c2_rc_x;
  real_T c2_sc_x;
  real_T c2_tc_x;
  real_T c2_ib_y;
  real_T c2_uc_x;
  real_T c2_vc_x;
  real_T c2_wc_x;
  real_T c2_jb_y;
  real_T c2_d_d;
  real_T c2_xc_x;
  real_T c2_kb_y;
  real_T c2_yc_x;
  real_T c2_lb_y;
  real_T c2_g_z;
  real_T c2_ad_x;
  real_T c2_mb_y;
  real_T c2_bd_x;
  real_T c2_nb_y;
  real_T c2_h_z;
  real_T c2_cd_x;
  real_T c2_dd_x;
  real_T c2_ed_x;
  real_T c2_fd_x;
  real_T c2_ob_y;
  real_T c2_gd_x;
  real_T c2_hd_x;
  real_T c2_id_x;
  real_T c2_pb_y;
  real_T c2_e_d;
  real_T c2_jd_x;
  real_T c2_kd_x;
  real_T c2_ld_x;
  real_T c2_md_x;
  real_T c2_qb_y;
  real_T c2_nd_x;
  real_T c2_od_x;
  real_T c2_pd_x;
  real_T c2_rb_y;
  real_T c2_f_d;
  int32_T c2_b_rtemp;
  real_T c2_qd_x;
  real_T c2_sb_y;
  real_T c2_rd_x;
  real_T c2_tb_y;
  real_T c2_i_z;
  int32_T c2_b_k;
  real_T c2_sd_x;
  int32_T c2_i428;
  real_T c2_ub_y;
  real_T c2_td_x;
  real_T c2_vb_y;
  real_T c2_j_z;
  int32_T c2_i429;
  real_T c2_ud_x;
  int32_T c2_i430;
  real_T c2_wb_y;
  real_T c2_vd_x;
  real_T c2_xb_y;
  real_T c2_d_a[3];
  real_T c2_k_z;
  real_T c2_d_nargin = 1.0;
  real_T c2_d_nargout = 1.0;
  real_T c2_wd_x;
  real_T c2_c_cross[9];
  real_T c2_yb_y;
  real_T c2_xd_x;
  real_T c2_ac_y;
  real_T c2_l_z;
  int32_T c2_i431;
  real_T c2_e_a[3];
  real_T c2_e_nargin = 1.0;
  real_T c2_e_nargout = 1.0;
  real_T c2_d_cross[9];
  int32_T c2_i432;
  real_T c2_f_a[3];
  real_T c2_f_nargin = 1.0;
  real_T c2_f_nargout = 1.0;
  real_T c2_e_cross[9];
  int32_T c2_i433;
  int32_T c2_i434;
  real_T c2_f_cross[9];
  real_T c2_c_J[9];
  int32_T c2_i435;
  int32_T c2_i436;
  real_T c2_g_cross[9];
  real_T c2_d_J[9];
  real_T c2_dv49[9];
  int32_T c2_i437;
  int32_T c2_i438;
  real_T c2_g_a[3];
  real_T c2_g_nargin = 1.0;
  real_T c2_g_nargout = 1.0;
  real_T c2_h_cross[9];
  int32_T c2_i439;
  int32_T c2_i440;
  int32_T c2_i441;
  int32_T c2_i442;
  int32_T c2_i443;
  int32_T c2_i444;
  static real_T c2_dv50[9] = { -1.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0,
    -1.0 };

  int32_T c2_i445;
  int32_T c2_i446;
  real_T c2_h_a[3];
  real_T c2_h_nargin = 1.0;
  real_T c2_h_nargout = 1.0;
  real_T c2_i_cross[9];
  real_T c2_i_a;
  int32_T c2_i447;
  int32_T c2_i448;
  int32_T c2_i449;
  int32_T c2_i450;
  int32_T c2_i451;
  int32_T c2_i452;
  int32_T c2_i453;
  int32_T c2_i454;
  int32_T c2_i455;
  int32_T c2_i456;
  int32_T c2_i457;
  int32_T c2_i458;
  int32_T c2_i459;
  int32_T c2_i460;
  real_T c2_j_a[3];
  real_T c2_i_nargin = 1.0;
  real_T c2_i_nargout = 1.0;
  real_T c2_j_cross[9];
  int32_T c2_i461;
  int32_T c2_i462;
  int32_T c2_i463;
  int32_T c2_i464;
  real_T c2_bc_y[3];
  int32_T c2_i465;
  int32_T c2_i466;
  int32_T c2_i467;
  int32_T c2_i468;
  int32_T c2_i469;
  int32_T c2_i470;
  int32_T c2_i471;
  int32_T c2_i472;
  int32_T c2_i473;
  int32_T c2_i474;
  int32_T c2_i475;
  int32_T c2_i476;
  int32_T c2_i477;
  int32_T c2_i478;
  int32_T c2_i479;
  int32_T c2_i480;
  int32_T c2_i481;
  int32_T c2_i482;
  int32_T c2_i483;
  int32_T c2_i484;
  int32_T c2_i485;
  int32_T c2_i486;
  int32_T c2_i487;
  int32_T c2_i488;
  int32_T c2_i489;
  int32_T c2_i490;
  int32_T c2_i491;
  int32_T c2_i492;
  int32_T c2_i493;
  int32_T c2_i494;
  int32_T c2_i495;
  int32_T c2_i496;
  static real_T c2_dv51[30] = { 0.0, 0.0, 0.0, 0.0, -1.0, -0.0, -0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -1.0, -0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    -0.0, -0.0, -1.0, 0.0, 0.0, 1.0 };

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 29U, 29U, c2_c_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_B, 0U, c2_bb_sf_marshallOut,
    c2_y_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_q, 1U, c2_x_sf_marshallOut,
    c2_v_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_q0, 2U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_qv, 3U, c2_v_sf_marshallOut,
    c2_t_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_hb, 4U, c2_v_sf_marshallOut,
    c2_t_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_hw, 5U, c2_v_sf_marshallOut,
    c2_t_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_w, 6U, c2_v_sf_marshallOut,
    c2_t_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_dfq_dq, 7U, c2_f_sf_marshallOut,
    c2_x_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_dfq_dhb, 8U, c2_y_sf_marshallOut,
    c2_w_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_dfq_dhw, 9U, c2_y_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_dfhb_dq, 10U, c2_ab_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_dfhb_dhb, 11U, c2_g_sf_marshallOut,
    c2_s_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_dfhb_dhw, 12U, c2_g_sf_marshallOut,
    c2_s_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_dfhw_dq, 13U, c2_ab_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_dfhw_dhb, 14U, c2_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_dfhw_dhw, 15U, c2_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_dfq_du, 16U, c2_y_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_dfhb_du, 17U, c2_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_dfhw_du, 18U, c2_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_fq, 19U, c2_x_sf_marshallOut,
    c2_v_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_fhb, 20U, c2_v_sf_marshallOut,
    c2_t_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_fhw, 21U, c2_v_sf_marshallOut,
    c2_t_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 22U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 23U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_x, 24U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_e_u, 25U, c2_v_sf_marshallOut,
    c2_t_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_J, 26U, c2_g_sf_marshallOut,
    c2_s_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_d_A, 27U, c2_w_sf_marshallOut,
    c2_u_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_f, 28U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 4);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 240U);
  for (c2_i401 = 0; c2_i401 < 4; c2_i401++) {
    c2_b_x[c2_i401] = c2_x[c2_i401];
  }

  c2_e_y = 0.0;
  c2_scale = 2.2250738585072014E-308;
  for (c2_k = 0; c2_k + 1 < 5; c2_k++) {
    c2_c_x = c2_b_x[c2_k];
    c2_d_x = c2_c_x;
    c2_e_x = c2_d_x;
    c2_absxk = muDoubleScalarAbs(c2_e_x);
    if (c2_absxk > c2_scale) {
      c2_t = c2_scale / c2_absxk;
      c2_e_y = 1.0 + c2_e_y * c2_t * c2_t;
      c2_scale = c2_absxk;
    } else {
      c2_t = c2_absxk / c2_scale;
      c2_e_y += c2_t * c2_t;
    }
  }

  c2_e_y = c2_scale * muDoubleScalarSqrt(c2_e_y);
  for (c2_i402 = 0; c2_i402 < 4; c2_i402++) {
    c2_b_x[c2_i402] = c2_x[c2_i402];
  }

  c2_f_y = c2_e_y;
  c2_g_y = c2_f_y;
  for (c2_i403 = 0; c2_i403 < 4; c2_i403++) {
    c2_q[c2_i403] = c2_b_x[c2_i403] / c2_g_y;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 241U);
  c2_q0 = c2_q[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 242U);
  for (c2_i404 = 0; c2_i404 < 3; c2_i404++) {
    c2_qv[c2_i404] = c2_q[c2_i404 + 1];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 243U);
  for (c2_i405 = 0; c2_i405 < 3; c2_i405++) {
    c2_hb[c2_i405] = c2_x[c2_i405 + 4];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 244U);
  for (c2_i406 = 0; c2_i406 < 3; c2_i406++) {
    c2_hw[c2_i406] = c2_x[c2_i406 + 7];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 245U);
  for (c2_i407 = 0; c2_i407 < 9; c2_i407++) {
    c2_e_A[c2_i407] = c2_b_J[c2_i407];
  }

  for (c2_i408 = 0; c2_i408 < 3; c2_i408++) {
    c2_b_B[c2_i408] = c2_hb[c2_i408];
  }

  c2_r1 = 0;
  c2_r2 = 1;
  c2_r3 = 2;
  c2_f_x = c2_e_A[0];
  c2_g_x = c2_f_x;
  c2_h_x = c2_g_x;
  c2_i_x = c2_h_x;
  c2_h_y = muDoubleScalarAbs(c2_i_x);
  c2_j_x = 0.0;
  c2_k_x = c2_j_x;
  c2_l_x = c2_k_x;
  c2_i_y = muDoubleScalarAbs(c2_l_x);
  c2_maxval = c2_h_y + c2_i_y;
  c2_m_x = c2_e_A[1];
  c2_n_x = c2_m_x;
  c2_o_x = c2_n_x;
  c2_p_x = c2_o_x;
  c2_j_y = muDoubleScalarAbs(c2_p_x);
  c2_q_x = 0.0;
  c2_r_x = c2_q_x;
  c2_s_x = c2_r_x;
  c2_k_y = muDoubleScalarAbs(c2_s_x);
  c2_a21 = c2_j_y + c2_k_y;
  if (c2_a21 > c2_maxval) {
    c2_maxval = c2_a21;
    c2_r1 = 1;
    c2_r2 = 0;
  }

  c2_t_x = c2_e_A[2];
  c2_u_x = c2_t_x;
  c2_v_x = c2_u_x;
  c2_w_x = c2_v_x;
  c2_l_y = muDoubleScalarAbs(c2_w_x);
  c2_x_x = 0.0;
  c2_y_x = c2_x_x;
  c2_ab_x = c2_y_x;
  c2_m_y = muDoubleScalarAbs(c2_ab_x);
  c2_d = c2_l_y + c2_m_y;
  if (c2_d > c2_maxval) {
    c2_r1 = 2;
    c2_r2 = 1;
    c2_r3 = 0;
  }

  c2_bb_x = c2_e_A[c2_r2];
  c2_n_y = c2_e_A[c2_r1];
  c2_cb_x = c2_bb_x;
  c2_o_y = c2_n_y;
  c2_z = c2_cb_x / c2_o_y;
  c2_e_A[c2_r2] = c2_z;
  c2_db_x = c2_e_A[c2_r3];
  c2_p_y = c2_e_A[c2_r1];
  c2_eb_x = c2_db_x;
  c2_q_y = c2_p_y;
  c2_b_z = c2_eb_x / c2_q_y;
  c2_e_A[c2_r3] = c2_b_z;
  c2_e_A[3 + c2_r2] -= c2_e_A[c2_r2] * c2_e_A[3 + c2_r1];
  c2_e_A[3 + c2_r3] -= c2_e_A[c2_r3] * c2_e_A[3 + c2_r1];
  c2_e_A[6 + c2_r2] -= c2_e_A[c2_r2] * c2_e_A[6 + c2_r1];
  c2_e_A[6 + c2_r3] -= c2_e_A[c2_r3] * c2_e_A[6 + c2_r1];
  c2_fb_x = c2_e_A[3 + c2_r3];
  c2_gb_x = c2_fb_x;
  c2_hb_x = c2_gb_x;
  c2_ib_x = c2_hb_x;
  c2_r_y = muDoubleScalarAbs(c2_ib_x);
  c2_jb_x = 0.0;
  c2_kb_x = c2_jb_x;
  c2_lb_x = c2_kb_x;
  c2_s_y = muDoubleScalarAbs(c2_lb_x);
  c2_b_d = c2_r_y + c2_s_y;
  c2_mb_x = c2_e_A[3 + c2_r2];
  c2_nb_x = c2_mb_x;
  c2_ob_x = c2_nb_x;
  c2_pb_x = c2_ob_x;
  c2_t_y = muDoubleScalarAbs(c2_pb_x);
  c2_qb_x = 0.0;
  c2_rb_x = c2_qb_x;
  c2_sb_x = c2_rb_x;
  c2_u_y = muDoubleScalarAbs(c2_sb_x);
  c2_c_d = c2_t_y + c2_u_y;
  if (c2_b_d > c2_c_d) {
    c2_rtemp = c2_r2 + 1;
    c2_r2 = c2_r3;
    c2_r3 = c2_rtemp - 1;
  }

  c2_tb_x = c2_e_A[3 + c2_r3];
  c2_v_y = c2_e_A[3 + c2_r2];
  c2_ub_x = c2_tb_x;
  c2_w_y = c2_v_y;
  c2_c_z = c2_ub_x / c2_w_y;
  c2_e_A[3 + c2_r3] = c2_c_z;
  c2_e_A[6 + c2_r3] -= c2_e_A[3 + c2_r3] * c2_e_A[6 + c2_r2];
  if ((c2_e_A[c2_r1] == 0.0) || (c2_e_A[3 + c2_r2] == 0.0) || (c2_e_A[6 + c2_r3]
       == 0.0)) {
    c2_warning(chartInstance);
  }

  c2_w[0] = c2_b_B[c2_r1];
  c2_w[1] = c2_b_B[c2_r2] - c2_w[0] * c2_e_A[c2_r2];
  c2_w[2] = (c2_b_B[c2_r3] - c2_w[0] * c2_e_A[c2_r3]) - c2_w[1] * c2_e_A[3 +
    c2_r3];
  c2_vb_x = c2_w[2];
  c2_x_y = c2_e_A[6 + c2_r3];
  c2_wb_x = c2_vb_x;
  c2_y_y = c2_x_y;
  c2_d_z = c2_wb_x / c2_y_y;
  c2_w[2] = c2_d_z;
  c2_w[0] -= c2_w[2] * c2_e_A[6 + c2_r1];
  c2_w[1] -= c2_w[2] * c2_e_A[6 + c2_r2];
  c2_xb_x = c2_w[1];
  c2_ab_y = c2_e_A[3 + c2_r2];
  c2_yb_x = c2_xb_x;
  c2_bb_y = c2_ab_y;
  c2_e_z = c2_yb_x / c2_bb_y;
  c2_w[1] = c2_e_z;
  c2_w[0] -= c2_w[1] * c2_e_A[3 + c2_r1];
  c2_ac_x = c2_w[0];
  c2_cb_y = c2_e_A[c2_r1];
  c2_bc_x = c2_ac_x;
  c2_db_y = c2_cb_y;
  c2_f_z = c2_bc_x / c2_db_y;
  c2_w[0] = c2_f_z;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 248U);
  for (c2_i409 = 0; c2_i409 < 3; c2_i409++) {
    c2_a[c2_i409] = c2_w[c2_i409];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c2_b_debug_family_names,
    c2_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_nargin, 0U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_nargout, 1U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_a, 2U, c2_v_sf_marshallOut,
    c2_t_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_cross, 3U, c2_g_sf_marshallOut,
    c2_s_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 4);
  c2_cross[0] = 0.0;
  c2_cross[3] = -c2_a[2];
  c2_cross[6] = c2_a[1];
  c2_cross[1] = c2_a[2];
  c2_cross[4] = 0.0;
  c2_cross[7] = -c2_a[0];
  c2_cross[2] = -c2_a[1];
  c2_cross[5] = c2_a[0];
  c2_cross[8] = 0.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, -4);
  _SFD_SYMBOL_SCOPE_POP();
  c2_b[0] = 0.0;
  c2_i410 = 0;
  for (c2_i411 = 0; c2_i411 < 3; c2_i411++) {
    c2_b[c2_i410 + 4] = -c2_w[c2_i411];
    c2_i410 += 4;
  }

  for (c2_i412 = 0; c2_i412 < 3; c2_i412++) {
    c2_b[c2_i412 + 1] = c2_w[c2_i412];
  }

  c2_i413 = 0;
  c2_i414 = 0;
  for (c2_i415 = 0; c2_i415 < 3; c2_i415++) {
    for (c2_i417 = 0; c2_i417 < 3; c2_i417++) {
      c2_b[(c2_i417 + c2_i413) + 5] = -c2_cross[c2_i417 + c2_i414];
    }

    c2_i413 += 4;
    c2_i414 += 3;
  }

  for (c2_i416 = 0; c2_i416 < 16; c2_i416++) {
    c2_dfq_dq[c2_i416] = 0.5 * c2_b[c2_i416];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 249U);
  for (c2_i418 = 0; c2_i418 < 3; c2_i418++) {
    c2_b_a[c2_i418] = c2_qv[c2_i418];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c2_b_debug_family_names,
    c2_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_nargin, 0U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_nargout, 1U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_a, 2U, c2_v_sf_marshallOut,
    c2_t_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_cross, 3U, c2_g_sf_marshallOut,
    c2_s_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 4);
  c2_b_cross[0] = 0.0;
  c2_b_cross[3] = -c2_b_a[2];
  c2_b_cross[6] = c2_b_a[1];
  c2_b_cross[1] = c2_b_a[2];
  c2_b_cross[4] = 0.0;
  c2_b_cross[7] = -c2_b_a[0];
  c2_b_cross[2] = -c2_b_a[1];
  c2_b_cross[5] = c2_b_a[0];
  c2_b_cross[8] = 0.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, -4);
  _SFD_SYMBOL_SCOPE_POP();
  c2_c_a = c2_q0;
  for (c2_i419 = 0; c2_i419 < 9; c2_i419++) {
    c2_e_A[c2_i419] = c2_c_a * c2_b_b[c2_i419];
  }

  c2_i420 = 0;
  for (c2_i421 = 0; c2_i421 < 3; c2_i421++) {
    c2_c_b[c2_i420] = -c2_qv[c2_i421];
    c2_i420 += 4;
  }

  c2_i422 = 0;
  c2_i423 = 0;
  for (c2_i424 = 0; c2_i424 < 3; c2_i424++) {
    for (c2_i426 = 0; c2_i426 < 3; c2_i426++) {
      c2_c_b[(c2_i426 + c2_i422) + 1] = c2_b_cross[c2_i426 + c2_i423] +
        c2_e_A[c2_i426 + c2_i423];
    }

    c2_i422 += 4;
    c2_i423 += 3;
  }

  for (c2_i425 = 0; c2_i425 < 12; c2_i425++) {
    c2_c_b[c2_i425] *= 0.5;
  }

  for (c2_i427 = 0; c2_i427 < 9; c2_i427++) {
    c2_e_A[c2_i427] = c2_b_J[c2_i427];
  }

  c2_b_r1 = 0;
  c2_b_r2 = 1;
  c2_b_r3 = 2;
  c2_cc_x = c2_e_A[0];
  c2_dc_x = c2_cc_x;
  c2_ec_x = c2_dc_x;
  c2_fc_x = c2_ec_x;
  c2_eb_y = muDoubleScalarAbs(c2_fc_x);
  c2_gc_x = 0.0;
  c2_hc_x = c2_gc_x;
  c2_ic_x = c2_hc_x;
  c2_fb_y = muDoubleScalarAbs(c2_ic_x);
  c2_b_maxval = c2_eb_y + c2_fb_y;
  c2_jc_x = c2_e_A[1];
  c2_kc_x = c2_jc_x;
  c2_lc_x = c2_kc_x;
  c2_mc_x = c2_lc_x;
  c2_gb_y = muDoubleScalarAbs(c2_mc_x);
  c2_nc_x = 0.0;
  c2_oc_x = c2_nc_x;
  c2_pc_x = c2_oc_x;
  c2_hb_y = muDoubleScalarAbs(c2_pc_x);
  c2_b_a21 = c2_gb_y + c2_hb_y;
  if (c2_b_a21 > c2_b_maxval) {
    c2_b_maxval = c2_b_a21;
    c2_b_r1 = 1;
    c2_b_r2 = 0;
  }

  c2_qc_x = c2_e_A[2];
  c2_rc_x = c2_qc_x;
  c2_sc_x = c2_rc_x;
  c2_tc_x = c2_sc_x;
  c2_ib_y = muDoubleScalarAbs(c2_tc_x);
  c2_uc_x = 0.0;
  c2_vc_x = c2_uc_x;
  c2_wc_x = c2_vc_x;
  c2_jb_y = muDoubleScalarAbs(c2_wc_x);
  c2_d_d = c2_ib_y + c2_jb_y;
  if (c2_d_d > c2_b_maxval) {
    c2_b_r1 = 2;
    c2_b_r2 = 1;
    c2_b_r3 = 0;
  }

  c2_xc_x = c2_e_A[c2_b_r2];
  c2_kb_y = c2_e_A[c2_b_r1];
  c2_yc_x = c2_xc_x;
  c2_lb_y = c2_kb_y;
  c2_g_z = c2_yc_x / c2_lb_y;
  c2_e_A[c2_b_r2] = c2_g_z;
  c2_ad_x = c2_e_A[c2_b_r3];
  c2_mb_y = c2_e_A[c2_b_r1];
  c2_bd_x = c2_ad_x;
  c2_nb_y = c2_mb_y;
  c2_h_z = c2_bd_x / c2_nb_y;
  c2_e_A[c2_b_r3] = c2_h_z;
  c2_e_A[3 + c2_b_r2] -= c2_e_A[c2_b_r2] * c2_e_A[3 + c2_b_r1];
  c2_e_A[3 + c2_b_r3] -= c2_e_A[c2_b_r3] * c2_e_A[3 + c2_b_r1];
  c2_e_A[6 + c2_b_r2] -= c2_e_A[c2_b_r2] * c2_e_A[6 + c2_b_r1];
  c2_e_A[6 + c2_b_r3] -= c2_e_A[c2_b_r3] * c2_e_A[6 + c2_b_r1];
  c2_cd_x = c2_e_A[3 + c2_b_r3];
  c2_dd_x = c2_cd_x;
  c2_ed_x = c2_dd_x;
  c2_fd_x = c2_ed_x;
  c2_ob_y = muDoubleScalarAbs(c2_fd_x);
  c2_gd_x = 0.0;
  c2_hd_x = c2_gd_x;
  c2_id_x = c2_hd_x;
  c2_pb_y = muDoubleScalarAbs(c2_id_x);
  c2_e_d = c2_ob_y + c2_pb_y;
  c2_jd_x = c2_e_A[3 + c2_b_r2];
  c2_kd_x = c2_jd_x;
  c2_ld_x = c2_kd_x;
  c2_md_x = c2_ld_x;
  c2_qb_y = muDoubleScalarAbs(c2_md_x);
  c2_nd_x = 0.0;
  c2_od_x = c2_nd_x;
  c2_pd_x = c2_od_x;
  c2_rb_y = muDoubleScalarAbs(c2_pd_x);
  c2_f_d = c2_qb_y + c2_rb_y;
  if (c2_e_d > c2_f_d) {
    c2_b_rtemp = c2_b_r2 + 1;
    c2_b_r2 = c2_b_r3;
    c2_b_r3 = c2_b_rtemp - 1;
  }

  c2_qd_x = c2_e_A[3 + c2_b_r3];
  c2_sb_y = c2_e_A[3 + c2_b_r2];
  c2_rd_x = c2_qd_x;
  c2_tb_y = c2_sb_y;
  c2_i_z = c2_rd_x / c2_tb_y;
  c2_e_A[3 + c2_b_r3] = c2_i_z;
  c2_e_A[6 + c2_b_r3] -= c2_e_A[3 + c2_b_r3] * c2_e_A[6 + c2_b_r2];
  if ((c2_e_A[c2_b_r1] == 0.0) || (c2_e_A[3 + c2_b_r2] == 0.0) || (c2_e_A[6 +
       c2_b_r3] == 0.0)) {
    c2_warning(chartInstance);
  }

  for (c2_b_k = 0; c2_b_k + 1 < 5; c2_b_k++) {
    c2_sd_x = c2_c_b[c2_b_k];
    c2_ub_y = c2_e_A[c2_b_r1];
    c2_td_x = c2_sd_x;
    c2_vb_y = c2_ub_y;
    c2_j_z = c2_td_x / c2_vb_y;
    c2_dfq_dhb[c2_b_k + (c2_b_r1 << 2)] = c2_j_z;
    c2_dfq_dhb[c2_b_k + (c2_b_r2 << 2)] = c2_c_b[4 + c2_b_k] - c2_dfq_dhb[c2_b_k
      + (c2_b_r1 << 2)] * c2_e_A[3 + c2_b_r1];
    c2_dfq_dhb[c2_b_k + (c2_b_r3 << 2)] = c2_c_b[8 + c2_b_k] - c2_dfq_dhb[c2_b_k
      + (c2_b_r1 << 2)] * c2_e_A[6 + c2_b_r1];
    c2_ud_x = c2_dfq_dhb[c2_b_k + (c2_b_r2 << 2)];
    c2_wb_y = c2_e_A[3 + c2_b_r2];
    c2_vd_x = c2_ud_x;
    c2_xb_y = c2_wb_y;
    c2_k_z = c2_vd_x / c2_xb_y;
    c2_dfq_dhb[c2_b_k + (c2_b_r2 << 2)] = c2_k_z;
    c2_dfq_dhb[c2_b_k + (c2_b_r3 << 2)] -= c2_dfq_dhb[c2_b_k + (c2_b_r2 << 2)] *
      c2_e_A[6 + c2_b_r2];
    c2_wd_x = c2_dfq_dhb[c2_b_k + (c2_b_r3 << 2)];
    c2_yb_y = c2_e_A[6 + c2_b_r3];
    c2_xd_x = c2_wd_x;
    c2_ac_y = c2_yb_y;
    c2_l_z = c2_xd_x / c2_ac_y;
    c2_dfq_dhb[c2_b_k + (c2_b_r3 << 2)] = c2_l_z;
    c2_dfq_dhb[c2_b_k + (c2_b_r2 << 2)] -= c2_dfq_dhb[c2_b_k + (c2_b_r3 << 2)] *
      c2_e_A[3 + c2_b_r3];
    c2_dfq_dhb[c2_b_k + (c2_b_r1 << 2)] -= c2_dfq_dhb[c2_b_k + (c2_b_r3 << 2)] *
      c2_e_A[c2_b_r3];
    c2_dfq_dhb[c2_b_k + (c2_b_r1 << 2)] -= c2_dfq_dhb[c2_b_k + (c2_b_r2 << 2)] *
      c2_e_A[c2_b_r2];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 250U);
  for (c2_i428 = 0; c2_i428 < 12; c2_i428++) {
    c2_dfq_dhw[c2_i428] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 251U);
  for (c2_i429 = 0; c2_i429 < 12; c2_i429++) {
    c2_dfhb_dq[c2_i429] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 252U);
  for (c2_i430 = 0; c2_i430 < 3; c2_i430++) {
    c2_d_a[c2_i430] = c2_hb[c2_i430];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c2_b_debug_family_names,
    c2_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_d_nargin, 0U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_d_nargout, 1U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_d_a, 2U, c2_v_sf_marshallOut,
    c2_t_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_c_cross, 3U, c2_g_sf_marshallOut,
    c2_s_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 4);
  c2_c_cross[0] = 0.0;
  c2_c_cross[3] = -c2_d_a[2];
  c2_c_cross[6] = c2_d_a[1];
  c2_c_cross[1] = c2_d_a[2];
  c2_c_cross[4] = 0.0;
  c2_c_cross[7] = -c2_d_a[0];
  c2_c_cross[2] = -c2_d_a[1];
  c2_c_cross[5] = c2_d_a[0];
  c2_c_cross[8] = 0.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, -4);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i431 = 0; c2_i431 < 3; c2_i431++) {
    c2_e_a[c2_i431] = c2_w[c2_i431];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c2_b_debug_family_names,
    c2_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_e_nargin, 0U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_e_nargout, 1U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_e_a, 2U, c2_v_sf_marshallOut,
    c2_t_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_d_cross, 3U, c2_g_sf_marshallOut,
    c2_s_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 4);
  c2_d_cross[0] = 0.0;
  c2_d_cross[3] = -c2_e_a[2];
  c2_d_cross[6] = c2_e_a[1];
  c2_d_cross[1] = c2_e_a[2];
  c2_d_cross[4] = 0.0;
  c2_d_cross[7] = -c2_e_a[0];
  c2_d_cross[2] = -c2_e_a[1];
  c2_d_cross[5] = c2_e_a[0];
  c2_d_cross[8] = 0.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, -4);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i432 = 0; c2_i432 < 3; c2_i432++) {
    c2_f_a[c2_i432] = c2_hw[c2_i432];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c2_b_debug_family_names,
    c2_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_f_nargin, 0U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_f_nargout, 1U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_f_a, 2U, c2_v_sf_marshallOut,
    c2_t_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_e_cross, 3U, c2_g_sf_marshallOut,
    c2_s_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 4);
  c2_e_cross[0] = 0.0;
  c2_e_cross[3] = -c2_f_a[2];
  c2_e_cross[6] = c2_f_a[1];
  c2_e_cross[1] = c2_f_a[2];
  c2_e_cross[4] = 0.0;
  c2_e_cross[7] = -c2_f_a[0];
  c2_e_cross[2] = -c2_f_a[1];
  c2_e_cross[5] = c2_f_a[0];
  c2_e_cross[8] = 0.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, -4);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i433 = 0; c2_i433 < 9; c2_i433++) {
    c2_f_cross[c2_i433] = c2_c_cross[c2_i433];
  }

  for (c2_i434 = 0; c2_i434 < 9; c2_i434++) {
    c2_c_J[c2_i434] = c2_b_J[c2_i434];
  }

  c2_mrdivide(chartInstance, c2_f_cross, c2_c_J, c2_e_A);
  for (c2_i435 = 0; c2_i435 < 9; c2_i435++) {
    c2_g_cross[c2_i435] = c2_e_cross[c2_i435];
  }

  for (c2_i436 = 0; c2_i436 < 9; c2_i436++) {
    c2_d_J[c2_i436] = c2_b_J[c2_i436];
  }

  c2_mrdivide(chartInstance, c2_g_cross, c2_d_J, c2_dv49);
  for (c2_i437 = 0; c2_i437 < 9; c2_i437++) {
    c2_dfhb_dhb[c2_i437] = (c2_e_A[c2_i437] - c2_d_cross[c2_i437]) +
      c2_dv49[c2_i437];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 253U);
  for (c2_i438 = 0; c2_i438 < 3; c2_i438++) {
    c2_g_a[c2_i438] = c2_w[c2_i438];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c2_b_debug_family_names,
    c2_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_g_nargin, 0U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_g_nargout, 1U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_g_a, 2U, c2_v_sf_marshallOut,
    c2_t_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_h_cross, 3U, c2_g_sf_marshallOut,
    c2_s_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 4);
  c2_h_cross[0] = 0.0;
  c2_h_cross[3] = -c2_g_a[2];
  c2_h_cross[6] = c2_g_a[1];
  c2_h_cross[1] = c2_g_a[2];
  c2_h_cross[4] = 0.0;
  c2_h_cross[7] = -c2_g_a[0];
  c2_h_cross[2] = -c2_g_a[1];
  c2_h_cross[5] = c2_g_a[0];
  c2_h_cross[8] = 0.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, -4);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i439 = 0; c2_i439 < 9; c2_i439++) {
    c2_dfhb_dhw[c2_i439] = -c2_h_cross[c2_i439];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 254U);
  for (c2_i440 = 0; c2_i440 < 12; c2_i440++) {
    c2_dfhw_dq[c2_i440] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, MAX_uint8_T);
  for (c2_i441 = 0; c2_i441 < 9; c2_i441++) {
    c2_dfhw_dhb[c2_i441] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 256);
  for (c2_i442 = 0; c2_i442 < 9; c2_i442++) {
    c2_dfhw_dhw[c2_i442] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 257);
  for (c2_i443 = 0; c2_i443 < 12; c2_i443++) {
    c2_dfq_du[c2_i443] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 258);
  for (c2_i444 = 0; c2_i444 < 9; c2_i444++) {
    c2_dfhb_du[c2_i444] = c2_dv50[c2_i444];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 259);
  for (c2_i445 = 0; c2_i445 < 9; c2_i445++) {
    c2_dfhw_du[c2_i445] = c2_b_b[c2_i445];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 262);
  for (c2_i446 = 0; c2_i446 < 3; c2_i446++) {
    c2_h_a[c2_i446] = c2_qv[c2_i446];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c2_b_debug_family_names,
    c2_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_h_nargin, 0U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_h_nargout, 1U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_h_a, 2U, c2_v_sf_marshallOut,
    c2_t_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_i_cross, 3U, c2_g_sf_marshallOut,
    c2_s_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 4);
  c2_i_cross[0] = 0.0;
  c2_i_cross[3] = -c2_h_a[2];
  c2_i_cross[6] = c2_h_a[1];
  c2_i_cross[1] = c2_h_a[2];
  c2_i_cross[4] = 0.0;
  c2_i_cross[7] = -c2_h_a[0];
  c2_i_cross[2] = -c2_h_a[1];
  c2_i_cross[5] = c2_h_a[0];
  c2_i_cross[8] = 0.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, -4);
  _SFD_SYMBOL_SCOPE_POP();
  c2_i_a = c2_q0;
  for (c2_i447 = 0; c2_i447 < 9; c2_i447++) {
    c2_e_A[c2_i447] = c2_i_a * c2_b_b[c2_i447];
  }

  c2_i448 = 0;
  for (c2_i449 = 0; c2_i449 < 3; c2_i449++) {
    c2_c_b[c2_i448] = -c2_qv[c2_i449];
    c2_i448 += 4;
  }

  c2_i450 = 0;
  c2_i451 = 0;
  for (c2_i452 = 0; c2_i452 < 3; c2_i452++) {
    for (c2_i454 = 0; c2_i454 < 3; c2_i454++) {
      c2_c_b[(c2_i454 + c2_i450) + 1] = c2_i_cross[c2_i454 + c2_i451] +
        c2_e_A[c2_i454 + c2_i451];
    }

    c2_i450 += 4;
    c2_i451 += 3;
  }

  for (c2_i453 = 0; c2_i453 < 12; c2_i453++) {
    c2_c_b[c2_i453] *= 0.5;
  }

  for (c2_i455 = 0; c2_i455 < 3; c2_i455++) {
    c2_b_B[c2_i455] = c2_w[c2_i455];
  }

  for (c2_i456 = 0; c2_i456 < 4; c2_i456++) {
    c2_fq[c2_i456] = 0.0;
  }

  for (c2_i457 = 0; c2_i457 < 4; c2_i457++) {
    c2_fq[c2_i457] = 0.0;
    c2_i459 = 0;
    for (c2_i460 = 0; c2_i460 < 3; c2_i460++) {
      c2_fq[c2_i457] += c2_c_b[c2_i459 + c2_i457] * c2_b_B[c2_i460];
      c2_i459 += 4;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 263);
  for (c2_i458 = 0; c2_i458 < 3; c2_i458++) {
    c2_j_a[c2_i458] = c2_hb[c2_i458] + c2_hw[c2_i458];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c2_b_debug_family_names,
    c2_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_i_nargin, 0U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_i_nargout, 1U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_j_a, 2U, c2_v_sf_marshallOut,
    c2_t_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_j_cross, 3U, c2_g_sf_marshallOut,
    c2_s_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 4);
  c2_j_cross[0] = 0.0;
  c2_j_cross[3] = -c2_j_a[2];
  c2_j_cross[6] = c2_j_a[1];
  c2_j_cross[1] = c2_j_a[2];
  c2_j_cross[4] = 0.0;
  c2_j_cross[7] = -c2_j_a[0];
  c2_j_cross[2] = -c2_j_a[1];
  c2_j_cross[5] = c2_j_a[0];
  c2_j_cross[8] = 0.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, -4);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i461 = 0; c2_i461 < 9; c2_i461++) {
    c2_e_A[c2_i461] = c2_j_cross[c2_i461];
  }

  for (c2_i462 = 0; c2_i462 < 3; c2_i462++) {
    c2_b_B[c2_i462] = c2_w[c2_i462];
  }

  for (c2_i463 = 0; c2_i463 < 3; c2_i463++) {
    c2_bc_y[c2_i463] = 0.0;
    c2_i465 = 0;
    for (c2_i466 = 0; c2_i466 < 3; c2_i466++) {
      c2_bc_y[c2_i463] += c2_e_A[c2_i465 + c2_i463] * c2_b_B[c2_i466];
      c2_i465 += 3;
    }
  }

  for (c2_i464 = 0; c2_i464 < 3; c2_i464++) {
    c2_fhb[c2_i464] = -c2_e_u[c2_i464] + c2_bc_y[c2_i464];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 264);
  for (c2_i467 = 0; c2_i467 < 3; c2_i467++) {
    c2_fhw[c2_i467] = c2_e_u[c2_i467];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 267);
  for (c2_i468 = 0; c2_i468 < 4; c2_i468++) {
    c2_f[c2_i468] = c2_fq[c2_i468];
  }

  for (c2_i469 = 0; c2_i469 < 3; c2_i469++) {
    c2_f[c2_i469 + 4] = c2_fhb[c2_i469];
  }

  for (c2_i470 = 0; c2_i470 < 3; c2_i470++) {
    c2_f[c2_i470 + 7] = c2_fhw[c2_i470];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 268);
  c2_i471 = 0;
  c2_i472 = 0;
  for (c2_i473 = 0; c2_i473 < 4; c2_i473++) {
    for (c2_i475 = 0; c2_i475 < 4; c2_i475++) {
      c2_d_A[c2_i475 + c2_i471] = c2_dfq_dq[c2_i475 + c2_i472];
    }

    c2_i471 += 10;
    c2_i472 += 4;
  }

  c2_i474 = 0;
  c2_i476 = 0;
  for (c2_i477 = 0; c2_i477 < 3; c2_i477++) {
    for (c2_i479 = 0; c2_i479 < 4; c2_i479++) {
      c2_d_A[(c2_i479 + c2_i474) + 40] = c2_dfq_dhb[c2_i479 + c2_i476];
    }

    c2_i474 += 10;
    c2_i476 += 4;
  }

  c2_i478 = 0;
  for (c2_i480 = 0; c2_i480 < 3; c2_i480++) {
    for (c2_i482 = 0; c2_i482 < 4; c2_i482++) {
      c2_d_A[(c2_i482 + c2_i478) + 70] = 0.0;
    }

    c2_i478 += 10;
  }

  c2_i481 = 0;
  for (c2_i483 = 0; c2_i483 < 4; c2_i483++) {
    for (c2_i485 = 0; c2_i485 < 3; c2_i485++) {
      c2_d_A[(c2_i485 + c2_i481) + 4] = 0.0;
    }

    c2_i481 += 10;
  }

  c2_i484 = 0;
  c2_i486 = 0;
  for (c2_i487 = 0; c2_i487 < 3; c2_i487++) {
    for (c2_i489 = 0; c2_i489 < 3; c2_i489++) {
      c2_d_A[(c2_i489 + c2_i484) + 44] = c2_dfhb_dhb[c2_i489 + c2_i486];
    }

    c2_i484 += 10;
    c2_i486 += 3;
  }

  c2_i488 = 0;
  c2_i490 = 0;
  for (c2_i491 = 0; c2_i491 < 3; c2_i491++) {
    for (c2_i493 = 0; c2_i493 < 3; c2_i493++) {
      c2_d_A[(c2_i493 + c2_i488) + 74] = c2_dfhb_dhw[c2_i493 + c2_i490];
    }

    c2_i488 += 10;
    c2_i490 += 3;
  }

  c2_i492 = 0;
  for (c2_i494 = 0; c2_i494 < 10; c2_i494++) {
    for (c2_i495 = 0; c2_i495 < 3; c2_i495++) {
      c2_d_A[(c2_i495 + c2_i492) + 7] = 0.0;
    }

    c2_i492 += 10;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 271);
  for (c2_i496 = 0; c2_i496 < 30; c2_i496++) {
    c2_B[c2_i496] = c2_dv51[c2_i496];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -271);
  _SFD_SYMBOL_SCOPE_POP();
}

static void c2_warning(SFc2_gnc2_libInstanceStruct *chartInstance)
{
  const mxArray *c2_e_y = NULL;
  static char_T c2_cv0[7] = { 'w', 'a', 'r', 'n', 'i', 'n', 'g' };

  const mxArray *c2_f_y = NULL;
  static char_T c2_cv1[7] = { 'm', 'e', 's', 's', 'a', 'g', 'e' };

  const mxArray *c2_g_y = NULL;
  static char_T c2_msgID[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T',
    'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a', 't',
    'r', 'i', 'x' };

  (void)chartInstance;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_cv0, 10, 0U, 1U, 0U, 2, 1, 7),
                false);
  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", c2_cv1, 10, 0U, 1U, 0U, 2, 1, 7),
                false);
  c2_g_y = NULL;
  sf_mex_assign(&c2_g_y, sf_mex_create("y", c2_msgID, 10, 0U, 1U, 0U, 2, 1, 27),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "feval", 0U, 2U, 14, c2_e_y, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "feval", 1U,
    2U, 14, c2_f_y, 14, c2_g_y));
}

static void c2_mrdivide(SFc2_gnc2_libInstanceStruct *chartInstance, real_T
  c2_d_A[9], real_T c2_B[9], real_T c2_e_y[9])
{
  int32_T c2_i497;
  int32_T c2_r1;
  real_T c2_e_A[9];
  int32_T c2_r2;
  int32_T c2_r3;
  real_T c2_x;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_f_y;
  real_T c2_e_x;
  real_T c2_f_x;
  real_T c2_g_x;
  real_T c2_g_y;
  real_T c2_maxval;
  real_T c2_h_x;
  real_T c2_i_x;
  real_T c2_j_x;
  real_T c2_k_x;
  real_T c2_h_y;
  real_T c2_l_x;
  real_T c2_m_x;
  real_T c2_n_x;
  real_T c2_i_y;
  real_T c2_a21;
  real_T c2_o_x;
  real_T c2_p_x;
  real_T c2_q_x;
  real_T c2_r_x;
  real_T c2_j_y;
  real_T c2_s_x;
  real_T c2_t_x;
  real_T c2_u_x;
  real_T c2_k_y;
  real_T c2_d;
  real_T c2_v_x;
  real_T c2_l_y;
  real_T c2_w_x;
  real_T c2_m_y;
  real_T c2_z;
  real_T c2_x_x;
  real_T c2_n_y;
  real_T c2_y_x;
  real_T c2_o_y;
  real_T c2_b_z;
  real_T c2_ab_x;
  real_T c2_bb_x;
  real_T c2_cb_x;
  real_T c2_db_x;
  real_T c2_p_y;
  real_T c2_eb_x;
  real_T c2_fb_x;
  real_T c2_gb_x;
  real_T c2_q_y;
  real_T c2_b_d;
  real_T c2_hb_x;
  real_T c2_ib_x;
  real_T c2_jb_x;
  real_T c2_kb_x;
  real_T c2_r_y;
  real_T c2_lb_x;
  real_T c2_mb_x;
  real_T c2_nb_x;
  real_T c2_s_y;
  real_T c2_c_d;
  int32_T c2_rtemp;
  real_T c2_ob_x;
  real_T c2_t_y;
  real_T c2_pb_x;
  real_T c2_u_y;
  real_T c2_c_z;
  int32_T c2_k;
  real_T c2_qb_x;
  real_T c2_v_y;
  real_T c2_rb_x;
  real_T c2_w_y;
  real_T c2_d_z;
  real_T c2_sb_x;
  real_T c2_x_y;
  real_T c2_tb_x;
  real_T c2_y_y;
  real_T c2_e_z;
  real_T c2_ub_x;
  real_T c2_ab_y;
  real_T c2_vb_x;
  real_T c2_bb_y;
  real_T c2_f_z;
  for (c2_i497 = 0; c2_i497 < 9; c2_i497++) {
    c2_e_A[c2_i497] = c2_B[c2_i497];
  }

  c2_r1 = 0;
  c2_r2 = 1;
  c2_r3 = 2;
  c2_x = c2_e_A[0];
  c2_b_x = c2_x;
  c2_c_x = c2_b_x;
  c2_d_x = c2_c_x;
  c2_f_y = muDoubleScalarAbs(c2_d_x);
  c2_e_x = 0.0;
  c2_f_x = c2_e_x;
  c2_g_x = c2_f_x;
  c2_g_y = muDoubleScalarAbs(c2_g_x);
  c2_maxval = c2_f_y + c2_g_y;
  c2_h_x = c2_e_A[1];
  c2_i_x = c2_h_x;
  c2_j_x = c2_i_x;
  c2_k_x = c2_j_x;
  c2_h_y = muDoubleScalarAbs(c2_k_x);
  c2_l_x = 0.0;
  c2_m_x = c2_l_x;
  c2_n_x = c2_m_x;
  c2_i_y = muDoubleScalarAbs(c2_n_x);
  c2_a21 = c2_h_y + c2_i_y;
  if (c2_a21 > c2_maxval) {
    c2_maxval = c2_a21;
    c2_r1 = 1;
    c2_r2 = 0;
  }

  c2_o_x = c2_e_A[2];
  c2_p_x = c2_o_x;
  c2_q_x = c2_p_x;
  c2_r_x = c2_q_x;
  c2_j_y = muDoubleScalarAbs(c2_r_x);
  c2_s_x = 0.0;
  c2_t_x = c2_s_x;
  c2_u_x = c2_t_x;
  c2_k_y = muDoubleScalarAbs(c2_u_x);
  c2_d = c2_j_y + c2_k_y;
  if (c2_d > c2_maxval) {
    c2_r1 = 2;
    c2_r2 = 1;
    c2_r3 = 0;
  }

  c2_v_x = c2_e_A[c2_r2];
  c2_l_y = c2_e_A[c2_r1];
  c2_w_x = c2_v_x;
  c2_m_y = c2_l_y;
  c2_z = c2_w_x / c2_m_y;
  c2_e_A[c2_r2] = c2_z;
  c2_x_x = c2_e_A[c2_r3];
  c2_n_y = c2_e_A[c2_r1];
  c2_y_x = c2_x_x;
  c2_o_y = c2_n_y;
  c2_b_z = c2_y_x / c2_o_y;
  c2_e_A[c2_r3] = c2_b_z;
  c2_e_A[3 + c2_r2] -= c2_e_A[c2_r2] * c2_e_A[3 + c2_r1];
  c2_e_A[3 + c2_r3] -= c2_e_A[c2_r3] * c2_e_A[3 + c2_r1];
  c2_e_A[6 + c2_r2] -= c2_e_A[c2_r2] * c2_e_A[6 + c2_r1];
  c2_e_A[6 + c2_r3] -= c2_e_A[c2_r3] * c2_e_A[6 + c2_r1];
  c2_ab_x = c2_e_A[3 + c2_r3];
  c2_bb_x = c2_ab_x;
  c2_cb_x = c2_bb_x;
  c2_db_x = c2_cb_x;
  c2_p_y = muDoubleScalarAbs(c2_db_x);
  c2_eb_x = 0.0;
  c2_fb_x = c2_eb_x;
  c2_gb_x = c2_fb_x;
  c2_q_y = muDoubleScalarAbs(c2_gb_x);
  c2_b_d = c2_p_y + c2_q_y;
  c2_hb_x = c2_e_A[3 + c2_r2];
  c2_ib_x = c2_hb_x;
  c2_jb_x = c2_ib_x;
  c2_kb_x = c2_jb_x;
  c2_r_y = muDoubleScalarAbs(c2_kb_x);
  c2_lb_x = 0.0;
  c2_mb_x = c2_lb_x;
  c2_nb_x = c2_mb_x;
  c2_s_y = muDoubleScalarAbs(c2_nb_x);
  c2_c_d = c2_r_y + c2_s_y;
  if (c2_b_d > c2_c_d) {
    c2_rtemp = c2_r2 + 1;
    c2_r2 = c2_r3;
    c2_r3 = c2_rtemp - 1;
  }

  c2_ob_x = c2_e_A[3 + c2_r3];
  c2_t_y = c2_e_A[3 + c2_r2];
  c2_pb_x = c2_ob_x;
  c2_u_y = c2_t_y;
  c2_c_z = c2_pb_x / c2_u_y;
  c2_e_A[3 + c2_r3] = c2_c_z;
  c2_e_A[6 + c2_r3] -= c2_e_A[3 + c2_r3] * c2_e_A[6 + c2_r2];
  if ((c2_e_A[c2_r1] == 0.0) || (c2_e_A[3 + c2_r2] == 0.0) || (c2_e_A[6 + c2_r3]
       == 0.0)) {
    c2_warning(chartInstance);
  }

  for (c2_k = 0; c2_k + 1 < 4; c2_k++) {
    c2_qb_x = c2_d_A[c2_k];
    c2_v_y = c2_e_A[c2_r1];
    c2_rb_x = c2_qb_x;
    c2_w_y = c2_v_y;
    c2_d_z = c2_rb_x / c2_w_y;
    c2_e_y[c2_k + 3 * c2_r1] = c2_d_z;
    c2_e_y[c2_k + 3 * c2_r2] = c2_d_A[3 + c2_k] - c2_e_y[c2_k + 3 * c2_r1] *
      c2_e_A[3 + c2_r1];
    c2_e_y[c2_k + 3 * c2_r3] = c2_d_A[6 + c2_k] - c2_e_y[c2_k + 3 * c2_r1] *
      c2_e_A[6 + c2_r1];
    c2_sb_x = c2_e_y[c2_k + 3 * c2_r2];
    c2_x_y = c2_e_A[3 + c2_r2];
    c2_tb_x = c2_sb_x;
    c2_y_y = c2_x_y;
    c2_e_z = c2_tb_x / c2_y_y;
    c2_e_y[c2_k + 3 * c2_r2] = c2_e_z;
    c2_e_y[c2_k + 3 * c2_r3] -= c2_e_y[c2_k + 3 * c2_r2] * c2_e_A[6 + c2_r2];
    c2_ub_x = c2_e_y[c2_k + 3 * c2_r3];
    c2_ab_y = c2_e_A[6 + c2_r3];
    c2_vb_x = c2_ub_x;
    c2_bb_y = c2_ab_y;
    c2_f_z = c2_vb_x / c2_bb_y;
    c2_e_y[c2_k + 3 * c2_r3] = c2_f_z;
    c2_e_y[c2_k + 3 * c2_r2] -= c2_e_y[c2_k + 3 * c2_r3] * c2_e_A[3 + c2_r3];
    c2_e_y[c2_k + 3 * c2_r1] -= c2_e_y[c2_k + 3 * c2_r3] * c2_e_A[c2_r3];
    c2_e_y[c2_k + 3 * c2_r1] -= c2_e_y[c2_k + 3 * c2_r2] * c2_e_A[c2_r2];
  }
}

static void c2_mldivide(SFc2_gnc2_libInstanceStruct *chartInstance, real_T
  c2_d_A[100], real_T c2_B[30], real_T c2_Y[30])
{
  int32_T c2_i498;
  real_T c2_e_A[100];
  int32_T c2_ipiv[10];
  int32_T c2_info;
  int32_T c2_i499;
  int32_T c2_xi;
  int32_T c2_j;
  int32_T c2_ip;
  int32_T c2_xj;
  int32_T c2_b_j;
  int32_T c2_jBcol;
  int32_T c2_k;
  real_T c2_temp;
  int32_T c2_b_jBcol;
  int32_T c2_b_k;
  int32_T c2_kAcol;
  int32_T c2_i500;
  int32_T c2_b_kAcol;
  boolean_T c2_overflow;
  real_T c2_x;
  real_T c2_e_y;
  int32_T c2_i;
  real_T c2_b_x;
  real_T c2_f_y;
  real_T c2_z;
  int32_T c2_i501;
  int32_T c2_b;
  int32_T c2_b_b;
  boolean_T c2_b_overflow;
  int32_T c2_b_i;
  for (c2_i498 = 0; c2_i498 < 100; c2_i498++) {
    c2_e_A[c2_i498] = c2_d_A[c2_i498];
  }

  c2_b_xgetrf(chartInstance, c2_e_A, c2_ipiv, &c2_info);
  if ((real_T)c2_info > 0.0) {
    c2_warning(chartInstance);
  }

  for (c2_i499 = 0; c2_i499 < 30; c2_i499++) {
    c2_Y[c2_i499] = c2_B[c2_i499];
  }

  for (c2_xi = 0; c2_xi + 1 < 10; c2_xi++) {
    if (c2_ipiv[c2_xi] != c2_xi + 1) {
      c2_ip = c2_ipiv[c2_xi] - 1;
      for (c2_xj = 0; c2_xj + 1 < 4; c2_xj++) {
        c2_temp = c2_Y[c2_xi + 10 * c2_xj];
        c2_Y[c2_xi + 10 * c2_xj] = c2_Y[c2_ip + 10 * c2_xj];
        c2_Y[c2_ip + 10 * c2_xj] = c2_temp;
      }
    }
  }

  for (c2_j = 0; c2_j + 1 < 4; c2_j++) {
    c2_jBcol = 10 * c2_j - 1;
    for (c2_k = 1; c2_k < 11; c2_k++) {
      c2_kAcol = 10 * (c2_k - 1) - 1;
      if (c2_Y[c2_k + c2_jBcol] != 0.0) {
        c2_i500 = c2_k;
        c2_overflow = false;
        if (c2_overflow) {
          c2_check_forloop_overflow_error(chartInstance, c2_overflow);
        }

        for (c2_i = c2_i500 + 1; c2_i < 11; c2_i++) {
          c2_Y[c2_i + c2_jBcol] -= c2_Y[c2_k + c2_jBcol] * c2_e_A[c2_i +
            c2_kAcol];
        }
      }
    }
  }

  for (c2_b_j = 0; c2_b_j + 1 < 4; c2_b_j++) {
    c2_b_jBcol = 10 * c2_b_j - 1;
    for (c2_b_k = 10; c2_b_k > 0; c2_b_k--) {
      c2_b_kAcol = 10 * (c2_b_k - 1) - 1;
      if (c2_Y[c2_b_k + c2_b_jBcol] != 0.0) {
        c2_x = c2_Y[c2_b_k + c2_b_jBcol];
        c2_e_y = c2_e_A[c2_b_k + c2_b_kAcol];
        c2_b_x = c2_x;
        c2_f_y = c2_e_y;
        c2_z = c2_b_x / c2_f_y;
        c2_Y[c2_b_k + c2_b_jBcol] = c2_z;
        c2_i501 = c2_b_k - 1;
        c2_b = c2_i501;
        c2_b_b = c2_b;
        c2_b_overflow = ((!(1 > c2_b_b)) && (c2_b_b > 2147483646));
        if (c2_b_overflow) {
          c2_check_forloop_overflow_error(chartInstance, c2_b_overflow);
        }

        for (c2_b_i = 1; c2_b_i <= c2_i501; c2_b_i++) {
          c2_Y[c2_b_i + c2_b_jBcol] -= c2_Y[c2_b_k + c2_b_jBcol] * c2_e_A[c2_b_i
            + c2_b_kAcol];
        }
      }
    }
  }
}

static void c2_xgetrf(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_d_A
                      [100], real_T c2_e_A[100], int32_T c2_ipiv[10], int32_T
                      *c2_info)
{
  int32_T c2_i502;
  for (c2_i502 = 0; c2_i502 < 100; c2_i502++) {
    c2_e_A[c2_i502] = c2_d_A[c2_i502];
  }

  c2_b_xgetrf(chartInstance, c2_e_A, c2_ipiv, c2_info);
}

static void c2_check_forloop_overflow_error(SFc2_gnc2_libInstanceStruct
  *chartInstance, boolean_T c2_overflow)
{
  const mxArray *c2_e_y = NULL;
  static char_T c2_cv2[34] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'i', 'n', 't', '_', 'f', 'o', 'r', 'l', 'o', 'o', 'p',
    '_', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w' };

  const mxArray *c2_f_y = NULL;
  static char_T c2_cv3[5] = { 'i', 'n', 't', '3', '2' };

  (void)chartInstance;
  if (!c2_overflow) {
  } else {
    c2_e_y = NULL;
    sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_cv2, 10, 0U, 1U, 0U, 2, 1, 34),
                  false);
    c2_f_y = NULL;
    sf_mex_assign(&c2_f_y, sf_mex_create("y", c2_cv3, 10, 0U, 1U, 0U, 2, 1, 5),
                  false);
    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                      sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message",
      1U, 2U, 14, c2_e_y, 14, c2_f_y));
  }
}

static void c2_b_mldivide(SFc2_gnc2_libInstanceStruct *chartInstance, real_T
  c2_d_A[100], real_T c2_B[10], real_T c2_Y[10])
{
  int32_T c2_i503;
  real_T c2_e_A[100];
  int32_T c2_ipiv[10];
  int32_T c2_info;
  int32_T c2_i504;
  int32_T c2_xi;
  int32_T c2_k;
  int32_T c2_ip;
  real_T c2_temp;
  int32_T c2_b_k;
  int32_T c2_kAcol;
  int32_T c2_i505;
  int32_T c2_b_kAcol;
  boolean_T c2_overflow;
  real_T c2_x;
  real_T c2_e_y;
  int32_T c2_i;
  real_T c2_b_x;
  real_T c2_f_y;
  real_T c2_z;
  int32_T c2_i506;
  int32_T c2_b;
  int32_T c2_b_b;
  boolean_T c2_b_overflow;
  int32_T c2_b_i;
  for (c2_i503 = 0; c2_i503 < 100; c2_i503++) {
    c2_e_A[c2_i503] = c2_d_A[c2_i503];
  }

  c2_b_xgetrf(chartInstance, c2_e_A, c2_ipiv, &c2_info);
  if ((real_T)c2_info > 0.0) {
    c2_warning(chartInstance);
  }

  for (c2_i504 = 0; c2_i504 < 10; c2_i504++) {
    c2_Y[c2_i504] = c2_B[c2_i504];
  }

  for (c2_xi = 0; c2_xi + 1 < 10; c2_xi++) {
    if (c2_ipiv[c2_xi] != c2_xi + 1) {
      c2_ip = c2_ipiv[c2_xi] - 1;
      c2_temp = c2_Y[c2_xi];
      c2_Y[c2_xi] = c2_Y[c2_ip];
      c2_Y[c2_ip] = c2_temp;
    }
  }

  for (c2_k = 0; c2_k + 1 < 11; c2_k++) {
    c2_kAcol = 10 * c2_k - 1;
    if (c2_Y[c2_k] != 0.0) {
      c2_i505 = c2_k + 1;
      c2_overflow = false;
      if (c2_overflow) {
        c2_check_forloop_overflow_error(chartInstance, c2_overflow);
      }

      for (c2_i = c2_i505 + 1; c2_i < 11; c2_i++) {
        c2_Y[c2_i - 1] -= c2_Y[c2_k] * c2_e_A[c2_i + c2_kAcol];
      }
    }
  }

  for (c2_b_k = 9; c2_b_k + 1 > 0; c2_b_k--) {
    c2_b_kAcol = 10 * c2_b_k - 1;
    if (c2_Y[c2_b_k] != 0.0) {
      c2_x = c2_Y[c2_b_k];
      c2_e_y = c2_e_A[(c2_b_k + c2_b_kAcol) + 1];
      c2_b_x = c2_x;
      c2_f_y = c2_e_y;
      c2_z = c2_b_x / c2_f_y;
      c2_Y[c2_b_k] = c2_z;
      c2_i506 = c2_b_k;
      c2_b = c2_i506;
      c2_b_b = c2_b;
      c2_b_overflow = ((!(1 > c2_b_b)) && (c2_b_b > 2147483646));
      if (c2_b_overflow) {
        c2_check_forloop_overflow_error(chartInstance, c2_b_overflow);
      }

      for (c2_b_i = 0; c2_b_i + 1 <= c2_i506; c2_b_i++) {
        c2_Y[c2_b_i] -= c2_Y[c2_b_k] * c2_e_A[(c2_b_i + c2_b_kAcol) + 1];
      }
    }
  }
}

static void c2_parse_ecos(SFc2_gnc2_libInstanceStruct *chartInstance, real_T
  c2_xi[10], real_T c2_xf[7], real_T c2_b_J[9], real_T c2_d_EH[10000], real_T
  c2_d_BE[3000], real_T c2_ES[100], real_T c2_AR[100], real_T c2_b_T_max, real_T
  c2_b_w_max, real_T c2_b_s_max, real_T c2_b_s_min, real_T c2_b_w_v, real_T
  c2_c[332], real_T c2_d_G[117528], real_T c2_h[354], real_T c2_d_A[38844],
  real_T c2_b[117])
{
  uint32_T c2_debug_family_var_map[33];
  real_T c2_u_max[30];
  real_T c2_Nx;
  real_T c2_Nu;
  real_T c2_Hg[332];
  real_T c2_Hs[332];
  real_T c2_hlin[322];
  real_T c2_hquad[32];
  real_T c2_c_w_max[30];
  real_T c2_N;
  real_T c2_nargin = 15.0;
  real_T c2_nargout = 5.0;
  int32_T c2_i507;
  int32_T c2_i508;
  int32_T c2_i509;
  real_T c2_c_J[9];
  real_T c2_dv52[9];
  int32_T c2_i510;
  int32_T c2_i511;
  real_T c2_dv53[100];
  static real_T c2_dv54[100] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1.0 };

  int32_T c2_i512;
  int32_T c2_i513;
  int32_T c2_i514;
  int32_T c2_i515;
  real_T c2_dv55[30];
  int32_T c2_i516;
  int32_T c2_i517;
  int32_T c2_i518;
  real_T c2_dv56[3000];
  int32_T c2_i519;
  int32_T c2_i520;
  int32_T c2_i521;
  int32_T c2_i522;
  int32_T c2_i523;
  int32_T c2_i524;
  int32_T c2_i525;
  real_T c2_dv57[900];
  int32_T c2_i526;
  int32_T c2_i527;
  int32_T c2_i528;
  int32_T c2_i529;
  int32_T c2_i530;
  int32_T c2_i531;
  int32_T c2_i532;
  int32_T c2_i533;
  int32_T c2_i534;
  int32_T c2_i535;
  int32_T c2_i536;
  int32_T c2_i537;
  int32_T c2_i538;
  int32_T c2_i539;
  int32_T c2_i540;
  int32_T c2_i541;
  int32_T c2_i542;
  int32_T c2_i543;
  int32_T c2_i544;
  int32_T c2_i545;
  int32_T c2_i546;
  int32_T c2_i547;
  int32_T c2_i548;
  int32_T c2_i549;
  int32_T c2_i550;
  static real_T c2_x[332] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  int32_T c2_i551;
  static real_T c2_dv59[332] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  int32_T c2_i552;
  int32_T c2_i553;
  int32_T c2_i554;
  int32_T c2_i555;
  int32_T c2_i556;
  int32_T c2_i557;
  real_T c2_a;
  int32_T c2_i558;
  int32_T c2_i559;
  real_T c2_e_y[100];
  int32_T c2_i560;
  int32_T c2_i561;
  int32_T c2_i562;
  int32_T c2_i563;
  int32_T c2_i564;
  int32_T c2_i565;
  int32_T c2_i566;
  int32_T c2_i567;
  int32_T c2_i568;
  static real_T c2_dv61[3320] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  int32_T c2_i569;
  int32_T c2_i570;
  int32_T c2_i571;
  int32_T c2_i572;
  int32_T c2_i573;
  int32_T c2_i574;
  int32_T c2_i575;
  int32_T c2_i576;
  int32_T c2_i577;
  int32_T c2_i578;
  int32_T c2_i579;
  int32_T c2_i580;
  int32_T c2_i581;
  int32_T c2_i582;
  int32_T c2_i583;
  int32_T c2_i584;
  int32_T c2_i585;
  int32_T c2_i586;
  int32_T c2_i587;
  static real_T c2_dv62[2324] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0 };

  int32_T c2_i588;
  int32_T c2_i589;
  int32_T c2_i590;
  int32_T c2_i591;
  int32_T c2_i592;
  int32_T c2_i593;
  int32_T c2_i594;
  int32_T c2_i595;
  int32_T c2_i596;
  int32_T c2_i597;
  int32_T c2_i598;
  int32_T c2_i599;
  int32_T c2_i600;
  int32_T c2_i601;
  int32_T c2_i602;
  int32_T c2_i603;
  int32_T c2_i604;
  int32_T c2_i605;
  int32_T c2_i606;
  int32_T c2_i607;
  int32_T c2_i608;
  int32_T c2_i609;
  int32_T c2_i610;
  int32_T c2_i611;
  int32_T c2_i612;
  int32_T c2_i613;
  int32_T c2_i614;
  int32_T c2_i615;
  int32_T c2_i616;
  int32_T c2_i617;
  int32_T c2_i618;
  int32_T c2_i619;
  int32_T c2_i620;
  static real_T c2_z[332] = { -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.70710678118654746, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0 };

  int32_T c2_i621;
  int32_T c2_i622;
  int32_T c2_i623;
  int32_T c2_i624;
  int32_T c2_i625;
  static real_T c2_b_z[332] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.70710678118654746, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  int32_T c2_i626;
  int32_T c2_i627;
  int32_T c2_i628;
  int32_T c2_i629;
  int32_T c2_i630;
  int32_T c2_i631;
  int32_T c2_i632;
  int32_T c2_i633;
  int32_T c2_i634;
  int32_T c2_i635;
  int32_T c2_i636;
  int32_T c2_i637;
  int32_T c2_i638;
  int32_T c2_i639;
  int32_T c2_i640;
  static real_T c2_dv63[32] = { 0.70710678118654746, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.70710678118654746 };

  int32_T c2_i641;
  int32_T c2_i642;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 33U, 34U, c2_g_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_u_max, 0U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Nx, 1U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Nu, 2U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_Hw, 3U,
    c2_lb_sf_marshallOut, c2_ib_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_Hu, 4U,
    c2_lb_sf_marshallOut, c2_ib_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_Hv, 5U,
    c2_jb_sf_marshallOut, c2_gb_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_Hg, 6U, c2_kb_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Hs, 7U, c2_kb_sf_marshallOut,
    c2_hb_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_Hev, 8U,
    c2_jb_sf_marshallOut, c2_gb_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_Glin, 9U,
    c2_ib_sf_marshallOut, c2_fb_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_Gquad, 10U,
    c2_hb_sf_marshallOut, c2_eb_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_hlin, 11U, c2_gb_sf_marshallOut,
    c2_db_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_hquad, 12U, c2_fb_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_c_w_max, MAX_uint32_T,
    c2_d_sf_marshallOut, c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_N, 14U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 15U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 16U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_xi, 17U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_xf, 18U, c2_u_sf_marshallOut,
    c2_r_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_J, 19U, c2_g_sf_marshallOut,
    c2_s_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_d_EH, 20U, c2_t_sf_marshallOut,
    c2_q_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_d_BE, 21U, c2_s_sf_marshallOut,
    c2_p_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_ES, 22U, c2_e_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_AR, 23U, c2_e_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_T_max, 24U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_w_max, 13U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_s_max, 25U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_s_min, 26U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_w_v, 27U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_c, 28U, c2_r_sf_marshallOut,
    c2_o_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_d_G, 29U, c2_q_sf_marshallOut,
    c2_n_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_h, 30U, c2_p_sf_marshallOut,
    c2_m_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_d_A, 31U, c2_o_sf_marshallOut,
    c2_l_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b, 32U, c2_n_sf_marshallOut,
    c2_k_sf_marshallIn);
  c2_N = 10.0;
  CV_EML_FCN(0, 5);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 279);
  for (c2_i507 = 0; c2_i507 < 30; c2_i507++) {
    c2_u_max[c2_i507] = c2_b_T_max;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 280);
  for (c2_i508 = 0; c2_i508 < 30; c2_i508++) {
    c2_c_w_max[c2_i508] = c2_b_w_max;
  }

  _SFD_SYMBOL_SWITCH(13U, 13U);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 281);
  c2_Nx = 10.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 282);
  c2_Nu = 3.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 284);
  for (c2_i509 = 0; c2_i509 < 9; c2_i509++) {
    c2_c_J[c2_i509] = c2_b_J[c2_i509];
  }

  c2_inv(chartInstance, c2_c_J, c2_dv52);
  for (c2_i510 = 0; c2_i510 < 100; c2_i510++) {
    c2_dv53[c2_i510] = c2_dv54[c2_i510];
  }

  c2_i511 = 0;
  for (c2_i512 = 0; c2_i512 < 4; c2_i512++) {
    for (c2_i514 = 0; c2_i514 < 3; c2_i514++) {
      c2_dv55[c2_i514 + c2_i511] = 0.0;
    }

    c2_i511 += 3;
  }

  c2_i513 = 0;
  for (c2_i515 = 0; c2_i515 < 3; c2_i515++) {
    for (c2_i517 = 0; c2_i517 < 3; c2_i517++) {
      c2_dv55[(c2_i517 + c2_i513) + 12] = c2_dv52[c2_i517 + c2_i513];
    }

    c2_i513 += 3;
  }

  c2_i516 = 0;
  for (c2_i518 = 0; c2_i518 < 3; c2_i518++) {
    for (c2_i519 = 0; c2_i519 < 3; c2_i519++) {
      c2_dv55[(c2_i519 + c2_i516) + 21] = 0.0;
    }

    c2_i516 += 3;
  }

  c2_kron(chartInstance, c2_dv53, c2_dv55, c2_dv56);
  c2_i520 = 0;
  for (c2_i521 = 0; c2_i521 < 100; c2_i521++) {
    for (c2_i523 = 0; c2_i523 < 30; c2_i523++) {
      chartInstance->c2_Hw[c2_i523 + c2_i520] = c2_dv56[c2_i523 + c2_i520];
    }

    c2_i520 += 30;
  }

  c2_i522 = 0;
  for (c2_i524 = 0; c2_i524 < 232; c2_i524++) {
    for (c2_i525 = 0; c2_i525 < 30; c2_i525++) {
      chartInstance->c2_Hw[(c2_i525 + c2_i522) + 3000] = 0.0;
    }

    c2_i522 += 30;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 285);
  c2_b_eye(chartInstance, c2_dv57);
  c2_i526 = 0;
  for (c2_i527 = 0; c2_i527 < 100; c2_i527++) {
    for (c2_i529 = 0; c2_i529 < 30; c2_i529++) {
      chartInstance->c2_Hu[c2_i529 + c2_i526] = 0.0;
    }

    c2_i526 += 30;
  }

  c2_i528 = 0;
  for (c2_i530 = 0; c2_i530 < 30; c2_i530++) {
    for (c2_i532 = 0; c2_i532 < 30; c2_i532++) {
      chartInstance->c2_Hu[(c2_i532 + c2_i528) + 3000] = c2_dv57[c2_i532 +
        c2_i528];
    }

    c2_i528 += 30;
  }

  c2_i531 = 0;
  for (c2_i533 = 0; c2_i533 < 202; c2_i533++) {
    for (c2_i534 = 0; c2_i534 < 30; c2_i534++) {
      chartInstance->c2_Hu[(c2_i534 + c2_i531) + 3900] = 0.0;
    }

    c2_i531 += 30;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 286);
  c2_c_eye(chartInstance, chartInstance->c2_dv58);
  c2_i535 = 0;
  for (c2_i536 = 0; c2_i536 < 100; c2_i536++) {
    for (c2_i538 = 0; c2_i538 < 100; c2_i538++) {
      chartInstance->c2_Hv[c2_i538 + c2_i535] = 0.0;
    }

    c2_i535 += 100;
  }

  c2_i537 = 0;
  for (c2_i539 = 0; c2_i539 < 30; c2_i539++) {
    for (c2_i541 = 0; c2_i541 < 100; c2_i541++) {
      chartInstance->c2_Hv[(c2_i541 + c2_i537) + 10000] = 0.0;
    }

    c2_i537 += 100;
  }

  c2_i540 = 0;
  for (c2_i542 = 0; c2_i542 < 2; c2_i542++) {
    for (c2_i544 = 0; c2_i544 < 100; c2_i544++) {
      chartInstance->c2_Hv[(c2_i544 + c2_i540) + 13000] = 0.0;
    }

    c2_i540 += 100;
  }

  c2_i543 = 0;
  for (c2_i545 = 0; c2_i545 < 100; c2_i545++) {
    for (c2_i547 = 0; c2_i547 < 100; c2_i547++) {
      chartInstance->c2_Hv[(c2_i547 + c2_i543) + 13200] = chartInstance->
        c2_dv58[c2_i547 + c2_i543];
    }

    c2_i543 += 100;
  }

  c2_i546 = 0;
  for (c2_i548 = 0; c2_i548 < 100; c2_i548++) {
    for (c2_i549 = 0; c2_i549 < 100; c2_i549++) {
      chartInstance->c2_Hv[(c2_i549 + c2_i546) + 23200] = 0.0;
    }

    c2_i546 += 100;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 288);
  for (c2_i550 = 0; c2_i550 < 332; c2_i550++) {
    c2_Hg[c2_i550] = c2_x[c2_i550];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 289);
  for (c2_i551 = 0; c2_i551 < 332; c2_i551++) {
    c2_Hs[c2_i551] = c2_dv59[c2_i551];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 290);
  c2_c_eye(chartInstance, chartInstance->c2_dv58);
  c2_i552 = 0;
  for (c2_i553 = 0; c2_i553 < 232; c2_i553++) {
    for (c2_i555 = 0; c2_i555 < 100; c2_i555++) {
      chartInstance->c2_Hev[c2_i555 + c2_i552] = 0.0;
    }

    c2_i552 += 100;
  }

  c2_i554 = 0;
  for (c2_i556 = 0; c2_i556 < 100; c2_i556++) {
    for (c2_i557 = 0; c2_i557 < 100; c2_i557++) {
      chartInstance->c2_Hev[(c2_i557 + c2_i554) + 23200] =
        chartInstance->c2_dv58[c2_i557 + c2_i554];
    }

    c2_i554 += 100;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 293);
  c2_a = c2_b_w_v;
  for (c2_i558 = 0; c2_i558 < 100; c2_i558++) {
    c2_e_y[c2_i558] = c2_a;
  }

  for (c2_i559 = 0; c2_i559 < 130; c2_i559++) {
    c2_c[c2_i559] = 0.0;
  }

  c2_c[130] = 1.0;
  c2_c[131] = 0.0;
  for (c2_i560 = 0; c2_i560 < 100; c2_i560++) {
    c2_c[c2_i560 + 132] = 0.0;
  }

  for (c2_i561 = 0; c2_i561 < 100; c2_i561++) {
    c2_c[c2_i561 + 232] = c2_e_y[c2_i561];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 295);
  c2_d_eye(chartInstance, chartInstance->c2_dv58);
  c2_c_eye(chartInstance, chartInstance->c2_dv60);
  c2_i562 = 0;
  c2_i563 = 0;
  for (c2_i564 = 0; c2_i564 < 332; c2_i564++) {
    for (c2_i566 = 0; c2_i566 < 10; c2_i566++) {
      c2_d_A[c2_i566 + c2_i562] = c2_dv61[c2_i566 + c2_i563];
    }

    c2_i562 += 117;
    c2_i563 += 10;
  }

  c2_i565 = 0;
  c2_i567 = 0;
  for (c2_i568 = 0; c2_i568 < 100; c2_i568++) {
    for (c2_i570 = 0; c2_i570 < 100; c2_i570++) {
      c2_d_A[(c2_i570 + c2_i565) + 10] = c2_d_EH[c2_i570 + c2_i567] -
        chartInstance->c2_dv58[c2_i570 + c2_i567];
    }

    c2_i565 += 117;
    c2_i567 += 100;
  }

  c2_i569 = 0;
  c2_i571 = 0;
  for (c2_i572 = 0; c2_i572 < 30; c2_i572++) {
    for (c2_i574 = 0; c2_i574 < 100; c2_i574++) {
      c2_d_A[(c2_i574 + c2_i569) + 11710] = c2_d_BE[c2_i574 + c2_i571];
    }

    c2_i569 += 117;
    c2_i571 += 100;
  }

  for (c2_i573 = 0; c2_i573 < 100; c2_i573++) {
    c2_d_A[c2_i573 + 15220] = 0.0;
  }

  for (c2_i575 = 0; c2_i575 < 100; c2_i575++) {
    c2_d_A[c2_i575 + 15337] = c2_ES[c2_i575];
  }

  c2_i576 = 0;
  c2_i577 = 0;
  for (c2_i578 = 0; c2_i578 < 100; c2_i578++) {
    for (c2_i580 = 0; c2_i580 < 100; c2_i580++) {
      c2_d_A[(c2_i580 + c2_i576) + 15454] = chartInstance->c2_dv60[c2_i580 +
        c2_i577];
    }

    c2_i576 += 117;
    c2_i577 += 100;
  }

  c2_i579 = 0;
  for (c2_i581 = 0; c2_i581 < 100; c2_i581++) {
    for (c2_i583 = 0; c2_i583 < 100; c2_i583++) {
      c2_d_A[(c2_i583 + c2_i579) + 27154] = 0.0;
    }

    c2_i579 += 117;
  }

  c2_i582 = 0;
  c2_i584 = 0;
  for (c2_i585 = 0; c2_i585 < 332; c2_i585++) {
    for (c2_i586 = 0; c2_i586 < 7; c2_i586++) {
      c2_d_A[(c2_i586 + c2_i582) + 110] = c2_dv62[c2_i586 + c2_i584];
    }

    c2_i582 += 117;
    c2_i584 += 7;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 298);
  for (c2_i587 = 0; c2_i587 < 10; c2_i587++) {
    c2_b[c2_i587] = c2_xi[c2_i587];
  }

  for (c2_i588 = 0; c2_i588 < 100; c2_i588++) {
    c2_b[c2_i588 + 10] = -c2_AR[c2_i588];
  }

  for (c2_i589 = 0; c2_i589 < 7; c2_i589++) {
    c2_b[c2_i589 + 110] = c2_xf[c2_i589];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 300);
  c2_i590 = 0;
  c2_i591 = 0;
  for (c2_i592 = 0; c2_i592 < 332; c2_i592++) {
    for (c2_i594 = 0; c2_i594 < 30; c2_i594++) {
      chartInstance->c2_Glin[c2_i594 + c2_i590] = chartInstance->c2_Hw[c2_i594 +
        c2_i591];
    }

    c2_i590 += 322;
    c2_i591 += 30;
  }

  c2_i593 = 0;
  c2_i595 = 0;
  for (c2_i596 = 0; c2_i596 < 332; c2_i596++) {
    for (c2_i598 = 0; c2_i598 < 30; c2_i598++) {
      chartInstance->c2_Glin[(c2_i598 + c2_i593) + 30] = -chartInstance->
        c2_Hw[c2_i598 + c2_i595];
    }

    c2_i593 += 322;
    c2_i595 += 30;
  }

  c2_i597 = 0;
  c2_i599 = 0;
  for (c2_i600 = 0; c2_i600 < 332; c2_i600++) {
    for (c2_i602 = 0; c2_i602 < 30; c2_i602++) {
      chartInstance->c2_Glin[(c2_i602 + c2_i597) + 60] = chartInstance->
        c2_Hu[c2_i602 + c2_i599];
    }

    c2_i597 += 322;
    c2_i599 += 30;
  }

  c2_i601 = 0;
  c2_i603 = 0;
  for (c2_i604 = 0; c2_i604 < 332; c2_i604++) {
    for (c2_i606 = 0; c2_i606 < 30; c2_i606++) {
      chartInstance->c2_Glin[(c2_i606 + c2_i601) + 90] = -chartInstance->
        c2_Hu[c2_i606 + c2_i603];
    }

    c2_i601 += 322;
    c2_i603 += 30;
  }

  c2_i605 = 0;
  for (c2_i607 = 0; c2_i607 < 332; c2_i607++) {
    chartInstance->c2_Glin[c2_i605 + 120] = c2_Hs[c2_i607];
    c2_i605 += 322;
  }

  c2_i608 = 0;
  for (c2_i609 = 0; c2_i609 < 332; c2_i609++) {
    chartInstance->c2_Glin[c2_i608 + 121] = -c2_Hs[c2_i609];
    c2_i608 += 322;
  }

  c2_i610 = 0;
  c2_i611 = 0;
  for (c2_i612 = 0; c2_i612 < 332; c2_i612++) {
    for (c2_i614 = 0; c2_i614 < 100; c2_i614++) {
      chartInstance->c2_Glin[(c2_i614 + c2_i610) + 122] = chartInstance->
        c2_Hv[c2_i614 + c2_i611] - chartInstance->c2_Hev[c2_i614 + c2_i611];
    }

    c2_i610 += 322;
    c2_i611 += 100;
  }

  c2_i613 = 0;
  c2_i615 = 0;
  for (c2_i616 = 0; c2_i616 < 332; c2_i616++) {
    for (c2_i617 = 0; c2_i617 < 100; c2_i617++) {
      chartInstance->c2_Glin[(c2_i617 + c2_i613) + 222] = -chartInstance->
        c2_Hv[c2_i617 + c2_i615] - chartInstance->c2_Hev[c2_i617 + c2_i615];
    }

    c2_i613 += 322;
    c2_i615 += 100;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 301);
  c2_i618 = 0;
  for (c2_i619 = 0; c2_i619 < 332; c2_i619++) {
    chartInstance->c2_Gquad[c2_i618] = c2_z[c2_i619];
    c2_i618 += 32;
  }

  c2_i620 = 0;
  c2_i621 = 0;
  for (c2_i622 = 0; c2_i622 < 332; c2_i622++) {
    for (c2_i624 = 0; c2_i624 < 30; c2_i624++) {
      chartInstance->c2_Gquad[(c2_i624 + c2_i620) + 1] = -chartInstance->
        c2_Hu[c2_i624 + c2_i621];
    }

    c2_i620 += 32;
    c2_i621 += 30;
  }

  c2_i623 = 0;
  for (c2_i625 = 0; c2_i625 < 332; c2_i625++) {
    chartInstance->c2_Gquad[c2_i623 + 31] = c2_b_z[c2_i625];
    c2_i623 += 32;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 302);
  c2_i626 = 0;
  c2_i627 = 0;
  for (c2_i628 = 0; c2_i628 < 332; c2_i628++) {
    for (c2_i630 = 0; c2_i630 < 322; c2_i630++) {
      c2_d_G[c2_i630 + c2_i626] = chartInstance->c2_Glin[c2_i630 + c2_i627];
    }

    c2_i626 += 354;
    c2_i627 += 322;
  }

  c2_i629 = 0;
  c2_i631 = 0;
  for (c2_i632 = 0; c2_i632 < 332; c2_i632++) {
    for (c2_i633 = 0; c2_i633 < 32; c2_i633++) {
      c2_d_G[(c2_i633 + c2_i629) + 322] = chartInstance->c2_Gquad[c2_i633 +
        c2_i631];
    }

    c2_i629 += 354;
    c2_i631 += 32;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 303);
  for (c2_i634 = 0; c2_i634 < 30; c2_i634++) {
    c2_hlin[c2_i634] = c2_c_w_max[c2_i634];
  }

  for (c2_i635 = 0; c2_i635 < 30; c2_i635++) {
    c2_hlin[c2_i635 + 30] = c2_c_w_max[c2_i635];
  }

  for (c2_i636 = 0; c2_i636 < 30; c2_i636++) {
    c2_hlin[c2_i636 + 60] = c2_u_max[c2_i636];
  }

  for (c2_i637 = 0; c2_i637 < 30; c2_i637++) {
    c2_hlin[c2_i637 + 90] = c2_u_max[c2_i637];
  }

  c2_hlin[120] = c2_b_s_max;
  c2_hlin[121] = -c2_b_s_min;
  for (c2_i638 = 0; c2_i638 < 100; c2_i638++) {
    c2_hlin[c2_i638 + 122] = 0.0;
  }

  for (c2_i639 = 0; c2_i639 < 100; c2_i639++) {
    c2_hlin[c2_i639 + 222] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 307);
  for (c2_i640 = 0; c2_i640 < 32; c2_i640++) {
    c2_hquad[c2_i640] = c2_dv63[c2_i640];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 308);
  for (c2_i641 = 0; c2_i641 < 322; c2_i641++) {
    c2_h[c2_i641] = c2_hlin[c2_i641];
  }

  for (c2_i642 = 0; c2_i642 < 32; c2_i642++) {
    c2_h[c2_i642 + 322] = c2_dv63[c2_i642];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -308);
  _SFD_SYMBOL_SCOPE_POP();
}

static void c2_inv(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_x[9],
                   real_T c2_e_y[9])
{
  int32_T c2_i643;
  int32_T c2_p1;
  real_T c2_b_x[9];
  int32_T c2_p2;
  int32_T c2_p3;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_e_x;
  real_T c2_absx11;
  real_T c2_f_x;
  real_T c2_g_x;
  real_T c2_h_x;
  real_T c2_absx21;
  real_T c2_i_x;
  real_T c2_j_x;
  real_T c2_k_x;
  real_T c2_absx31;
  real_T c2_t1;
  real_T c2_l_x;
  real_T c2_f_y;
  real_T c2_z;
  real_T c2_m_x;
  real_T c2_g_y;
  real_T c2_b_z;
  real_T c2_n_x;
  real_T c2_o_x;
  real_T c2_p_x;
  real_T c2_h_y;
  real_T c2_q_x;
  real_T c2_r_x;
  real_T c2_s_x;
  real_T c2_i_y;
  int32_T c2_itmp;
  real_T c2_t_x;
  real_T c2_j_y;
  real_T c2_c_z;
  real_T c2_u_x;
  real_T c2_k_y;
  real_T c2_t3;
  real_T c2_v_x;
  real_T c2_l_y;
  real_T c2_t2;
  int32_T c2_a;
  int32_T c2_c;
  real_T c2_w_x;
  real_T c2_m_y;
  real_T c2_d_z;
  int32_T c2_b_a;
  int32_T c2_b_c;
  int32_T c2_c_a;
  int32_T c2_c_c;
  real_T c2_x_x;
  real_T c2_n_y;
  real_T c2_y_x;
  real_T c2_o_y;
  int32_T c2_d_a;
  int32_T c2_d_c;
  real_T c2_ab_x;
  real_T c2_p_y;
  real_T c2_e_z;
  int32_T c2_e_a;
  int32_T c2_e_c;
  int32_T c2_f_a;
  int32_T c2_f_c;
  real_T c2_q_y;
  real_T c2_bb_x;
  real_T c2_r_y;
  int32_T c2_g_a;
  int32_T c2_g_c;
  real_T c2_cb_x;
  real_T c2_s_y;
  real_T c2_f_z;
  int32_T c2_h_a;
  int32_T c2_h_c;
  int32_T c2_i_a;
  int32_T c2_i_c;
  int32_T c2_i644;
  real_T c2_n1x;
  real_T c2_db_x[9];
  int32_T c2_i645;
  real_T c2_n1xinv;
  real_T c2_t_y[9];
  real_T c2_rc;
  real_T c2_eb_x;
  boolean_T c2_b;
  real_T c2_fb_x;
  const mxArray *c2_u_y = NULL;
  static char_T c2_rfmt[6] = { '%', '1', '4', '.', '6', 'e' };

  const mxArray *c2_v_y = NULL;
  char_T c2_str[14];
  for (c2_i643 = 0; c2_i643 < 9; c2_i643++) {
    c2_b_x[c2_i643] = c2_x[c2_i643];
  }

  c2_p1 = 0;
  c2_p2 = 3;
  c2_p3 = 6;
  c2_c_x = c2_b_x[0];
  c2_d_x = c2_c_x;
  c2_e_x = c2_d_x;
  c2_absx11 = muDoubleScalarAbs(c2_e_x);
  c2_f_x = c2_b_x[1];
  c2_g_x = c2_f_x;
  c2_h_x = c2_g_x;
  c2_absx21 = muDoubleScalarAbs(c2_h_x);
  c2_i_x = c2_b_x[2];
  c2_j_x = c2_i_x;
  c2_k_x = c2_j_x;
  c2_absx31 = muDoubleScalarAbs(c2_k_x);
  if ((c2_absx21 > c2_absx11) && (c2_absx21 > c2_absx31)) {
    c2_p1 = 3;
    c2_p2 = 0;
    c2_t1 = c2_b_x[0];
    c2_b_x[0] = c2_b_x[1];
    c2_b_x[1] = c2_t1;
    c2_t1 = c2_b_x[3];
    c2_b_x[3] = c2_b_x[4];
    c2_b_x[4] = c2_t1;
    c2_t1 = c2_b_x[6];
    c2_b_x[6] = c2_b_x[7];
    c2_b_x[7] = c2_t1;
  } else {
    if (c2_absx31 > c2_absx11) {
      c2_p1 = 6;
      c2_p3 = 0;
      c2_t1 = c2_b_x[0];
      c2_b_x[0] = c2_b_x[2];
      c2_b_x[2] = c2_t1;
      c2_t1 = c2_b_x[3];
      c2_b_x[3] = c2_b_x[5];
      c2_b_x[5] = c2_t1;
      c2_t1 = c2_b_x[6];
      c2_b_x[6] = c2_b_x[8];
      c2_b_x[8] = c2_t1;
    }
  }

  c2_l_x = c2_b_x[1];
  c2_f_y = c2_b_x[0];
  c2_z = c2_l_x / c2_f_y;
  c2_b_x[1] = c2_z;
  c2_m_x = c2_b_x[2];
  c2_g_y = c2_b_x[0];
  c2_b_z = c2_m_x / c2_g_y;
  c2_b_x[2] = c2_b_z;
  c2_b_x[4] -= c2_b_x[1] * c2_b_x[3];
  c2_b_x[5] -= c2_b_x[2] * c2_b_x[3];
  c2_b_x[7] -= c2_b_x[1] * c2_b_x[6];
  c2_b_x[8] -= c2_b_x[2] * c2_b_x[6];
  c2_n_x = c2_b_x[5];
  c2_o_x = c2_n_x;
  c2_p_x = c2_o_x;
  c2_h_y = muDoubleScalarAbs(c2_p_x);
  c2_q_x = c2_b_x[4];
  c2_r_x = c2_q_x;
  c2_s_x = c2_r_x;
  c2_i_y = muDoubleScalarAbs(c2_s_x);
  if (c2_h_y > c2_i_y) {
    c2_itmp = c2_p2;
    c2_p2 = c2_p3;
    c2_p3 = c2_itmp;
    c2_t1 = c2_b_x[1];
    c2_b_x[1] = c2_b_x[2];
    c2_b_x[2] = c2_t1;
    c2_t1 = c2_b_x[4];
    c2_b_x[4] = c2_b_x[5];
    c2_b_x[5] = c2_t1;
    c2_t1 = c2_b_x[7];
    c2_b_x[7] = c2_b_x[8];
    c2_b_x[8] = c2_t1;
  }

  c2_t_x = c2_b_x[5];
  c2_j_y = c2_b_x[4];
  c2_c_z = c2_t_x / c2_j_y;
  c2_b_x[5] = c2_c_z;
  c2_b_x[8] -= c2_b_x[5] * c2_b_x[7];
  c2_u_x = c2_b_x[5] * c2_b_x[1] - c2_b_x[2];
  c2_k_y = c2_b_x[8];
  c2_t3 = c2_u_x / c2_k_y;
  c2_v_x = -(c2_b_x[1] + c2_b_x[7] * c2_t3);
  c2_l_y = c2_b_x[4];
  c2_t2 = c2_v_x / c2_l_y;
  c2_a = c2_p1;
  c2_c = c2_a;
  c2_w_x = (1.0 - c2_b_x[3] * c2_t2) - c2_b_x[6] * c2_t3;
  c2_m_y = c2_b_x[0];
  c2_d_z = c2_w_x / c2_m_y;
  c2_e_y[c2_c] = c2_d_z;
  c2_b_a = c2_p1;
  c2_b_c = c2_b_a;
  c2_e_y[c2_b_c + 1] = c2_t2;
  c2_c_a = c2_p1;
  c2_c_c = c2_c_a;
  c2_e_y[c2_c_c + 2] = c2_t3;
  c2_x_x = -c2_b_x[5];
  c2_n_y = c2_b_x[8];
  c2_t3 = c2_x_x / c2_n_y;
  c2_y_x = 1.0 - c2_b_x[7] * c2_t3;
  c2_o_y = c2_b_x[4];
  c2_t2 = c2_y_x / c2_o_y;
  c2_d_a = c2_p2;
  c2_d_c = c2_d_a;
  c2_ab_x = -(c2_b_x[3] * c2_t2 + c2_b_x[6] * c2_t3);
  c2_p_y = c2_b_x[0];
  c2_e_z = c2_ab_x / c2_p_y;
  c2_e_y[c2_d_c] = c2_e_z;
  c2_e_a = c2_p2;
  c2_e_c = c2_e_a;
  c2_e_y[c2_e_c + 1] = c2_t2;
  c2_f_a = c2_p2;
  c2_f_c = c2_f_a;
  c2_e_y[c2_f_c + 2] = c2_t3;
  c2_q_y = c2_b_x[8];
  c2_t3 = 1.0 / c2_q_y;
  c2_bb_x = -c2_b_x[7] * c2_t3;
  c2_r_y = c2_b_x[4];
  c2_t2 = c2_bb_x / c2_r_y;
  c2_g_a = c2_p3;
  c2_g_c = c2_g_a;
  c2_cb_x = -(c2_b_x[3] * c2_t2 + c2_b_x[6] * c2_t3);
  c2_s_y = c2_b_x[0];
  c2_f_z = c2_cb_x / c2_s_y;
  c2_e_y[c2_g_c] = c2_f_z;
  c2_h_a = c2_p3;
  c2_h_c = c2_h_a;
  c2_e_y[c2_h_c + 1] = c2_t2;
  c2_i_a = c2_p3;
  c2_i_c = c2_i_a;
  c2_e_y[c2_i_c + 2] = c2_t3;
  for (c2_i644 = 0; c2_i644 < 9; c2_i644++) {
    c2_db_x[c2_i644] = c2_x[c2_i644];
  }

  c2_n1x = c2_norm(chartInstance, c2_db_x);
  for (c2_i645 = 0; c2_i645 < 9; c2_i645++) {
    c2_t_y[c2_i645] = c2_e_y[c2_i645];
  }

  c2_n1xinv = c2_norm(chartInstance, c2_t_y);
  c2_rc = 1.0 / (c2_n1x * c2_n1xinv);
  if ((c2_n1x == 0.0) || (c2_n1xinv == 0.0) || (c2_rc == 0.0)) {
    c2_warning(chartInstance);
  } else {
    c2_eb_x = c2_rc;
    c2_b = muDoubleScalarIsNaN(c2_eb_x);
    if (c2_b || (c2_rc < 2.2204460492503131E-16)) {
      c2_fb_x = c2_rc;
      c2_u_y = NULL;
      sf_mex_assign(&c2_u_y, sf_mex_create("y", c2_rfmt, 10, 0U, 1U, 0U, 2, 1, 6),
                    false);
      c2_v_y = NULL;
      sf_mex_assign(&c2_v_y, sf_mex_create("y", &c2_fb_x, 0, 0U, 0U, 0U, 0),
                    false);
      c2_ob_emlrt_marshallIn(chartInstance, sf_mex_call_debug
        (sfGlobalDebugInstanceStruct, "sprintf", 1U, 2U, 14, c2_u_y, 14, c2_v_y),
        "sprintf", c2_str);
      c2_b_warning(chartInstance, c2_str);
    }
  }
}

static real_T c2_norm(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_x[9])
{
  real_T c2_e_y;
  int32_T c2_j;
  real_T c2_b_j;
  real_T c2_g_s;
  int32_T c2_i;
  real_T c2_b_x;
  real_T c2_b_i;
  boolean_T c2_b;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_e_x;
  real_T c2_f_y;
  boolean_T exitg1;
  (void)chartInstance;
  c2_e_y = 0.0;
  c2_j = 0;
  exitg1 = false;
  while ((!exitg1) && (c2_j < 3)) {
    c2_b_j = 1.0 + (real_T)c2_j;
    c2_g_s = 0.0;
    for (c2_i = 0; c2_i < 3; c2_i++) {
      c2_b_i = 1.0 + (real_T)c2_i;
      c2_c_x = c2_x[((int32_T)c2_b_i + 3 * ((int32_T)c2_b_j - 1)) - 1];
      c2_d_x = c2_c_x;
      c2_e_x = c2_d_x;
      c2_f_y = muDoubleScalarAbs(c2_e_x);
      c2_g_s += c2_f_y;
    }

    c2_b_x = c2_g_s;
    c2_b = muDoubleScalarIsNaN(c2_b_x);
    if (c2_b) {
      c2_e_y = rtNaN;
      exitg1 = true;
    } else {
      if (c2_g_s > c2_e_y) {
        c2_e_y = c2_g_s;
      }

      c2_j++;
    }
  }

  return c2_e_y;
}

static void c2_b_warning(SFc2_gnc2_libInstanceStruct *chartInstance, char_T
  c2_varargin_1[14])
{
  const mxArray *c2_e_y = NULL;
  static char_T c2_cv4[7] = { 'w', 'a', 'r', 'n', 'i', 'n', 'g' };

  const mxArray *c2_f_y = NULL;
  static char_T c2_cv5[7] = { 'm', 'e', 's', 's', 'a', 'g', 'e' };

  const mxArray *c2_g_y = NULL;
  static char_T c2_msgID[33] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T',
    'L', 'A', 'B', ':', 'i', 'l', 'l', 'C', 'o', 'n', 'd', 'i', 't', 'i', 'o',
    'n', 'e', 'd', 'M', 'a', 't', 'r', 'i', 'x' };

  const mxArray *c2_h_y = NULL;
  (void)chartInstance;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_cv4, 10, 0U, 1U, 0U, 2, 1, 7),
                false);
  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", c2_cv5, 10, 0U, 1U, 0U, 2, 1, 7),
                false);
  c2_g_y = NULL;
  sf_mex_assign(&c2_g_y, sf_mex_create("y", c2_msgID, 10, 0U, 1U, 0U, 2, 1, 33),
                false);
  c2_h_y = NULL;
  sf_mex_assign(&c2_h_y, sf_mex_create("y", c2_varargin_1, 10, 0U, 1U, 0U, 2, 1,
    14), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "feval", 0U, 2U, 14, c2_e_y, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "feval", 1U,
    3U, 14, c2_f_y, 14, c2_g_y, 14, c2_h_y));
}

static void c2_kron(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_d_A
                    [100], real_T c2_B[30], real_T c2_K[3000])
{
  int32_T c2_kidx;
  int32_T c2_j1;
  int32_T c2_j2;
  int32_T c2_i1;
  int32_T c2_i2;
  int32_T c2_a;
  (void)chartInstance;
  c2_kidx = -1;
  for (c2_j1 = 0; c2_j1 + 1 < 11; c2_j1++) {
    for (c2_j2 = 0; c2_j2 + 1 < 11; c2_j2++) {
      for (c2_i1 = 0; c2_i1 + 1 < 11; c2_i1++) {
        for (c2_i2 = 0; c2_i2 + 1 < 4; c2_i2++) {
          c2_a = c2_kidx + 1;
          c2_kidx = c2_a;
          c2_K[c2_kidx] = c2_d_A[c2_i1 + 10 * c2_j1] * c2_B[c2_i2 + 3 * c2_j2];
        }
      }
    }
  }
}

static void c2_b_eye(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_I[900])
{
  int32_T c2_i646;
  int32_T c2_k;
  (void)chartInstance;
  for (c2_i646 = 0; c2_i646 < 900; c2_i646++) {
    c2_I[c2_i646] = 0.0;
  }

  for (c2_k = 0; c2_k + 1 < 31; c2_k++) {
    c2_I[c2_k + 30 * c2_k] = 1.0;
  }
}

static void c2_c_eye(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_I
                     [10000])
{
  int32_T c2_i647;
  int32_T c2_k;
  (void)chartInstance;
  for (c2_i647 = 0; c2_i647 < 10000; c2_i647++) {
    c2_I[c2_i647] = 0.0;
  }

  for (c2_k = 0; c2_k + 1 < 101; c2_k++) {
    c2_I[c2_k + 100 * c2_k] = 1.0;
  }
}

static void c2_d_eye(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_I
                     [10000])
{
  int32_T c2_i648;
  int32_T c2_k;
  (void)chartInstance;
  for (c2_i648 = 0; c2_i648 < 10000; c2_i648++) {
    c2_I[c2_i648] = 0.0;
  }

  for (c2_k = 0; c2_k + 1 < 101; c2_k++) {
    c2_I[c2_k + 100 * c2_k] = 1.0;
  }
}

static void c2_convert_to_CCS(SFc2_gnc2_libInstanceStruct *chartInstance, real_T
  c2_e_X[38844], real_T c2_Xir[1278], real_T c2_Xjc[333], real_T c2_Xpr[1278])
{
  uint32_T c2_debug_family_var_map[8];
  real_T c2_col;
  real_T c2_Xir_size;
  real_T c2_nargin = 2.0;
  real_T c2_nargout = 3.0;
  int32_T c2_i649;
  real_T c2_b_Xir[1278];
  real_T c2_b_Xpr[1278];
  int32_T c2_i650;
  int32_T c2_i651;
  int32_T c2_i652;
  int32_T c2_b_col;
  int32_T c2_i653;
  int32_T c2_c_col;
  int32_T c2_i654;
  int32_T c2_n;
  int32_T c2_k;
  int32_T c2_b_n;
  real_T c2_g_s[117];
  int32_T c2_b_k;
  real_T c2_c_n;
  real_T c2_c_k;
  int32_T c2_a;
  real_T c2_d_n;
  real_T c2_d_k;
  int32_T c2_b_a;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 8U, 8U, c2_i_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_col, 0U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Xir_size, 1U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 2U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 3U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_e_X, 4U, c2_o_sf_marshallOut,
    c2_l_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Xir, 5U, c2_m_sf_marshallOut,
    c2_j_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Xjc, 6U, c2_l_sf_marshallOut,
    c2_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Xpr, 7U, c2_m_sf_marshallOut,
    c2_j_sf_marshallIn);
  c2_Xir_size = 1278.0;
  CV_EML_FCN(0, 6);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 314);
  for (c2_i649 = 0; c2_i649 < 38844; c2_i649++) {
    chartInstance->c2_b_X[c2_i649] = c2_e_X[c2_i649];
  }

  c2_my_find(chartInstance, chartInstance->c2_b_X, c2_b_Xir, c2_b_Xpr);
  for (c2_i650 = 0; c2_i650 < 1278; c2_i650++) {
    c2_Xir[c2_i650] = c2_b_Xir[c2_i650];
  }

  for (c2_i651 = 0; c2_i651 < 1278; c2_i651++) {
    c2_Xpr[c2_i651] = c2_b_Xpr[c2_i651];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 315);
  for (c2_i652 = 0; c2_i652 < 333; c2_i652++) {
    c2_Xjc[c2_i652] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 316);
  c2_col = 2.0;
  c2_b_col = 0;
  while (c2_b_col < 331) {
    c2_col = 2.0 + (real_T)c2_b_col;
    CV_EML_FOR(0, 1, 3, 1);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 317);
    c2_c_col = sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 9518, 5, MAX_uint32_T, (int32_T)sf_integer_check
      (chartInstance->S, 1U, 9518U, 5U, c2_col - 1.0), 1, 332) - 1;
    for (c2_i654 = 0; c2_i654 < 117; c2_i654++) {
      c2_g_s[c2_i654] = c2_e_X[c2_i654 + 117 * c2_c_col];
    }

    c2_b_n = 0;
    for (c2_b_k = 0; c2_b_k < 117; c2_b_k++) {
      c2_d_k = 1.0 + (real_T)c2_b_k;
      if (c2_g_s[(int32_T)c2_d_k - 1] != 0.0) {
        c2_b_a = c2_b_n + 1;
        c2_b_n = c2_b_a;
      }
    }

    c2_d_n = (real_T)c2_b_n;
    c2_Xjc[sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 9488, 8, MAX_uint32_T, (int32_T)sf_integer_check
      (chartInstance->S, 1U, 9488U, 8U, c2_col), 1, 333) - 1] =
      c2_Xjc[sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 9499, 10, MAX_uint32_T, (int32_T)sf_integer_check
      (chartInstance->S, 1U, 9499U, 10U, c2_col - 1.0), 1, 333) - 1] + c2_d_n;
    c2_b_col++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 3, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 319);
  for (c2_i653 = 0; c2_i653 < 38844; c2_i653++) {
    chartInstance->c2_c_s[c2_i653] = c2_e_X[c2_i653];
  }

  c2_n = 0;
  for (c2_k = 0; c2_k < 38844; c2_k++) {
    c2_c_k = 1.0 + (real_T)c2_k;
    if (chartInstance->c2_c_s[(int32_T)c2_c_k - 1] != 0.0) {
      c2_a = c2_n + 1;
      c2_n = c2_a;
    }
  }

  c2_c_n = (real_T)c2_n;
  c2_Xjc[332] = c2_c_n;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -319);
  _SFD_SYMBOL_SCOPE_POP();
}

static void c2_my_find(SFc2_gnc2_libInstanceStruct *chartInstance, real_T
  c2_e_X[38844], real_T c2_Xir[1278], real_T c2_Xpr[1278])
{
  uint32_T c2_debug_family_var_map[12];
  real_T c2_n;
  real_T c2_m;
  real_T c2_X_nnz;
  real_T c2_id;
  real_T c2_col;
  real_T c2_row;
  real_T c2_Xir_size;
  real_T c2_nargin = 2.0;
  real_T c2_nargout = 2.0;
  int32_T c2_i655;
  int32_T c2_i656;
  int32_T c2_i657;
  int32_T c2_b_n;
  int32_T c2_k;
  real_T c2_b_k;
  int32_T c2_a;
  int32_T c2_b_col;
  int32_T c2_b_row;
  real_T c2_d2;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 12U, 12U, c2_h_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_n, 0U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_m, 1U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_X_nnz, 2U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_id, 3U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_col, 4U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_row, 5U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Xir_size, 6U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 7U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 8U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_e_X, 9U, c2_o_sf_marshallOut,
    c2_l_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Xir, 10U, c2_m_sf_marshallOut,
    c2_j_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Xpr, 11U, c2_m_sf_marshallOut,
    c2_j_sf_marshallIn);
  c2_Xir_size = 1278.0;
  CV_EML_FCN(0, 7);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 324);
  c2_n = 117.0;
  c2_m = 332.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 325);
  for (c2_i655 = 0; c2_i655 < 1278; c2_i655++) {
    c2_Xir[c2_i655] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 326);
  for (c2_i656 = 0; c2_i656 < 1278; c2_i656++) {
    c2_Xpr[c2_i656] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 327);
  for (c2_i657 = 0; c2_i657 < 38844; c2_i657++) {
    chartInstance->c2_d_s[c2_i657] = c2_e_X[c2_i657];
  }

  c2_b_n = 0;
  for (c2_k = 0; c2_k < 38844; c2_k++) {
    c2_b_k = 1.0 + (real_T)c2_k;
    if (chartInstance->c2_d_s[(int32_T)c2_b_k - 1] != 0.0) {
      c2_a = c2_b_n + 1;
      c2_b_n = c2_a;
    }
  }

  c2_X_nnz = (real_T)c2_b_n;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 328);
  c2_id = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 329);
  c2_col = 1.0;
  c2_b_col = 0;
  while (c2_b_col < 332) {
    c2_col = 1.0 + (real_T)c2_b_col;
    CV_EML_FOR(0, 1, 4, 1);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 330);
    c2_row = 1.0;
    c2_b_row = 0;
    while (c2_b_row < 117) {
      c2_row = 1.0 + (real_T)c2_b_row;
      CV_EML_FOR(0, 1, 5, 1);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 331);
      c2_d2 = c2_e_X[(sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
        chartInstance->S, 1U, 9756, 3, MAX_uint32_T, (int32_T)sf_integer_check
        (chartInstance->S, 1U, 9756U, 3U, c2_row), 1, 117) + 117 *
                      (sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
        chartInstance->S, 1U, 9760, 3, MAX_uint32_T, (int32_T)sf_integer_check
        (chartInstance->S, 1U, 9760U, 3U, c2_col), 1, 332) - 1)) - 1];
      if (CV_EML_COND(0, 1, 2, CV_RELATIONAL_EVAL(4U, 0U, 7, c2_d2, 0.0, -1, 1U,
            c2_d2 != 0.0)) && CV_EML_COND(0, 1, 3, CV_RELATIONAL_EVAL(4U, 0U, 8,
            c2_id, c2_X_nnz + 1.0, -1, 2U, c2_id < c2_X_nnz + 1.0))) {
        CV_EML_MCDC(0, 1, 1, true);
        CV_EML_IF(0, 1, 6, true);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 332);
        c2_Xir[sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
          chartInstance->S, 1U, 9798, 7, MAX_uint32_T, (int32_T)sf_integer_check
          (chartInstance->S, 1U, 9798U, 7U, c2_id), 1, 1278) - 1] = c2_row - 1.0;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 333);
        c2_Xpr[sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
          chartInstance->S, 1U, 9853, 7, MAX_uint32_T, (int32_T)sf_integer_check
          (chartInstance->S, 1U, 9853U, 7U, c2_id), 1, 1278) - 1] = c2_e_X
          [(sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
             chartInstance->S, 1U, 9865, 3, MAX_uint32_T, (int32_T)
             sf_integer_check(chartInstance->S, 1U, 9865U, 3U, c2_row), 1, 117)
            + 117 * (sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
              chartInstance->S, 1U, 9869, 3, MAX_uint32_T, (int32_T)
              sf_integer_check(chartInstance->S, 1U, 9869U, 3U, c2_col), 1, 332)
                     - 1)) - 1];
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 334);
        c2_id++;
      } else {
        CV_EML_MCDC(0, 1, 1, false);
        CV_EML_IF(0, 1, 6, false);
      }

      c2_b_row++;
      _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 5, 0);
    c2_b_col++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 4, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -334);
  _SFD_SYMBOL_SCOPE_POP();
}

static void c2_b_convert_to_CCS(SFc2_gnc2_libInstanceStruct *chartInstance,
  real_T c2_e_X[117528], real_T c2_Xir[674], real_T c2_Xjc[333], real_T c2_Xpr
  [674])
{
  uint32_T c2_debug_family_var_map[8];
  real_T c2_col;
  real_T c2_Xir_size;
  real_T c2_nargin = 2.0;
  real_T c2_nargout = 3.0;
  int32_T c2_i658;
  real_T c2_b_Xir[674];
  real_T c2_b_Xpr[674];
  int32_T c2_i659;
  int32_T c2_i660;
  int32_T c2_i661;
  int32_T c2_b_col;
  int32_T c2_i662;
  int32_T c2_c_col;
  int32_T c2_i663;
  int32_T c2_n;
  int32_T c2_k;
  int32_T c2_b_n;
  real_T c2_g_s[354];
  int32_T c2_b_k;
  real_T c2_c_n;
  real_T c2_c_k;
  int32_T c2_a;
  real_T c2_d_n;
  real_T c2_d_k;
  int32_T c2_b_a;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 8U, 8U, c2_k_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_col, 0U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Xir_size, 1U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 2U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 3U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_e_X, 4U, c2_q_sf_marshallOut,
    c2_n_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Xir, 5U, c2_k_sf_marshallOut,
    c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Xjc, 6U, c2_l_sf_marshallOut,
    c2_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Xpr, 7U, c2_k_sf_marshallOut,
    c2_h_sf_marshallIn);
  c2_Xir_size = 674.0;
  CV_EML_FCN(0, 6);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 314);
  for (c2_i658 = 0; c2_i658 < 117528; c2_i658++) {
    chartInstance->c2_X[c2_i658] = c2_e_X[c2_i658];
  }

  c2_b_my_find(chartInstance, chartInstance->c2_X, c2_b_Xir, c2_b_Xpr);
  for (c2_i659 = 0; c2_i659 < 674; c2_i659++) {
    c2_Xir[c2_i659] = c2_b_Xir[c2_i659];
  }

  for (c2_i660 = 0; c2_i660 < 674; c2_i660++) {
    c2_Xpr[c2_i660] = c2_b_Xpr[c2_i660];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 315);
  for (c2_i661 = 0; c2_i661 < 333; c2_i661++) {
    c2_Xjc[c2_i661] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 316);
  c2_col = 2.0;
  c2_b_col = 0;
  while (c2_b_col < 331) {
    c2_col = 2.0 + (real_T)c2_b_col;
    CV_EML_FOR(0, 1, 3, 1);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 317);
    c2_c_col = sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 9518, 5, MAX_uint32_T, (int32_T)sf_integer_check
      (chartInstance->S, 1U, 9518U, 5U, c2_col - 1.0), 1, 332) - 1;
    for (c2_i663 = 0; c2_i663 < 354; c2_i663++) {
      c2_g_s[c2_i663] = c2_e_X[c2_i663 + 354 * c2_c_col];
    }

    c2_b_n = 0;
    for (c2_b_k = 0; c2_b_k < 354; c2_b_k++) {
      c2_d_k = 1.0 + (real_T)c2_b_k;
      if (c2_g_s[(int32_T)c2_d_k - 1] != 0.0) {
        c2_b_a = c2_b_n + 1;
        c2_b_n = c2_b_a;
      }
    }

    c2_d_n = (real_T)c2_b_n;
    c2_Xjc[sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 9488, 8, MAX_uint32_T, (int32_T)sf_integer_check
      (chartInstance->S, 1U, 9488U, 8U, c2_col), 1, 333) - 1] =
      c2_Xjc[sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 9499, 10, MAX_uint32_T, (int32_T)sf_integer_check
      (chartInstance->S, 1U, 9499U, 10U, c2_col - 1.0), 1, 333) - 1] + c2_d_n;
    c2_b_col++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 3, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 319);
  for (c2_i662 = 0; c2_i662 < 117528; c2_i662++) {
    chartInstance->c2_s[c2_i662] = c2_e_X[c2_i662];
  }

  c2_n = 0;
  for (c2_k = 0; c2_k < 117528; c2_k++) {
    c2_c_k = 1.0 + (real_T)c2_k;
    if (chartInstance->c2_s[(int32_T)c2_c_k - 1] != 0.0) {
      c2_a = c2_n + 1;
      c2_n = c2_a;
    }
  }

  c2_c_n = (real_T)c2_n;
  c2_Xjc[332] = c2_c_n;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -319);
  _SFD_SYMBOL_SCOPE_POP();
}

static void c2_b_my_find(SFc2_gnc2_libInstanceStruct *chartInstance, real_T
  c2_e_X[117528], real_T c2_Xir[674], real_T c2_Xpr[674])
{
  uint32_T c2_debug_family_var_map[12];
  real_T c2_n;
  real_T c2_m;
  real_T c2_X_nnz;
  real_T c2_id;
  real_T c2_col;
  real_T c2_row;
  real_T c2_Xir_size;
  real_T c2_nargin = 2.0;
  real_T c2_nargout = 2.0;
  int32_T c2_i664;
  int32_T c2_i665;
  int32_T c2_i666;
  int32_T c2_b_n;
  int32_T c2_k;
  real_T c2_b_k;
  int32_T c2_a;
  int32_T c2_b_col;
  int32_T c2_b_row;
  real_T c2_d3;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 12U, 12U, c2_j_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_n, 0U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_m, 1U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_X_nnz, 2U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_id, 3U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_col, 4U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_row, 5U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Xir_size, 6U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 7U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 8U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_e_X, 9U, c2_q_sf_marshallOut,
    c2_n_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Xir, 10U, c2_k_sf_marshallOut,
    c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Xpr, 11U, c2_k_sf_marshallOut,
    c2_h_sf_marshallIn);
  c2_Xir_size = 674.0;
  CV_EML_FCN(0, 7);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 324);
  c2_n = 354.0;
  c2_m = 332.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 325);
  for (c2_i664 = 0; c2_i664 < 674; c2_i664++) {
    c2_Xir[c2_i664] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 326);
  for (c2_i665 = 0; c2_i665 < 674; c2_i665++) {
    c2_Xpr[c2_i665] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 327);
  for (c2_i666 = 0; c2_i666 < 117528; c2_i666++) {
    chartInstance->c2_b_s[c2_i666] = c2_e_X[c2_i666];
  }

  c2_b_n = 0;
  for (c2_k = 0; c2_k < 117528; c2_k++) {
    c2_b_k = 1.0 + (real_T)c2_k;
    if (chartInstance->c2_b_s[(int32_T)c2_b_k - 1] != 0.0) {
      c2_a = c2_b_n + 1;
      c2_b_n = c2_a;
    }
  }

  c2_X_nnz = (real_T)c2_b_n;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 328);
  c2_id = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 329);
  c2_col = 1.0;
  c2_b_col = 0;
  while (c2_b_col < 332) {
    c2_col = 1.0 + (real_T)c2_b_col;
    CV_EML_FOR(0, 1, 4, 1);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 330);
    c2_row = 1.0;
    c2_b_row = 0;
    while (c2_b_row < 354) {
      c2_row = 1.0 + (real_T)c2_b_row;
      CV_EML_FOR(0, 1, 5, 1);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 331);
      c2_d3 = c2_e_X[(sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
        chartInstance->S, 1U, 9756, 3, MAX_uint32_T, (int32_T)sf_integer_check
        (chartInstance->S, 1U, 9756U, 3U, c2_row), 1, 354) + 354 *
                      (sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
        chartInstance->S, 1U, 9760, 3, MAX_uint32_T, (int32_T)sf_integer_check
        (chartInstance->S, 1U, 9760U, 3U, c2_col), 1, 332) - 1)) - 1];
      if (CV_EML_COND(0, 1, 2, CV_RELATIONAL_EVAL(4U, 0U, 7, c2_d3, 0.0, -1, 1U,
            c2_d3 != 0.0)) && CV_EML_COND(0, 1, 3, CV_RELATIONAL_EVAL(4U, 0U, 8,
            c2_id, c2_X_nnz + 1.0, -1, 2U, c2_id < c2_X_nnz + 1.0))) {
        CV_EML_MCDC(0, 1, 1, true);
        CV_EML_IF(0, 1, 6, true);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 332);
        c2_Xir[sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
          chartInstance->S, 1U, 9798, 7, MAX_uint32_T, (int32_T)sf_integer_check
          (chartInstance->S, 1U, 9798U, 7U, c2_id), 1, 674) - 1] = c2_row - 1.0;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 333);
        c2_Xpr[sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
          chartInstance->S, 1U, 9853, 7, MAX_uint32_T, (int32_T)sf_integer_check
          (chartInstance->S, 1U, 9853U, 7U, c2_id), 1, 674) - 1] = c2_e_X
          [(sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
             chartInstance->S, 1U, 9865, 3, MAX_uint32_T, (int32_T)
             sf_integer_check(chartInstance->S, 1U, 9865U, 3U, c2_row), 1, 354)
            + 354 * (sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
              chartInstance->S, 1U, 9869, 3, MAX_uint32_T, (int32_T)
              sf_integer_check(chartInstance->S, 1U, 9869U, 3U, c2_col), 1, 332)
                     - 1)) - 1];
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 334);
        c2_id++;
      } else {
        CV_EML_MCDC(0, 1, 1, false);
        CV_EML_IF(0, 1, 6, false);
      }

      c2_b_row++;
      _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 5, 0);
    c2_b_col++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 4, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -334);
  _SFD_SYMBOL_SCOPE_POP();
}

static real_T c2_b_norm(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_x
  [100])
{
  real_T c2_e_y;
  int32_T c2_k;
  real_T c2_b_k;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_f_y;
  (void)chartInstance;
  c2_e_y = 0.0;
  for (c2_k = 0; c2_k < 100; c2_k++) {
    c2_b_k = 1.0 + (real_T)c2_k;
    c2_b_x = c2_x[(int32_T)c2_b_k - 1];
    c2_c_x = c2_b_x;
    c2_d_x = c2_c_x;
    c2_f_y = muDoubleScalarAbs(c2_d_x);
    c2_e_y += c2_f_y;
  }

  return c2_e_y;
}

static real_T c2_c_norm(SFc2_gnc2_libInstanceStruct *chartInstance, real_T c2_x
  [99])
{
  real_T c2_e_y;
  int32_T c2_k;
  real_T c2_b_k;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_f_y;
  (void)chartInstance;
  c2_e_y = 0.0;
  for (c2_k = 0; c2_k < 99; c2_k++) {
    c2_b_k = 1.0 + (real_T)c2_k;
    c2_b_x = c2_x[(int32_T)c2_b_k - 1];
    c2_c_x = c2_b_x;
    c2_d_x = c2_c_x;
    c2_f_y = muDoubleScalarAbs(c2_d_x);
    c2_e_y += c2_f_y;
  }

  return c2_e_y;
}

static void c2_ob_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_sprintf, const char_T *c2_identifier, char_T c2_e_y[14])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_pb_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_sprintf), &c2_thisId,
    c2_e_y);
  sf_mex_destroy(&c2_sprintf);
}

static void c2_pb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, char_T c2_e_y[14])
{
  char_T c2_cv6[14];
  int32_T c2_i667;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_cv6, 1, 10, 0U, 1, 0U, 2, 1,
                14);
  for (c2_i667 = 0; c2_i667 < 14; c2_i667++) {
    c2_e_y[c2_i667] = c2_cv6[c2_i667];
  }

  sf_mex_destroy(&c2_e_u);
}

static const mxArray *c2_mb_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_e_u;
  const mxArray *c2_e_y = NULL;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_e_u = *(int32_T *)c2_inData;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_e_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_e_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_qb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_e_y;
  int32_T c2_i668;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), &c2_i668, 1, 6, 0U, 0, 0U, 0);
  c2_e_y = c2_i668;
  sf_mex_destroy(&c2_e_u);
  return c2_e_y;
}

static void c2_jb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_e_y;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_e_y = c2_qb_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_e_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static void c2_rb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId,
  c2_saot08BhBJej868PSk74SzB *c2_e_y)
{
  emlrtMsgIdentifier c2_thisId;
  static const char * c2_fieldNames[17] = { "ic", "sample_time_s", "N", "dt",
    "c_size", "Air_size", "Ajc_size", "Apr_size", "b_size", "Gir_size",
    "Gjc_size", "Gpr_size", "h_size", "q_size", "y_size", "l_dim", "soc_dim" };

  c2_thisId.fParent = c2_parentId;
  c2_thisId.bParentIsCell = false;
  sf_mex_check_struct(c2_parentId, c2_e_u, 17, c2_fieldNames, 0U, NULL);
  c2_thisId.fIdentifier = "ic";
  c2_sb_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_e_u, "ic",
    "ic", 0)), &c2_thisId, &c2_e_y->ic);
  c2_thisId.fIdentifier = "sample_time_s";
  c2_e_y->sample_time_s = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c2_e_u, "sample_time_s", "sample_time_s", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "N";
  c2_e_y->N = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_e_u, "N", "N", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "dt";
  c2_e_y->dt = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_e_u, "dt", "dt", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "c_size";
  c2_e_y->c_size = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c2_e_u, "c_size", "c_size", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "Air_size";
  c2_e_y->Air_size = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c2_e_u, "Air_size", "Air_size", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "Ajc_size";
  c2_e_y->Ajc_size = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c2_e_u, "Ajc_size", "Ajc_size", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "Apr_size";
  c2_e_y->Apr_size = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c2_e_u, "Apr_size", "Apr_size", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "b_size";
  c2_e_y->b_size = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c2_e_u, "b_size", "b_size", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "Gir_size";
  c2_e_y->Gir_size = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c2_e_u, "Gir_size", "Gir_size", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "Gjc_size";
  c2_e_y->Gjc_size = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c2_e_u, "Gjc_size", "Gjc_size", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "Gpr_size";
  c2_e_y->Gpr_size = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c2_e_u, "Gpr_size", "Gpr_size", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "h_size";
  c2_e_y->h_size = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c2_e_u, "h_size", "h_size", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "q_size";
  c2_e_y->q_size = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c2_e_u, "q_size", "q_size", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "y_size";
  c2_e_y->y_size = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c2_e_u, "y_size", "y_size", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "l_dim";
  c2_e_y->l_dim = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c2_e_u, "l_dim", "l_dim", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "soc_dim";
  c2_e_y->soc_dim = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c2_e_u, "soc_dim", "soc_dim", 0)), &c2_thisId);
  sf_mex_destroy(&c2_e_u);
}

static void c2_sb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId,
  c2_sKpQB9jVSEZrFP5iOeb0DOE *c2_e_y)
{
  emlrtMsgIdentifier c2_thisId;
  static const char * c2_fieldNames[11] = { "sc_mode", "quat_in", "w_body_radps",
    "hw_Nms", "quat_cmd", "w_body_cmd_radps", "sun_inertial_unit", "gps_epoch_s",
    "gps_time_s", "cmd_torque", "cmd_state" };

  c2_thisId.fParent = c2_parentId;
  c2_thisId.bParentIsCell = false;
  sf_mex_check_struct(c2_parentId, c2_e_u, 11, c2_fieldNames, 0U, NULL);
  c2_thisId.fIdentifier = "sc_mode";
  c2_e_y->sc_mode = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c2_e_u, "sc_mode", "sc_mode", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "quat_in";
  c2_bb_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_e_u,
    "quat_in", "quat_in", 0)), &c2_thisId, c2_e_y->quat_in);
  c2_thisId.fIdentifier = "w_body_radps";
  c2_y_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_e_u,
    "w_body_radps", "w_body_radps", 0)), &c2_thisId, c2_e_y->w_body_radps);
  c2_thisId.fIdentifier = "hw_Nms";
  c2_y_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_e_u,
    "hw_Nms", "hw_Nms", 0)), &c2_thisId, c2_e_y->hw_Nms);
  c2_thisId.fIdentifier = "quat_cmd";
  c2_bb_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_e_u,
    "quat_cmd", "quat_cmd", 0)), &c2_thisId, c2_e_y->quat_cmd);
  c2_thisId.fIdentifier = "w_body_cmd_radps";
  c2_y_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_e_u,
    "w_body_cmd_radps", "w_body_cmd_radps", 0)), &c2_thisId,
                        c2_e_y->w_body_cmd_radps);
  c2_thisId.fIdentifier = "sun_inertial_unit";
  c2_y_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_e_u,
    "sun_inertial_unit", "sun_inertial_unit", 0)), &c2_thisId,
                        c2_e_y->sun_inertial_unit);
  c2_thisId.fIdentifier = "gps_epoch_s";
  c2_tb_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_e_u,
    "gps_epoch_s", "gps_epoch_s", 0)), &c2_thisId, c2_e_y->gps_epoch_s);
  c2_thisId.fIdentifier = "gps_time_s";
  c2_tb_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_e_u,
    "gps_time_s", "gps_time_s", 0)), &c2_thisId, c2_e_y->gps_time_s);
  c2_thisId.fIdentifier = "cmd_torque";
  c2_y_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_e_u,
    "cmd_torque", "cmd_torque", 0)), &c2_thisId, c2_e_y->cmd_torque);
  c2_thisId.fIdentifier = "cmd_state";
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_e_u,
    "cmd_state", "cmd_state", 0)), &c2_thisId, c2_e_y->cmd_state);
  sf_mex_destroy(&c2_e_u);
}

static void c2_tb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_e_y[2])
{
  real_T c2_dv64[2];
  int32_T c2_i669;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), c2_dv64, 1, 0, 0U, 1, 0U, 1, 2);
  for (c2_i669 = 0; c2_i669 < 2; c2_i669++) {
    c2_e_y[c2_i669] = c2_dv64[c2_i669];
  }

  sf_mex_destroy(&c2_e_u);
}

static void c2_kb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_soac_params;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  c2_saot08BhBJej868PSk74SzB c2_e_y;
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)chartInstanceVoid;
  c2_b_soac_params = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_rb_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_soac_params), &c2_thisId,
    &c2_e_y);
  sf_mex_destroy(&c2_b_soac_params);
  *(c2_saot08BhBJej868PSk74SzB *)c2_outData = c2_e_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_ub_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_gnc2_lib, const char_T *c2_identifier)
{
  uint8_T c2_e_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_e_y = c2_vb_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_gnc2_lib), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_gnc2_lib);
  return c2_e_y;
}

static uint8_T c2_vb_emlrt_marshallIn(SFc2_gnc2_libInstanceStruct *chartInstance,
  const mxArray *c2_e_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_e_y;
  uint8_T c2_u0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_e_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_e_y = c2_u0;
  sf_mex_destroy(&c2_e_u);
  return c2_e_y;
}

static void c2_b_xgetrf(SFc2_gnc2_libInstanceStruct *chartInstance, real_T
  c2_d_A[100], int32_T c2_ipiv[10], int32_T *c2_info)
{
  int32_T c2_i670;
  int32_T c2_b_info;
  int32_T c2_j;
  int32_T c2_a;
  int32_T c2_jm1;
  int32_T c2_b;
  int32_T c2_mmj;
  int32_T c2_b_a;
  int32_T c2_c;
  int32_T c2_b_b;
  int32_T c2_jj;
  int32_T c2_c_a;
  int32_T c2_jp1j;
  int32_T c2_d_a;
  int32_T c2_b_c;
  int32_T c2_n;
  int32_T c2_ix0;
  int32_T c2_b_n;
  int32_T c2_b_ix0;
  int32_T c2_idxmax;
  int32_T c2_ix;
  int32_T c2_e_a;
  real_T c2_x;
  int32_T c2_jpiv_offset;
  real_T c2_b_x;
  int32_T c2_f_a;
  real_T c2_c_x;
  int32_T c2_c_b;
  real_T c2_d_x;
  int32_T c2_jpiv;
  real_T c2_e_y;
  real_T c2_e_x;
  real_T c2_f_x;
  int32_T c2_g_a;
  real_T c2_g_x;
  int32_T c2_d_b;
  int32_T c2_h_a;
  int32_T c2_e_b;
  real_T c2_f_y;
  int32_T c2_c_c;
  int32_T c2_d_c;
  int32_T c2_e_c;
  real_T c2_smax;
  int32_T c2_i_a;
  int32_T c2_j_a;
  int32_T c2_f_b;
  int32_T c2_f_c;
  int32_T c2_g_b;
  int32_T c2_h_b;
  int32_T c2_i_b;
  int32_T c2_k_a;
  int32_T c2_i671;
  int32_T c2_jrow;
  boolean_T c2_overflow;
  int32_T c2_g_c;
  int32_T c2_l_a;
  int32_T c2_m_a;
  int32_T c2_m;
  int32_T c2_j_b;
  int32_T c2_k_b;
  int32_T c2_c_n;
  int32_T c2_n_a;
  int32_T c2_jprow;
  int32_T c2_k;
  int32_T c2_c_ix0;
  int32_T c2_l_b;
  int32_T c2_d_ix0;
  int32_T c2_iy0;
  boolean_T c2_b_overflow;
  int32_T c2_b_iy0;
  int32_T c2_ia0;
  int32_T c2_e_ix0;
  int32_T c2_o_a;
  int32_T c2_b_m;
  int32_T c2_c_iy0;
  int32_T c2_d_n;
  int32_T c2_i;
  int32_T c2_b_ix;
  real_T c2_h_x;
  int32_T c2_f_ix0;
  int32_T c2_iy;
  real_T c2_i_x;
  int32_T c2_d_iy0;
  int32_T c2_b_k;
  real_T c2_j_x;
  int32_T c2_b_ia0;
  real_T c2_k_x;
  real_T c2_l_x;
  int32_T c2_c_m;
  real_T c2_g_y;
  real_T c2_h_y;
  int32_T c2_e_n;
  real_T c2_z;
  real_T c2_temp;
  real_T c2_m_x;
  int32_T c2_g_ix0;
  real_T c2_n_x;
  int32_T c2_e_iy0;
  real_T c2_o_x;
  int32_T c2_c_ia0;
  int32_T c2_p_a;
  real_T c2_i_y;
  int32_T c2_d_m;
  real_T c2_g_s;
  int32_T c2_f_n;
  int32_T c2_q_a;
  int32_T c2_h_ix0;
  int32_T c2_f_iy0;
  int32_T c2_d_ia0;
  int32_T c2_r_a;
  int32_T c2_jA;
  int32_T c2_jy;
  int32_T c2_m_b;
  int32_T c2_n_b;
  boolean_T c2_c_overflow;
  int32_T c2_b_j;
  real_T c2_yjy;
  real_T c2_b_temp;
  int32_T c2_s_a;
  int32_T c2_c_ix;
  int32_T c2_o_b;
  int32_T c2_t_a;
  int32_T c2_i672;
  int32_T c2_u_a;
  int32_T c2_p_b;
  int32_T c2_i673;
  int32_T c2_v_a;
  int32_T c2_q_b;
  int32_T c2_w_a;
  int32_T c2_r_b;
  boolean_T c2_d_overflow;
  int32_T c2_ijA;
  int32_T c2_x_a;
  for (c2_i670 = 0; c2_i670 < 10; c2_i670++) {
    c2_ipiv[c2_i670] = 1 + c2_i670;
  }

  c2_b_info = 0;
  for (c2_j = 1; c2_j < 10; c2_j++) {
    c2_a = c2_j - 1;
    c2_jm1 = c2_a;
    c2_b = c2_j;
    c2_mmj = 10 - c2_b;
    c2_b_a = c2_jm1;
    c2_c = c2_b_a * 11;
    c2_b_b = c2_c + 1;
    c2_jj = c2_b_b;
    c2_c_a = c2_jj + 1;
    c2_jp1j = c2_c_a;
    c2_d_a = c2_mmj + 1;
    c2_b_c = c2_d_a;
    c2_n = c2_b_c;
    c2_ix0 = c2_jj;
    c2_b_n = c2_n;
    c2_b_ix0 = c2_ix0;
    if (c2_b_n < 1) {
      c2_idxmax = 0;
    } else {
      c2_idxmax = 1;
      if (c2_b_n > 1) {
        c2_ix = c2_b_ix0;
        c2_x = c2_d_A[c2_b_ix0 - 1];
        c2_b_x = c2_x;
        c2_c_x = c2_b_x;
        c2_d_x = c2_c_x;
        c2_e_y = muDoubleScalarAbs(c2_d_x);
        c2_e_x = 0.0;
        c2_f_x = c2_e_x;
        c2_g_x = c2_f_x;
        c2_f_y = muDoubleScalarAbs(c2_g_x);
        c2_smax = c2_e_y + c2_f_y;
        c2_f_b = c2_b_n;
        c2_i_b = c2_f_b;
        c2_overflow = ((!(2 > c2_i_b)) && (c2_i_b > 2147483646));
        if (c2_overflow) {
          c2_check_forloop_overflow_error(chartInstance, c2_overflow);
        }

        for (c2_k = 2; c2_k <= c2_b_n; c2_k++) {
          c2_o_a = c2_ix + 1;
          c2_ix = c2_o_a;
          c2_h_x = c2_d_A[c2_ix - 1];
          c2_i_x = c2_h_x;
          c2_j_x = c2_i_x;
          c2_l_x = c2_j_x;
          c2_h_y = muDoubleScalarAbs(c2_l_x);
          c2_m_x = 0.0;
          c2_n_x = c2_m_x;
          c2_o_x = c2_n_x;
          c2_i_y = muDoubleScalarAbs(c2_o_x);
          c2_g_s = c2_h_y + c2_i_y;
          if (c2_g_s > c2_smax) {
            c2_idxmax = c2_k;
            c2_smax = c2_g_s;
          }
        }
      }
    }

    c2_e_a = c2_idxmax - 1;
    c2_jpiv_offset = c2_e_a;
    c2_f_a = c2_jj;
    c2_c_b = c2_jpiv_offset;
    c2_jpiv = (c2_f_a + c2_c_b) - 1;
    if (c2_d_A[c2_jpiv] != 0.0) {
      if (c2_jpiv_offset != 0) {
        c2_g_a = c2_j;
        c2_e_b = c2_jpiv_offset;
        c2_e_c = c2_g_a + c2_e_b;
        c2_ipiv[c2_j - 1] = c2_e_c;
        c2_h_b = c2_jm1 + 1;
        c2_jrow = c2_h_b;
        c2_m_a = c2_jrow;
        c2_k_b = c2_jpiv_offset;
        c2_jprow = c2_m_a + c2_k_b;
        c2_d_ix0 = c2_jrow;
        c2_b_iy0 = c2_jprow;
        c2_e_ix0 = c2_d_ix0;
        c2_c_iy0 = c2_b_iy0;
        c2_b_ix = c2_e_ix0;
        c2_iy = c2_c_iy0;
        for (c2_b_k = 1; c2_b_k < 11; c2_b_k++) {
          c2_temp = c2_d_A[c2_b_ix - 1];
          c2_d_A[c2_b_ix - 1] = c2_d_A[c2_iy - 1];
          c2_d_A[c2_iy - 1] = c2_temp;
          c2_p_a = c2_b_ix + 10;
          c2_b_ix = c2_p_a;
          c2_q_a = c2_iy + 10;
          c2_iy = c2_q_a;
        }
      }

      c2_h_a = c2_mmj - 1;
      c2_d_c = c2_h_a;
      c2_j_a = c2_jp1j;
      c2_g_b = c2_d_c;
      c2_i671 = c2_j_a + c2_g_b;
      c2_l_a = c2_jp1j;
      c2_j_b = c2_i671;
      c2_n_a = c2_l_a;
      c2_l_b = c2_j_b;
      c2_b_overflow = ((!(c2_n_a > c2_l_b)) && (c2_l_b > 2147483646));
      if (c2_b_overflow) {
        c2_check_forloop_overflow_error(chartInstance, c2_b_overflow);
      }

      for (c2_i = c2_jp1j - 1; c2_i + 1 <= c2_i671; c2_i++) {
        c2_k_x = c2_d_A[c2_i];
        c2_g_y = c2_d_A[c2_jj - 1];
        c2_z = c2_k_x / c2_g_y;
        c2_d_A[c2_i] = c2_z;
      }
    } else {
      c2_b_info = c2_j;
    }

    c2_d_b = c2_j;
    c2_c_c = 10 - c2_d_b;
    c2_i_a = c2_jj + 10;
    c2_f_c = c2_i_a;
    c2_k_a = c2_jj + 11;
    c2_g_c = c2_k_a;
    c2_m = c2_mmj;
    c2_c_n = c2_c_c;
    c2_c_ix0 = c2_jp1j;
    c2_iy0 = c2_f_c;
    c2_ia0 = c2_g_c;
    c2_b_m = c2_m;
    c2_d_n = c2_c_n;
    c2_f_ix0 = c2_c_ix0;
    c2_d_iy0 = c2_iy0;
    c2_b_ia0 = c2_ia0;
    c2_c_m = c2_b_m;
    c2_e_n = c2_d_n;
    c2_g_ix0 = c2_f_ix0;
    c2_e_iy0 = c2_d_iy0;
    c2_c_ia0 = c2_b_ia0;
    c2_d_m = c2_c_m;
    c2_f_n = c2_e_n;
    c2_h_ix0 = c2_g_ix0;
    c2_f_iy0 = c2_e_iy0;
    c2_d_ia0 = c2_c_ia0;
    c2_r_a = c2_d_ia0 - 1;
    c2_jA = c2_r_a;
    c2_jy = c2_f_iy0;
    c2_m_b = c2_f_n;
    c2_n_b = c2_m_b;
    c2_c_overflow = ((!(1 > c2_n_b)) && (c2_n_b > 2147483646));
    if (c2_c_overflow) {
      c2_check_forloop_overflow_error(chartInstance, c2_c_overflow);
    }

    for (c2_b_j = 1; c2_b_j <= c2_f_n; c2_b_j++) {
      c2_yjy = c2_d_A[c2_jy - 1];
      if (c2_yjy != 0.0) {
        c2_b_temp = -c2_yjy;
        c2_c_ix = c2_h_ix0;
        c2_o_b = c2_jA + 1;
        c2_i672 = c2_o_b;
        c2_u_a = c2_d_m;
        c2_p_b = c2_jA;
        c2_i673 = c2_u_a + c2_p_b;
        c2_v_a = c2_i672;
        c2_q_b = c2_i673;
        c2_w_a = c2_v_a;
        c2_r_b = c2_q_b;
        c2_d_overflow = ((!(c2_w_a > c2_r_b)) && (c2_r_b > 2147483646));
        if (c2_d_overflow) {
          c2_check_forloop_overflow_error(chartInstance, c2_d_overflow);
        }

        for (c2_ijA = c2_i672 - 1; c2_ijA + 1 <= c2_i673; c2_ijA++) {
          c2_d_A[c2_ijA] += c2_d_A[c2_c_ix - 1] * c2_b_temp;
          c2_x_a = c2_c_ix + 1;
          c2_c_ix = c2_x_a;
        }
      }

      c2_s_a = c2_jy + 10;
      c2_jy = c2_s_a;
      c2_t_a = c2_jA + 10;
      c2_jA = c2_t_a;
    }
  }

  if (((real_T)c2_b_info == 0.0) && (!(c2_d_A[99] != 0.0))) {
    c2_b_info = 10;
  }

  *c2_info = c2_b_info;
}

static void init_dsm_address_info(SFc2_gnc2_libInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc2_gnc2_libInstanceStruct *chartInstance)
{
  chartInstance->c2_c_X = (real_T (*)[100])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c2_U = (real_T (*)[30])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_e_s = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c2_J = (real_T (*)[9])ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c2_ME = (real_T (*)[16])ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c2_MI = (real_T (*)[16])ssGetInputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c2_T_max = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c2_w_max = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 7);
  chartInstance->c2_s_max = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 8);
  chartInstance->c2_s_min = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 9);
  chartInstance->c2_w_v = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 10);
  chartInstance->c2_d_X = (real_T (*)[100])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_b_U = (real_T (*)[30])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c2_f_s = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c2_exitcode = (real_T (*)[11])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c2_time = (real_T (*)[10])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 5);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c2_gnc2_lib_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(801151492U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1686953400U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3014802052U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4166296678U);
}

mxArray* sf_c2_gnc2_lib_get_post_codegen_info(void);
mxArray *sf_c2_gnc2_lib_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("ueAoE3CB19C5TtMcOfWrvC");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,11,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(100);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(30);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(3);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(4);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(4);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,10,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,10,"type",mxType);
    }

    mxSetField(mxData,10,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(13));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(100);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(30);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(11);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(10);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c2_gnc2_lib_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_gnc2_lib_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,1);
  mxSetCell(mxcell3p, 0, mxCreateString("coder.internal.blas.BLASApi"));
  return(mxcell3p);
}

mxArray *sf_c2_gnc2_lib_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("late");
  mxArray *fallbackReason = mxCreateString("client_server");
  mxArray *hiddenFallbackType = mxCreateString("");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("run_ecos");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c2_gnc2_lib_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c2_gnc2_lib_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString(
      "OySX0hZYOyRCOpSNpD3n0F");
    mwSize exp_dims[2] = { 1, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);

    {
      mxArray* mxFcnName = mxCreateString("run_ecos");
      mxSetCell(mxExportedFunctionsUsedByThisChart, 0, mxFcnName);
    }

    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c2_gnc2_lib(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x6'type','srcId','name','auxInfo'{{M[1],M[56],T\"U\",},{M[1],M[5],T\"X\",},{M[1],M[58],T\"exitcode\",},{M[1],M[57],T\"s\",},{M[1],M[59],T\"time\",},{M[8],M[0],T\"is_active_c2_gnc2_lib\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 6, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_gnc2_lib_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_gnc2_libInstanceStruct *chartInstance = (SFc2_gnc2_libInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _gnc2_libMachineNumber_,
           2,
           1,
           1,
           0,
           17,
           0,
           0,
           0,
           0,
           1,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_gnc2_libMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_gnc2_libMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _gnc2_libMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"X");
          _SFD_SET_DATA_PROPS(1,1,1,0,"U");
          _SFD_SET_DATA_PROPS(2,1,1,0,"s");
          _SFD_SET_DATA_PROPS(3,1,1,0,"J");
          _SFD_SET_DATA_PROPS(4,1,1,0,"ME");
          _SFD_SET_DATA_PROPS(5,1,1,0,"MI");
          _SFD_SET_DATA_PROPS(6,1,1,0,"T_max");
          _SFD_SET_DATA_PROPS(7,1,1,0,"w_max");
          _SFD_SET_DATA_PROPS(8,1,1,0,"s_max");
          _SFD_SET_DATA_PROPS(9,1,1,0,"s_min");
          _SFD_SET_DATA_PROPS(10,1,1,0,"w_v");
          _SFD_SET_DATA_PROPS(11,2,0,1,"X");
          _SFD_SET_DATA_PROPS(12,2,0,1,"U");
          _SFD_SET_DATA_PROPS(13,2,0,1,"s");
          _SFD_SET_DATA_PROPS(14,2,0,1,"exitcode");
          _SFD_SET_DATA_PROPS(15,2,0,1,"time");
          _SFD_SET_DATA_PROPS(16,10,0,0,"soac_params");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,8,0,7,0,0,0,6,0,4,2);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,3167);
        _SFD_CV_INIT_EML_FCN(0,1,"foh",3398,-1,6078);
        _SFD_CV_INIT_EML_FCN(0,2,"deriv",6080,-1,6538);
        _SFD_CV_INIT_EML_FCN(0,3,"get_f_vals",6540,-1,6996);
        _SFD_CV_INIT_EML_FCN(0,4,"Q_linearize",6998,-1,7975);
        _SFD_CV_INIT_EML_FCN(0,5,"parse_ecos",7977,-1,9321);
        _SFD_CV_INIT_EML_FCN(0,6,"convert_to_CCS",9323,-1,9561);
        _SFD_CV_INIT_EML_FCN(0,7,"my_find",9563,-1,9927);
        _SFD_CV_INIT_EML_IF(0,1,0,2622,2643,-1,2686);
        _SFD_CV_INIT_EML_IF(0,1,1,2696,2736,-1,-2);
        _SFD_CV_INIT_EML_IF(0,1,2,2887,2903,-1,3162);
        _SFD_CV_INIT_EML_IF(0,1,3,2936,2966,-1,3158);
        _SFD_CV_INIT_EML_IF(0,1,4,2977,2998,3082,3100);
        _SFD_CV_INIT_EML_IF(0,1,5,3082,3100,-1,3100);
        _SFD_CV_INIT_EML_IF(0,1,6,9749,9785,-1,9911);
        _SFD_CV_INIT_EML_FOR(0,1,0,1441,1460,2824);
        _SFD_CV_INIT_EML_FOR(0,1,1,4819,4833,6072);
        _SFD_CV_INIT_EML_FOR(0,1,2,5130,5148,5510);
        _SFD_CV_INIT_EML_FOR(0,1,3,9458,9480,9534);
        _SFD_CV_INIT_EML_FOR(0,1,4,9709,9723,9923);
        _SFD_CV_INIT_EML_FOR(0,1,5,9727,9741,9919);

        {
          static int condStart[] = { 2702, 2724 };

          static int condEnd[] = { 2718, 2735 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,2701,2736,2,0,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 9754, 9773 };

          static int condEnd[] = { 9767, 9783 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,1,9753,9784,2,2,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        _SFD_CV_INIT_EML_RELATIONAL(0,1,0,2626,2642,-1,1);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,1,2702,2718,-1,2);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,2,2724,2735,-1,2);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,3,2891,2902,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,4,2940,2966,-1,1);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,5,2981,2997,-1,4);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,6,3090,3099,-1,4);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,7,9754,9767,-1,1);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,8,9773,9783,-1,2);
        _SFD_CV_INIT_SCRIPT(0,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"skew",0,-1,109);

        {
          unsigned int dimVector[1];
          dimVector[0]= 100U;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 30U;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_g_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 4U;
          dimVector[1]= 4U;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 4U;
          dimVector[1]= 4U;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 100U;
          _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_e_sf_marshallOut,(MexInFcnForType)
            c2_e_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 30U;
          _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)
            c2_d_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(13,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)c2_c_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 11U;
          _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 10U;
          _SFD_SET_DATA_COMPILED_PROPS(15,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(16,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_h_sf_marshallOut,(MexInFcnForType)
          c2_kb_sf_marshallIn);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _gnc2_libMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_gnc2_libInstanceStruct *chartInstance = (SFc2_gnc2_libInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, *chartInstance->c2_c_X);
        _SFD_SET_DATA_VALUE_PTR(1U, *chartInstance->c2_U);
        _SFD_SET_DATA_VALUE_PTR(2U, chartInstance->c2_e_s);
        _SFD_SET_DATA_VALUE_PTR(3U, *chartInstance->c2_J);
        _SFD_SET_DATA_VALUE_PTR(4U, *chartInstance->c2_ME);
        _SFD_SET_DATA_VALUE_PTR(5U, *chartInstance->c2_MI);
        _SFD_SET_DATA_VALUE_PTR(6U, chartInstance->c2_T_max);
        _SFD_SET_DATA_VALUE_PTR(7U, chartInstance->c2_w_max);
        _SFD_SET_DATA_VALUE_PTR(8U, chartInstance->c2_s_max);
        _SFD_SET_DATA_VALUE_PTR(9U, chartInstance->c2_s_min);
        _SFD_SET_DATA_VALUE_PTR(10U, chartInstance->c2_w_v);
        _SFD_SET_DATA_VALUE_PTR(11U, *chartInstance->c2_d_X);
        _SFD_SET_DATA_VALUE_PTR(16U, &chartInstance->c2_soac_params);
        _SFD_SET_DATA_VALUE_PTR(12U, *chartInstance->c2_b_U);
        _SFD_SET_DATA_VALUE_PTR(13U, chartInstance->c2_f_s);
        _SFD_SET_DATA_VALUE_PTR(14U, *chartInstance->c2_exitcode);
        _SFD_SET_DATA_VALUE_PTR(15U, *chartInstance->c2_time);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "sIu4rPgwTarNqI4GFKM26oC";
}

static void sf_opaque_initialize_c2_gnc2_lib(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_gnc2_libInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c2_gnc2_lib((SFc2_gnc2_libInstanceStruct*) chartInstanceVar);
  initialize_c2_gnc2_lib((SFc2_gnc2_libInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_gnc2_lib(void *chartInstanceVar)
{
  enable_c2_gnc2_lib((SFc2_gnc2_libInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_gnc2_lib(void *chartInstanceVar)
{
  disable_c2_gnc2_lib((SFc2_gnc2_libInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_gnc2_lib(void *chartInstanceVar)
{
  sf_gateway_c2_gnc2_lib((SFc2_gnc2_libInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c2_gnc2_lib(SimStruct* S)
{
  return get_sim_state_c2_gnc2_lib((SFc2_gnc2_libInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c2_gnc2_lib(SimStruct* S, const mxArray *st)
{
  set_sim_state_c2_gnc2_lib((SFc2_gnc2_libInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c2_gnc2_lib(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_gnc2_libInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_gnc2_lib_optimization_info();
    }

    finalize_c2_gnc2_lib((SFc2_gnc2_libInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_gnc2_lib((SFc2_gnc2_libInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_gnc2_lib(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_gnc2_lib((SFc2_gnc2_libInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c2_gnc2_lib(SimStruct *S)
{
  /* Actual parameters from chart:
     soac_params
   */
  const char_T *rtParamNames[] = { "soac_params" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* Set overwritable ports for inplace optimization */
  ssSetInputPortOverWritable(S, 0, 1);
  ssSetOutputPortOverwritesInputPort(S, 1, 0);
  ssSetInputPortOverWritable(S, 1, 1);
  ssSetOutputPortOverwritesInputPort(S, 2, 1);
  ssSetInputPortOverWritable(S, 2, 1);
  ssSetOutputPortOverwritesInputPort(S, 3, 2);
  ssSetStatesModifiedOnlyInUpdate(S, 0);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_gnc2_lib_optimization_info(sim_mode_is_rtw_gen(S),
      sim_mode_is_modelref_sim(S), sim_mode_is_external(S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,2,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 2);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 8, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 9, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 10, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,11);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,5);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=5; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 11; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(319317770U));
  ssSetChecksum1(S,(2303606625U));
  ssSetChecksum2(S,(3684023159U));
  ssSetChecksum3(S,(1449574949U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,0);
}

static void mdlRTW_c2_gnc2_lib(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_gnc2_lib(SimStruct *S)
{
  SFc2_gnc2_libInstanceStruct *chartInstance;
  chartInstance = (SFc2_gnc2_libInstanceStruct *)utMalloc(sizeof
    (SFc2_gnc2_libInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc2_gnc2_libInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_gnc2_lib;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_gnc2_lib;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_gnc2_lib;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_gnc2_lib;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_gnc2_lib;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_gnc2_lib;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_gnc2_lib;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_gnc2_lib;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_gnc2_lib;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_gnc2_lib;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_gnc2_lib;
  chartInstance->chartInfo.callGetHoverDataForMsg = NULL;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
  mdl_start_c2_gnc2_lib(chartInstance);
}

void c2_gnc2_lib_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_gnc2_lib(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_gnc2_lib(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_gnc2_lib(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_gnc2_lib_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
