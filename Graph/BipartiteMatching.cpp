/**
  Complexity : O(nm)
  Checked on : http://lightoj.com/volume_showproblem.php?problem=1176
  Code Reference : http://www.codechef.com/viewplaintext/1945675
**/

#include <bits/stdc++.h>
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

const int NN = 51;
const int MM = NN*NN*2;
string sizes[] = {"XXL","XL","L","M","S","XS"};

int head[NN], to[MM], nxt[MM];
int matchL[NN], matchR[MM];
bool seen[MM];
int n,m,nEdges = 0;

inline void init(){
    nEdges = 0;
    memset(head,-1,sizeof(head));
    memset(matchL,-1,sizeof(matchL));
    memset(matchR,-1,sizeof(matchR));
}

inline void addEdge(int x,int y){
    to[nEdges] = y, nxt[nEdges] = head[x];
    head[x] = nEdges++;
}

bool path(int x){
    for(int i = head[x]; i >= 0; i = nxt[i]){
        int y = to[i];
        if (seen[y]) continue;
        seen[y] = true;

        if (matchR[y] < 0 or path(matchR[y])){
            matchR[y] = x;
            matchL[x] = y;
            return true;
        }
    }
    return false;
}

int bpm(){
    int ans = 0;
    for(int i = 0; i < m; ++i){
        memset(seen,false,sizeof(seen));
        if (path(i)) ++ans;
    }
    return ans;
}

bool solve(){
    init();
    cin >> n >> m;
    string s1,s2;

    for(int i = 0; i < m; ++i){
        cin >> s1 >> s2;
        for(int j = 0; j < 6; ++j){
            if (sizes[j] != s1 and sizes[j] != s2)
                continue;
            for(int k = 0; k < n; ++k)
                addEdge(i,k*6+j);
        }
    }

    int ans = bpm();
    return (ans == m);
}

int main()
{
    int t;
    cin >> t;
    for(int i = 1; i <= t; ++i){
        bool flag = solve();
        cout << "Case " << i << ": " << (flag ? "YES" : "NO") << "\n";
    }
    return 0;
}
