// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


//
// Created by Ruochen Xie on 2019-07-31.
//

#include <functional>   // std::greater
using namespace std; // priority_queue

#define ElementType int
#define MaxNumber 1000


void Heap_Sort_Simple( ElementType A[], int N);

int main(void) {
    int N;
    
	scanf_s("%d", &N);

	// build adj
	int i;
	int HASH[MaxNumber] = {0};
	int Indegree[MaxNumber] = {0};
	int MOD = N;
	int Need_Index; // the element should put into the index
	int True_Index; // the true index of the element
	vector<int> Adj[MaxNumber];
	int j;
	for (i = 0; i < N; i++) {
		scanf_s("%d", &HASH[i]);
	}
	for (i = 0; i < N; i++) {
		Need_Index = HASH[i]%MOD;
		True_Index = i;
		if ( Need_Index == i) {
			Indegree[i] = 0;
		} else {
			Indegree[i] = (True_Index - Need_Index + N) % N;
			for (j = 0; j < Indegree[i]; j++){
				Adj[(Need_Index+j+N) % N].push_back(i);
			}
		}
	}


	// build order
	priority_queue <ElementType, vector<ElementType>, greater<ElementType> > QHASH;
	priority_queue <ElementType, vector<ElementType>, greater<ElementType> > QIndex;
	int size;
	int p, pIndex;
	int TopOrder[MaxNumber];
	int cnt = 0;

	for(int i = 0; i < N; i++) {
		if(Indegree[i] == 0){
			QHASH.push(HASH[i]);
			QIndex.push(i);
        }
	}
    while(!QHASH.empty()){
        p = QHASH.top(); /* 弹出一个入度为0的顶点 */
		pIndex = QIndex.top();
		TopOrder[cnt++] = p; /* 将之存为结果序列的下一个元素 */
		QHASH.pop();
		QIndex.pop();
		/* 对V的每个邻接点W->AdjV */
		for (i = 0; i < Adj[pIndex].size(); i++) {
			if (--Indegree[i] == 0) {
				QHASH.push(HASH[i]);
				QIndex.push(i);
			}
		}

    }


    return 0;
}
