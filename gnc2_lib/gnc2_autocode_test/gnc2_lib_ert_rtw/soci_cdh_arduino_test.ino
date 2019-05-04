
extern "C" {
  #include "fsw_lib.h"    
  #include "rtwtypes.h"
  #include "test_fsw_inputs.h"
  #include <time.h>
  #include <stddef.h>
  #include <stdio.h> 
}

void Print_Results(ExtY input) {
  Serial.println("opt_state = ");
  for(int i = 0; i < 100; i++) {
    Serial.println(input.opt_state[i]);
  }
  
  Serial.println("opt_ctrl_Nm = ");
  for(int i = 0; i < 30; i++) {
    Serial.println(input.opt_ctrl_Nm[i]);
  }
  
  Serial.print("final_time_s = ");
  Serial.println(input.final_time_s);
  
  Serial.print("exitcode = ");
  for(int i = 0; i < 11; i++) {
    Serial.println(input.exitcode[i]);
  }
  
  Serial.println("sol_times_s = ");
  for(int i = 0; i < 10; i++) {
    Serial.println(input.sol_times_s[i]);
  }
  
}

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


int main(int argc, const char *argv[]) {
  Serial.begin(9600);

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
  // Clocked for 5ms per rt_OneStep()
  int array_size = sizeof(Inputs) / sizeof(ExtU);
  time_t timer = clock();
  Serial.println("Starting rt_OneStop() loop at time = " + timer);
  for(int i = 0; i < array_size; i++) {
    Serial.println("===========================");
    rtU = Inputs[i];
    Serial.print("Running OneStep() for Input[" + i);
    Serial.println("]");
    timer = clock();
    Serial.println("Time before rt_OneStep() = " + timer);
    rt_OneStep();
    timer = clock();
    Serial.println("Time after rt_OneStep() = " + timer);
    Serial.println("Printing results...");
    Print_Results(rtY);
  }
  timer = clock();
  Serial.println("Stopping rt_OneStop() loop at time = " + timer);
  
  Serial.print("Warning: The simulation will run forever.\n"
               "Generated ERT main won't simulate model step behavior.\n"
               "To change this behavior select the 'MAT-file logging' option.\n");
  fflush((NULL));
  while (rtmGetErrorStatus(rtM) == (NULL)) {
    /*  Perform other application tasks here */
  }

  /* Disable rt_OneStep() here */

  /* Terminate model */
  fsw_lib_terminate();
  return 0;
}
