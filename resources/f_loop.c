
#define N 5

int f_loop(int* a,int* b,int* c){
	
	for(int i = 0; i < N; i++){
		a[i] = a[i]+b[i];
		c[i] = a[i]*c[i];
	}
	return 0;
}

int main(){
	
	int a[] = { 1, 2, 3, 4, 5};
	int b[] = { 10, 20, 30, 40, 50};
	int c[] = { 100, 200, 300, 400, 500};
	
	return f_loop(a,b,c);
}
