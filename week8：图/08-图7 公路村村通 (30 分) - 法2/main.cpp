#include <stdio.h>
#include <queue>

using namespace std;

#define MAX 1001
#define INF 1000000000
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
            G[i][j].distance = INF;
        }
    }

    int v1, v2, dis;

    for (i = 0; i < M; i++) {
        scanf("%d %d %d", &v1, &v2, &dis);
        G[v1][v2].distance = dis;
        G[v2][v1].distance = dis;
    }

    // S => 1
    int dist[MAX], vis[MAX] = {0};
    for (i = 1; i <=N; i++) {
        dist[i] = INF; // 后面要进行比较
    }
    dist[1] = 0;
    
    // *
    int ans = 0;
    int flag = 1;
    for (i = 1; i<= N; i++) {
        int u = -1, MIN = INF;
        for (j = 1; j<= N; j++) {
            if (vis[j] == 0 && dist[j] < MIN) {
                MIN = dist[j];
                u = j;
            }
        }
        if (u == -1) {
            flag = 0;
            break;
        }
        vis[u] = 1;

        ans += dist[u];

        for (int v = 1; v <= N; v++) {
            if (vis[v] ==0 && G[u][v].distance != INF) {
                if (G[u][v].distance < dist[v]) {
                    dist[v] = G[u][v].distance;
                }
            }
        }
    }

    if (flag == 0) {
        printf("-1");
    } else {
        printf("%d", ans);
    }

    return 0;
}