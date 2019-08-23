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

// ������ 
int main(void) {
    int N;
    int A[MaxNumber] = {0};
    int table[MaxNumber] = {0};
    int AFlag[MaxNumber] = {0}; // don't change the A array �洢Ԫ���Ƿ񱻷��ʹ� 
    
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
	
	// ����˼·: ���㺬0�Ķ�Ԫ���Լ�����0�Ķ�Ԫ���ĳ���֮�� 
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

// ʹ�ò���������Ϊ��ʾ �����һ���������� 
void insert_Sort( ElementType A[], int N, int table[]) {
    int p, temp, i, temp2;
    for (p = 1; p < N; p++) {
        temp = A[table[p]];
        temp2 = table[p];
        for (i = p; i >= 1 && temp < A[table[i - 1]]; i--) { // �����һ����ǰһ��ҪС 
            table[i] = table[i-1]; // ����table�Ľ���������A�Ľ��� 
        }
        table[i] = temp2; // ע��֮ǰi--�� 
    }
}

// ָ������ĳ�ʼ�� 
void setTable ( int table[], int N){
	int i;
	for (i = 0;i<N;i++) {
		table[i] = i;
	}
	 
}

void physicalSwap (ElementType A[], int N) {
	// TODO
}
