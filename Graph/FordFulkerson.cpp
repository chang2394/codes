/**
    Checked on : http://lightoj.com/volume_showproblem.php?problem=1154
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

const int NN = 212;
const int MM = NN*NN;

int head[NN], cap[MM], parent[NN], edge[NN];
int to[MM], nxt[MM], myq[NN], flow[MM];
int nEdges = 0, n;
int source,sink;

double xco[NN], yco[NN];
int cur[NN], val[NN];
double jump;

inline void init(){
    nEdges = source = 0;
    memset(head,-1,sizeof(head));
}

inline void addEdge(int a,int b,int c){
    to[nEdges] = b, nxt[nEdges] = head[a];
    cap[nEdges] = c, flow[nEdges] = 0, head[a] = nEdges++;
}

bool reacheable(int x,int y){
    double ans = (xco[x] - xco[y]) * (xco[x] - xco[y]);
    ans += (yco[x] - yco[y]) * (yco[x] - yco[y]);
    return (ans <= jump);
}

void construct(){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if (i == j) continue;
            if (reacheable(i,j)){
                addEdge(2*i+2,2*j+1,MM);
                addEdge(2*j+1,2*i+2,0);
            }
        }
    }

    for(int i = 0; i < n; ++i){
        addEdge(2*i+1,2*i+2,val[i]);
        addEdge(2*i+2,2*i+1,0);
    }

    for(int i = 0; i < n; ++i){
        addEdge(source,2*i+1,cur[i]);
        addEdge(2*i+1,source,0);
    }
}

bool bfs(){
    memset(parent,-1,sizeof(parent));
    int st = 0,en = 0;
    parent[source] = source;
    myq[en++] = source;

    while(st < en){
        int x = myq[st++];
        if (x == sink)
            return true;
        for(int i = head[x]; i >= 0; i = nxt[i]){
            int y = to[i];
            if ((cap[i]-flow[i]) > 0 and parent[y] == -1){
                parent[y] = x;
                edge[y] = i;
                myq[en++] = y;
            }
        }
    }
    return (parent[sink] != -1);
}

int maxflow(){
    memset(flow,0,sizeof(flow));
    int ans = 0;
    while(bfs()){
        int x = sink, add;
        add = MM;
        while(x != source){
            int e = edge[x];
            add = min(add,cap[e]-flow[e]);
            x = parent[x];
        }
        x = sink;
        while(x != source){
            int e = edge[x];
            flow[e] += add;
            flow[e^1] -= add;
            x = parent[x];
        }
        ans += add;
    }
    return ans;
}

void solve(int tc){
    init();
    cin >> n >> jump;
    jump = jump * jump;

    int sum = 0;
    for(int i = 0; i < n; ++i){
        cin >> xco[i] >> yco[i] >> cur[i] >> val[i];
        sum += cur[i];
    }

    construct();
    vi ans;
    for(int i = 0; i < n; ++i){
        sink = 2*i+1;
        int valflow = maxflow();
        if (valflow == sum)
            ans.push_back(i);
    }

    cout << "Case " << tc << ": ";
    if (ans.empty()) cout << "-1\n";

    for(int i = 0; i < (int)ans.size(); ++i){
        cout << ans[i];
        if (i+1 == (int)ans.size()) cout << "\n";
        else cout << " ";
    }
}

int main()
{
    int t;
    cin >> t;
    for(int i = 1; i <= t; ++i)
        solve(i);
    return 0;
}
