
#include <iostream>
#include <queue>

using namespace std;

#define INFI 1000000
#define MAX 31
struct Node {
	int data;
	Node* lchild;
	Node* rchild;
};

int post[MAX], in[MAX];
int N, num = 0;

Node* solve(int postL, int postR, int inL, int inR) {
	if (postL > postR) return NULL;
	Node* root = new Node;

	root->data = post[postR];
	
	int k;
	for (int i = inL; i <= inR; i++) {
		if (in[i] == post[postR]) {
			k = i;
			break;
		}
	}

	int numLeft = k - inL;
	
	root->lchild = solve(postL, postL + numLeft -1, inL, k - 1);
	root->rchild = solve(postL + numLeft, postR - 1, k+1, inR);

	return root;
}

void BFS(Node* root) {
	queue<Node*> Q;
	Q.push(root);

	while(!Q.empty()) {
		Node* now = Q.front();
		printf("%d", now->data);
		Q.pop();

		num++;
		if (num < N) {
			printf(" ");
		}

		if (now->lchild) {
			Q.push(now->lchild);
		}
		if (now->rchild) {
			Q.push(now->rchild);
		}
	}
}

int main(void) {
	scanf("%d", &N);
	int i;

	for (i = 0; i < N; i++) {
		scanf("%d", &post[i]);
	}

		for (i = 0; i < N; i++) {
		scanf("%d", &in[i]);
	}

	Node* root = solve(0, N-1, 0, N-1);

	BFS(root);

    return 0;
}