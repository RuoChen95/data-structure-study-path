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

void PercDown( ElementType A[], int p, int N );
int main(void) {
    int N;
    int A[MaxNumber] = {0};
    scanf("%d", &N);

    getArray(A, N);

    Heap_Sort(A, N);

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
    int i = 0;
    int p = N - 1;
    int flag;

    for (p = N - 1; p >=0; p--) {
        flag = 0;
        for (i = 0; i < p; i++) {
            if (A[i] > A[i + 1]) {
                Switch(&A[i], &A[i+1]);
                flag = 1;
            }
        }
        if (flag == 0) {
            break;
        }
    }
}

// index为0默认已经在手上了
void insert_Sort( ElementType A[], int N) {
    int p, temp, i;
    for (p = 1; p < N; p++) {
        temp = A[p];
        for (i = p; i >= 1 && temp < A[i - 1]; i--) {
            A[i] = A[i -1];
        }
        A[i]= temp;
    }
}







void shell_Sort( ElementType A[], int N) {
    int D;
    int p, temp, i;
    for (D = N/2; D >= 1; D = D/2) { // 原始的增量序列
        for (p = D; p < N; p++) { // 插入排序
            temp = A[p];
            for (i = p; i >= D && temp < A[i - D]; i = i - D) {
                A[i] = A[i -D];
            }
            A[i]= temp;
        }
    }
}





void Heap_Sort_Simple( ElementType A[], int N) {
    priority_queue <ElementType, vector<ElementType>, greater<ElementType> > q;
    int i;
    ElementType temp[MaxNumber];
    for (i = 0; i < N; i++) {
        q.push(A[i]);
    }
    for (i = 0; i < N; i++) {
        temp[i]= q.top();
        q.pop();
    }
    for (i = 0 ; i < N; i++) {
        A[i] = temp[i];
    }
}
void Heap_Sort( ElementType A[], int N )
{
    int i;
    for ( i=N/2; i>=0; i-- ) {
        PercDown( A, i, N );
    }

    for ( i=N-1; i>0; i-- ) {
        Switch( &A[0], &A[i] );
        PercDown( A, 0, i );
    }
}
void PercDown( ElementType A[], int p, int N )
{
    int parent, child;
    ElementType X = A[p];
    for (parent = p; (parent*2+1)<N; parent = child) {
        child = parent * 2 + 1;
        if ((A[child] < A[child+1]) && (child != N - 1)) {
            child++;
        }
        if (X >= A[child]) break;
        else A[parent] = A[child];
    }
    A[parent] = X;
}


// 标准的函数接口
void Merge_Sort(ElementType A[], int N) {
    ElementType *TmpA;
    TmpA = (ElementType *)malloc(N*sizeof(ElementType));

    if ( TmpA != NULL ) {
        MSort( A, TmpA, 0, N-1 );
        free( TmpA );
    }
    else printf( "space is not enough" );
}
// 递归算法策略
void MSort( ElementType A[], ElementType TmpA[], int L, int RightEnd ) {
    int Center;
    if (L<RightEnd) {
        Center = (L + RightEnd) / 2;
        MSort(A, TmpA, L, Center); // 左边排好序
        MSort(A, TmpA, Center+1, RightEnd); // 右边排好序
        Merge(A, TmpA, L, Center+1, RightEnd); // 进行核心的合并
    }
}
/*

类似于线性表的合并，左右两个序列都是有序的

A: 原始待排序列
temp：临时数组
L: 左边起始位置
R: 右边起始位置
RightEnd: 右边终点位置
*/
void Merge (ElementType A[], ElementType TmpA[], int L, int R, int RightEnd) {
    int LeftEnd = R - 1;
    int Tmp = L;
    int Start = L; // 开始存放的位置（左边起始位置）
    int NumElements = RightEnd - L + 1; // 存在的元素数目
    // 时间复杂度为O(N)
    while (L <= LeftEnd && R <= RightEnd) {
        if (A[L] <= A[R]) {
            TmpA[Tmp++] = A[L++]; // 先赋值，后自加1
        }
        else {
            TmpA[Tmp++] = A[R++];
        }
    }
    while (L <= LeftEnd) {
        TmpA[Tmp++] = A[L++];
    }
    while (R <= RightEnd) {
        TmpA[Tmp++] = A[R++];
    }
    int i;
    for (i = 0; i < NumElements; i++, Start++) {
        A[Start] = TmpA[Start];
    }
}