/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c
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

#include <stddef.h>
#include <stdio.h>                     /* This ert_main.c example uses fprintf/fflush */
#include "fsw_lib.h"                   /* Model's header file */
#include "rtwtypes.h"
#include "test_fsw_inputs.h"
#include <time.h>

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
void rt_OneStep(void);
void Print_Results(ExtY input, FILE* f);
void rt_OneStep(void)
{
  static boolean_T OverrunFlags[4] = { 0, 0, 0, 0 };

  static boolean_T eventFlags[4] = { 0, 0, 0, 0 };/* Model has 4 rates */

  static int_T taskCounter[4] = { 0, 0, 0, 0 };

  int_T i;

  /* Disable interrupts here */

  /* Check base rate for overrun */
  if (OverrunFlags[0]) {
    rtmSetErrorStatus(rtM, "Overrun");
    return;
  }

  OverrunFlags[0] = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */

  /*
   * For a bare-board target (i.e., no operating system), the
   * following code checks whether any subrate overruns,
   * and also sets the rates that need to run this time step.
   */
  for (i = 1; i < 4; i++) {
    if (taskCounter[i] == 0) {
      if (eventFlags[i]) {
        OverrunFlags[0] = false;
        OverrunFlags[i] = true;

        /* Sampling too fast */
        rtmSetErrorStatus(rtM, "Overrun");
        return;
      }

      eventFlags[i] = true;
    }
  }

  taskCounter[1]++;
  if (taskCounter[1] == 10) {
    taskCounter[1]= 0;
  }

  taskCounter[2]++;
  if (taskCounter[2] == 20) {
    taskCounter[2]= 0;
  }

  taskCounter[3]++;
  if (taskCounter[3] == 80) {
    taskCounter[3]= 0;
  }

  /* Set model inputs associated with base rate here */

  /* Step the model for base rate */
  fsw_lib_step0();

  /* Get model outputs here */

  /* Indicate task for base rate complete */
  OverrunFlags[0] = false;

  /* Step the model for any subrate */
  for (i = 1; i < 4; i++) {
    /* If task "i" is running, don't run any lower priority task */
    if (OverrunFlags[i]) {
      return;
    }

    if (eventFlags[i]) {
      OverrunFlags[i] = true;

      /* Set model inputs associated with subrates here */

      /* Step the model for subrate "i" */
      switch (i) {
       case 1 :
        fsw_lib_step1();

        /* Get model outputs here */
        break;

       case 2 :
        fsw_lib_step2();

        /* Get model outputs here */
        break;

       case 3 :
        fsw_lib_step3();

        /* Get model outputs here */
        break;

       default :
        break;
      }

      /* Indicate task complete for sample time "i" */
      OverrunFlags[i] = false;
      eventFlags[i] = false;
    }
  }

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example "main" function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific.  This example
 * illustrates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{

  time_t rawtime;
  struct tm*  time_;

  time(&rawtime);
  time_ = localtime(&rawtime);

  /* Unused arguments */
  (void)(argc);
  (void)(argv);

  /* Initialize model */
  fsw_lib_initialize();

  /* Attach rt_OneStep to a timer or interrupt service routine with
   * period 0.005 seconds (the model's base sample time) here.  The
   * call syntax for rt_OneStep is
   *
   *  rt_OneStep();
   */

  FILE *f = fopen("output.txt", "w");
  int array_size = sizeof(Inputs) / sizeof(ExtU);
  fprintf(f, "Starting rt_OneStop() loop at time = %i:%i:%i\n", time_->tm_hour, time_->tm_min, time_->tm_sec);
  for(int i = 0; i < array_size; i++) {
    fprintf(f, "===========================\n");
    rtU = Inputs[i];
    fprintf(f, "Running OneStep() for Input[%d]\n", i);
    fprintf(f, "Time before rt_OneStep() = %i:%i:%i\n", time_->tm_hour, time_->tm_min, time_->tm_sec);
    rt_OneStep();
    fprintf(f, "Time after rt_OneStep() = %i:%i:%i\n", time_->tm_hour, time_->tm_min, time_->tm_sec);
    fprintf(f, "Printing results...\n");
    Print_Results(rtY, f);
  }
  fprintf(f, "Stopping rt_OneStop() loop at time = %i:%i:%i\n", time_->tm_hour, time_->tm_min, time_->tm_sec);
  fclose(f);

  printf("Warning: The simulation will run forever. "
         "Generated ERT main won't simulate model step behavior. "
         "To change this behavior select the 'MAT-file logging' option.\n");
  //fflush((NULL));
  while (rtmGetErrorStatus(rtM) == (NULL)) {
    /*  Perform other application tasks here */
  }

  /* Disable rt_OneStep() here */

  /* Terminate model */
  fsw_lib_terminate();
  return 0;
}

void Print_Results(ExtY input, FILE *f) {
  fprintf(f, "sc_quat = ");
  for(int i = 0; i < 4; i++) {
    fprintf(f, "%f ", input.sc_quat[i]);
  }
  fprintf(f, "\n");
  
  fprintf(f, "body_rates = ");
  for(int i = 0; i < 3; i++) {
    fprintf(f, "%f ", input.body_rates[i]);
  }
  fprintf(f, "\n");
  
  fprintf(f, "sc_mode = ");
  fprintf(f, "%hhd \n",input.sc_mode);
  
  fprintf(f, "vel_point = ");
  fprintf(f, "%hhu \n",input.vel_point);
  
  fprintf(f, "quat_cmd = ");
  for(int i = 0; i < 4; i++) {
    fprintf(f, "%f ",input.quat_cmd[i]);
  }
  fprintf(f, "\n");
  
  fprintf(f, "sc_above_gs = ");
  fprintf(f, "%hhu \n",input.sc_above_gs);
  
  fprintf(f, "sc_in_sun = ");
  fprintf(f, "%hhu \n",input.sc_in_sun);
  
  fprintf(f, "mag_eci_unit = ");
  for(int i = 0; i < 3; i++) {
    fprintf(f, "%f ",input.mag_eci_unit[i]);
  }
  fprintf(f, "\n");
  
  fprintf(f, "pos_eci_km = ");
  for(int i = 0; i < 3; i++) {
    fprintf(f, "%f ",input.pos_eci_km[i]);
  }
  fprintf(f, "\n");
  
  fprintf(f, "vel_eci_kmps = ");
  for(int i = 0; i < 3; i++) {
    fprintf(f, "%f ",input.vel_eci_kmps[i]);
  }
  fprintf(f, "\n");
  
  fprintf(f, "gyro_valid = ");
  fprintf(f, "%hhu \n",input.gyro_valid);
  
  fprintf(f, "cmd_RW_rpm = ");
  for(int i = 0; i < 3; i++) {
    fprintf(f, "%f ",input.cmd_RW_rpm[i]);
  }
  fprintf(f, "\n");
  
  fprintf(f, "cmd_MT_dv = ");
  for(int i = 0; i < 3; i++) {
    fprintf(f, "%hhd ",input.cmd_MT_dv[i]);
  }
  fprintf(f, "\n");
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
