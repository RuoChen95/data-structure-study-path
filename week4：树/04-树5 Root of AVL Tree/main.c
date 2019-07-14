#include <stdio.h>
#include <stdlib.h> // malloc

typedef struct AVLNode *Position;
typedef Position AVLTree; /* AVL树类型 */
typedef int ElementType;
struct AVLNode{
    ElementType Data; /* 结点数据 */
    AVLTree Left;     /* 指向左子树 */
    AVLTree Right;    /* 指向右子树 */
    int Height;       /* 树高 */
};

AVLTree Insert( AVLTree T, ElementType X );
AVLTree SingleLeftRotation ( AVLTree A );
AVLTree DoubleLeftRightRotation ( AVLTree A );
AVLTree SingleRightRotation ( AVLTree A );
AVLTree DoubleRightLeftRotation ( AVLTree A );
int Max ( int a, int b );
int GetHeight( AVLTree A );

int main(void) {
    AVLTree T = NULL;
    int n, i, x; // 二叉树的数据数量; 计数; 具体的数据
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &x);
        // 数据源不保证为二叉树
        T = Insert(T, x);
    }

    if (T) {
        printf("%d", T->Data);
    }
    return 0;
}

AVLTree Insert( AVLTree T, ElementType X )
{ /* 将X插入AVL树T中，并且返回调整后的AVL树 */
    if ( !T ) { /* 若插入空树，则新建包含一个结点的树 */
        T = (AVLTree)malloc(sizeof(struct AVLNode));
        T->Data = X;
        T->Height = 0;
        T->Left = T->Right = NULL;
    } /* if (插入空树) 结束 */

    else if ( X < T->Data ) {
        /* 插入T的左子树 */
        T->Left = Insert( T->Left, X);
        /* 如果需要左旋 */
        if ( GetHeight(T->Left)-GetHeight(T->Right) == 2 )
            if ( X < T->Left->Data )
                T = SingleLeftRotation(T);      /* 左单旋 */
            else
                T = DoubleLeftRightRotation(T); /* 左-右双旋 */
    } /* else if (插入左子树) 结束 */

    else if ( X > T->Data ) {
        /* 插入T的右子树 */
        T->Right = Insert( T->Right, X );
        /* 如果需要右旋 */
        if ( GetHeight(T->Left)-GetHeight(T->Right) == -2 )
            if ( X > T->Right->Data )
                T = SingleRightRotation(T);     /* 右单旋 */
            else
                T = DoubleRightLeftRotation(T); /* 右-左双旋 */
    } /* else if (插入右子树) 结束 */

    /* else X == T->Data，无须插入 */

    /* 别忘了更新树高 */
    T->Height = Max( GetHeight(T->Left), GetHeight(T->Right) ) + 1;

    return T;
}

AVLTree SingleLeftRotation ( AVLTree A )
{ /* 注意：A必须有一个左子结点B */
    /* 将A与B做左单旋，更新A与B的高度，返回新的根结点B */

    AVLTree B = A->Left;
    A->Left = B->Right;
    B->Right = A;
    A->Height = Max( GetHeight(A->Left), GetHeight(A->Right) ) + 1;
    B->Height = Max( GetHeight(B->Left), A->Height ) + 1;

    return B;
}

AVLTree DoubleLeftRightRotation ( AVLTree A )
{ /* 注意：A必须有一个左子结点B，且B必须有一个右子结点C */
    /* 将A、B与C做两次单旋，返回新的根结点C */

    /* 将B与C做右单旋，C被返回 */
    A->Left = SingleRightRotation(A->Left);
    /* 将A与C做左单旋，C被返回 */
    return SingleLeftRotation(A);
}

/*************************************/
/* 对称的右单旋与右-左双旋请自己实现 */
/*************************************/

AVLTree SingleRightRotation ( AVLTree A ) {
    AVLTree B = A->Right;
    A->Right = B->Left;
    B->Left = A;
    A->Height = Max( GetHeight(A->Right), GetHeight(A->Left) ) + 1;
    B->Height = Max( GetHeight(B->Right), A->Height ) + 1;

    return B;
}
AVLTree DoubleRightLeftRotation ( AVLTree A ) {
    A->Right = SingleLeftRotation(A->Right);
    /* 将A与C做左单旋，C被返回 */
    return SingleRightRotation(A);

}

int Max ( int a, int b )
{
    return a > b ? a : b;
}

int GetHeight( AVLTree A ) {
    if (!A) {
        return -1;
    } else {
        return A->Height;
    }
}