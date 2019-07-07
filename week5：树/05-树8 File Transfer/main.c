#include <stdio.h>

#define MaxSize 10000

typedef int ElementType;
typedef int SetName;
typedef ElementType SetType[MaxSize];


SetName Find( SetType S, ElementType X);
void Union( SetType S, SetName Root1, SetName Root2);
void Input_connection( SetType S );
void Check_connection( SetType S );
void Check_network(SetType S, int n);



int main (void) {
    SetType S;
    int n;
    char in;

    scanf("%d\n", &n);

    // 初始化
    int i;
    for (i = 0; i < n; i++) {
        S[i] = -1; // 数组从0到n-1，这棵树的规模一开始为1
    }

    do {
        scanf("%c", &in);

        switch (in) {
            case 'I': Input_connection(S); break; // 合并 + 查询
            case 'C': Check_connection(S); break; // 查询
            case 'S': Check_network(S, n); break; // 集合中有多少个根节点
        }

    } while ( in != 'S');

    return 0;
}

void Input_connection( SetType S) {
    ElementType u, v;
    SetName Root1, Root2;

    scanf("%d %d\n", &u, &v);

    Root1 = Find(S, u-1); // 计算机从1-n编号
    Root2 = Find(S, v-1);

    if (Root1 != Root2) {
        Union(S, Root1, Root2);
    }
}

void Check_connection( SetType S) {
    ElementType u, v;
    SetName Root1, Root2;

    scanf("%d %d\n", &u, &v);

    Root1 = Find(S, u-1);
    Root2 = Find(S, v-1);

    if (Root1 == Root2) {
        printf("yes\n");
    } else {
        printf("no\n");
    }
}

void Check_network(SetType S, int n) {
    int i, counter = 0;
    for (i = 0; i < n; i++) {
        if (S[i] < 0) counter++;
    }

    if (counter == 1) {
        printf("The network is connected.\n");
    } else {
        printf("There are %d components.\n", counter);
    }
}


// 路径压缩
SetName Find( SetType S, ElementType X) {
    if (S[X] < 0) {
        return X;
    } else {
        return S[X] = Find( S, S[X] ); //重新设定root
    }
}

// 通过规模归并
void Union( SetType S, SetName Root1, SetName Root2) {
    if (S[Root2] < S[Root1]) {
        S[Root2] += S[Root1];
        S[Root1] = Root2;
    } else {
        S[Root1] += S[Root2];
        S[Root2] = Root1;
    }
}