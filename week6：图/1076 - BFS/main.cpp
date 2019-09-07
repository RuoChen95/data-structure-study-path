#include "stdafx.h"
#pragma warning(disable:4996)
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAXV 1010

struct Node {
	int id;
	int layer;
};

vector<Node> G[MAXV];
int vis[MAXV] = {0};


int BFS(int s, int L) {
	int numForward = 0;
	queue<Node> Q;
	Node start;
	start.id = s;
	start.layer = 0;
	Q.push(start);

	while (!Q.empty()) {
		Node topNode = Q.front();
		Q.pop();

		int u = topNode.id;

		for (int i = 0; i < G[u].size(); i++) {
			Node now = G[u][i];
			now.layer = topNode.layer + 1;

			if (vis[now.id] == 0 && now.layer <= L && now.id != start.id) {
				Q.push(now);
				vis[now.id] = 1;
				numForward++;
			}
		}
	}

	return numForward;
}
int main(void) {
	Node user;
	int N, L, nFollow, FollowId;

	scanf("%d %d", &N, &L);

	for (int i = 1; i <= N; i++) {
		scanf("%d", &nFollow);
		for (int j = 0; j < nFollow; j++) {
			scanf("%d", &FollowId);
			user.id = i;

			G[FollowId].push_back(user);
		}
	}

	int K, s;
	scanf("%d", &K);
	for (int i = 0; i < K; i++) {
		for (int j = 1; j <= N; j++) {
			vis[j] = 0;
		}
		
		scanf("%d", &s);

		int numForward = BFS(s, L);

		printf("%d\n", numForward);
	}


    return 0;
}