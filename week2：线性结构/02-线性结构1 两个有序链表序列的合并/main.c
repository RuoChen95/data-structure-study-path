// 未完成🤚
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

List Merge( List L1, List L2 ) {
    List a, b, x, c;
    x = (List) malloc(sizeof(struct Node));
    a = L1->Next;
    b = L2->Next;

    c = x;

    while (a!= NULL && b!= NULL) {
        if (a->Data <= b->Data) {
            c->Next = a;//c这个地址的下一个元素为a
            c=c->Next;//将c这个地址指向其下一层级


            a = a->Next;
        } else {
            c->Next = b;
            c=c->Next;


            b= b->Next;
        }
    }

    if (a != NULL) {
        c->Next = a;
    }
    if (b != NULL) {
        c->Next = b;
    }

    L1->Next=NULL;
    L2->Next=NULL;
    return x;
}