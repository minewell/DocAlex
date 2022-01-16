#include "dnn.h"
#include "ap_fixed.h"
//void dnn(int *input,int *out){}
int dnn(
		image_t input_image[IMAGE_SIZE],
		w1_t w1[IMAGE_SIZE][HIDDEN_LAYER],
		b1_t b1[HIDDEN_LAYER],
		w2_t w2[HIDDEN_LAYER][OUTPUT_CLASS],
		b2_t b2[OUTPUT_CLASS])
{
	int label = 0;
	tmp_t1 Hidden[HIDDEN_LAYER];
	tmp_t1 temp1[HIDDEN_LAYER];
	tmp_t1 temp3[HIDDEN_LAYER];
	tmp_t1 temp4[HIDDEN_LAYER];
	tmp_t1 temp5[HIDDEN_LAYER];
	tmp_t1 temp6[HIDDEN_LAYER];
	tmp_t1 temp7[HIDDEN_LAYER];
	tmp_t1 temp8[HIDDEN_LAYER];
	tmp_t2 Output[OUTPUT_CLASS];
	tmp_t2 temp2[OUTPUT_CLASS];

	Add_prel:
		for(int i=0;i<HIDDEN_LAYER;i++){
			Hidden[i]=b1[i];
		}

	Add_pre2:
		for(int i=0;i<OUTPUT_CLASS;i++){
			Output[i]=b2[i];
		}

	Hidden_Outer_Loop:
	for (int i=0;i<IMAGE_SIZE;i+=4){
		Hidden_Inner_Loop:
			for(int j=0;j<=HIDDEN_LAYER;j++){
				temp1[j]=input_image[i]*w1[i][j];
				temp3[j]=input_image[i+1]*w1[i+1][j];
				temp4[j]=input_image[i+2]*w1[i+2][j];
				temp5[j]=input_image[i+3]*w1[i+3][j];
				temp6[j]=temp1[j]+temp3[j];
				temp7[j]=temp4[j]+temp5[j];
				temp8[j]=temp6[j]+temp7[j];
				Hidden[j]=Hidden[j]+temp8[j];
			}
	}


	ReLU:
	for(int i=0;i<HIDDEN_LAYER;i++){
		if (Hidden[i]<0) Hidden[i]=0;
	}

	Output_Outer_Loop:
	for(int i=0;i<HIDDEN_LAYER;i++){
	Output_Inner_Loop:
		for(int j=0;j<OUTPUT_CLASS;j++){
			temp2[j]=Hidden[i]*w2[i][j];
			Output[j]+=temp2[j];
		}
	}

	Find_max:
	for(int i=0;i<OUTPUT_CLASS;i++){
		if(Output[i]>Output[label]) label=i;
	}

	return label;
}
