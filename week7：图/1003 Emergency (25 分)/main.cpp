#include "stdafx.h"
#pragma warning(disable:4996)
#include <iostream>
using namespace std;

#define INFI 1000000
#define MAX 500
struct node {
    int L;
}citys[500][500];

int main(void) {
    int N, M, C1, C2;
    scanf("%d %d %d %d", &N, &M, &C1, &C2);

    int rescueTeam[MAX];
    int i, j;

    for (i = 0; i < N; i++) {
        scanf("%d", &rescueTeam[i]);
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            citys[i][j].L = INFI;
        }
    }

    // from picture
    int c1, c2, L;


    for (i = 0; i < M; i++) {
        scanf("%d %d %d", &c1, &c2, &L);
        citys[c1][c2].L = L;
        citys[c2][c1].L = L;
    }

    // diji
    int dist[MAX];
    int num[MAX];
    int w[MAX];
    for ( i = 0; i < N; i++) {
        dist[i] = INFI;
        num[i] = 0; // 最短路径长度
        w[i] = 0; // 最大点权之和
    }
    dist[C1] = 0;
    num[C1] = 1;
    w[C1] = rescueTeam[C1];
    int visit[MAX] = {0};
    int path[MAX];


    int flag = 0;
    for (i = 0; i < N; i++) {
        int u = -1;
        int min = INFI;
        for (j = 0; j < N; j++) {
            if (visit[j] == 0 && dist[j] < min) {
                u = j;
                min = dist[j];
            }
        }
        if (u == -1) {
            flag = 1;
            break;
        }
        visit[u] = 1;
        for (j = 0; j < N; j++) {
            if (visit[j] == 0 && citys[u][j].L != INFI) {
                // ???
                if (dist[j] > dist[u] + citys[u][j].L) {
                    dist[j] = dist[u] + citys[u][j].L;
                    num[j] = num[u];
                    w[j] = w[u] + rescueTeam[j];
                } else if (dist[j] == dist[u] + citys[u][j].L) {
                    num[j] += num[u];

                    if (w[u] + rescueTeam[j] > w[j]) {
                        w[j] = w[u] + rescueTeam[j];
                    }
                }
            }
        }
    }

    printf("%d %d",num[C2], w[C2]);

    return 0;
}