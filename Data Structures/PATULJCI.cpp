//Code for spoj Snow white and the N dwarfs
// includes + defines {{{
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>
#define REP(i, n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for(int i = (int)(a); i <= (int)(b); ++i)
#define FORD(i, a, b) for(int i = (int)(a); i >= (int)(b); --i)
#define FORE(it, c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define SIZE(x) ((int)((x).size()))
#define DEBUG(x) { cout << #x << ": " << (x) << endl; }
#define SQR(x) ((x) * (x))
#define INF 1234567890
using namespace std;
// }}}

int N, C;
vector<vector<int> > W;

bool owni(int kto, int a, int b){
	if(kto == -1)
		return false;

	vector<int>::iterator wa = lower_bound(W[kto].begin(), W[kto].end(), a);
	vector<int>::iterator wb = lower_bound(W[kto].begin(), W[kto].end(), b);

	return (wb - wa) * 2 > (b - a);
}

int N2;
vector<int> S;

void buduj(int x, int u, int v){
	if(v - u == 1)
		return;

	buduj(2 * x, u, (u + v) / 2);
	buduj(2 * x + 1, (u + v) / 2, v);

	if(owni(S[2 * x], u, v))
		S[x] = S[2 * x];
	else if(owni(S[2 * x + 1], u, v))
		S[x] = S[2 * x + 1];
	else
		S[x] = -1;
}

vector<int> K;
int a, b;

void kandidati(int x, int u, int v){
	if(b <= u || v <= a)
		return;
	if(a <= u && v <= b){
		K.push_back(S[x]);
		return;
	}

	kandidati(2 * x, u, (u + v) / 2);
	kandidati(2 * x + 1, (u + v) / 2, v);
}

int main(){
	scanf("%d %d", &N, &C);
	W.resize(C);

	N2 = 1;
	while(N2 < N)
		N2 *= 2;
	S.resize(2 * N2, -1);

	REP(i, N){
		int x;
		scanf("%d", &x);

		S[N2 + i] = x - 1;
		W[x - 1].push_back(i);
	}

	buduj(1, 0, N2);

	int M;
	scanf("%d", &M);
	while(M--){
		scanf("%d %d", &a, &b);
		--a;

		K.clear();
		kandidati(1, 0, N2);
		bool ok = false;

		FORE(i, K)
			if(owni(*i, a, b)){
				printf("yes %d\n", *i + 1);
				ok = true;
				break;
			}

		if(!ok)
			printf("no\n");
	}
}
