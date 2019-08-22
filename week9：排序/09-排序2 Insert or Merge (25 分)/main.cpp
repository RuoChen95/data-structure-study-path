#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <queue>
#include <stdlib.h>

using namespace std;

#define MaxNumber 100
#define ElementType int

void getArray (ElementType A[], int N);
void showArray (ElementType A[], int N);
void one_step_insert_Sort( ElementType A[], int N, int p); 
void one_step_Merge_Sort(ElementType A[], int N, int L);


void Merge_Sort(ElementType A[], int N);
void MSort_new( ElementType A[], ElementType TmpA[], int L, int RightEnd);
void Merge1 (ElementType A[], ElementType TmpA[], int L, int R, int RightEnd);


int distinguish(ElementType A[], ElementType B[], int N);
int getLength(ElementType B[], int N);
int main(void) {
    int N;
    int flag;
    int A[MaxNumber] = {0};
    int B[MaxNumber] = {0};
    scanf("%d", &N);

    getArray(A, N);
    getArray(B, N);

	// distinguish insert or merge sort
	// using insert sort
	flag = distinguish(A, B, N);
	if (flag){
		printf("Insertion Sort\n");
		one_step_insert_Sort(B, N, flag);
		showArray(B, N);
	} else {
		printf("Merge Sort\n");
		int L = getLength(B, N);
		one_step_Merge_Sort(B, N, L);
		showArray(B, N);
	}
	
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





// index为0默认已经在手上了
// 单步 
void one_step_insert_Sort( ElementType A[], int N, int p) {
    int temp, i;

    temp = A[p];
    for (i = p; i >= 1 && temp < A[i - 1]; i--) {
        A[i] = A[i -1];
    }
    A[i]= temp;
}



// 标准的函数接口
// 单步: 输入子序列长度 
void one_step_Merge_Sort(ElementType A[], int N, int L) {
    ElementType *TmpA;
    TmpA = (ElementType *)malloc(N*sizeof(ElementType));
    if ( TmpA != NULL ) {
    	MSort_new(A, TmpA, N, 1); // 将A的值放到TmpA上
        MSort_new(TmpA, A, N, L);
        free( TmpA );
    }
    else printf( "space is not enough" );
}
// 非递归算法策略:
// 将相邻的两个子序列进行归并

// length = 当前有序子列的长度 or 当前归并段的长度 

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

// 判断是否为插入排序 
int distinguish(ElementType A[], ElementType B[], int N){
	int i, j;
	for (i = 0; i < N-1; i++){
		if (B[i] > B[i+1]){
			break;
		}
	}
	for (j = i+1; j < N; j++){
		if (A[j] != B[j]){
			return 0;
		}
	}
	return i;
}

int getLength(ElementType B[], int N){
	int l;
	for (l = 2; l <= N; l *= 2){
		while (l <= N) {
			if (B[l-1] <= B[l]){
				l = l + l*2;
			} else {
				return l;
			}
		}
	}
}
