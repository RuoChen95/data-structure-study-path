#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode * Tree;
struct TreeNode {
    int v;
    Tree Left, Right;
    int flag;
};
Tree MakeTree(int N);
Tree NewNode(int V);
Tree Insert(Tree T, int V);
int check(Tree T, int V); //*
int Judge(Tree T, int N); //*
void ResetT( Tree T);
void FreeTree(Tree T);
int main(void) {
    int N, L, i; // 树的长度；比较的次数；计数符号
    Tree T;

    scanf("%d", &N);
    while(N) { // 读到0结尾
        scanf("%d", &L);
        // 根据第一行序列建树
        T = MakeTree(N);
        // 对于后续的每一行进行判断
        for (i = 0; i < L; i++ ){
            if (Judge(T, N)) printf("Yes\n"); // 为1：同一颗
            else printf("No\n"); // 为0：不是同一颗
            ResetT(T);
        }
        FreeTree(T); // 清空树
        scanf("%d", &N);
    }
    return 0;
}
Tree MakeTree(int N) {
    Tree T; // Root
    int i, V; // 计数符号，节点index

    scanf("%d", &V);
    // 新建根节点
    T = NewNode(V);
    for (i = 1; i < N; i++) {
        scanf("%d", &V);
        // 在T这个根节点处插入V
        // 数据源保证为二叉树
        T = Insert(T, V);
    }
    return T;
}
Tree Insert(Tree T, int V) {
    // 如果节点不存在则新建
    if (!T) T = NewNode(V);
    else {
        if (V>T->v) {
            T->Right = Insert(T->Right, V); // 如果比根节点大则放在右边
        } else  {
            T->Left = Insert(T->Left, V); // 否则放在左边
        }
    }
    return T; // 返回这个节点
}
Tree NewNode(int V) {
    Tree T = (Tree)malloc(sizeof(struct TreeNode));
    T->v = V;
    T->Left = T->Right = NULL; // 一开始为Null
    T->flag = 0;
    return T;
}
int Judge(Tree T, int N) {
    int i, V, flag = 0;
    scanf("%d", &V);
    if (V!=T->v) {
        flag = 1;
    }else {
        T->flag = 1;
    }

    for (i = 1; i < N; i++) {
        scanf("%d", &V);
        if (!check(T, V)) flag = 1;
    }
    if (flag) return 0; // flag为1：不是同一颗
    return 1; // flag为0：是同一颗
}
int check(Tree T, int V) {
    if (T->flag) { // 这个节点已经检查过的话
        if (V<T->v) return check(T->Left, V);
        else if (V>T->v) return check(T->Right, V);
        else return 0;
    } else { // 没有检查过的话
        if (V==T->v) {
            T->flag = 1;
            return 1;
        } else {
            return 0;
        }
    }
}
void ResetT( Tree T ) {
    if (T->Left) ResetT(T->Left);
    if (T->Right) ResetT(T->Right);
    T->flag = 0;
}
void FreeTree(Tree T) {
    if (T->Left) FreeTree(T->Left);
    if (T->Right) FreeTree(T->Right);
    free(T);
}