//多项式表示
//程序框架
//读
//+
//*
//输出

#include <stdio.h>
#include <stdlib.h>
typedef struct PolyNode * Polynomial;
struct PolyNode {
    int value; // 系数
    int expon; // 指数
    Polynomial link; // 指针（结构指针）
};
Polynomial Read(void);
Polynomial Multi(Polynomial P1, Polynomial P2);
Polynomial Add(Polynomial P1, Polynomial P2);
void Print(Polynomial PP);
int main(void) {
    Polynomial P1, P2;
    // 读入1
    P1 = Read();
    // 读入2
    P2 = Read();

    // 乘法，输出
    Polynomial PP = Multi(P1, P2);
    Print(PP);

    // 加法，输出
    printf("\n");
    Polynomial PS = Add(P1, P2);
    Print(PS);

    return 0;
}
//

void Attach(int v, int e, Polynomial *pRear);
Polynomial Read(void) {
    int N, v, e = 0;
    Polynomial Rear, P, t;
    scanf("%d", &N);

    P = (Polynomial)malloc(sizeof(struct PolyNode)); P->link = NULL; Rear = P;
    while (N--) {
        scanf("%d %d", &v, &e);
        Attach(v, e, &Rear);
    }
    t = P; P = P->link; free(t);

    return P;
}
void Attach(int v, int e, Polynomial *pRear) {
    Polynomial P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->value = v; P->expon = e; P->link = NULL;
    (*pRear)->link = P;
    *pRear = P;
}
Polynomial Add(Polynomial P1, Polynomial P2) {
    Polynomial t1, t2, P, Rear;
    int sum;
    t1 = P1;
    t2 = P2;
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->link = NULL;
    Rear = P;
    while (t1 && t2) {
        if (t1->expon == t2->expon) {
            sum = t1->value + t2->value;
            if (sum) {
                Attach(sum, t1->expon, &Rear);
            }
            t1=t1->link;
            t2=t2->link;
        } else if (t1->expon > t2->expon) {
            Attach(t1->value, t1->expon, &Rear);
            t1=t1->link;
        } else {
            Attach(t2->value, t2->expon, &Rear);
            t2=t2->link;
        }
    }
    while (t1) {
        Attach(t1->value, t1->expon, &Rear);
        t1=t1->link;
    }
    while (t2) {
        Attach(t2->value, t2->expon, &Rear);
        t2=t2->link;
    }
    Rear->link = NULL;
    P = P->link;

    return P;
}
Polynomial Multi(Polynomial P1, Polynomial P2) {
    Polynomial t1, t2, P, Rear, t;
    int e, c;

    if (!P1 || !P2) return NULL;

    t1 = P1; t2 = P2;
    P = (Polynomial)malloc(sizeof(struct PolyNode)); P->link = NULL;
    Rear = P;
    while(t2) {
        Attach(t1->value * t2->value, t1->expon + t2->expon, &Rear);
        t2 = t2->link;
    }
    t1 = t1->link;
    while(t1) {
        t2 = P2; Rear = P;
        while(t2) {
            c = t1->value * t2->value;
            e = t1->expon + t2->expon;
            while(Rear->link && Rear->link->expon > e) {
                Rear = Rear->link;
            }
            if (Rear->link && Rear->link->expon == e) {
                if (Rear->link->value+c) {
                    Rear->link->value+=c;
                } else {
                    t = Rear->link;
                    Rear->link = t->link;
                    free(t);
                }
            } else {
                t = (Polynomial)malloc(sizeof(struct PolyNode));
                t->value = c;
                t->expon = e;
                t->link = Rear->link;
                Rear->link = t;
                Rear = Rear->link;
            }
            t2 = t2->link;
        }
        t1 = t1->link;
    }
    t2 = P;
    P = P->link;
    free(t2);
    return P;
}
void Print(Polynomial P) {
    if (!P) {
        printf("0 0");
        return;
    }
    while (P) {
        printf("%d %d", P->value, P->expon);
        P=P->link;
        if (P) {
            printf(" ");
        }
    }
}