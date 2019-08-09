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
void Swap (int * A, int * B);

void quick_sort(ElementType A[], int N);
void Quicksort(ElementType A[], int Left, int Right);
ElementType Median3(ElementType A[], int Left, int Right);
int main(void) {
    int N;
    int A[MaxNumber] = {0};
    scanf("%d", &N);

    getArray(A, N);

    quick_sort(A, N);

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
void Swap (int * A, int * B) {
    int temp = *A;
    *A = *B;
    *B = temp;
}


void quick_sort(ElementType A[], int N) {
    Quicksort(A, 0, N - 1);
}

void Quicksort(ElementType A[], int Left, int Right) {
    int Pivot = Median3(A, Left, Right);
    int i = Left + 1;
    int j = Right - 2;

    while (i < j) {
        while (A[i] < Pivot) {
            i++;
        }
        while (A[j] > Pivot) {
            j--;
        }
        if (i < j) {
            Swap(&A[i], &A[j]);
        } else {
            break;
        }
    }
    Swap(&A[i], &A[Right-1]);

    Quicksort(A, Left, i-1);
    Quicksort(A, i+1, Right);
}

ElementType Median3(ElementType A[], int Left, int Right) {
    int Center = (Left + Right)/2;
    if (A[Left] > A[Center]) {
        Swap(&A[Left], &A[Center]);
    }
    if (A[Right] < A[Left]) {
        Swap(&A[Right], &A[Left]);
    }
    if (A[Center] > A[Right]) {
        Swap(&A[Center], &A[Right]);
    }

    //return A[Center];
    Swap(&A[Center], &A[Right-1]);
    return A[Right-1];
}
