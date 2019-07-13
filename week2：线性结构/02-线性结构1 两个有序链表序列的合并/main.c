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
    List a, b, L3, template;
    a = L1->Next;
    b = L2->Next;

    L3 = (List)malloc(sizeof(struct Node));
    template = L3;

    while (a&&b) {
        if (a->Data <= b->Data) {
            template->Next = a;
            template = template->Next;
            a = a->Next;
        } else {
            template->Next = b;
            template = template->Next;
            b = b->Next;
        }
    }

    if (a) {
        template->Next = a;
    }
    if (b) {
        template->Next = b;
    }

    L1->Next = NULL;
    L2->Next = NULL;

    return L3;
}