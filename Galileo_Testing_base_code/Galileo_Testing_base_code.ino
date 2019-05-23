extern "C" {
#include "nohdopppmohdjmoh_eye.h"
#include "gdbifkfcbaimlfkn_norm.h"
#include "cone.h"
#include "iecbbimomgdjjekn_xnrm2.h"
#include "expcone.h"
#include "hdjmdbaaiecbkfcj_get_f_vals.h"
#include "knohcbaaphlnkfcb_convert_to_CCS.h"
#include "ldl.h"
#include "mgdbiecbmohlcjmo_convert_to_CCS.h"
#include "rt_hypotd_snf.h"
#include "nglnimohlfkfphln_norm.h"
#include "aieknglfdbimpppp_mldivide.h"
#include "data.h"
#include "fcbilfcbmohdjekn_eye.h"
#include "lfknecbacjmgaimo_xgerc.h"
#include "kkt.h"
#include "rtGetNaN.h"
#include "mgdjecjmkfkndbim_eye.h"
#include "wright_omega.h"
#include "ohdbdjecdjekngln_xzlarfg.h"
#include "rt_nonfinite.h"
#include "hdbaecbadjekpphd_xgehrd.h"
#include "cbaalnglphdjcjek_mrdivide.h"
#include "baiegdbacjmgjekn_xungorghr.h"
#include "timer.h"
#include "glblopts.h"
#include "rtGetInf.h"
#include "splamm.h"
#include "equil.h"
#include "ohlnfkfchlnoaimo_my_find.h"
#include "ecos.h"
#include "cjmgngdjaiecmgln_my_find.h"
#include "spla.h"
#include "SuiteSparse_config.h"
#include "aiekglfkjmoplfcb_xgetrf.h"
#include "fcbafcjedbimfkfc_inv.h"
#include "fkfkimopaimgfkno_kron.h"
#include "hdbippphieknimgl_xnrm2.h"
#include "baaicbaafcbiglfk_linspace.h"
#include "amd_internal.h"
#include "cbaiohlfjeknbaim_xrot.h"
#include "biecbaaiaieclnop_eml_dlahqr.h"
#include "ecbagdjmpphdgdjm_deriv.h"
#include "bimghlngphlfpphl_Q_linearize.h"
#include "rtwtypes.h"
#include "lfkfaaaafknomohl_xdlanv2.h"
#include "gnc2_lib.h"
#include "phlnfknoohlfohdj_mldivide.h"
#include "ctrlc.h"
#include "pphlkfcjfcjmiekf_foh.h"
#include "amd.h"
#include "jmglbiekmgdbbaai_xrot.h"
}

int stop = 0;

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
  Serial.println("Starting rt_OneStep()...");
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
  Serial.println("Stepping model...");
  gnc2_lib_step();
  Serial.println("Step complete!!!");

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
  Serial.println("Serial connection initialized!");
}

void loop() {
  if(!stop) {
    /* Initialize model */
    Serial.println("Initializing model...");
    gnc2_lib_initialize();
    /* Attach rt_OneStep to a timer or interrupt service routine with
     * period 0.005 seconds (the model's base sample time) here.  The
     * call syntax for rt_OneStep is
     *
     *  rt_OneStep();
     */
    Serial.println("Model has been initialized!!");
    
    ExtU input = {{0.99789,-0.037527,-0.037527,-0.037527}, {-0.025415,0.0027721,-0.0019598}, {0.0030769,0.0030769,0.0030769}, {1,0,0,0}, {0,0,0}, {1,0,0}};
    ExtU Inputs[1];
    Inputs[0] = input;
     
    // Clocked for 5ms per rt_OneStep()
    int array_size = sizeof(Inputs) / sizeof(ExtU);

    uint32_t data [array_size];
    // time_t timer = clock();
    uint32_t ts1 = micros();
    Serial.print("Starting rt_OneStep() loop at time = ");
    Serial.println(ts1);
    for(int i = 0; i < array_size; i++) {
      Serial.println("===========================");
      rtU = Inputs[i];
      Serial.print("Running OneStep() for Inputs[");
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
