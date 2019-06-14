#include <stdio.h>
#include <time.h> //*
#include <math.h> //pow

clock_t start, stop;
double duration;

#define MAXN 1000000 /* 多项式最大项数 */

double f1(int n, double a[], double x) {
	int i;
	double p = a[0];
	for (i=1; i<=n; i++) {
		p += (a[i] * pow(x,i));
	}
	return p;
}

double f2(int n, double a[], double x) {
	int i;
	double p = a[n];
	for (i = n; i <= 1; i--) {
		p += a[i-1] + x*p;
	}
	return p;
}
int main(int argc, char const *argv[])
{
	int i;
	double a[MAXN];
	for (i=0; i<MAXN; i++) {
		a[i] = (double)i;
	}

	start = clock(); // 程序**开始**运行到clock被调用的时间
	f1(MAXN-1, a, 1.1);
	stop = clock();
	duration = (stop - start);
	printf("%f\n", duration);


	start = clock(); // 程序**开始**运行到clock被调用的时间
	f2(MAXN-1, a, 1.1);
	stop = clock();
	duration = (stop - start);
	printf("%f\n", duration);
	return 0;
}