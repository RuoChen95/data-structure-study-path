#include <stdio.h>
#include <queue>

using namespace std;

#define MAX 500
#define INFI 1000000000
struct node {
    int distance;
    int price;
} G[MAX][MAX];

queue<int> Q;


int main(void) {
    int N, M, S, D;

    scanf("%d %d %d %d", &N, &M, &S, &D);

    int i, j;
    // 注意：这里不能加等号
    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++) {
            G[i][j].distance = INFI;
            G[i][j].price = INFI;
        
        }
    }

    int v1, v2, dis, p;

    for (i = 0; i < M; i++) {
        scanf("%d %d %d %d", &v1, &v2, &dis, &p);
        G[v1][v2].distance = dis;
        G[v1][v2].price = p; 
    
        G[v2][v1].distance = dis;
        G[v2][v1].price = p;
    }


    int dist[MAX], cost[MAX];
    int vis[MAX] = {0}; // vis[i]表示已经被访问过的

    for (i = 0; i < N; i++) {
        dist[i] = INFI; // 必须要正无穷由于后期需要比较
        cost[i] = INFI; // 同上
    }

    //diji 源点为S，终点为D
    dist[S] = 0;
    cost[S] = 0;
    for (i = 0; i < N; i++) {
        int u = -1, min = INFI;
        for (int j = 0; j < N; j++) {
            if (vis[j] == 0 && dist[j] < min) {
                 min = dist[j];
                 u = j;
            }
        }
        if (u == -1) break;
        vis[u] = 1;
        
        for (int w = 0; w < N; w++) {
            if (G[u][w].distance != INFI && vis[w] == 0) {
                if (dist[u] + G[u][w].distance < dist[w]) {
                    dist[w] = dist[u] + G[u][w].distance;
                    cost[w] = cost[u] + G[u][w].price;
                } else if (dist[u] + G[u][w].distance == dist[w] && cost[w] > cost[u] + G[u][w].price) {
                    cost[w] = cost[u] + G[u][w].price;
                }
            }
        }
    }
    
    printf("%d %d\n", dist[D], cost[D]);

    return 0;
}