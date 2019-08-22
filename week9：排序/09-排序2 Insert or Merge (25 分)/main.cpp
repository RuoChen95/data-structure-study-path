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





// indexΪ0Ĭ���Ѿ���������
// ���� 
void one_step_insert_Sort( ElementType A[], int N, int p) {
    int temp, i;

    temp = A[p];
    for (i = p; i >= 1 && temp < A[i - 1]; i--) {
        A[i] = A[i -1];
    }
    A[i]= temp;
}



// ��׼�ĺ����ӿ�
// ����: ���������г��� 
void one_step_Merge_Sort(ElementType A[], int N, int L) {
    ElementType *TmpA;
    TmpA = (ElementType *)malloc(N*sizeof(ElementType));
    if ( TmpA != NULL ) {
    	MSort_new(A, TmpA, N, 1); // ��A��ֵ�ŵ�TmpA��
        MSort_new(TmpA, A, N, L);
        free( TmpA );
    }
    else printf( "space is not enough" );
}
// �ǵݹ��㷨����:
// �����ڵ����������н��й鲢

// length = ��ǰ�������еĳ��� or ��ǰ�鲢�εĳ��� 

void MSort_new( ElementType A[], ElementType TmpA[], int N, int length ) {
    // �ȴ���֮ǰ��֤�ɶԵ�i
    int i;
    for ( i = 0; i < N - 2 * length; i += 2 * length) {
        Merge1(A, TmpA, i, i + length, i + 2 * length - 1);
    }
    // ����һ�����е����
    if (i + length < N) {
        Merge1(A, TmpA, i, i + length, N - 1);
    } else {
        // ֻ��һ�����е����
        int j;
        for (j = i; j < N; j++) {
            TmpA[j] = A[j];
        }
    }
}
void Merge1 (ElementType A[], ElementType TmpA[], int L, int R, int RightEnd) {
    int LeftEnd = R - 1;
    int Tmp = L;
    int Start = L; // ��ʼ��ŵ�λ�ã������ʼλ�ã�
    int NumElements = RightEnd - L + 1; // ���ڵ�Ԫ����Ŀ
    // ʱ�临�Ӷ�ΪO(N)
    while (L <= LeftEnd && R <= RightEnd) {
        if (A[L] <= A[R]) {
            TmpA[Tmp++] = A[L++]; // �ȸ�ֵ�����Լ�1
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

// �ж��Ƿ�Ϊ�������� 
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
