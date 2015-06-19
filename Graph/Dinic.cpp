/**
    Complexity - O(mn^2)
    Tested on - http://www.spoj.com/problems/FASTFLOW/
    Code Reference - http://zobayer.blogspot.in/2010/05/maximum-flow-dinitz-algorithm.html
    Reference - http://www.cs.cmu.edu/~15451/lectures/lec11/dinic.pdf
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

const int inf = 0x7fffffff;
const int NN = 5123;
const int MM = 61234;

int head[NN], ptr[NN], myq[NN];
int to[MM], nxt[MM], cap[MM], flow[MM];
int dist[NN];

int src, sink, n, m;
int nEdges = 0;

inline void init(){
    memset(head,-1,sizeof(head));
    nEdges = 0;
}

inline void addEdge(int x,int y,int c){
    cap[nEdges] = c, flow[nEdges] = 0;
    to[nEdges] = y, nxt[nEdges] = head[x];
    head[x] = nEdges++;
}

bool bfs(){
    memset(dist,-1,n*sizeof(int));
    int st = 0, en = 0;
    dist[src] = 0;
    myq[en++] = src;

    while(st < en){
        int x = myq[st++];
        for(int i = head[x]; i >= 0; i = nxt[i]){
            int y = to[i];
            if (flow[i] < cap[i] and dist[y] == -1){
                dist[y] = dist[x] + 1;
                myq[en++] = y;
            }
        }
    }

    return (dist[sink] != -1);
}

int dfs(int x,int cflow){
    if (x == sink)
        return cflow;

    for(int &i = ptr[x]; i >= 0; i = nxt[i]){
        int y = to[i];
        if (flow[i] < cap[i] and dist[y] == dist[x]+1){
            int addflow = dfs(y,min(cflow,cap[i]-flow[i]));
            if (addflow > 0){
                flow[i] += addflow;
                flow[i^1] -= addflow;
                return addflow;
            }
        }
    }
    return 0;
}

long long dinic(){
    long long ans = 0;
    while(bfs()){
        memcpy(ptr,head,n*sizeof(int));
        while(true){
            int add = dfs(src,inf);
            if (add > 0) ans += (long long)add;
            else break;
        }
    }
    return ans;
}

void solve(){
    init();
    cin >> n >> m;
    src = 0, sink = n-1;

    for(int i = 0; i < m; ++i){
        int a,b,c;
        cin >> a >> b >> c;
        --a,--b;

        addEdge(a,b,c);
        addEdge(b,a,c);
    }

    long long ans = dinic();
    cout << ans << endl;
}

int main()
{
    solve();
    return 0;
}
