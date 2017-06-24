#define N 10
#define M_1 20
#define M_2 15
#define G 6.67e-11

int gravitational_force(float* x1, float* x2,float m1,float m2,float g, float* f){


	for(int i = 0; i < N; i++){
		f[i] = (g * m1 * m2) / ((x1[i]-x2[i])*(x1[i]-x2[i])); 	
	}
	return 0;
}

int main(){
	float x[N] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
	float y[N] = {2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0};
	float f[N] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

	return  gravitational_force(x,y,M_1,M_2,G,f);

}

