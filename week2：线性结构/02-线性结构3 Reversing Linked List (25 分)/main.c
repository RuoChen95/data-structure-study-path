//
// Created by Ruochen Xie on 2019-07-08.
//

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
Polynomial ReversingLinkedList( Polynomial head , int K );

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

    // 反转
    P = ReversingLinkedList(P, K);

    // 输出
    Print(P);

    return 0;
}

void Attach(int Address, int Data, int Next, Polynomial *pRear) {
    Polynomial P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->Address = Address; P->Data = Data; P->Next = Next;
    (*pRear)->link = P;
    *pRear = (*pRear)->link;
}

void Print(Polynomial P) {
    Polynomial PNext;
    while (P) {
        if (P->link != NULL) {
            printf("%05d %d %05d", P->Address, P->Data, P->link->Address);
        } else {
            printf("%05d %d %d", P->Address, P->Data, -1);
        }
        P=P->link;
        if (P) {
            printf("\n");
        }
    }
}

// *
Polynomial Reverse (Polynomial head, int K) {
    int count = 1;
    Polynomial new = head->link;
    Polynomial old = new->link;
    Polynomial temp;
    while (count < K) {
        temp = old->link;
        old->link = new;
        new = old;
        old = temp;
        count++;
    }
    head->link->link = old;
    return new;
}

// **
Polynomial ReversingLinkedList( Polynomial head , int K ) {
    // 循环：判断是否需要reverse

    // 是：reverse一遍
    // 修改head到old处

    // 否：跳出
}