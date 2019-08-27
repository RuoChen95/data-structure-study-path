#include <stdio.h>
#include <queue>

using namespace std;



void SDS( int N, queue<int> Q);
double BFS( int v, int N, queue<int> Q);

static int G[1001][33003];
int visited[1001] = {0};

int main(void) {

    int N, E, v1, v2, i;

    scanf("%d %d", &N, &E);

    for (i = 1; i <= E; i++) {
        scanf("%d %d", &v1, &v2);

        G[v1][v2] = 1;
        G[v2][v1] = 1;
    }


    queue<int> Q;
    SDS(N, Q);

    return 0;
}


void SDS( int N, queue<int> Q) {
    int i;
	double count;
	int j;
    for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			visited[j] = 0;
		}
        count = BFS(i, N, Q);
        printf("%d: %.2f%%\n", i, count/N * 100);
    }
}



double BFS( int v, int N, queue<int> Q) {
    visited[v] = 1; double count = 1.0;
	int level = 0; // 
	int last = v; // 当前level的最后一个元素的index
	int tail; // 下一层level的最后一个元素的index
	Q.push(v);
	int i;
    while (!Q.empty()) {
        v = Q.front();
		Q.pop();
        for (i = 1; i <= N; i++) {
            if (visited[i] == 0) {
                // * 如果i是v的相邻节点
                if (G[v][i] == 1) {
                    visited[i] = 1;
                    Q.push(i);
					count++;
					tail = i;
                }
            }
        }
		if (v == last){
				last = tail;
				level++;
			}
		if (level == 6) break;
    }
	return count;
}