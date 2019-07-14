#include <stdio.h>
#include <stdlib.h>

#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1

struct TreeNode {
    ElementType Element; // 具体元素内容
    Tree Left;
    Tree Right;
} T1[MaxTree], T2[MaxTree]; // 通过数组来建立树，提示：非负整数N (≤10)

Tree BuildTree(struct TreeNode T[]); // 建树
int Isomorphic(Tree R1, Tree R2); // 比较

int main(void) {
    Tree R1, R2; // 根节点

    R1 = BuildTree(T1); // 返回根节点
    R2 = BuildTree(T2); // 返回根节点

    if (Isomorphic(R1, R2) == 1) {
        printf("Yes");
    } else {
        printf("No");
    }

    return 0;
}
Tree BuildTree(struct TreeNode T[]) {
    int N, i, Root = Null; // N：数量，i：计数符号（节点编号），Root根节点
    char cl, cr; // 左节点编号，右节点编号
    int check[MaxTree]; // 确认头节点的index
    scanf("%d", &N);
    if (N) { // 如果N大雨0的话
        for (i = 0; i < N; i++) {
            check[i] = 0;
        }
        for (i = 0; i < N; i++) { // 节点从0到N-1编号
            scanf("\n%c %c %c", &T[i].Element, &cl, &cr);
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
            if (!check[i]) break; // 如果这个i为0的话
        Root = i;
    }
    return Root;
}
int Isomorphic(Tree R1, Tree R2) {
    if (R1 == Null && R2 == Null) {
        return 1;
    }
    if (R1 != Null && R2 == Null) {
        return 0;
    }
    if (R2 != Null && R1 == Null) {
        return 0;
    }
    if (T1[R1].Element != T2[R2].Element) { // 对应index的元素不同的话，非同构
        return 0;
    }
    if (T1[R1].Left == Null && T2[R2].Left == Null) { // 如果Left都为空的话，比较Right
        return Isomorphic(T1[R1].Right, T2[R2].Right);
    }
    if (T1[R1].Left != Null && T2[R2].Left != Null) { // 如果Left都非空的话
        if ((T1[T1[R1].Left].Element == T2[T2[R2].Left].Element)) { // 如果Left相同的话
            // 比较同边
            return (Isomorphic(T1[R1].Left, T2[R2].Left) && Isomorphic(T1[R1].Right, T2[R2].Right));
        } else {
            // 比较异边
            return (Isomorphic(T1[R1].Left, T2[R2].Right) && Isomorphic(T1[R1].Right, T2[R2].Left));
        }
    }
    if (T1[R1].Left != Null && T2[R2].Left == Null) {
        return Isomorphic(T1[R1].Left, T2[R2].Right);
    }
    if (T1[R1].Left == Null && T2[R2].Left != Null) {
        return Isomorphic(T1[R1].Right, T2[R2].Left);
    }
}