#include "stdafx.h"
#pragma warning(disable:4996)
#include <iostream>
#include <string>
#include <map>

using namespace std;

#define MAXN 2010
#define INF 1000000000

map<int, string> intToString;
map<string, int> stringToInt;
map<string, int> Gang;

int G[MAXN][MAXN] = {0};
int weight[MAXN] = {0};
int N, K, w;

int personIndex = 0; // index + 总人数(!!!)
int vis[MAXN] = {0};
int change(string str) {
	if (stringToInt.find(str) != stringToInt.end()) {
		return stringToInt[str];
	} else {
		stringToInt[str] = personIndex;
		intToString[personIndex] = str;
		return personIndex++;
	}
}

// index，头目节点（会变），人数（用于判断是否大于2），总价值（和K判断）
void DFS(int now, int & head, int & numMember, int & totalValue) {
	numMember++;
	vis[now] = 1;
	if (weight[now] > weight[head]) {
		head = now;
	}

	for (int i = 0; i < personIndex; i++) {
		if (G[now][i] > 0) {
			totalValue += G[now][i];
			G[now][i] = 0;
			G[i][now] = 0;
			if (vis[i] == 0) {
			
				DFS(i, head, numMember, totalValue);
			}
		}
	}
}

// 获取Gang
void DFSSolve() {
	for (int i = 0; i < personIndex; i++) {
		if (vis[i] == 0) {
			int head = i, numMember = 0, totalValue = 0;
			DFS(i, head, numMember, totalValue);

			if (numMember > 2 && totalValue > K) {
				Gang[intToString[head]] = numMember;
			}
		}
	}
}

int main(void) {
	string str1, str2;
	int id1, id2;
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		cin >> str1 >> str2 >> w;

		id1 = change(str1);
		id2 = change(str2);

		weight[id1] += w;
		weight[id2] += w;

		G[id1][id2] += w;
		G[id2][id1] += w;

	}

	DFSSolve();

	printf("%d\n", Gang.size());

	map <string, int>:: iterator it;
	for (it = Gang.begin(); it != Gang.end(); it++) {
		cout << it->first<< " " << it->second << endl;
	}

    return 0;
}