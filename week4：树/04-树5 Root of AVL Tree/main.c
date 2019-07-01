#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode *AVLTree;
struct AVLNode {
    int Data;
    int Height;
    AVLTree Left;
    AVLTree Right;
};
AVLTree Insert(int X, AVLTree T);
int GetHeight(AVLTree T);
int main(void) {
    AVLTree T = NULL;
    int n;
    scanf("%d", &n);
    while(n--) {
        int x;
        scanf("%d", &x);
        T = Insert(x, T);
    }

    if (T) {
        printf("%d", T->Data);
    }
    return 0;
}
AVLTree Insert(int X, AVLTree T) {
    if (T == NULL) {
        T = (AVLTree)malloc(sizeof(struct AVLNode));
        T->Data = X;
        T->Height = 0;
        T->Left = NULL;
        T->Right = NULL;
    } else if (X < T->Data) {
        // 将X作为左值导入
        T->Left = Insert(X, T->Left);
        if (GetHeight(T->Left) - GetHeight(T->Right) == 2) {
            if (X < T->Left->Data) {
                T = SingleLeft(T);
            } else {
                T = DoubleLeft(T);
            }
        }
    } else if (X > T->Data) {

    }
    // height

    return T;
}
int GetHeight(AVLTree T) {

}