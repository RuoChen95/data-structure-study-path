#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_User 10000
#define MAX_Problem 5
#define MAX_Submission 100000

struct Users {
	int score_sets[MAX_Problem];
	int total_socre;
	int perfect;
	int userId;
} users_sets[MAX_User];
void setUsers(int N, int K, int M);
void insert_Sort( int table[], int N);

int Compare(int table[], int a, int b);

void show(int table[], int K);
int main(void) {
    int N, K, M;

	scanf("%d %d %d", &N, &K, &M);
	
	setUsers(N, K, M);

	int table[MAX_User] = {0};
	int i;
	for (i = 0; i < MAX_User; i++) {
		table[i] = i;
	}


	insert_Sort(table, MAX_User);

	show(table, K);

    return 0;
}

void setUsers(int N, int K, int M) {


	int problem_sets[MAX_Problem] = {0};

	int i;
	int j;
	for (i = 1; i <= MAX_User; i++) {
		for (j = 1; j <= MAX_Problem; j++) {
			users_sets[i].score_sets[j] = -2;
		}
	}


	for (i = 1; i <= K; i++) {
		scanf("%d", &problem_sets[i]);
	}

	int userId, problemId, score;
	for (i = 0; i < M; i++) {
		scanf("%d %d %d", &userId, &problemId, &score);

		if (!users_sets[userId].score_sets[problemId] || users_sets[userId].score_sets[problemId] < score) {
			users_sets[userId].score_sets[problemId] = score;
		}

		users_sets[userId].userId = userId;
	}

	int total_socre, perfect, one_score;
	for (i = 1; i <= MAX_User; i++) {
		total_socre = 0;
		perfect = 0;
		for (j = 1; j <= MAX_Problem; j++) {
			one_score = users_sets[i].score_sets[j];
			if (one_score >= 0) {
				total_socre+=one_score;
				if (one_score == problem_sets[j]) {
					perfect++;
				}
			}
		}
		users_sets[i].total_socre = total_socre;
		users_sets[i].perfect = perfect;
	}

}

void insert_Sort( int table[], int N) {
    int p, temp, i;
    for (p = 1; p < N; p++) {
        temp = table[p];
        for (i = p; i >= 1; i--) {
			if (Compare(table, temp, i - 1)) {
				table[i] = table[i -1];
			} else {
				break;
			}
        }
        table[i]= temp;
    }
}


int Compare(int table[], int a, int b) {
	if (users_sets[a].total_socre > users_sets[table[b]].total_socre) {
		return 1;
	} else if (users_sets[a].total_socre < users_sets[table[b]].total_socre) {
		return 0;
	} else {
		if (users_sets[a].perfect > users_sets[table[b]].perfect) {
			return 1;
		} else {
			return 0;
		}
	}
}

void show(int table[], int K) {
	int i = 0;
	int j;
	int m;
	Users temp;
	int current = 1;
	for (i = 0; i < MAX_User; i++) {
		j = table[i];
		temp = users_sets[j];
		if (temp.total_socre != 0) {
			if (i >  0 && users_sets[table[i]].total_socre != users_sets[table[i-1]].total_socre) {
				printf("%d", i+1);
				current++;
			} else {
				printf("%d", current);
			}
			printf(" %05d %d", temp.userId, temp.total_socre);
			for (m = 1; m <= K; m++) {
				if (temp.score_sets[m] == -2) {
					printf(" -");
				} else if (temp.score_sets[m] == -1) {
					printf(" 0");
				} else {
					printf(" %d", temp.score_sets[m]);	
				}
			}

			printf("\n");
		}
	}
}
