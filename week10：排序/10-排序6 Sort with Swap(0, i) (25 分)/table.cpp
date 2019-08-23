#include <stdio.h>
#include <stdbool.h>
#include <queue>
#include <stdlib.h> 
#include <time.h> 

using namespace std;

#define MaxNumber 100000
#define ElementType int

void getArray (ElementType A[], int N);

void showArray (ElementType A[], int N, int table[]);

void Swap (int * A, int * B);

void insert_Sort( ElementType A[], int N, int table[]);

void setTable ( int table[], int N);

void physicalSwap (ElementType A[], int N);

void showTable (int table[], int N);

// 表排序 
int main(void) {
    int N;
    int A[MaxNumber] = {0};
    int table[MaxNumber] = {0};
    int AFlag[MaxNumber] = {0}; // don't change the A array 存储元素是否被访问过 
    
    scanf("%d", &N);

    getArray(A, N);
    setTable(table, N);

    insert_Sort(A, N, table);

	// showTable(table, N);
    
    // showArray(A, N, table);
    
	int i, nextIndex;
	int hasZero = 0; // loop including 0 or not
	int totalLength = 0; // loop length 
	int result = 0; // result
	for (i = 0; i < N; i++){
		AFlag[i] = A[i];
	}
	
	// 基本思路: 计算含0的多元环以及不含0的多元环的长度之和 
	for (i = 0; i < N; i++){
		if (i != table[i] && AFlag[i] != -1){
			nextIndex = i;
			while (AFlag[nextIndex] != -1){
				if (AFlag[nextIndex] == 0){
					hasZero = 1;
				}
				AFlag[nextIndex] = -1;
				totalLength++;
				nextIndex = table[nextIndex];
			}
			// printf("%d\n", totalLength);
		}
		if (totalLength != 0){
			if (hasZero == 0) {
				result+=totalLength + 1; // not include 0	
			} else {
				result+=totalLength - 1; // include 0
			}
		}
		totalLength = 0;
		hasZero = 0;
	}
	printf("%d\n", result);
	
    return 0;
}

void getArray (ElementType A[], int N) {
    int i;
    for (i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
}
void showArray (ElementType A[], int N, int table[]) {
    int i;
    printf("%d", A[table[0]]);
    for (i = 1; i < N; i++) {
        printf(" %d", A[table[i]]);
    }
    printf("\n");
}
void showTable (int table[], int N){
	int i;
    printf("%d", table[0]);
    for (i = 1; i < N; i++) {
        printf(" %d", table[i]);
    }
    printf("\n");
}
void Swap (int * a, int * b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 使用插入排序作为演示 假设第一张牌在手里 
void insert_Sort( ElementType A[], int N, int table[]) {
    int p, temp, i, temp2;
    for (p = 1; p < N; p++) {
        temp = A[table[p]];
        temp2 = table[p];
        for (i = p; i >= 1 && temp < A[table[i - 1]]; i--) { // 如果后一个比前一个要小 
            table[i] = table[i-1]; // 进行table的交换而不是A的交换 
        }
        table[i] = temp2; // 注意之前i--了 
    }
}

// 指针数组的初始化 
void setTable ( int table[], int N){
	int i;
	for (i = 0;i<N;i++) {
		table[i] = i;
	}
	 
}

void physicalSwap (ElementType A[], int N) {
	// TODO
}
