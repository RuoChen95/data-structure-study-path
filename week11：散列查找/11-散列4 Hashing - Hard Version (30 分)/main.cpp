// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <queue> // priority_queue


//
// Created by Ruochen Xie on 2019-07-31.
//

#include <functional>   // std::greater
using namespace std; // priority_queue

#define ElementType int
#define MaxNumber 1000


int main(void) {
    int N;
    
	scanf("%d", &N);

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
		scanf("%d", &HASH[i]);
	}
	for (i = 0; i < N; i++) {
		if (HASH[i] != -1){
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
		} else {
			Indegree[i] = -1;
			Adj[i].push_back(-1);
		}
	}


	// build order
	priority_queue <ElementType, vector<ElementType>, greater<ElementType> > QHASH;
	int size;
	int p, pIndex;
	int TopOrder[MaxNumber];
	int cnt = 0;

	for(int i = 0; i < N; i++) {
		if(Indegree[i] == 0){
			QHASH.push(HASH[i]); // �ڶ���ѡ���ʱ�����ֵΪ��С��
        }
	}
    while(!QHASH.empty()){
        p = QHASH.top(); /* ����һ�����Ϊ0�Ķ��� */
		TopOrder[cnt++] = p; /* ��֮��Ϊ������е���һ��Ԫ�� */
		QHASH.pop();

		// pIndex
		for ( i = 0; i < N; i++){
			if (p == HASH[i]) {
				pIndex = i;
				break;
			}
		}

//		printf("%d %d\n", pIndex, p);

		/* ��V��ÿ���ڽӵ�W->AdjV */
		for (i = 0; i < Adj[pIndex].size(); i++) {

			if (--Indegree[Adj[pIndex][i]] == 0) {
				QHASH.push(HASH[Adj[pIndex][i]]);
			}
		}

    }
    
    
	printf("%d", TopOrder[0]);
    for (i = 1; i < cnt; i++) {
    	printf(" %d", TopOrder[i]);
	}


    return 0;
}

