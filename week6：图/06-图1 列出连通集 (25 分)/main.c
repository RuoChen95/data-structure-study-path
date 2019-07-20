//
// Created by Ruochen Xie on 2019-07-20.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 队列定义开始
#define ElementType char
typedef int Position;
struct QNode {
    ElementType *Data;     /* 存储元素的数组 */
    Position Front, Rear;  /* 队列的头、尾指针 */
    int MaxSize;           /* 队列最大容量 */
};
typedef struct QNode *Queue;

Queue CreateQueue( int MaxSize )
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
    Q->Front = Q->Rear = 0;
    Q->MaxSize = MaxSize;
    return Q;
}

bool IsFull( Queue Q )
{
    return ((Q->Rear+1)%Q->MaxSize == Q->Front);
}

bool AddQ( Queue Q, ElementType X )
{
    if ( IsFull(Q) ) {
        printf("队列满");
        return false;
    }
    else {
        Q->Rear = (Q->Rear+1)%Q->MaxSize;
        Q->Data[Q->Rear] = X;
        return true;
    }
}

bool IsEmpty( Queue Q )
{
    return (Q->Front == Q->Rear);
}

ElementType DeleteQ( Queue Q )
{
    if ( IsEmpty(Q) ) {
        printf("队列空");
        return false;
    }
    else  {
        Q->Front =(Q->Front+1)%Q->MaxSize;
        return  Q->Data[Q->Front];
    }
}
// 队列定义结束


void ListComponentsDFS( int N );
void ListComponentsBFS( int N, Queue Q);
void DFS( int v, int N );
void BFS( int v, int N, Queue Q);

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

    Queue Q;
    Q = CreateQueue(MaxTree);
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

void ListComponentsBFS( int N, Queue Q) {
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

void BFS( int v, int N, Queue Q) {
    visited[v] = 1;
    int i;

    AddQ(Q, v);
    while (!IsEmpty(Q)) {
        v = DeleteQ(Q);
        for (i = 0; i < N; i++) {
            if (visited[i] == 0) {
                // * 如果i是v的相邻节点
                if (G[v][i] == 1) {
                    visited[i] = 1;
                    printf("%d ", i);
                    AddQ(Q, i);
                }
            }
        }
    }
}