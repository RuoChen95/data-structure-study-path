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

void physicalSwap (ElementType A[], int N)

int main(void) {
    int N;
    int A[MaxNumber] = {0};
    int table[MaxNumber] = {0};
    scanf("%d", &N);

    getArray(A, N);
    setTable(table, N);

    insert_Sort(A, N, table);

    showArray(A, N, table);
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
