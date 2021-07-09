#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <climits>

using namespace std;

#ifdef LOCAL
ifstream fin("2.in");
ofstream fout("test.out");
#else
#define fin cin
#define fout cout
#endif

int N;
int lastpos[200000];
int nextpos[200000];

vector<int> tree;

void update(int k, int x) {
	k += N;
	tree[k] = x;

	for (k /= 2; k > 0; k /= 2) {
		tree[k] = tree[2 * k + 1] + tree[2 * k];
	}
}

int query(int a, int b) {
	a += N;
	b += N;

	int sum = 0;

	while (a <= b) {
		if (a % 2 == 1) {
			sum += tree[a++];
		}

		if (b % 2 == 0) {
			sum += tree[b--];
		}

		a /= 2;
		b /= 2;
	}

	return sum;
}

int main() {
	fin >> N;

	vector<int> breeds(N);
	tree.resize(2 * N, 0);

	for (int& i : breeds) {
		fin >> i;
		lastpos[i] = -1;
		nextpos[i] = -1;
	}

	for (int i = 0; i < N; i++) {

	}

	int opencount = 0;

	for (int r = 0; r < N; r++) {
		if (lastpos[breeds[r]] == -1) {

		}
		else {
			update(lastpos[breeds[r]], 0);
		}
	}
}