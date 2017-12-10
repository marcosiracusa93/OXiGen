#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
#include "MaxJFunctions.h"

#define Data_Type float
#define n 30

Data_Type SQRT_2PI = 2.5066282746310002;

Data_Type d_A[6] = { 0.0, 3.16112374387056560, 113.864154151050156,
		377.485237685302021, 3209.37758913846947, 0.185777706184603153 };

Data_Type d_B[5] = { 0.0, 23.6012909523441209, 244.024637934444173,
		1282.61652607737228, 2844.23683343917062 };

Data_Type d_C[10] = { 0.0, 0.564188496988670089, 8.88314979438837594,
		66.1191906371416295, 298.635138197400131, 881.952221241769090,
		1712.04761263407058, 2051.07837782607147, 1230.33935479799725,
		2.15311535474403846e-8 };

Data_Type d_D[9] = { 0.0, 15.7449261107098347, 117.693950891312499,
		537.181101862009858, 1621.38957456669019, 3290.79923573345963,
		4362.61909014324716, 3439.36767414372164, 1230.33935480374942 };

Data_Type d_P[7] = { 0.0, 0.305326634961232344, 0.360344899949804439,
		0.125781726111229246, 0.0160837851487422766, 0.000658749161529837803,
		0.0163153871373020978 };

Data_Type d_Q[6] = { 0.0, 2.56852019228982242, 1.87295284992346047,
		0.527905102951428412, 0.0605183413124413191, 0.00233520497626869185 };


unsigned long getTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 * 1000 + tv.tv_usec;
}

/*Data_Type Ncdf(Data_Type x)
{
	static const Data_Type THRESH = 0.46875;
	static const Data_Type INV_SQRT_PI = 0.56418958354775628;
	static const Data_Type INV_SQRT_TWO = 0.70710678118654752;

	Data_Type d = x * INV_SQRT_TWO;
	Data_Type y = fabs(d);
	int i;
	Data_Type res;

	if (y <= THRESH)
	{

		Data_Type ysq = y * y;
		Data_Type Xnum = d_A[5] * ysq;
		Data_Type Xden = ysq;
		for (i = 1; i < 4; i++) {

			Xnum = (Xnum + d_A[i]) * ysq;
			Xden = (Xden + d_B[i]) * ysq;
		}
		Data_Type ans = d * (Xnum + d_A[4]) / (Xden + d_B[4]);
		res = 0.5 * (1.0 + ans);
	} else if (y <= 4.0)
	{

		Data_Type Xnum = d_C[9] * y;
		Data_Type Xden = y;

		for (i = 1; i < 8; i++) {

			Xnum = (Xnum + d_C[i]) * y;
			Xden = (Xden + d_D[i]) * y;
		}
		Data_Type ans = (Xnum + d_C[8]) / (Xden + d_D[8]);
		ans *= exp(-y * y);

		if (d > 0)
			res = 1.0 - 0.5 * ans;
		else
			res = 0.5 * ans;
	} else
	{

		Data_Type ysq_inv = 1 / (y * y);
		Data_Type Xnum = d_P[6] * ysq_inv;
		Data_Type Xden = ysq_inv;
		for (i = 1; i < 5; i++) {

			Xnum = (Xnum + d_P[i]) * ysq_inv;
			Xden = (Xden + d_Q[i]) * ysq_inv;
		}
		Data_Type ans = ysq_inv * (Xnum + d_P[5]) / (Xden + d_Q[5]);
		ans = (INV_SQRT_PI - ans) / y;
		ans *= exp(-y * y);

		if (d > 0)
			res = 1.0 - 0.5 * ans;
		else
			res = 0.5 * ans;
	}
	return res;
}*/

void Calculation(int *Type, Data_Type *S, Data_Type *X, Data_Type *t1,
		Data_Type *T, short int *m, short int *ave, Data_Type *r, Data_Type *b,
		Data_Type *v, Data_Type *res, long Data_Dim)
{

	int i, j;
	Data_Type logS, logX, vx, my, Km;
	Data_Type dt, sum1 = 0, sum2 = 0, Nc_arg;
	Data_Type logkmvx, N1, N2;
	Data_Type Nc1, Nc2, sgn;
	Data_Type sum1_array[n], sum2_array[n], exp_arg[n];
	Data_Type v_i, v_xi[n], m_yi;
	Data_Type res1, res2, res3, res4, div_vx;
	Data_Type itmp2, temp2, v_i_pow, ttt;
	Data_Type tmp0, temp1, tmp3, tmp4, tmp5, tmp6, tmp1, p1;

	for (j = 0; j < Data_Dim; j++) {

		sum1 = 0.0;
		sum2 = 0.0;

		tmp0 = ave[j] - 1.0;

		tmp1 = v[j] * v[j];

		tmp3 = b[j] - tmp1 * 0.5;

		dt = (T[j] - t1[j]) / (tmp0);

		logS = log(S[j]);
		ttt = 1 / (2.0 * ave[j]);

		my = logS + (tmp3) * (t1[j] + (tmp0) * dt * 0.5);
		temp1 = t1[j] + dt * (tmp0) * (2 * ave[j] - 1.0) / (6.0 * ave[j]);
		vx = v[j] * sqrt(temp1);

		tmp4 = 1 / (vx * vx);
		logX = log(X[j]);
		tmp5 = logX - my;
		tmp6 = tmp4 * tmp5;

		for (i = 0; i < n; i++) {

			itmp2 = dt * (i - ((i + 1) * i) * ttt);

			temp2 = t1[j] + i * dt;

			v_i = v[j] * sqrt(temp2);
			v_i_pow = v_i * v_i;
			v_xi[i] = tmp1 * (t1[j] + itmp2);
			m_yi = logS + tmp3 * (t1[j] + i * dt);
			exp_arg[i] = m_yi + v_i_pow * 0.5;
			p1 = m_yi + v_xi[i] * tmp6 + (v_i_pow - v_xi[i] * v_xi[i] * tmp4)
					* 0.5;
			sum1_array[i] = exp(p1);

		}

		for (i = 0; i < n; i++) {
			sum1 += sum1_array[i];
		}

		Km = log(2.0 * X[j] - sum1 / ave[j]);
		div_vx = 1 / vx;
		logkmvx = (my - Km) * div_vx;

		sgn = (Type[j] == 0) ? 1 : -1;

		N1 = sgn * logkmvx;
		N2 = sgn * div_vx;

		for (i = 0; i < n; i++) {

			Nc_arg = (N1 + N2 * v_xi[i]);
			Nc1 = Ncdf(Nc_arg);

			sum2_array[i] = exp(exp_arg[i]) * Nc1;

		}

		for (i = 0; i < n; i++) {
			sum2 += sum2_array[i];
		}
		Nc_arg = (sgn * logkmvx);
		Nc2 = Ncdf(Nc_arg);

		res1 = exp(r[j] * T[j]);
		res4 = (1 / res1);
		res2 = (sum2 / ave[j] - X[j] * Nc2);

		res3 = (sgn * (ave[j] - m[j])) / ave[j];
		res[j] = (res2 * res3 * res4);
	}

}

int main(int argc, char *argv[])
{

	double time0, time1, execTime;

	int i = 0;

	if(argc < 2) {
		perror("missing parameters. Run as: ./program RANGE_FILE");
		return 1;
	}

	FILE *fd;
	fd = fopen(argv[1], "r");
	if (fd == NULL) {
		perror("Error during the opening of the input file!");
		return (1);
	}
	printf("Done!\n");
	printf("Read the input data...\n");

	float minF, maxF;
	short int minSI, maxSI;

	long Data_Dim;

	fscanf(fd, "%lu",&Data_Dim);

	int *Tpe = (int *) malloc(sizeof(int) * Data_Dim);
	Data_Type *S = (Data_Type *) malloc(sizeof(Data_Type) * Data_Dim);
	Data_Type *X = (Data_Type *) malloc(sizeof(Data_Type) * Data_Dim);
	Data_Type *t1 = (Data_Type *) malloc(sizeof(Data_Type) * Data_Dim);
	Data_Type *T = (Data_Type *) malloc(sizeof(Data_Type) * Data_Dim);
	short int *ave = (short int *) malloc(sizeof(short int) * Data_Dim);
	short int *m = (short int *) malloc(sizeof(short int) * Data_Dim);
	Data_Type *r = (Data_Type *) malloc(sizeof(Data_Type) * Data_Dim);
	Data_Type *b = (Data_Type *) malloc(sizeof(Data_Type) * Data_Dim);
	Data_Type *v = (Data_Type *) malloc(sizeof(Data_Type) * Data_Dim);
	Data_Type *res = (Data_Type *) malloc(sizeof(Data_Type) * Data_Dim);
	
	fscanf(fd, "%f %f",&minF,&maxF);
	for (i = 0; i < Data_Dim; i++) {
		Tpe[i] = (Data_Type)(rand()*(maxF-minF)) / RAND_MAX  + minF;
	}

	fscanf(fd, "%f %f",&minF,&maxF);
	for (i = 0; i < Data_Dim; i++) {
		S[i] = (Data_Type)(rand()*(maxF-minF)) / RAND_MAX  + minF;
	}

	fscanf(fd, "%f %f",&minF,&maxF);
	for (i = 0; i < Data_Dim; i++) {
		X[i] = (Data_Type)(rand()*(maxF-minF)) / RAND_MAX  + minF;
	}

	fscanf(fd, "%f %f",&minF,&maxF);
	for (i = 0; i < Data_Dim; i++) {
		t1[i] = (Data_Type)(rand()*(maxF-minF)) / RAND_MAX  + minF;
	}

	fscanf(fd, "%f %f",&minF,&maxF);
	for (i = 0; i < Data_Dim; i++) {
		T[i] = (Data_Type)(rand()*(maxF-minF)) / RAND_MAX  + minF;
	}

	fscanf(fd, "%f %f",&minF,&maxF);
	for (i = 0; i < Data_Dim; i++) {
		r[i] = (Data_Type)(rand()*(maxF-minF)) / RAND_MAX  + minF;
	}

	fscanf(fd, "%f %f",&minF,&maxF);
	for (i = 0; i < Data_Dim; i++) {
		b[i] = (Data_Type)(rand()*(maxF-minF)) / RAND_MAX  + minF;
	}

	fscanf(fd, "%f %f",&minF,&maxF);
	for (i = 0; i < Data_Dim; i++) {
		v[i] = (Data_Type)(rand()*(maxF-minF)) / RAND_MAX  + minF;
	}

	fscanf(fd, "%hd %hd",&minSI,&maxSI);
	for (i = 0; i < Data_Dim; i++) {
		m[i] = (Data_Type)(rand()*(maxSI-minSI)) / RAND_MAX  + minSI;
	}

	fscanf(fd, "%hd %hd",&minSI,&maxSI);
	for (i = 0; i < Data_Dim; i++) {
		ave[i] = (short int)(rand()*(maxSI-minSI)) / RAND_MAX  + minSI;
		if (ave[i] != n) {
			printf("Problem reading files, ave is %d", ave[i]);
			return 1;
		}
	}

	fclose(fd);

	printf("Starting computation...\n");
	time0 = getTime();

	Calculation(Tpe, S, X, t1, T, m, ave, r, b, v, res, Data_Dim);

	time1 = getTime();
	execTime = time1 - time0;

	printf("Execution time: %lf seconds\n", execTime / 1000000);

	free(Tpe);
	free(S);
	free(X);
	free(t1);
	free(T);
	free(ave);
	free(m);
	free(r);
	free(b);
	free(v);
	free(res);
	
	printf("End\n");
	return 0;
}

