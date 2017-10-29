#define N 100

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
        out[i] = in[i+1] + in[i+2];
    }
}