#include <stdio.h>

#define MaxNumber 100000
#define ElementType int

void getArray (ElementType A[], int N);

void showArray (ElementType A[], int N, int table[]);

void Swap (int * A, int * B);

void insert_Sort( ElementType A[], int N, int table[]);

void setTable ( int table[], int N);

void showTable (int table[], int N);

// 表排序 
int main(void) {
    int N, i;
    int A[MaxNumber] = {0};
    int table[MaxNumber] = {0}; // 指针数组（详见表排序） 
    int AFlag[MaxNumber] = {0}; // don't change the A array 存储元素是否被访问过 
    
    scanf("%d", &N);

    getArray(A, N);
    
    for (i = 0;i<N;i++) {
		table[A[i]] = i;
	}


	// showTable(table, N);
    
    // showArray(A, N, table);
    
	int nextIndex;
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

