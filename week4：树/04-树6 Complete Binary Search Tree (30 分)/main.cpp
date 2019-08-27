
#include <iostream>
#include <algorithm> // sort
#include <cmath> // pow log floor

using namespace std;

#define MAXNUMBER 1000

int A[MAXNUMBER] = {0};
int T[MAXNUMBER] = {0};

void solve(int ALeft, int ARight, int TRoot);
int GetLeftLength(int n);
int main (void){
	int N;
	int i;
	
	scanf("%d", &N);
	for (i = 0; i < N; i++){
		scanf("%d", &A[i]);
	}

	sort(A, A + N);

	solve(0, N-1, 0);

	printf("%d", T[0]);
	for (i = 1; i < N; i++){
		printf(" %d", T[i]);
	}

	return 0;
}

// 左边，右边，当前子树根节点的位置
// 从A中选出正确数字，填到T中
void solve(int ALeft, int ARight, int TRoot) {
	int n;
	int L; // 左子树的节点数目
	n = ARight - ALeft + 1;
	if (n==0) return;
	L = GetLeftLength(n);
	T[TRoot] = A[ALeft + L];

	solve(ALeft, ALeft+L-1, TRoot * 2 + 1);
	solve(ALeft+L+1, ARight, TRoot * 2 + 2);
}

// 节点总数
int GetLeftLength(int N){
	int H = floor(log(N+1)/log(2)); // 层数 取下界，忽略X
	int X = N - pow(2, H) + 1; // 反求X
	X = X < pow(2, H-1)? X : pow(2, H -1);
	if(X < 0){
		X = 0;
	}

	int L = pow(2, H - 1) - 1 + X;

	return L;
}