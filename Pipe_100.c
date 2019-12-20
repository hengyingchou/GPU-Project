#include"gpumain.h"
#include<time.h>
extern float *h_A;// Host variable
extern float *h_x;
extern float *h_B;
extern float *h_R;
extern float *h_scalar;
extern float *Q;
extern float *R;
extern float *h_r;


extern float *d_A;
extern float *d_B;//Device variable
extern float *d_x;
extern float *d_R;
extern float *d_p;
extern float *d_Ap;
extern float *d_temp;
extern float *d_scalar;

int main()
{
	clock_t t ; 
	t = clock();
	int i;
	Allocate_Memory();
	friction();
	float sum = 0 ; 
	for(int i = 0 ; i < 25 ; i++){
	sum = 0 ;
 	jaco(Q,h_r);
        comR(h_r, Q);
	for(int j = 0 ; j < N ; j++){
        sum = sum + R[i]*R[i];
        }
	Init();
	Send_To_Device();
	Call_GPUSerial_Function();
	Get_From_Device();
	UpdateQ(Q,h_x);
	}
	t = clock() - t;
	for(int i = 0 ; i < N ; i++){
       	printf("Q[%d] = %g\n",i,Q[i]);
	}
	printf("GPU takes %f second\n",((float)t/CLOCKS_PER_SEC));
	Free_Memory();
	return 0;
}

