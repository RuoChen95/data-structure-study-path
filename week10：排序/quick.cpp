#include <stdio.h>
#include <stdbool.h>
#include <queue>
#include <stdlib.h> 
#include <time.h> 

using namespace std;

#define MaxNumber 100000
#define ElementType int

void getArray (ElementType A[], int N);
void showArray (ElementType A[], int N);
void Swap (int * A, int * B);

ElementType Median3( ElementType A[], int Left, int Right );
ElementType First( ElementType A[], int Left, int Right);
void Qsort( ElementType A[], int Left, int Right );
void QuickSort( ElementType A[], int N );
void InsertionSort( ElementType A[], int Left, int Right );

void tableSort ( ElementType A[], int N);
int main(void) {
    int N;
    int A[MaxNumber] = {0};
    scanf("%d", &N);

    getArray(A, N);

    QuickSort(A, N);

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
    printf("\n");
}
void Swap (int * a, int * b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}



ElementType Median3( ElementType A[], int Left, int Right )
{
    int Center = (Left + Right)/2;
    if (A[Left] > A[Center]){
        Swap(&A[Left], &A[Center]);
    }
    if (A[Left] > A[Right]) {
        Swap(&A[Left], &A[Right]);
    }

    if (A[Center] > A[Right]) {
        Swap(&A[Center], &A[Right]);
    }

    Swap(&A[Center], &A[Right-1]);

    return A[Right-1];
}

ElementType First( ElementType A[], int Left, int Right)
{
	int Center = Left + 1;
    if (A[Left] > A[Center]){
        Swap(&A[Left], &A[Center]);
    }
    if (A[Left] > A[Right]) {
        Swap(&A[Left], &A[Right]);
    }

    if (A[Center] > A[Right]) {
        Swap(&A[Center], &A[Right]);
    }

    Swap(&A[Center], &A[Right-1]);

    return A[Right-1];
}

ElementType Random( ElementType A[], int Left, int Right)
{
	srand(time(NULL));
	int Center = (rand() % 
           (Right - Left - 1)) + Left + 1;
//    printf("----%d %d %d----\n", Center, Left, Right);
    if (A[Left] > A[Center]){
        Swap(&A[Left], &A[Center]);
    }
    if (A[Left] > A[Right]) {
        Swap(&A[Left], &A[Right]);
    }

    if (A[Center] > A[Right]) {
        Swap(&A[Center], &A[Right]);
    }

    Swap(&A[Center], &A[Right-1]);

    return A[Right-1];
}

void Qsort( ElementType A[], int Left, int Right )
{
    int P, Cutoff = 50, Low, High;

    if ( Cutoff <= Right-Left ) {
		// Median 
		P = Median3(A, Left, Right);
		// First
//		P = First(A, Left, Right);
		// Random
//		P = Random(A, Left, Right);
		
        Low = Left;
        High = Right - 1;
        
        while(1) {
            while(P > A[++Low]){}
            while(P < A[--High]){}
            if (Low < High) {
                Swap(&A[Low], &A[High]);
            } else {
                break;
            }
        }
        Swap(&A[Low], &A[Right-1]);
        Qsort(A, Left, Low-1);
        Qsort(A, Low+1, Right);
    }
    else InsertionSort( A, Left, Right );
}

void QuickSort( ElementType A[], int N )
{
    Qsort( A, 0, N-1 );
}

void InsertionSort( ElementType A[], int Left, int Right ) {
    int p, temp, i;
    for (p = Left+1; p <= Right; p++) {
        temp = A[p];
        for (i = p; i >= Left+1 && temp < A[i - 1]; i--) {
            A[i] = A[i -1];
        }
        A[i]= temp;
    }
}

void tableSort ( ElementType A[], int N)
{
	 int table[MaxNumber] = {0};
	 
	 int i = 0;
	 for (i = 0;i<N;i++) {
	 	table[i] = i;
	 }
	 
}
