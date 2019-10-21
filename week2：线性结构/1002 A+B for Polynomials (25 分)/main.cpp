#include "stdafx.h"
#pragma warning(disable:4996)
#include <cstdio>

struct node {
	float value;
	int exp;
	node* next;
};
void attach(node* &temp, float value, int exp) {
	node * p = new node;
	p->value = value; p->exp = exp; p->next=NULL;

	temp->next = p;
	temp = p;
}

node* formLink(void) {
	node* head = new node;
	head->next = NULL;
	node* temp = head;
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		float value;
		int exp;
		scanf("%d %f", &exp, &value);
		attach(temp, value, exp);
	}

	return head->next;
}

int main() {
	node* link1 = formLink();
	node* link2 = formLink();

	node* result = new node;
	node* temp = result;
	int num = 0;
	while (link1 && link2) {
		if (link1->exp == link2->exp) {
			if (link1->value+link2->value != 0) {
				attach(temp, link1->value+link2->value, link1->exp);
				num++;
			}
			link1 = link1->next;
			link2 = link2->next;
		} else if (link1->exp > link2->exp) {
			attach(temp, link1->value, link1->exp);
			link1 = link1->next;
			num++;
		} else {
			attach(temp, link2->value, link2->exp);
			link2 = link2->next;
			num++;
		}
	}

	while(link1) {
		attach(temp, link1->value, link1->exp);
		link1 = link1->next;
		num++;
	}
	while(link2) {
		attach(temp, link2->value, link2->exp);
		link2 = link2->next;
		num++;
	}

	result = result->next;
	node* p = result;

	if (num == 0) {
		printf("0");
	} else {
		printf("%d ", num);
		while (p) {
			printf("%d %0.1f", p->exp, p->value);
			p = p->next;
			if (p) {
				printf(" ");
			}
		}

	}
	return 0;
}