#include <stdio.h>

// clock_t start, stop;
// double duration;

int MaxSum ( int a[], int n) {
    int thisSum = 0;
    int maxSum = 0;
    for (int i = 0; i < n; i++) {
        thisSum += a[i];

        if (thisSum > maxSum) {
            maxSum = thisSum;
        } else if (thisSum < 0) {
            thisSum = 0;
        }
    }

    return maxSum;
}

int main(int argc, char const *argv[])
{
    /* code */
    int length = 0;
    scanf("%d", &length);

    int A[length];
    for (int i=0; i<length; i++) {
        scanf("%d", &A[i]);
    }

    printf("%d\n", MaxSum(A, length));

    return 0;
}