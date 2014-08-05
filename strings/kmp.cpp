// Code for KMP String Matching
// Tested on :- http://lightoj.com/volume_showproblem.php?problem=1255
// Complexity -> O(N+M)

#include <bits/stdc++.h>
using namespace std;

// Uzumaki Naruto :)

#define DEBUG
#ifdef DEBUG
	#define dbg(a) cerr << __LINE__ << ": " << #a << " = " << (a) << endl
	#define dbg_all(a,sz) cerr << "_____ " << #a << " = "; for(int i = 0; i < sz; ++i) cerr << a[i] << " "; cerr << "\n"
	#define pause() cin.get();cin.get();
#else
	#define dbg(a)
	#define dbg_all(a,sz)
	#define pause()
#endif

typedef long long LL;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int NN = 1123456;

char txt[NN],pat[NN];
int LPS[NN];

void build(int n){
    int k = LPS[1] = 0;
    for(int i = 2; i <= n; ++i){
        while(k > 0 and pat[k] != pat[i-1])
            k = LPS[k];
        k += (pat[k] == pat[i-1]);
        LPS[i] = k;
    }
}

int cnt(int n,int m){
    int k = 0, ans = 0;
    for(int i = 1; i <= n; ++i){
        while(k > 0 and pat[k] != txt[i-1])
            k = LPS[k];
        k += (pat[k] == txt[i-1]);
        if (k == m)
            ++ans, k = LPS[k];
    }
    return ans;
}

int solve(){
    scanf("%s%s",txt,pat);
    int n = (int)strlen(txt);
    int m = (int)strlen(pat);

    build(m);
    int ans = cnt(n,m);
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int t; scanf("%d",&t);
    for(int i = 1; i <= t; ++i)
        printf("Case %d: %d\n",i,solve());
    return 0;
}
