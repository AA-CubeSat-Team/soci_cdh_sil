int stop = 0;

extern "C" {
  #include <stddef.h>
  #include <time.h>
  #include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
  #include "gnc2_lib.h"                  /* Model's header file */
  #include "rtwtypes.h" 
  #include "test_gnc_inputs.h"
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
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(rtM, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  gnc2_lib_step();

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

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
    gnc2_lib_initialize();
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
    
    
    /* Attach rt_OneStep to a timer or interrupt service routine with
     * period 0.2 seconds (the model's base sample time) here.  The
     * call syntax for rt_OneStep is
     *
     *  rt_OneStep();
     */
    printf("Warning: The simulation will run forever. "
           "Generated ERT main won't simulate model step behavior. "
           "To change this behavior select the 'MAT-file logging' option.\n");
    fflush((NULL));
    while (rtmGetErrorStatus(rtM) == (NULL)) {
      /*  Perform other application tasks here */
    }

    /* Disable rt_OneStep() here */

    /* Terminate model */
    gnc2_lib_terminate();
  }
  stop = 1;
}
