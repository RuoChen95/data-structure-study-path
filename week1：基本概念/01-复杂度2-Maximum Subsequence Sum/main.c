#include <stdio.h>

#define MAXNUMBER 10000

void MaxSum ( int a[], int N);

int main(int argc, char const *argv[])
{
    /* code */
    int N = 0;
    scanf("%d", &N);

    int A[MAXNUMBER];
    for (int i=0; i<N; i++) {
        scanf("%d", &A[i]);
    }

    MaxSum(A, N);

    return 0;
}

void MaxSum ( int a[], int N) {
	int i;
	int ThisSum, MaxSum;
	int m, n, temp;
	ThisSum = 0;
	MaxSum = -1; // 为了正确判断出0的存在区域 
	m = 0;
	n = 0;
	temp = 0;
	for (i = 0; i < N; i++){
		ThisSum += a[i];
		if (ThisSum > MaxSum) {
			MaxSum = ThisSum;
			n = i;
			m = temp;
		} 
		if (ThisSum < 0) {
			ThisSum = 0;
			temp = i+1;
		}
	}

	if (MaxSum >= 0) {
		printf("%d %d %d", MaxSum, a[m], a[n]);
	} else {
		printf("%d %d %d", 0, a[0], a[N-1]);
	}
}
