#include "stdafx.h"
#pragma warning(disable:4996)
#include <cstdio>
#include <vector>
#include <algorithm>

#define MAX 110
using namespace std;
struct node {
	int weight;
	vector<int> child;
}Node[MAX];

int path[110];

bool cmp(int a, int b) {
	return Node[a].weight > Node[b].weight;
}

int N, M, S;

// 当前访问节点的index
// 节点的数量（用于输出
// 节点的和
void DFS(int index, int numNode, int sum) {
	if(sum > S) return;
	if (sum == S) {
		if (Node[index].child.size() != 0) return;

		//
		for (int i = 0; i < numNode; i++) {
			printf("%d", Node[path[i]].weight);
			if (i < numNode - 1) {
				printf(" ");
			} else {
				printf("\n");
			}
		}
	}

	for(int i = 0; i < Node[index].child.size(); i++) {
		int childIndex = Node[index].child[i];

		//*
		path[numNode] = childIndex;

		//*
		DFS(childIndex, numNode+1, sum+Node[childIndex].weight);
	}
}
int main(void) {
	scanf("%d %d %d", &N, &M, &S);

	for (int i = 0; i < N; i++) {
		scanf("%d", &Node[i].weight);
	}

	int id, K, child;
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &id, &K);

		for (int j = 0; j < K; j++) {
			scanf("%d", &child);

			Node[id].child.push_back(child);
		}

		sort(Node[id].child.begin(), Node[id].child.end(), cmp);
	}

	path[0] = 0;

	DFS(0, 1, Node[0].weight);

    return 0;
}