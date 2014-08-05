#include <bits/stdc++.h>
using namespace std;

/*** START OF TEMPLATE CODE ***/
#define MAX (int)(5*1e4+2)
#define LOG(num) (31 - __builtin_clz(num))
typedef pair<int,int> pii;

int dp[MAX],P[MAX][17];
int T[MAX],L[MAX];
bool valid[MAX];
vector<pii> v[MAX];

void dfs(int idx,int lv,int par,int wt){
    valid[idx] = true;
    int size = v[idx].size();

    T[idx] = par,L[idx] = lv+1;
    dp[idx] = wt;
    for(int i = 0; i < size; ++i){
        int id = v[idx][i].first, w = v[idx][i].second;
        if (valid[id]) continue;
        dfs(id,lv+1,idx,wt+w);
    }
    valid[idx] = false;
}

//Function to compute the LCA
int LCA(int x,int y){
    if (L[x] < L[y]) swap(x,y);
    int mx = LOG(L[x]);
    for(int i = mx; i >= 0; --i)
        if ((L[x] - (1 << i)) >= L[y]) x = P[x][i];

    if (x == y) return x;
    for(int i = mx; i >= 0; --i){
        if (P[x][i] != -1 && P[x][i] != P[y][i])
            x = P[x][i] , y = P[y][i];
    }
    return T[x];
}

int main()
{
    ios::sync_with_stdio(0);
    int n,a,b,w;
    cin >> n;

    memset(P,-1,sizeof(P));
    for(int i = 1; i <= n-1; ++i){
        cin >> a >> b >> w;
        v[a].push_back(pii(b,w));
        v[b].push_back(pii(a,w));
    }

    dfs(0,0,-1,0);

    //Precomputation of parents at each 2^k imtervals.
    for(int i = 1; i <= n; ++i) P[i][0] = T[i];
    for(int k = 1; (1 << k) < n; ++k){
        for(int i = 1; i <= n; ++i){
            if (P[i][k-1] != 0)
                P[i][k] = P[P[i][k-1]][k-1];
        }
    }

    int q;
    cin >> q;

    while(q--){
        cin >> a >> b;
        int cm = LCA(a,b);
        int ans = dp[a] + dp[b] - 2*dp[cm];
        cout << ans << endl;
    }
    return 0;
}
