/**
 * @author chang
 * @date 17-11-2015
 * Complexity : O(N+M)
 * Problem : http://www.lightoj.com/volume_showproblem.php?problem=1168
 * Finds all the SCC and reconstructs the graph according to that.
*/

#include <cstdio>
#include <iostream>
#include <cassert>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cstring>
#include <bitset>
#include <deque>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>
#include <cmath>

#define  each(v,c)  for(typeof((c).begin()) v = (c).begin(); v != (c).end(); ++v)
#define  sync(x)    ios_base::sync_with_stdio(x)
#define  sz(a)      ((int)(a.size()))
#define  all(a)     (a).begin(), (a).end()
#define  pb         push_back
#define  mp         make_pair
#define  fi         first
#define  se         second
using namespace std;

#define debug(a,n)    cerr << "["; for(int i = 0; i < n; ++i) cerr << a[i] << " ";cerr << "\b]\n";
#define dbg(args...)  {debug1,args; cerr<<endl;}
#define pause()       cin.get();cin.get();

struct debugger {
    template<typename T> debugger& operator , (const T& v) {
        cerr<<v<<" "; return *this;
    }
} debug1;

template <typename T1, typename T2>
inline ostream& operator << (ostream& os, const pair<T1, T2>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}

template<typename T>
inline ostream &operator << (ostream & os,const vector<T>& v) {
    bool first = true; os << "[";
    for (typename vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
        os << *ii; first = false;
    }
    return os << "]";
}

typedef long long LL;
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef vector<int> vi;
const int inf = 0x7fffffff;

const int ND = 1123;

vi con[ND], edge[ND];
int n = 1000;

int low[ND], desc[ND], inc = 0;
int fa[ND], scc = 0;

bool inStack[ND];
stack<int> elements;

bool input[ND];

void dfs(int x){
    low[x] = desc[x] = inc++;
    elements.push(x);
    inStack[x] = true;

    for(int i = 0; i < sz(con[x]); ++i){
        int y = con[x][i];
        if (desc[y] == -1) {
            dfs(y);
            low[x] = min(low[x],low[y]);
        } 
        else if (inStack[y])
            low[x] = min(low[x],desc[y]);
    }    

    if (low[x] == desc[x]){
        // head node found 
        while(elements.top() != x){
            int y = elements.top();
            elements.pop();
            fa[y] = scc;
            inStack[y] = false;
        }
        elements.pop();
        inStack[x] = false;
        fa[x] = scc++;
    }
}

bool visited[ND];
void go(int x) {
    if (sz(edge[x]) > 1) return;
    visited[x] = true;
    for(int i = 0; i < sz(edge[x]); ++i){
        int y = edge[x][i];
        if (!visited[y]) 
            go(y);
    }    
}

void solve(int tc){
    int m;
    cin >> m;
    
    inc = scc = 0;
    memset(input,false,sizeof(input));
    memset(desc,-1,sizeof(desc));
    memset(visited,false,sizeof(visited));
    
    for(int i = 0; i < n; ++i){
        con[i].clear();
        edge[i].clear();
    }

    for(int i = 0; i < m; ++i){
        int no;
        cin >> no;
        for(int k = 0; k < no; ++k){
            int x,y;
            cin >> x >> y;
            con[x].pb(y);
            input[x] = input[y] = true;
        }
    }
    
    input[0] = true;
    for(int i = 0; i < n; ++i){
        if (input[i] and desc[i] == -1)
            dfs(i);
    }
    
    for(int i = 0; i < n; ++i){
        if (!input[i]) continue;
        for(int j = 0; j < sz(con[i]); ++j){
            int y = con[i][j];
            if (fa[i] == fa[y]) continue;
            edge[fa[i]].pb(fa[y]);
        }
    }

    go(fa[0]);
    for(int i = 0; i < scc; ++i){
        if (!visited[i]){
            cout << "Case " << tc << ": NO\n";
            return;
        }
    }

    cout << "Case " << tc << ": YES\n";
}

int main()
{
    int tc;
    cin >> tc;
    for(int i = 1; i <= tc; ++i)
        solve(i);
    return 0;
}
