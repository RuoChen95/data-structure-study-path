#include <iostream>

using namespace std;
struct node {
	int exp;
	float val;
	node* next;
};


void Attach (float sum, int exp, node * & Rear) {
	node * p = new node;
	p->val = sum; p->exp = exp; p->next = NULL;
	Rear->next = p;
	Rear = p;
}
node* formLink() {
	int N, nodeExp ,i;
	float nodeValue;
	node *head, *Temp, *p;

	head = new node;
	head->next = NULL;
	Temp = head;

	scanf("%d", &N);
	for (i = 0; i < N; i++) {
		scanf("%d %f", &nodeExp, &nodeValue);
		Attach(nodeValue, nodeExp, Temp);
	}
	return head->next;
}
int main(void) {
	
	node *head1 = formLink();
	node *head2 = formLink();

	node *P = new node;
	node *Rear = P;
	float sum;
	int num = 0;
	while (head1 && head2) {
		if (head1->exp == head2->exp) {
			sum = head1->val+ head2->val;
			if (sum) {
				Attach(sum, head1->exp, Rear);
				num++;
			}
			head1 = head1->next;
			head2 = head2->next;
		} else if (head1->exp > head2->exp) {
			Attach(head1->val, head1->exp, Rear);
			head1 = head1->next;
			num++;
		} else {
			Attach(head2->val, head2->exp, Rear);
			head2 = head2->next;
			num++;
		}
	}

	while (head1) {
		Attach(head1->val, head1->exp, Rear);
		head1 = head1->next;
		num++;
	}

	while (head2) {
		Attach(head2->val, head2->exp, Rear);
		head2 = head2->next;
		num++;
	}

	P = P->next;


	if (!P) {
		printf("0");
	} else {
		printf("%d ", num);
		while (P) {
			printf("%d %.1f", P->exp, P->val);
			P=P->next;
			if (P) {
				printf(" ");
			}
		}
	}


    return 0;
}