// Code for Z-Algorithm
// Complexity -> O(N)
// Checked on -> http://codeforces.com/contest/126/problem/B
// Reference -> http://codeforces.com/blog/entry/3107

#include <bits/stdc++.h>
using namespace std;

// Uzumaki Naruto :)

#define DB(a) cerr << __LINE__ << ": " << #a << " = " << (a) << endl
#define debug(A,sz) for(int i = 0; i < sz; ++i) cerr << A[i] << " ";cerr << "\n";
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;

const int MAX = 1123456;
int Z[MAX],A[MAX],B[MAX],N;
string str;

// The Z Array contains the value of LCP(0,i) 
void solve(){
    cin >> str;
    N = (int)str.size();

    int L = 0, R = 0,k;
    for(int i = 1; i < N; ++i){
        k = i-L;
        if (i <= R and Z[k] < R-i+1)
            Z[i] = Z[k];
        else {
            L = i, R = max(R,i);
            while(R < N and str[R-L] == str[R]) ++R;
            Z[i] = R-L, --R;
        }

        if (Z[i]+i >= N) ++A[Z[i]], ++B[Z[i]-1],assert(A[Z[i]] <= 1);
        else ++B[Z[i]];
    }

    for(int i = N; i > 0; --i) if ((B[i] += B[i+1]) and A[i] and B[i]) {
        puts(str.substr(0,i).c_str());
        return;
    }

    puts("Just a legend");
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	solve();
	return 0;
}
