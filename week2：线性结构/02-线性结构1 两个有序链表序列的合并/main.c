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

/* 你的代码将被嵌在这里 */
List Merge( List L1, List L2 )
{
    List c,x;
    x=(List)malloc(sizeof(struct Node)); 
    L1=L1->Next;
    L2=L2->Next;
    c=x;
    while(a&&b)
    {
        if(L1->Data<=L2->Data)
        {
            c->Next=L1;
            c=L1;
            L1=L1->Next;
        }
        else
        {
            c->Next=L2;
            c=L2;
            L2=L2->Next;
        }
    }
    c->Next=L1?L1:L2; //如果L1存在，则指向L1；如果b存在，则指向b
    L1->Next=NULL;
    L2->Next=NULL;
    return x;
    
}