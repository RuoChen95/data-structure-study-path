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

void Merge_Sort(ElementType A[], int N);
void MSort_new( ElementType A[], ElementType TmpA[], int L, int RightEnd);
void Merge1 (ElementType A[], ElementType TmpA[], int L, int R, int RightEnd);
int main(void) {
    int N;
    int A[MaxNumber] = {0};
    scanf("%d", &N);

    getArray(A, N);

    Merge_Sort(A, N);

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


// 标准的函数接口
void Merge_Sort(ElementType A[], int N) {
    ElementType *TmpA;
    TmpA = (ElementType *)malloc(N*sizeof(ElementType));
    int length = 1;
    if ( TmpA != NULL ) {
        while(length < N) {
            // 保证while循环跳出后，结果存在A内
            MSort_new(A, TmpA, N, length);
            length = length * 2;
            MSort_new(TmpA, A, N, length);
            length = length * 2;
        }
        free( TmpA );
    }
    else printf( "space is not enough" );
}
// 非递归算法策略
// 将相邻的两个子序列进行归并
/*
A: 原始待排序列
temp：临时数组
N: 待排序列长度
length: 当前有序子列的长度
*/
void MSort_new( ElementType A[], ElementType TmpA[], int N, int length ) {
    // 先处理之前保证成对的i
    int i;
    for ( i = 0; i < N - 2 * length; i += 2 * length) {
        Merge1(A, TmpA, i, i + length, i + 2 * length - 1);
    }
    // 大于一个子列的情况
    if (i + length < N) {
        Merge1(A, TmpA, i, i + length, N - 1);
    } else {
        // 只有一个子列的情况
        int j;
        for (j = i; j < N; j++) {
            TmpA[j] = A[j];
        }
    }
}
void Merge1 (ElementType A[], ElementType TmpA[], int L, int R, int RightEnd) {
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
}
