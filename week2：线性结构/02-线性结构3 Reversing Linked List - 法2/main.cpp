#include <iostream>

#define MAXSIZE 100000

struct node {
    int index;
    int data;
    int nextIndex;
} List[MAXSIZE];
// 一个充分大的结构数组来代表其内存空间

void showList(int address) {
    node Child = List[address];

    while (Child.nextIndex != -1) {
        printf("%05d %d %05d\n", Child.index, Child.data, Child.nextIndex);

        Child = List[Child.nextIndex];
    }
    printf("%05d %d %d\n", Child.index, Child.data, Child.nextIndex);

}

int main(void) {
    int first_address, N, K;
    int address, data, next;
    scanf_s("%d %d %d", &first_address, &N, &K);

    if (K > N) {
        K = N;
    }
    // 输入
    int i;
    for (i = 0; i < N; i++) {
        scanf_s("%d %d %d", &address, &data, &next);
        List[address].index = address;
        List[address].data = data;
        List[address].nextIndex = next;
    }

    int New =  List[first_address].index;
    int Old = List[New].nextIndex;
    int Temp = List[Old].nextIndex;

    for ( i = 0; i < K-1; i++) {
        List[Old].nextIndex = New; // *

        New = Old;
        Old = Temp;
        Temp = List[Temp].nextIndex;
    }


    List[first_address].nextIndex = Old;
    first_address = New;


    showList(first_address);
    return 0;
}