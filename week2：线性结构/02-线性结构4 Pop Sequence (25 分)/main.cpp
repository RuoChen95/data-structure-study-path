// https://blog.csdn.net/liyuanyue2017/article/details/83302030
#include <stdio.h>
#include <stack>

#define MAXNUMBER 1000
using namespace std;

int detect(int M, int N);
void print(int N);
int main (void){
	int M, N, K;
	scanf("%d %d %d", &M, &N, &K);

	int i;
    int res[MAXNUMBER] = {0};
	for (i = 0; i < K; i++){
		res[i] = detect(M, N);
	}
	
	print(res[0]);
	for (i = 1; i < K; i++) {
		printf("\n");
		print(res[i]);
	}
}

int detect(int M, int N){
	int v[MAXNUMBER] = {0};
	int i;
	for (i = 0; i < N; i++){
		scanf("%d", &v[i]);
	}
	
	stack<int> s;
	int current = 0;
	for (i = 1; i <= N; i++){
		s.push(i);
		if (s.size() > M) {
			break;
		}
		while (!s.empty() && v[current] == s.top()){
			current++;
			s.pop();
		}
	}

	if (current == N) {
		return 1;
	} else {
		return 0;
	}
}

void print(int N) {
	if (N == 1){
		printf("YES");
	} else {
		printf("NO");
	}
}
