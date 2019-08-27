#include <stdio.h>
#include <queue>

using namespace std;

void ListComponentsDFS( int N );
void ListComponentsBFS( int N, queue<int> Q);
void DFS( int v, int N );
void BFS( int v, int N, queue<int> Q);

static int G[10][10];
int visited[10] = {0};
#define MaxTree 10

int main(void) {

    int N, E, v1, v2, i;

    scanf("%d %d", &N, &E);

    for (i = 0; i < E; i++) {
        scanf("%d %d", &v1, &v2);

        G[v1][v2] = 1;
        G[v2][v1] = 1;
    }


    // DFS
    ListComponentsDFS(N);


    // 初始化
    for (i = 0; i < 10; i++) {
        visited[i] = 0;
    }

    queue<int> Q;
    ListComponentsBFS(N, Q);

    return 0;
}

void ListComponentsDFS( int N ) {
    int i;
    for (i = 0; i < N; i++) {
        if (visited[i] == 0) {
            printf("{ %d ", i);
            DFS(i, N);
            printf("}\n");
        }
    }
}

void ListComponentsBFS( int N, queue<int> Q) {
    int i;
    for (i = 0; i < N; i++) {
        if (visited[i] == 0) {
            printf("{ %d ", i);
            BFS(i, N, Q);
            printf("}\n");
        }
    }
}

void DFS( int v, int N) {
    visited[v] = 1;
    int i;
    for (i = 0; i < N; i++) {
        if (visited[i] == 0) {
            // * 如果i是v的相邻节点
            if (G[v][i] == 1) {
                printf("%d ", i);
                DFS(i, N);
            }
        }
    }
}

void BFS( int v, int N, queue<int> Q) {
    visited[v] = 1;
    int i;

	Q.push(v);
    while (!Q.empty()) {
        v = Q.front();
		Q.pop();
        for (i = 0; i < N; i++) {
            if (visited[i] == 0) {
                // * 如果i是v的相邻节点
                if (G[v][i] == 1) {
                    visited[i] = 1;
                    printf("%d ", i);
                    Q.push(i);
                }
            }
        }
    }
}