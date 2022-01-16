#ifndef __DNN_H__
#define __DNN_H__

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "ap_fixed.h"
using namespace std;


#define IMAGE_NUMS 100
#define IMAGE_SIZE 196
#define HIDDEN_LAYER 32
#define OUTPUT_CLASS 10
//#define PRINT_DEBUG

////////////////////////// Define Your Data Type here //////////////////////////
//typedef float w1_t;
//typedef float w2_t;
//typedef float b1_t;
//typedef float b2_t;
//typedef float image_t;
//typedef float tmp_t;


typedef ap_fixed<3,1,AP_RND,AP_SAT> w1_t;
typedef ap_fixed<3,1,AP_RND,AP_SAT> w2_t;
typedef ap_fixed<2,1,AP_RND,AP_SAT> b1_t;
typedef ap_fixed<2,1,AP_RND,AP_SAT> b2_t;
typedef ap_fixed<4,1,AP_RND,AP_SAT> image_t;
typedef ap_fixed<5,3,AP_RND,AP_SAT> tmp_t1;
typedef ap_fixed<6,4,AP_RND,AP_SAT> tmp_t2;

////////////////////////// Define Your Functions here //////////////////////////
// This is an example top, you can modify it freely.
int dnn(
		image_t input_image[IMAGE_SIZE],
		w1_t w1[IMAGE_SIZE][HIDDEN_LAYER],
		b1_t b1[HIDDEN_LAYER],
		w2_t w2[HIDDEN_LAYER][OUTPUT_CLASS],
		b2_t b2[OUTPUT_CLASS]);
		
// Some sub-functions:

#endif // __DNN_H__ not defined
