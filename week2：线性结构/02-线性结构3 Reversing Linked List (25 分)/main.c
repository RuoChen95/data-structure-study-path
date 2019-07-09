#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100000

struct node {
    int data;
    int next;
} List[MAXSIZE];
// 一个充分大的结构数组来代表其内存空间
// 地址(address)即数组的下标

typedef struct PolyNode * Polynomial;
struct PolyNode {
    int Address;
    int Data;
    int Next;
    Polynomial link; // 指针（结构指针）
};

void Attach(int Address, int Data, int Next,Polynomial *pRear);

Polynomial Reverse (Polynomial head, int K);
void Print(Polynomial PP);

int main(void) {
    int first_address, N, K;
    int address, data, next;
    scanf("%d %d %d", &first_address, &N, &K);

    if (K > N) {
        K = N;
    }
    // 输入
    while (N > 0) {
        scanf("%d %d %d", &address, &data, &next);

        List[address].data = data;
        List[address].next = next;

        N--;
    }

    // 新的链表
    int nextAddress = first_address;
    Polynomial Rear, P, t;
    P = (Polynomial)malloc(sizeof(struct PolyNode)); P->link = NULL; Rear = P;
    do {
        Attach(nextAddress, List[nextAddress].data, List[nextAddress].next, &Rear);
        nextAddress = List[nextAddress].next;
    } while(nextAddress != -1);

    P = P->link;
    // 反转
    P = Reverse(P, K);


    // 输出
    Print(P);

    return 0;
}


Polynomial Reverse (Polynomial head, int K) {
    int cnt = 1;
    Polynomial new = head;
    Polynomial old = new->link;
    Polynomial temp;

    while (cnt < K) {
        temp = old->link;
        old->link = new;

        new = old;
        old = temp;
        cnt++;
    }
    head->link = old;
    return new;
}

void Attach(int Address, int Data, int Next, Polynomial *pRear) {
    Polynomial P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->Address = Address; P->Data = Data; P->Next = Next;
    (*pRear)->link = P;
    *pRear = (*pRear)->link;
}

void Print(Polynomial P) {
    while (P) {
        if (P->link != NULL) {
            printf("%05d %d %05d\n", P->Address, P->Data, P->link->Address);
        } else {
            printf("%05d %d %d", P->Address, P->Data, -1);
        }
        P=P->link;
    }
}