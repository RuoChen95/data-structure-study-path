#include <stdio.h>

int MaxSum ( int a[], int n) {
    int thisSum = 0;
    int maxSum = 0;
    int startIndexFack = 0;
    int startIndexReal = 0;
    int endIndex = 0;
    for (int i = 0; i < n; i++) {
        thisSum += a[i];

        if (thisSum > maxSum) {
            maxSum = thisSum;
            endIndex = i;
            if (startIndexFack <= endIndex) {
                startIndexReal = startIndexFack;
            }
        } else if (thisSum <= 0) {
            thisSum = 0;
            startIndexFack = i+1;
        }
    }
    printf("%d %d %d\n", maxSum, startIndexReal,endIndex);
    return 0;
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

    MaxSum(A, length);

    return 0;
}
