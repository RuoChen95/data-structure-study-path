#include "stdafx.h"
#pragma warning(disable:4996)
#include <cstdio>

struct node {
	int exp;
	float val;
	node* next;
};

void attach(node * &temp, float val, int exp) {
	node *p = new node;
	p->exp = exp;
	p->val = val;
	p->next = NULL;
	
	temp->next = p;
	temp = p;
}

node* formLink(void) {
	int n, e;
	float v;
	
	node* head = new node;
	head->exp = 0;
	head->val = 0;
	head->next = NULL;
	
	node* temp = head;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %f", &e, &v);
		attach(temp, v, e);
	}
	
	return head->next;
}

int main (void) {
	node* link1 = formLink();
	node* link2 = formLink();
	
	node* t1 = link1;
	node* t2 = link2;
	
	node* p = new node;
	p->val = 0;
	p->exp = 0;
	p->next = NULL;
	node* rear = p;
	
	node* t;
	
	float val;
	int exp;
	
	while (t2) {
		attach(rear, t1->val*t2->val, t1->exp+t2->exp);
		t2 = t2->next;
	}
	t1 = t1->next;
	while (t1) {
		t2 = link2;
		rear = p->next;
		while (t2) {
			val = t1->val * t2->val;
			exp = t1->exp + t2->exp;
			
			while (rear->next && rear->next->exp > exp) {
				rear = rear->next;
			}
			
			if (rear->next && rear->next->exp == exp) {
				if (rear->next->val + val) {
					rear->next->val += val;
				} else {
					t = rear->next;
					rear->next = t->next;
				}
			} else {
				t = new node;
				t->exp = exp;
				t->val = val;
				t->next = rear->next;
				rear->next = t;
				rear = t;
			}
			t2 = t2->next;
		}
		t1 = t1->next;
	}
	
	p = p->next;
	if (!p) {
		printf("NO");
        return 0;
	}
	int num = 0;
	rear = p;
	while (rear) {
		num++;
		rear = rear->next;
	}
	printf("%d ", num);
	while (p) {
		printf("%d %0.1f", p->exp, p->val);
		p = p->next;
		if (p) {
			printf(" ");
		}
	}
	return 0;
}