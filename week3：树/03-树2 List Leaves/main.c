#include <stdio.h>
#include <stdlib.h>

#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1

#ifndef MAIN_H
#define MAIN_H
#include <stdbool.h>
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
#endif //MAIN_H


struct TreeNode {
    ElementType Element;
    Tree Left;
    Tree Right;
} T1[MaxTree];

Tree BuildTree(struct TreeNode T[]);
int LevelOrderTraversal(Tree R1);

int main(void) {
    Tree R1;

    R1 = BuildTree(T1);

    LevelOrderTraversal(R1);

    return 0;
}
Tree BuildTree(struct TreeNode T[]) {
    int N, i, Root = Null;
    char cl, cr;
    int check[MaxTree];
    scanf("%d", &N);

    for (i = 0; i < N; i++) {
        check[i] = 0;
    }
    for (i = 0; i < N; i++) {
        T[i].Element = (char)i;
        scanf("\n%c %c", &cl, &cr);
        if (cl == '-') {
            T[i].Left = Null;
        } else {
            T[i].Left = cl - '0';
            check[T[i].Left] = 1;
        }

        if (cr == '-') {
            T[i].Right = Null;
        } else {
            T[i].Right = cr - '0';
            check[T[i].Right] = 1;
        }
    }
    for (i = 0; i < N; i++)
        if (!check[i]) break;
    Root = i;

    return Root;
}

int LevelOrderTraversal(Tree R1) {
    Queue Q; Tree T;
    int flag = 0;
    if (T == Null) {
        return 0;
    }
    Q = CreateQueue(MaxTree);
    AddQ(Q, R1);
    while(!IsEmpty(Q)) {
        T = DeleteQ(Q);
        if (T1[T].Left == Null && T1[T].Right == Null) {
            if (flag != 0) {
                printf(" ");
            }
            printf("%d", T);
            flag = 1;
        }
        if (T1[T].Left != Null) AddQ(Q, T1[T].Left);
        if (T1[T].Right != Null) AddQ(Q, T1[T].Right);
    }
}