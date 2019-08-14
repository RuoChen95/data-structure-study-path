#include <stdio.h>
#include <stdbool.h>
#include <queue>
#include <stdlib.h> 
#include <time.h> 

using namespace std;

#define MaxNumber 100000
#define MaxTableNumber 51
#define ElementType int

void Bucket_Sort(ElementType A[], int N);

int main(void) {
	int N;
	int A[MaxNumber] = {0};
    scanf("%d", &N);
    
    Bucket_Sort(A, N);
    
    return 0;
}

void Bucket_Sort(ElementType A[], int N)
{
	int count[MaxTableNumber] = {0};
	int i;
	for (i=0;i<N;i++){
		scanf("%d", &A[i]);
		count[A[i]]++;
	}
	for (i=0;i<MaxTableNumber;i++){
		if(count[i]) {
			printf("%d:%d\n", i, count[i]);
		}
	}
}








