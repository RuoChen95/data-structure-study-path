#include <stdio.h>
#include <stdlib.h>

#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1

#include "main.h"

struct TreeNode {
    ElementType Element;
    Tree Left;
    Tree Right;
} T1[MaxTree];

Tree BuildTree(struct TreeNode T[]);
int Leafs(Tree R1);

int main(void) {
    Tree R1;

    R1 = BuildTree(T1);

    Isomorphic(R1);
    return 0;
}
Tree BuildTree(struct TreeNode T[]) {
    int N, i, Root = Null;
    char cl, cr;
    int check[MaxTree];
    scanf("%d", &N);
    if (N) {
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
    }
    return Root;
}
int Leafs(Tree R1) {
    Queue Q; Tree T;
    int flag = 0; // 为了输出 4_1_5
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