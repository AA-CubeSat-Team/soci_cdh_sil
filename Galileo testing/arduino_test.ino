int stop = 0;

extern "C" {
  #include "fsw_lib.h"    
  #include "rtwtypes.h"
  #include "test_fsw_inputs.h"
  #include <time.h>
  #include <stddef.h>
  #include <stdio.h> 
}

void Print_Results(ExtY input) {
  Serial.print("sc_quat \t= ");
  for(int i = 0; i < 4; i++) {
    Serial.print(input.sc_quat[i]);
    Serial.print("   ");
  }
  Serial.println();
  
  Serial.print("body_rates \t= ");
  for(int i = 0; i < 3; i++) {
    Serial.print(input.body_rates[i]);
    Serial.print("   ");
  }
  Serial.println();
  
  Serial.print("sc_mode \t= ");
  Serial.println(input.sc_mode);
  
  Serial.print("vel_point \t= ");
  Serial.println(input.vel_point);
  
  Serial.print("quat_cmd \t= ");
  for(int i = 0; i < 4; i++) {
    Serial.print(input.quat_cmd[i]);
    Serial.print("   ");
  }
  Serial.println();
  
  Serial.print("sc_above_gs \t= ");
  Serial.println(input.sc_above_gs);
  
  Serial.print("sc_in_sun \t= ");
  Serial.println(input.sc_in_sun);
  
  Serial.print("mag_eci_unit \t= ");
  for(int i = 0; i < 3; i++) {
    Serial.print(input.mag_eci_unit[i]);
    Serial.print("   ");
  }
  Serial.println();
  
  Serial.print("pos_eci_km \t= ");
  for(int i = 0; i < 3; i++) {
    Serial.print(input.pos_eci_km[i]);
    Serial.print("   ");
  }
  Serial.println();
  
  Serial.print("vel_eci_kmps \t= ");
  for(int i = 0; i < 3; i++) {
    Serial.print(input.vel_eci_kmps[i]);
    Serial.print("   ");
  }
  Serial.println();
  
  Serial.print("gyro_valid \t= ");
  Serial.println(input.gyro_valid);
  
  Serial.print("cmd_RW_rpm \t= ");
  for(int i = 0; i < 3; i++) {
    Serial.print(input.cmd_RW_rpm[i]);
    Serial.print("   ");
  }
  Serial.println();
  
  Serial.print("cmd_MT_dv \t= ");
  for(int i = 0; i < 3; i++) {
    Serial.print(input.cmd_MT_dv[i]);
    Serial.print("   ");
  }
  Serial.println();
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

void swap(uint32_t *xp, uint32_t *yp) 
{ 
    uint32_t temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
// A function to implement bubble sort 
void bubbleSort(uint32_t arr[], int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)       
  
       // Last i elements are already in place    
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
} 

double calculateSD(uint32_t data[], int array_size)
{
    double sum = 0.0, mean, standardDeviation = 0.0;

    int i;

    for(i=0; i<array_size; ++i)
    {
        sum += data[i];
    }

    mean = sum/array_size;

    for(i=0; i<array_size; ++i)
        standardDeviation += pow(data[i] - mean, 2);

    return sqrt(standardDeviation/array_size);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(!stop) {
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

    uint32_t data [array_size];
    // time_t timer = clock();
    uint32_t ts1 = micros();
    Serial.print("Starting rt_OneStop() loop at time = ");
    Serial.println(ts1);
    for(int i = 0; i < array_size; i++) {
      Serial.println("===========================");
      rtU = Inputs[i];
      Serial.print("Running OneStep() for Input[");
      Serial.print(i);
      Serial.println("]");
      //timer = clock();
      uint32_t ts2 = micros();
      Serial.print("Time before rt_OneStep() = ");
      Serial.println(ts2);
      rt_OneStep();
      //timer = clock();
      uint32_t ts3 = micros();
      Serial.print("Time after rt_OneStep() = ");
      Serial.println(ts3);
      Serial.print("Time elapsed between rt_OneStep = ");
      Serial.println(ts3-ts2);
      data[i] = ts3-ts2;
      Serial.println("Printing results...");
      Print_Results(rtY);
    }
    //timer = clock();
    uint32_t ts4 = micros();
    Serial.print("Stopping rt_OneStop() loop at time = ");
    Serial.println(ts4);
    Serial.print("Time elapsed between rt_OneStep() loop calls = ");
    Serial.println(ts4-ts1);
    
    //print timing analysis
    bubbleSort(data, array_size);
    Serial.print("Max time: ");
    Serial.println(data[array_size-1]);
    Serial.print("Min time: ");
    Serial.println(data[0]);
    Serial.print("Median time: ");
    Serial.println(data[array_size/2]);
    Serial.print("Average Time: ");
    uint32_t sum = 0;
    for(int i = 0; i < array_size; i++) {
      sum += data[i];
    }
    Serial.println(1.0 * sum / array_size );
    Serial.print("Std deviation: ");
    Serial.println(calculateSD(data, array_size));
    
    
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
  }
  stop = 1;
}
