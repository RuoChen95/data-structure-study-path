#include <iostream>
#include <algorithm>

using namespace std;

#define MaxNumber 100
#define ElementType int

void getArray (ElementType A[], int N);
void showArray (ElementType A[], int N);
void one_step_insert_Sort( ElementType A[], int N, int p); 


int distinguish(ElementType A[], ElementType B[], int N);


void one_step_Heap_Sort( ElementType A[], int N, int l );
void PercDown( ElementType A[], int p, int N );
void Switch (int * a, int * b);
int main(void) {
    int N;
    int flag;
    int A[MaxNumber] = {0};
    int B[MaxNumber] = {0};
	int C_Sorted[MaxNumber] = {0};
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
		printf("Heap Sort\n");
		int i;
		int l=0;
		for (i = 0; i < N; i++) {
			C_Sorted[i] = B[i];
		}
		sort(C_Sorted, C_Sorted + N);
		for (i = N - 1; i >=0; i--) {
			if (B[i] == C_Sorted[i]) {
				l++;
			} else {
				break;
			}
		}
		one_step_Heap_Sort(B, N, l);
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



// 判断是否为插入排序 ls 
// 如果为插入排序，至少前两个有序（partially sorted sequence） 而且后面的不变
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
	return i+1;
}


void one_step_Heap_Sort( ElementType A[], int N, int l )
{

    Switch( &A[0], &A[N-l-1] );
    PercDown( A, 0, N-l-1 );
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
void Switch (int * a, int * b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}