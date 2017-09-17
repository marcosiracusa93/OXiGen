
#define N 5

int f_loop(int* a,int* b){
	
	int c[N]; 
	for(int i = 0; i < N; i++){
		c[i] = a[i]+b[i];
		a[i] = c[i]*a[i];
	}
	return 0;
}

int main(){
	
	int a[] = { 1, 2, 3, 4, 5};
	int b[] = { 10, 20, 30, 40, 50};
	
	return f_loop(a,b);
}
