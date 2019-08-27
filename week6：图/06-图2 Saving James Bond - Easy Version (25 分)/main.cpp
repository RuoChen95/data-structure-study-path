#include <iostream>
#include <cmath> // abs pow

struct Node
{
	int x; // 鳄鱼的x坐标
	int y; // 鳄鱼的y坐标
	int tag; // 是否被访问过，0：没有，1：有
};

using namespace std;

void Save007( int N, int dis );
int FirstJump(int index, int dis);
int DFS( int index, int N, int Dis);



#define MaxTree 100
#define Diameter 15 // 岛的半径
#define Square 50 // 安全区域的边长

Node node[MaxTree]; // 全局变量：鳄鱼

int main(void) {

    int N, JumpDis, v1, v2, i;

    scanf("%d %d", &N, &JumpDis);

    for (i = 0; i < N; i++) {
        scanf("%d %d", &v1, &v2);

        node[i].x = v1;
		node[i].y = v2;
		node[i].tag = 0;
    }

    Save007(N, JumpDis);

    return 0;
}

void Save007( int N, int dis) {
    int i;
	int answer;
    for (i = 0; i < N; i++) {
        if (node[i].tag == 0 && FirstJump(i, dis) == 1) {
            answer = DFS(i, N, dis);
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
		return 1;
	} else {
		return 0;
	}
}


int DFS( int index, int N, int Dis) {
    node[index].tag = 1;
	int answer = 0;
	if ((Square - node[index].x <= Dis) || (Square - node[index].y <= Dis) || (node[index].x + Square <= Dis) || (node[index].y + Square <= Dis)) {
		answer = 1;
	} else {
		int i;
		for (i = 0; i < N; i++) {
			// 没有被踩过的鳄鱼
			if (node[i].tag == 0) {
				// v的每个临节点w
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