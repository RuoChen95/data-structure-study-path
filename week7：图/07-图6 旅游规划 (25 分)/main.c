//
// Created by Ruochen Xie on 2019-07-27.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MaxVertexNum 500
#define INFINITY 65535
#define ERROR -1
typedef int Vertex;
typedef int WeightType;

typedef struct GNode * PtrToGNode;
struct GNode {
    int Nv; // 顶点
    int Ne; // 边
    WeightType GLength[MaxVertexNum][MaxVertexNum];
    WeightType GPrice[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;

typedef struct ENode * PtrToENode;
struct ENode {
    Vertex V1, V2; // 顶点
    WeightType Length; // 权重
    WeightType Price;
};
typedef PtrToENode Edge;

MGraph BuildGraph(int *SDic, int *DDic);
MGraph CreateGraph( int VertexNum );
void InsertEdge( MGraph Graph, Edge E);

bool Dijkstra( MGraph Graph, int dist[], int cost[], Vertex S );
Vertex FindMinDist(MGraph Graph, int dist[], int collect[]);

int main(void) {
    int S, D; // 出发的编号，到达的编号
    int dist[MaxVertexNum];
    int cost[MaxVertexNum];

    MGraph G = BuildGraph(&S, &D);

    Dijkstra( G, dist, cost, S );

    printf("%d %d\n", dist[D], cost[D]);

    return 0;
}

MGraph BuildGraph(int* SDic, int *DDic) {
    MGraph Graph;
    Edge E;
    int Nv, i;

    scanf("%d", &Nv);
    Graph = CreateGraph(Nv);

    scanf("%d", &(Graph->Ne));

    scanf("%d", SDic);
    scanf("%d", DDic);

    E = (Edge)malloc(sizeof(struct ENode));
    for (i = 0; i < Graph->Ne; i++) {
        scanf("%d %d %d %d", &E->V1, &E->V2, &E->Length, &E->Price);
        InsertEdge(Graph, E);
    }

    return Graph;
}
// 模块1,2: 建造图以及插入边
MGraph CreateGraph( int VertexNum ) {
    Vertex V, W;
    MGraph Graph;

    Graph = (MGraph)malloc(sizeof(struct GNode));

    Graph->Nv = VertexNum;
    Graph->Ne = 0;

    for (V = 0; V<Graph->Nv; V++) {
        for (W=0; W<Graph->Nv; W++) {
            Graph->GLength[V][W] = INFINITY; //*
            Graph->GPrice[V][W] = INFINITY;
        }
    }

    return Graph;
}
void InsertEdge( MGraph Graph, Edge E) {
    Graph->GLength[E->V1][E->V2] = E->Length;
    Graph->GLength[E->V2][E->V1] = E->Length;

    Graph->GPrice[E->V1][E->V2] = E->Price;
    Graph->GPrice[E->V2][E->V1] = E->Price;
}

/* 邻接矩阵存储 - 有权图的单源最短路算法 */
Vertex FindMinDist( MGraph Graph, int dist[], int collected[] )
{ /* 返回未被收录顶点中dist最小者 */
    Vertex MinV, V;
    int MinDist = INFINITY;

    for (V=0; V<Graph->Nv; V++) {
        if ( collected[V]==false && dist[V]<MinDist) {
            /* 若V未被收录，且dist[V]更小 */
            MinDist = dist[V]; /* 更新最小距离 */
            MinV = V; /* 更新对应顶点 */
        }
    }
    if (MinDist < INFINITY) /* 若找到最小dist */
        return MinV; /* 返回对应的顶点下标 */
    else return ERROR;  /* 若这样的顶点不存在，返回错误标记 */
}

bool Dijkstra( MGraph Graph, int dist[], int cost[], Vertex S )
{
    int collected[MaxVertexNum];
    Vertex V, W;

    for ( V=0; V<Graph->Nv; V++ ) {
        dist[V] = Graph->GLength[S][V];
        cost[V] = Graph->GPrice[S][V];
        collected[V] = false;
    }
    /* 先将起点收入集合 */
    dist[S] = 0;
    collected[S] = true;

    while (1) {
        V = FindMinDist( Graph, dist, collected );
        if ( V==ERROR )
            break;
        collected[V] = true;
        for( W=0; W<Graph->Nv; W++ ) {
            if ( collected[W]==false && Graph->GLength[V][W]<INFINITY ) {
                if ( dist[V]+Graph->GLength[V][W] < dist[W] ) {
                    dist[W] = dist[V]+Graph->GLength[V][W];
                    cost[W] = cost[V]+Graph->GPrice[V][W];
                }
                // *
                else if ( dist[V]+Graph->GLength[V][W] == dist[W]) {
                    if (cost[W] > cost[V]+Graph->GPrice[V][W]) {
                        cost[W] = cost[V]+Graph->GPrice[V][W];
                    }
                }
            }
        }
    } /* while结束*/
    return true; /* 算法执行完毕，返回正确标记 */
}