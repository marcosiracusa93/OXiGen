#define N 100

#include "MaxJFunctions.h"

void test_1(int* in_1,int* in_2,int* out_1, int* out_2){

    for(int i = 0; i < N; i++){
        out_1[i] = in_1[i] - in_2[i];//in : in -> out
        out_2[i] = 5*3 + 7/8;        //scalar_expr -> out
    }

    int a = 10, b = 15;
    int tmp[N];

    for(int i =0; i < N; i++){
        tmp[i] = out_2[i] + a/b; //out : scalar -> tmp
    }

    for(int i = 0; i < N; i++){
        out_1[i] = tmp[i]*2;     //tmp : scalar -> out
    }
}

//WAW test
void test_2(int* in, int* out){

    for(int i = 0; i < N; i++){
        out[i] = in[i] + 10;
        out[i] = 2*in[i];
    }

    for(int i = 0; i < N; i++){
        out[i] = 3*in[i];
    }
}

void test_3(int* in,int* out){

    for(int i = 0; i < N; i++){
        out[i] = in[i] + 5;
    }
    for(int i = 0; i < N; i++){
        out[i] = out[i] + in[i]*2;
    }
}
//unused a, tmp copy
void test_4(int* in,int* out){

    for(int i = 0; i < N; i++){
        out[i] = in[i] + 5;
    }
    int tmp[N];
    int tmp2[N];
    int a = 3;
    for(int i = 0; i < N; i++){
        tmp[i] = out[i];
        tmp2[i] = tmp[i];
        out[i] = tmp2[i]*5;
    }

}

void test_5(int* in, int* out){

    for(int i = 0; i < N-1; i++){
        out[i+1] = in[i] + 5;
    }
}

void test_6(int* in, int* out){

    for(int i = 0; i < N-2; i++){
        out[i+1] = in[i+1] + in[i+2];
    }
}

void test_7(int* in,int* out){

    int tmp[N];

    for(int i = 0; i < N-1; i++) {
        tmp[i + 1] = in[i] + 5;
    }
    for(int i = 0; i < N-1; i++){
        out[i] = tmp[i] + 3;
    }

}

void test_8(int* in,int* out) {

    int tmp[N];

    for (int i = 1; i < N - 1; i++) {
        tmp[i] = in[i - 1] + 5;
    }
    for (int i = 1; i < N - 1; i++) {
        out[i] = tmp[i+1] + in[i-1];
    }
}

void test_9(int* in, int* out){

    for(int i = 0; i < N; i++){
        out[i] = in[i] + 1;
    }
    for(int i = 1; i < N-1; i++){
        out[i] = in[i] + 10;
    }
    for(int i = 2; i < N-2; i++){
        out[i] = in[i] + 100;
    }
}

void test_10(int* in,int* out){

    int tmp[N];

    for(int i = 0; i < N; i++){
        out[i] = out[i+1] + out[i+2];
        out[i+1] = out[i+1] + 3;
    }
}

void mov_avg(int * in, int* out){

    for(int i = 1; i < N-1; i++){
        out[i] = (in[i-1] + in[i] + in[i+1])/3;
    }
}


void averageKernel(float* input, float* output){

    int i;

    output[0] = (input[0] + input[1]) / 2;

    for(i = 1; i < N - 1; i++){

        output[i] = (input[i - 1] + input[i] + input[i + 1]) / 3;

    }

    output[N - 1] = (input[N - 2] + input[N - 1]) / 2;

    return;

}

void test_cast(float* in, int* out){

    for(int i = 0; i < N; i++){
        out[i] = (int)in[i] + 2;

    }
}

void func_test(float* in, float* out){

    for(int i = 0; i < N; i++){
        out[i] = log(exp(in[i]));
    }
}

void cond_test(int a,int* in,int* out){

    for(int i = 0; i < N; i++){
        out[i] = a > 3 ? 5 : 10;
    }
}

void nested_test_1(int* in,int* v,int* out){

    for(int i = 0; i < N; i++){
        for (int j = 0; j < N/10; j++) {	//NESTED LOOP #2
            out[i] = in[i] + v[j];
        }
    }
}

void unroll_test(int* in,int* v,int* out){
    for(int j = 0; j < 1000; j++){
        *in = v[j] + 3;
    }
}

void counter_test(int* in, int* out){

    for(int i = 0; i < N; i++) {
        for (int j = 0; j < 4; j++) {
            out[i] = in[i] + j;
        }
    }
}

void acc_test(int* in, int* out){

    int acc = 3;
    for(int i = 0; i < N; i++){
        out[i] = in[i]*acc;
        acc = 2*acc;
    }
}

void acc_test_2(int* in, int* out){
	
	int sum = 0;
	for(int i = 0; i < N; i++){
		sum += in[i];	
		out[i] = sum*2;
	}

}

void newton_raphson(float* in,float* out){

    for (int i = 0; i < N; i++) {

        float v = 2.9142 - 2*in[i];

        for (int j=0; j< 4; j++) {
            v = v * (2.0 - in[i] * v);
        }
        out[i] = v;
    }
}

void two_loops(float* in, float* out,float* out1){

    for(int i = 0; i < N; i++){

        for(int j = 0; j < 4; j++){
            out1[i] = in[i] + 4;
        }
        for(int j = 0; j < 4; j++){
            out[i] = out1[i] + 5;
        }
    }
}

void two_d_test(unsigned char in[N][3], unsigned char out[N][3]){

    float x[N];

    for(int i = 0; i < N; i++){
        x[i] = in[i][0] + in[i][1] + in[i][2];
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++) {
            out[i][j] = x[i] + in[i][j];
        }
    }
}