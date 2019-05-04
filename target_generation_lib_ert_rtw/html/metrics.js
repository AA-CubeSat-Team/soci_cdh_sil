function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.var["rtM_"] = {file: "/Users/Taylor/uw_cubesat_adcs/adcs/sw/components/adcs_fsw/matlab/test/fsw-autocode-test/target_generation/target_generation_lib0_ert_rtw/target_generation_lib0.c",
	size: 4};
	 this.metricsArray.var["rtU"] = {file: "/Users/Taylor/uw_cubesat_adcs/adcs/sw/components/adcs_fsw/matlab/test/fsw-autocode-test/target_generation/target_generation_lib0_ert_rtw/target_generation_lib0.c",
	size: 184};
	 this.metricsArray.var["rtY"] = {file: "/Users/Taylor/uw_cubesat_adcs/adcs/sw/components/adcs_fsw/matlab/test/fsw-autocode-test/target_generation/target_generation_lib0_ert_rtw/target_generation_lib0.c",
	size: 64};
	 this.metricsArray.fcn["fabs"] = {file: "/Applications/MATLAB_R2016b.app/sys/lcc/include/math.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["memset"] = {file: "/Applications/MATLAB_R2016b.app/sys/lcc/include/string.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["sqrt"] = {file: "/Applications/MATLAB_R2016b.app/sys/lcc/include/math.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["target_generation_lib0.c:norm"] = {file: "/Users/Taylor/uw_cubesat_adcs/adcs/sw/components/adcs_fsw/matlab/test/fsw-autocode-test/target_generation/target_generation_lib0_ert_rtw/target_generation_lib0.c",
	stack: 32,
	stackTotal: 32};
	 this.metricsArray.fcn["target_generation_lib0_initialize"] = {file: "/Users/Taylor/uw_cubesat_adcs/adcs/sw/components/adcs_fsw/matlab/test/fsw-autocode-test/target_generation/target_generation_lib0_ert_rtw/target_generation_lib0.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["target_generation_lib0_step"] = {file: "/Users/Taylor/uw_cubesat_adcs/adcs/sw/components/adcs_fsw/matlab/test/fsw-autocode-test/target_generation/target_generation_lib0_ert_rtw/target_generation_lib0.c",
	stack: 292,
	stackTotal: 324};
	 this.metricsArray.fcn["target_generation_lib0_terminate"] = {file: "/Users/Taylor/uw_cubesat_adcs/adcs/sw/components/adcs_fsw/matlab/test/fsw-autocode-test/target_generation/target_generation_lib0_ert_rtw/target_generation_lib0.c",
	stack: 0,
	stackTotal: 0};
	 this.getMetrics = function(token) { 
		 var data;
		 data = this.metricsArray.var[token];
		 if (!data) {
			 data = this.metricsArray.fcn[token];
			 if (data) data.type = "fcn";
		 } else { 
			 data.type = "var";
		 }
	 return data;}
}
	 CodeMetrics.instance = new CodeMetrics();
