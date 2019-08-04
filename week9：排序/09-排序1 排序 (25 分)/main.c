#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MaxNumber 100000
#define ElementType int

void getArray (ElementType A[], int N);
void showArray (ElementType A[], int N);
void bubble_Sort( ElementType A[], int N);
void insert_Sort( ElementType A[], int N);
void Switch (int * a, int * b);
int main(void) {
    int N;
    int A[MaxNumber] = {0};
    scanf("%d", &N);

    getArray(A, N);

    insert_Sort( A, N);

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
        for (i = P; i > 0 && A[i-1] > Tmp; i--) {
            A[i] = A[i-1];
        }
        A[i] = Tmp;
    }
}