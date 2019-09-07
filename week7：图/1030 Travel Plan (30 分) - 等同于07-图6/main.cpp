#include <iostream>
using namespace std;

#define maxv 500
#define INFI 1000000000

struct Node {
    int distance;
    int cost;
} node[maxv][maxv];

int N, M, S, D;
// 距离、花费、路径（图）
int dist[maxv], cost[maxv], pre[maxv];
void DFS(int v) {
    if (v == S) {
        printf("%d ", v);
        return;
    }
    DFS(pre[v]);
    printf("%d ", v);
}

int main(void) {

    scanf("%d %d %d %d", &N, &M, &S, &D);

    int c1, c2, dis, p, i;

    for (i = 0; i < maxv; i++) {
        for (int j = 0; j < maxv; j++) {
            node[i][j].distance = INFI;
            node[i][j].cost = INFI;
        
        }
    }

    for (i = 0; i < M; i++) {
        scanf("%d %d %d %d", &c1, &c2, &dis, &p);

        node[c1][c2].distance = dis;
        node[c2][c1].distance = dis;

        node[c1][c2].cost = p;
        node[c2][c1].cost = p;
    }

    int vis[maxv] = {0};
    for (i = 0; i < N; i++) {
        dist[i] = INFI;
        cost[i] = INFI;
        pre[i] = -1;
    }

    dist[S] = 0;
    cost[S] = 0;

    for (i = 0; i < N; i++) {
        int u = -1, min = INFI;
        for (int j = 0; j < N; j++) {
            if (vis[j] == 0 && dist[j] < min) {
                u = j;
                min = dist[j];
            }
        }

        if (u == -1) break;
        vis[u] = 1;

        for (int w = 0; w < N; w++) {
            if (vis[w] == 0 && node[u][w].distance != INFI) {
                if (dist[w] > dist[u] + node[u][w].distance) {
                    dist[w] = dist[u] + node[u][w].distance;
                    cost[w] = cost[u] + node[u][w].cost;
                    pre[w] = u;
                } else if (dist[w] == dist[u] + node[u][w].distance) {
                    if (cost[w] > cost[u] + node[u][w].cost) {
                        cost[w] = cost[u] + node[u][w].cost;
                        pre[w] = u;
                    }
                
                }
            }
        
        }
    }


    DFS(D);
    printf("%d %d", dist[D], cost[D]);


    return 0;
}