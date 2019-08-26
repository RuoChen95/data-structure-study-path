#include <iostream>
#include <stack>
#include <string>

#define MAXNUMBER 30
using namespace std;

int pre[MAXNUMBER] = {0}, in[MAXNUMBER] = {0}, post[MAXNUMBER] = {0};
void solve(int preL, int inL, int postL, int n);
int main (void){
	stack<int> s;
	int i, N, temp, pre_index = 0, in_index = 0;
	string str;
	scanf("%d", &N);
	for (i = 0; i < 2*N; i++){
		cin >> str;
		if (str == "Push") {
			scanf("%d", &temp);
			pre[pre_index] = temp; pre_index++;
			s.push(temp);
		} else {
			in[in_index] = s.top(); in_index++;
			s.pop();
		}
	}
	solve(0, 0, 0, N);
	printf("%d", post[0]);
	for (i = 1; i < N; i++) {
		printf(" %d", post[i]);
	}
	return 0;
}

void solve(int preL, int inL, int postL, int n) {
	int root;
	int i;
	int L, R;

	if (n==0) return;
	if (n==1) {
		post[postL] = pre[preL];
		return;
	}

	root = pre[preL];
	post[postL+n-1] = root;

	for (i = 0; i <n; i++){
		if (in[inL+i] == root) break;
	}
	L = i;
	R = n-L -1;

	solve(preL+1, inL, postL, L);
	solve(preL+L+1, inL+L+1, postL+L, R);
}