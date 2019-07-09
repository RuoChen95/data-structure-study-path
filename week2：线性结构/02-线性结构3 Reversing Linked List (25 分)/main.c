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
Polynomial ReversingLinkedList (Polynomial head, int K);
int NeedReverse (Polynomial head, int K);

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
    P = ReversingLinkedList (P, K);


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
    while (P) {
        if (P->link != NULL) {
            printf("%05d %d %05d\n", P->Address, P->Data, P->link->Address);
        } else {
            printf("%05d %d %d", P->Address, P->Data, -1);
        }
        P=P->link;
    }
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

int NeedReverse (Polynomial head, int K) {
    int i;
    if (head == NULL) {
        return 0;
    }
    for ( i = 1; head->link != NULL; head = head->link) {
        i++;
        if ( i == K ) return 1; // 还有K个节点，逆转
    }

    return 0;
}

Polynomial ReversingLinkedList (Polynomial head, int K) {
    Polynomial UnreversedHead = head; // 未逆转的链表的第一个节点
    Polynomial ListHead; // 整个表的第一个节点
    Polynomial TempTail; // 临时表尾部，用于连接下一段逆转的链表

    if ( NeedReverse(UnreversedHead, K) ) {
        ListHead = Reverse( UnreversedHead, K);
        TempTail = UnreversedHead;
        UnreversedHead = TempTail->link;
    } else {
        return head;
    }

    while (NeedReverse( UnreversedHead, K)) {
        TempTail->link = Reverse( UnreversedHead, K);
        TempTail = UnreversedHead;
        UnreversedHead = TempTail->link;
    }
    return ListHead;
}