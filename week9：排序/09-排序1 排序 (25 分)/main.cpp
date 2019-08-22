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
void bubble_Sort( ElementType A[], int N);
void insert_Sort( ElementType A[], int N);
void shell_Sort( ElementType A[], int N);
void Heap_Sort_Simple( ElementType A[], int N);
void Heap_Sort( ElementType A[], int N);
void Merge_Sort(ElementType A[], int N);

void Switch (int * a, int * b);
void MSort( ElementType A[], ElementType TmpA[], int L, int RightEnd);
void Merge (ElementType A[], ElementType TmpA[], int L, int R, int RightEnd);

void PercDown( ElementType A[], int p, int N );
int main(void) {
    int N;
    int A[MaxNumber] = {0};
    scanf("%d", &N);

    getArray(A, N);

    Merge_Sort(A, N);

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
    int i = 0;
    int p = N - 1;
    int flag;

    for (p = N - 1; p >=0; p--) {
        flag = 0;
        for (i = 0; i < p; i++) {
            if (A[i] > A[i + 1]) {
                Switch(&A[i], &A[i+1]);
                flag = 1;
            }
        }
        if (flag == 0) {
            break;
        }
    }
}
// indexΪ0Ĭ���Ѿ���������
void insert_Sort( ElementType A[], int N) {
    int p, temp, i;
    for (p = 1; p < N; p++) {
        temp = A[p];
        for (i = p; i >= 1 && temp < A[i - 1]; i--) {
            A[i] = A[i -1];
        }
        A[i]= temp;
    }
}





void shell_Sort( ElementType A[], int N) {
    int D;
    int p, temp, i;
    for (D = N/2; D >= 1; D = D/2) { // ԭʼ����������
        for (p = D; p < N; p++) { // ��������
            temp = A[p];
            for (i = p; i >= D && temp < A[i - D]; i = i - D) {
                A[i] = A[i -D];
            }
            A[i]= temp;
        }
    }
}





void Heap_Sort_Simple( ElementType A[], int N) {
    priority_queue <ElementType, vector<ElementType>, greater<ElementType> > q;
    int i;
    ElementType temp[MaxNumber];
    for (i = 0; i < N; i++) {
        q.push(A[i]);
    }
    for (i = 0; i < N; i++) {
        temp[i]= q.top();
        q.pop();
    }
    for (i = 0 ; i < N; i++) {
        A[i] = temp[i];
    }
}
void Heap_Sort( ElementType A[], int N )
{
    int i;
    for ( i=N/2; i>=0; i-- ) {
        PercDown( A, i, N );
    }

    for ( i=N-1; i>0; i-- ) {
        Switch( &A[0], &A[i] );
        PercDown( A, 0, i );
    }
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


// ��׼�ĺ����ӿ�
void Merge_Sort(ElementType A[], int N) {
    ElementType *TmpA;
    TmpA = (ElementType *)malloc(N*sizeof(ElementType));

    if ( TmpA != NULL ) {
        MSort( A, TmpA, 0, N-1 );
        free( TmpA );
    }
    else printf( "space is not enough" );
}
// �ݹ��㷨����
void MSort( ElementType A[], ElementType TmpA[], int L, int RightEnd ) {
    int Center;
    if (L<RightEnd) {
        Center = (L + RightEnd) / 2;
        MSort(A, TmpA, L, Center); // ����ź���
        MSort(A, TmpA, Center+1, RightEnd); // �ұ��ź���
        Merge(A, TmpA, L, Center+1, RightEnd); // ���к��ĵĺϲ�
    }
}
/*

���������Ա�ĺϲ��������������ж��������

A: ԭʼ��������
temp����ʱ����
L: �����ʼλ��
R: �ұ���ʼλ��
RightEnd: �ұ��յ�λ��
*/
void Merge (ElementType A[], ElementType TmpA[], int L, int R, int RightEnd) {
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
    int i;
    for (i = 0; i < NumElements; i++, Start++) {
        A[Start] = TmpA[Start];
    }
}
