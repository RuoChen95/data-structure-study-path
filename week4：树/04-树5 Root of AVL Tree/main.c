#include <stdio.h>
#include <stdlib.h>

#define MaxTree 20
#define ElementType char
#define Tree int
#define Null -1

struct TreeNode {
    ElementType Element;
    Tree Left;
    Tree Right;
} T1[MaxTree];

Tree BuildAVLTree(struct TreeNode T[]);

int main(void) {
    Tree R1;

    R1 = BuildAVLTree(T1);

    printf("%d\n", R1);

    return 0;
}

Tree BuildAVLTree(struct TreeNode T[]) {
    int N, i, Root = Null;
    char cl, cr;
    scanf("%d", &N);
    if (N) {
        for (i = 0; i < N; i++) {
            T[i].Element = (char)i;
            scanf("\n%c %c", &cl, &cr);
            if (cl != '-') {
                T[i].Left = cl - '0';
            } else T[i].Left = Null;

            if (cr != '-') {
                T[i].Right = cr - '0';
            } else T[i].Right = Null;
        }
        Root = i;
    }
    return Root;
}