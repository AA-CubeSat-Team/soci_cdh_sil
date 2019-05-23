#include "ecos.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

double RANDOM_DOUBLE_UPPER_BOUND = 30.0;
int RANDOM_INTEGER_UPPER_BOUND = 20; 

void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

double rd(a) {
	return (double)rand()/(double)(RAND_MAX/a);	
}

double ri(a) {
	return abs(rand() % a);	
}

void callecos(int n, int m, int p, int l, int ncones, double *c, int *Gjc, int *Gir, double *Gpr,
			  double* h, int* q, int* Ajc, int* Air, double *Apr, double *b, double *y) {
	/* Initialize */

	printf("setting up ecos...\n");

	pwork* mywork = ECOS_setup(n, m, p, l, ncones, q, 0, Gpr, Gjc, Gir, Apr, Ajc, Air, c, h, b);

	printf("ecos set up! Solving the problem....\n");
	/* Solve */
	idxint exitflag = ECOS_solve(mywork);
	printf("ecos solver has finished! Extacting solution...."); 

	/* Extract optimal solution */
	int i;
    int N=332; // c_size
	// Save optimal decision vector
	for(i=0;i<N;i++) {
		y[i] = mywork->x[i];
	}
	// Save exitflag
	y[N] = exitflag;
	// Save solution time
	y[N+1] = mywork->info->tsetup + mywork->info->tsolve;
	// Clean up memory
	ECOS_cleanup(mywork, 0);
}

int main() {	
	signal(SIGSEGV, handler);   // install our handler

	srand(time(0)); 

	int NUM_TEST_CASES = 1; 
	int n;
	int m;
	int p;
	int l;
	int ncones;
	double c[332];
	int Air[1278];
	int Ajc[333];
	double Apr[1278];
	double b[117];
	int Gir[674];
	int Gjc[333];
	double Gpr[674];
	double h[354];
	int q[1];
	double y[334];

	for (int i=0; i<NUM_TEST_CASES; i++) {

		printf("initializing new collection of random inputs...\n");

	  	n = ri(RANDOM_INTEGER_UPPER_BOUND);
	  	m = ri(RANDOM_INTEGER_UPPER_BOUND);
	  	p = ri(RANDOM_INTEGER_UPPER_BOUND);
	  	l = ri(RANDOM_INTEGER_UPPER_BOUND);
	  	ncones = ri(RANDOM_INTEGER_UPPER_BOUND);

	  	for (int j=0; j<332; j++) {
	  		c[j] = rd(RANDOM_DOUBLE_UPPER_BOUND);
	  	}
	  	for (int j=0; j<1278; j++) {
	  		Air[j] = ri(RANDOM_INTEGER_UPPER_BOUND);
	  	}
	  	for (int j=0; j<333; j++) {
	  		Ajc[j] = ri(RANDOM_INTEGER_UPPER_BOUND);
	  	}
	  	for (int j=0; j<1278; j++) {
	  		Apr[j] = rd(RANDOM_DOUBLE_UPPER_BOUND);
	  	}
	  	for (int j=0; j<117; j++) {
	  		b[j] = rd(RANDOM_DOUBLE_UPPER_BOUND);
	  	}
	  	for (int j=0; j<674; j++) {
	  		Gir[j] = ri(RANDOM_INTEGER_UPPER_BOUND);
	  	}
	  	for (int j=0; j<333; j++) {
	  		Gjc[j] = ri(RANDOM_INTEGER_UPPER_BOUND);
	  	}
	  	for (int j=0; j<674; j++) {
	  		Gpr[j] = rd(RANDOM_DOUBLE_UPPER_BOUND);
	  	}
	  	for (int j=0; j<354; j++) {
	  		h[j] = rd(RANDOM_DOUBLE_UPPER_BOUND);
	  	}
	  	for (int j=0; j<1; j++) {
	  		q[j] = ri(RANDOM_INTEGER_UPPER_BOUND);
	  	}

	  	printf("random inputs initialized!");

	  	printf("Calling callecos()...\n");
		callecos(n,m,p,l,ncones,c,Gjc,Gir,Gpr,h,q,Ajc,Air,Apr,b,y);
		printf("Done. The result is being printed below:");

   		for(int loop = 0; loop < 334; loop++) {
      		printf("%f ", y[loop]);
   		}

	}

	return 0;
}