#include "stdafx.h"
#pragma warning(disable:4996)
#include <cstdio>
#include <vector>

using namespace std;
struct node {
	int data;
	node* left;
	node* right;
};

void insert(node* &root, int data) {
	if (root == NULL) {
		root = new node;
		root->data = data;
		root->left = NULL;
		root->right = NULL;
		return;
	}
	if (data < root->data) {
		insert(root->left, data);
	} else {
		insert(root->right, data);
	}
}

void perOrder(node* root, vector<int>&vi) {
	if (root == NULL) return;
	vi.push_back(root->data);

	perOrder(root->left, vi);
	perOrder(root->right, vi);
}

void perOrderMirror(node * root, vector<int>&vi) {
	if (root == NULL) return;
	vi.push_back(root->data);

	perOrderMirror(root->right, vi);
	perOrderMirror(root->left, vi);
}

void postOrder(node* root, vector<int>&vi) {
	if (root == NULL) return;

	postOrder(root->left, vi);
	postOrder(root->right, vi);

	vi.push_back(root->data);
}

void postOrderMirror(node * root, vector<int>&vi) {
	if (root == NULL) return;

	postOrderMirror(root->right, vi);
	postOrderMirror(root->left, vi);

	vi.push_back(root->data);
}


vector<int> per, perMirror, post, postMirror, origin;
int main(void) {
	int N, data;
	node* root = NULL;

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &data);

		origin.push_back(data);

		insert(root, data);
	}

	perOrder(root, per);
	perOrderMirror(root, perMirror);
	postOrder(root, post);
	postOrderMirror(root, postMirror);

	if (origin == per) {
		printf("YES\n");

		for (int i = 0; i < post.size(); i++) {
			printf("%d", post[i]);
			if (i < post.size() - 1) printf(" ");
		}
	} else if (origin == perMirror) {
		printf("YES\n");

		for (int i = 0; i < postMirror.size(); i++) {
			printf("%d", postMirror[i]);
			if (i < postMirror.size() - 1) printf(" ");
		}
	} else {
		printf("No\n");
	}

    return 0;
}