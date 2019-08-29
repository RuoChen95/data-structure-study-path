#include <iostream>
#include <cmath> // abs pow
#include <queue>

using namespace std;

struct Node
{
	int x; // 鳄鱼的x坐标
	int y; // 鳄鱼的y坐标
	int tag; // 是否被访问过，0：没有，1：有
	int dist; // 判断相对于原始点的距离
	int path;
};

using namespace std;

void Save007( int N, int dis );
int FirstJump(int index, int dis);
int DFS( int index, int N, int Dis);
int BFS(int index, int N, int Dis, queue<int> Q);



#define MaxTree 100
#define Diameter 15 // 岛的半径
#define Square 50 // 安全区域的边长

Node node[MaxTree]; // 全局变量：鳄鱼

int main(void) {

    int N, JumpDis, v1, v2, i;

    scanf_s("%d %d", &N, &JumpDis);

    for (i = 0; i < N; i++) {
        scanf_s("%d %d", &v1, &v2);

        node[i].x = v1;
		node[i].y = v2;
		node[i].tag = 0;
		node[i].dist = -1;
		node[i].path = -1;
    }

    Save007(N, JumpDis);

    return 0;
}

void Save007( int N, int dis) {
    int i;
	int answer;
	queue<int> Q;
    for (i = 0; i < N; i++) {
        if (node[i].tag == 0 && FirstJump(i, dis) == 1) {
            answer = BFS(i, N, dis, Q);
			if (answer == 1) {
				break;
			}
        }
    }
	if (answer == 1) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}
}


int FirstJump(int index, int dis) {
	int sum_diameter = dis + Diameter;
		if ((pow(node[index].x, 2) + pow(node[index].y, 2)) <= pow(sum_diameter,2)) {
		node[index].tag = 1;
		node[index].dist = 0; // 第一跳
		return 1;
	} else {
		return 0;
	}
}


int DFS( int index, int N, int Dis) {
    node[index].tag = 1;
	int answer = 0;
	// 如果能跳到边上
	if ((Square - node[index].x <= Dis) || (Square - node[index].y <= Dis) || (node[index].x + Square <= Dis) || (node[index].y + Square <= Dis)) {
		answer = 1;
	} else {
		int i;
		for (i = 0; i < N; i++) {
			// 没有被踩过的鳄鱼
			if (node[i].tag == 0) {
				// v的每个临节点w（007能跳到） 注意正确的计算方法
				if (abs(pow(node[i].x - node[index].x, 2) + pow(node[i].y - node[index].y, 2))<= pow(Dis,2)) {
					node[i].tag = 1;
					answer = DFS(i, N, Dis);
					if (answer == 1) {
						break;
					}
				}
			}
		}
	}

	return answer;
}

int BFS(int index, int N, int Dis, queue<int> Q) {
	node[index].tag = 1;
	int answer = 0;
	if ((Square - node[index].x <= Dis) || (Square - node[index].y <= Dis) || (node[index].x + Square <= Dis) || (node[index].y + Square <= Dis)) {
		answer = 1;
	} else {
		Q.push(index);
		int i;
		while (!Q.empty()) {
			index = Q.front();
			Q.pop();
			if ((Square - node[index].x <= Dis) || (Square - node[index].y <= Dis) || (node[index].x + Square <= Dis) || (node[index].y + Square <= Dis)) {
				answer = 1;
			}
			for (i = 0; i < N; i++) {
				if (node[i].tag == 0) {
				// v的每个临节点w（007能跳到） 注意正确的计算方法
					if (abs(pow(node[i].x - node[index].x, 2) + pow(node[i].y - node[index].y, 2))<= pow(Dis,2)) {
						node[i].tag = 1;
						Q.push(i); // !!!注意这里是i
					}
				}
			}
		}
	}

	return answer;
}