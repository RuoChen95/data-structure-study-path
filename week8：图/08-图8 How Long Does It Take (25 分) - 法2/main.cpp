// todo: 最大N可行未过

#include <stdio.h>
#include <queue>

using namespace std;

#define MAX 100
#define INF 1000000000
struct node {
    int time;
} G[MAX][MAX];

queue<int> Q;


int main(void) {
    int N, M;

    scanf("%d %d", &N, &M);

    int i, j;
    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++) {
            G[i][j].time = INF;
        }
    }

    int v1, v2, time;

    for (i = 0; i < M; i++) {
        scanf("%d %d %d", &v1, &v2, &time);
        G[v1][v2].time = time;
    }

    int indegree[MAX] = {0};

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (G[i][j].time != INF) {
                indegree[j]++;
            }
        }
    }
    
    int T[MAX] = {0};
    for (i = 0; i < N; i++) {
        if (indegree[i] == 0) {
            T[i] = 0;
            Q.push(i);
        } else {
            T[i] = INF;
        }
    }
    int num = 0;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        for (i = 0; i < N; i++) {
            if (G[u][i].time != INF && u != i) {
                indegree[i]--;
                if (indegree[i] == 0) {
                    Q.push(i);
                    if (T[i] >  T[u] + G[u][i].time) {
                        T[i] = T[u] + G[u][i].time;
                    }
                }
            }
        }
        num++;
    }
    
    if (num == N) {
        int result = 0;
        for (i = 0; i < N; i++) {
            if (result < T[i]) {
                result = T[i];
            }
        }

        printf("%d\n", result);
    } else {
        printf("Impossible");
    }


    return 0;
}