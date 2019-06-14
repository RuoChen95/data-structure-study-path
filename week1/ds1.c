#include <stdio.h>

void PrintN(int N) {
	int i;
	for (i=1; i<=N; i++) {
		printf("%d\n", i);
	}
}

void PrintN2(int N) {
	if (N >= 1) {
		PrintN2(N-1);
		printf("%d\n", N);
	}
}
int main(int argc, char const *argv[])
{
	int N;
	scanf("%d", &N);
	PrintN2(N);
	return 0;
}