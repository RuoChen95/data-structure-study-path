#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 队列定义开始
#define ElementType char
typedef int Position;
struct QNode {
    ElementType *Data;     /* 存储元素的数组 */
    Position Front, Rear;  /* 队列的头、尾指针 */
    int MaxSize;           /* 队列最大容量 */
};
typedef struct QNode *Queue;
Queue CreateQueue( int MaxSize )
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
    Q->Front = Q->Rear = 0;
    Q->MaxSize = MaxSize;
    return Q;
}
bool IsFull( Queue Q )
{
    return ((Q->Rear+1)%Q->MaxSize == Q->Front);
}
bool AddQ( Queue Q, ElementType X )
{
    if ( IsFull(Q) ) {
        printf("队列满");
        return false;
    }
    else {
        Q->Rear = (Q->Rear+1)%Q->MaxSize;
        Q->Data[Q->Rear] = X;
        return true;
    }
}
bool IsEmpty( Queue Q )
{
    return (Q->Front == Q->Rear);
}
ElementType DeleteQ( Queue Q )
{
    if ( IsEmpty(Q) ) {
        printf("队列空");
        return false;
    }
    else  {
        Q->Front =(Q->Front+1)%Q->MaxSize;
        return  Q->Data[Q->Front];
    }
}
// 队列定义结束


#define MaxVertexNum 100    /* 最大顶点数设为100 */
#define INFINITY 65535
typedef int Vertex;         /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;        /* 边的权值设为整型 */

/* 边的定义 */
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;      /* 有向边<V1, V2> */
    WeightType Weight;  /* 权重 */
};
typedef PtrToENode Edge;

/* 邻接点的定义 */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
    Vertex AdjV;        /* 邻接点下标 */
    WeightType Weight;  /* 边权重 */
    PtrToAdjVNode Next;    /* 指向下一个邻接点的指针 */
};

/* 顶点表头结点的定义 */
typedef struct Vnode{
    PtrToAdjVNode FirstEdge;/* 边表头指针 */
} AdjList[MaxVertexNum];    /* AdjList是邻接表类型 */

/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;     /* 顶点数 */
    int Ne;     /* 边数   */
    AdjList G;  /* 邻接表 */
};
typedef PtrToGNode LGraph; /* 以邻接表方式存储的图类型 */

LGraph CreateGraph( int VertexNum );
void InsertEdge( LGraph Graph, Edge E );
LGraph BuildGraph();

int TopSort( LGraph Graph, Vertex TopOrder[] );

int main(void) {
    LGraph G = BuildGraph();
    Vertex TopOrder[MaxVertexNum] = {0};

    int result = TopSort( G, TopOrder );
    if(result == -1) {
        printf("0");
    }

    return 0;
}

LGraph CreateGraph( int VertexNum )
{ /* 初始化一个有VertexNum个顶点但没有边的图 */
    Vertex V;
    LGraph Graph;

    Graph = (LGraph)malloc( sizeof(struct GNode) ); /* 建立图 */
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    /* 初始化邻接表头指针 */
    /* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
    for (V=0; V<Graph->Nv; V++)
        Graph->G[V].FirstEdge = NULL;

    return Graph;
}
void InsertEdge( LGraph Graph, Edge E )
{
    PtrToAdjVNode NewNode;

    /* 插入边 <V1, V2> */
    /* 为V2建立新的邻接点 */
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;
    /* 将V2插入V1的表头 */
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;
}
LGraph BuildGraph()
{
    LGraph Graph;
    Edge E;
    Vertex V;
    int Nv, i;

    scanf("%d", &Nv);   /* 读入顶点个数 */
    Graph = CreateGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */

    scanf("%d", &(Graph->Ne));   /* 读入边数 */
    if ( Graph->Ne != 0 ) { /* 如果有边 */
        E = (Edge)malloc( sizeof(struct ENode) ); /* 建立边结点 */
        /* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
        for (i=0; i<Graph->Ne; i++) {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);

            // 如果从0开始计数不需要-1
            E->V1 = E->V1 - 1;
            E->V2 = E->V2 - 1;

            /* 注意：如果权重不是整型，Weight的读入格式要改 */
            InsertEdge( Graph, E );
        }
    }
    return Graph;
}


/* 邻接表存储 - 拓扑排序算法 */
int TopSort( LGraph Graph, Vertex TopOrder[] )
{ /* 对Graph进行拓扑排序,  TopOrder[]顺序存储排序后的顶点下标 */
    int Indegree[MaxVertexNum], cnt, time[MaxVertexNum] = {0}, endTime[MaxVertexNum];
    Vertex V;
    PtrToAdjVNode W;
    Queue Q = CreateQueue( Graph->Nv );

    /* 初始化Indegree[] */
    for (V=0; V<Graph->Nv; V++)
        Indegree[V] = 0;

    /* 遍历图，得到Indegree[] */
    for (V=0; V<Graph->Nv; V++)
        for (W=Graph->G[V].FirstEdge; W; W=W->Next)
            Indegree[W->AdjV]++; /* 对有向边<V, W->AdjV>累计终点的入度 */

    /* 将所有入度为0的顶点入列 */
    for (V=0; V<Graph->Nv; V++)
        if ( Indegree[V]==0 )
            AddQ(Q, V);

    /* 下面进入拓扑排序 */
    cnt = 0;
    while( !IsEmpty(Q) ){
        V = DeleteQ(Q); /* 弹出一个入度为0的顶点 */
        TopOrder[cnt++] = V; /* 将之存为结果序列的下一个元素  输出 */
        /* 对V的每个邻接点W->AdjV */
        for ( W=Graph->G[V].FirstEdge; W; W=W->Next ) {
            Indegree[W->AdjV] = Indegree[W->AdjV] - 1;
            if ( Indegree[W->AdjV] == 0 ) {
                AddQ(Q, W->AdjV);
            }

            /* 下面进入最早完成时间的计算 */
            if (time[V] + W->Weight > time[W->AdjV]) {
                time[W->AdjV] = time[V] + W->Weight;
            }
        }

    } /* while结束*/


    /* 下面进入最晚完成时间的计算 */
    int i, index;
    int result = 0;

    for (i = 0; i < Graph->Nv; i++) {
        if (result < time[i]) {
            result = time[i];
        }
    }
    for (i = 0; i < Graph->Nv-1; i++) {
        endTime[i] = INFINITY;
    }

    for (i = Graph->Nv - 1; i >= 0; i--) {
        index = TopOrder[i];
        if (!Graph->G[index].FirstEdge) {
            endTime[index] = result; // 注意先将每个终点的最早时间改成计算出的t（终点的最早时间==最晚时间）
        }

        for (W=Graph->G[index].FirstEdge; W; W=W->Next) {
            //printf("%d %d %d\n", endTime[index], endTime[W->AdjV], W->Weight);
            if (endTime[index] > endTime[W->AdjV] - W->Weight) {
                endTime[index] = endTime[W->AdjV] - W->Weight;
            }
        }
    }

    if ( cnt != Graph->Nv ) {
        return -1; /* 说明图中有回路, 返回不成功标志 */
    }
    else {
        printf("%d\n", result);

        int i;
        int index;

        for (i = 0; i < Graph->Nv; i++) {
            for ( W=Graph->G[i].FirstEdge; W; W=W->Next ) {
                index = W->AdjV;
                if (time[i] == endTime[i] && time[index] == endTime[index]) {
                    printf("%d->%d\n", i+1, index+1);
                }
            }
        }

        return 0;
    }
}