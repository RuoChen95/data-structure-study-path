#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <queue>
#include <stdlib.h>

using namespace std;

#define MaxNumber 100000
#define ElementType int

void getArray (ElementType A[], int N);
void showArray (ElementType A[], int N);
void bubble_Sort( ElementType A[], int N);
void insert_Sort( ElementType A[], int N);
void shell_Sort( ElementType A[], int N);
void Heap_Sort_Simple( ElementType A[], int N);
void Heap_Sort( ElementType A[], int N);
void Merge_Sort(ElementType A[], int N);

void Switch (int * a, int * b);
void MSort( ElementType A[], ElementType TmpA[], int L, int RightEnd);
void Merge (ElementType A[], ElementType TmpA[], int L, int R, int RightEnd);
int main(void) {
    int N;
    int A[MaxNumber] = {0};
    scanf("%d", &N);

    getArray(A, N);

    insert_Sort(A, N);

    showArray(A, N);
    return 0;
}

void getArray (ElementType A[], int N) {
    int i;
    for (i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
}
void showArray (ElementType A[], int N) {
    int i;
    printf("%d", A[0]);
    for (i = 1; i < N; i++) {
        printf(" %d", A[i]);
    }
}

void Switch (int * a, int * b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_Sort( ElementType A[], int N) {
    int i;
    int p;
    int flag;
    for (p = N - 1; p > 0; p--) {
        flag = 0;
        for (i = 0; i < p; i++) {
            if (A[i] > A[i+1]) {
                Switch(&A[i], &A[i+1]);
                flag = 1;
            }
        }
        if (flag == 0) {
            break;
        }
    }
}

void insert_Sort( ElementType A[], int N) {
    int P, Tmp, i;
    for (P = 1; P < N; P++) {
        Tmp = A[P];
        for (i = P; i >= 1 && A[i-1] > Tmp; i--) {
            A[i] = A[i-1];
        }
        A[i] = Tmp;
    }
}

void shell_Sort( ElementType A[], int N) {
    int P, Tmp, i, D;
    for ( D = N/2; D > 0; D = D/2) {
        for (P = D; P < N; P++) {
            Tmp = A[P];
            for (i = P; i >= D && A[i-D] > Tmp; i = i-D) {
                A[i] = A[i-D];
            }
            A[i] = Tmp;
        }
    }
}

void Heap_Sort_Simple( ElementType A[], int N) {
    priority_queue<ElementType, vector<ElementType>, greater<ElementType>> q;
    int i;
    ElementType TmpA[MaxNumber];
    for (i = 0; i < N; i++) {
        q.push(A[i]);
    }

    for (i = 0; i < N; i++) {
        TmpA[i] = q.top();
        q.pop();
    }

    for (i = 0; i < N; i++) {
        A[i] = TmpA[i];
    }
}
void PercDown( ElementType A[], int p, int N )
{ /* 改编代码4.24的PercDown( MaxHeap H, int p )    */
    /* 将N个元素的数组中以A[p]为根的子堆调整为最大堆 */
    int Parent, Child;
    ElementType X;

    X = A[p]; /* 取出根结点存放的值 */
    for( Parent=p; (Parent*2+1)<N; Parent=Child ) {
        Child = Parent * 2 + 1;
        if( (Child!=N-1) && (A[Child]<A[Child+1]) )
            Child++;  /* Child指向左右子结点的较大者 */
        if( X >= A[Child] ) break; /* 找到了合适位置 */
        else  /* 下滤X */
            A[Parent] = A[Child];
    }
    A[Parent] = X;
}

void Heap_Sort( ElementType A[], int N )
{ /* 堆排序 */
    int i;

    for ( i=N/2-1; i>=0; i-- )/* 建立最大堆 */
        PercDown( A, i, N );

    for ( i=N-1; i>0; i-- ) {
        /* 删除最大堆顶 */
        Switch( &A[0], &A[i] ); /* 见代码7.1 */
        PercDown( A, 0, i );
    }
}

void Merge_Sort(ElementType A[], int N) {
    ElementType *TmpA;
    TmpA = (ElementType *)malloc(N*sizeof(ElementType));

    if ( TmpA != NULL ) {
        MSort( A, TmpA, 0, N-1 );
        free( TmpA );
    }
    else printf( "空间不足" );
}

void MSort( ElementType A[], ElementType TmpA[], int L, int RightEnd) {
    int Center;
    if (L<RightEnd) {
        Center = (L + RightEnd) / 2;
        MSort(A, TmpA, L, Center);
        MSort(A, TmpA, Center+1, RightEnd);
        Merge(A, TmpA, L, Center+1, RightEnd);
    }
}

void Merge (ElementType A[], ElementType TmpA[], int L, int R, int RightEnd) {
    int LeftEnd = R - 1;
    int Tmp = L; // 从哪里开始存放
    int NumElements = RightEnd - L + 1; // 元素总个数 N
    while (L <= LeftEnd && R <= RightEnd) {
        if (A[L] <= A[R]) TmpA[Tmp++] = A[L++];
        else    TmpA[Tmp++] = A[R++];
    }
    while (L <= LeftEnd) {
        TmpA[Tmp++] = A[L++];
    }
    while (R <= RightEnd) {
        TmpA[Tmp++] = A[R++];
    }
    int i;
    for (i = 0; i < NumElements; i++, RightEnd--) {
        A[RightEnd] = TmpA[RightEnd];
    }
}