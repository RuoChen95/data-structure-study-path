#include <stdio.h>
#include <stdlib.h> // malloc
#include <stdbool.h> // bool

typedef int ElementType;
typedef struct HNode *Heap; /* 堆的类型定义 */
struct HNode {
    ElementType *Data; /* 存储元素的数组 */
    int Size;          /* 堆中当前元素个数 */
    int Capacity;      /* 堆的最大容量 */
};
typedef Heap MaxHeap; /* 最大堆 */
typedef Heap MinHeap; /* 最小堆 */

#define MINDATA -10000

MinHeap CreateHeap( int MaxSize );

bool Insert( MaxHeap H, ElementType X );
bool IsFull( MaxHeap H );


int main(void) {
    int MaxSize, search_number, n, i, j;
    MinHeap H;

    scanf("%d", &MaxSize);
    scanf("%d", &search_number);

    H = CreateHeap(MaxSize);

    for (i = 0; i < MaxSize; i++) {
        scanf("%d", &n);
        Insert(H, n);
    }

    for (i = 0; i < search_number; i++) {
        scanf("%d", &j);

        printf("%d", H->Data[j]);
        j = j/2;
        while (j > 0) {
            int X = H->Data[j];
            printf(" %d", X);
            j = j/2;
        }
        printf("\n");
    }


    return 0;
}

MinHeap CreateHeap( int MaxSize )
{ /* 创建容量为MaxSize的空的最大堆 */

    MaxHeap H = (MaxHeap)malloc(sizeof(struct HNode));
    H->Data = (ElementType *)malloc((MaxSize+1)*sizeof(ElementType));
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Data[0] = MINDATA; /* 定义"哨兵"为大于堆中所有可能元素的值*/

    return H;
}

bool Insert( MinHeap H, ElementType X )
{ /* 将元素X插入最小堆H，其中H->Data[0]已经定义为哨兵 */
    int i;

    if ( IsFull(H) ) {
        printf("最小堆已满");
        return false;
    }
    i = ++(H->Size); /* i指向插入后堆中的最后一个元素的位置 */
    for ( ; H->Data[i/2] > X; i/=2 )
        H->Data[i] = H->Data[i/2]; /* 上滤X */
    H->Data[i] = X; /* 将X插入 */
    return true;
}


bool IsFull( MinHeap H )
{
    return (H->Size == H->Capacity);
}