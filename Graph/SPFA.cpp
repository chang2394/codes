/* Algorithm -> SPFA (Shortest Path Faster Algorithm)
   Checked on -> http://codeforces.com/contest/20/problem/C
   with Djisktra -> AC in 122 ms 
   with SPFA -> AC in 92 ms  */

#include <bits/stdc++.h>
using namespace std;

// Uzumaki Naruto :)

#define DB(a) cerr << __LINE__ << ": " << #a << " = " << (a) << endl
#define dbg(A,sz) for(int i = 0; i < sz; ++i) cerr << A[i] << " "; cerr << "\n"
#define pause() cin.get();cin.get();

typedef long long LL;
typedef pair<LL,int> PII;
typedef vector<int> VI;

const int NN = 112345;
struct EDGE{
    int to,next,cost;
} edge[2*NN];

int head[NN],nxt[NN];
LL dist[NN];
bool inq[NN];
int N,M,E = 0;

void addEdge(int a,int b,int wt){
    edge[E].to = b;
    edge[E].next = head[a];
    edge[E].cost = wt;
    head[a] = E++;
}

void SPFA(){
    queue<int> q;
    dist[1] = 0,nxt[1] = -1;
    q.push(1);

    while(!q.empty()){
        int st = q.front(); q.pop();
        inq[st] = false;
        for(int i = head[st]; i != -1; i = edge[i].next){
            int x = edge[i].to;
            if (dist[x] == -1 or dist[x] > dist[st] + edge[i].cost){
                dist[x] = dist[st] + edge[i].cost, nxt[x] = st;
                if (!inq[x]) inq[x] = true, q.push(x);
            }
        }
    }
}

void print(int st){
    if (st != -1){
        print(nxt[st]);
        cout << st << " ";
    }
}

void solve(){
    memset(head,-1,sizeof(head));
    memset(dist,-1,sizeof(dist));
    memset(inq,false,sizeof(inq));

    cin >> N >> M;
    int a,b,wt,id;
    for(int i = 1; i <= M; ++i)
        cin >> a >> b >> wt, addEdge(a,b,wt), addEdge(b,a,wt);
    SPFA();
    if (dist[N] != -1)print(N), cout << endl;
    else puts("-1");
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    solve();
    return 0;
}
