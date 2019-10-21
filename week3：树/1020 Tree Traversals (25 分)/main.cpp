#include "stdafx.h"
#pragma warning(disable:4996)
#include <cstdio>
#include <queue>

using namespace std;

#define maxv 31

struct node {
	int data;
	node* left;
	node* right;
};

int post[maxv], in[maxv];
int N;

node* solve(int postL, int postR, int inL, int inR) {
	if (postL > postR) return NULL;
	node* root = new node;
	root->data = post[postR];

	int k;
	for(int i = inL; i <= inR; i++) {
		if (in[i] ==  root->data) {
			k = i;
			break;
		}
	}

	int numLeft =  k - inL;
	root->left = solve(postL, postL+numLeft-1, inL, k-1);
	root->right = solve(postL+numLeft, postR - 1, k+1, inR);

	return root;
}

void BFS(node* root) {
	queue<node*> Q;
	Q.push(root);
	int num = 0;
	while (!Q.empty()) {
		node* now = Q.front();
		printf("%d", now->data);
		Q.pop();
		num++;
		if (num < N) {
			printf(" ");
		}
		if (now->left) {
			Q.push(now->left);
		}

		if (now->right) {
			Q.push(now->right);
		}
	}

}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &post[i]);
	}
	for (int i = 0; i < N; i++) {
		scanf("%d", &in[i]);
	}

	node* root = solve(0, N-1, 0, N-1);

	BFS(root);


	return 0;
}