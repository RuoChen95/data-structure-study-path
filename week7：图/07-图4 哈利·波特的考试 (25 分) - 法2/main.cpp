#include <stdio.h>
#include <queue>

using namespace std;

#define MAX 101
#define INFI 1000000000
struct node {
	int distance;
} G[MAX][MAX];

queue<int> Q;


int main(void) {
	int N, M;

	scanf("%d %d", &N, &M);

	int i, j;
	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			G[i][j].distance = INFI;
		}
	}

	int v1, v2, dis;

	for (i = 0; i < M; i++) {
		scanf("%d %d %d", &v1, &v2, &dis);
		G[v1][v2].distance = dis;
		G[v2][v1].distance = dis;
	}

	int D[MAX][MAX];

	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			D[i][j] = G[i][j].distance;
			if (i == j) {
				D[i][j] = 0;
			}
		}
	}

	int k;

	for (k = 1; k <= N; k++) {
		for (i = 1; i <= N; i++) {
			for (j = 1; j <= N; j++) {
				if (D[i][j] > D[i][k] + D[k][j]) {
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}

	int index = 1;
	int MaxLength = INFI;
	for (i = 1; i <= N; i++) {
		int L = 0;
		for (j = 1; j <= N; j++) {
			if (D[i][j] > L) {
				L = D[i][j];
			}
		}
		if (MaxLength > L) {
			index = i;
			MaxLength = L;
		}
	}

    if (MaxLength == INFI) {
		printf("0");
	} else {
		printf("%d %d", index, MaxLength);
	}

    return 0;
}