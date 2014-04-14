// SPOJ - QTREE
#include <bits/stdc++.h>
using namespace std;
#define debug(arr,sz) for(int i = 0; i < sz; ++i) cerr << arr[i] << " "; cerr << endl;
#define MID (st+en)/2
#define LT (2*node)
#define RT (2*node+1)

const int MAX = 11234;
const int LOG = 17;

struct EDGE{
    int to,from,next,wt;
} edge[2*MAX];

int head[MAX],subtree[MAX];
int bestWt[MAX],bestSub[MAX];
int N,e = 0;
void addEdge(int a,int b,int w){
    edge[e].to = b;
    edge[e].from = a;
    edge[e].next = head[a];
    edge[e].wt = w;
    head[a] = e++;
}

int P[20][MAX],H[MAX];
bool vis[MAX];
void computeSize(int st,int parent,int height){
    vis[st] = true;
    P[0][st] = parent;
    subtree[st] = 1;
    H[st] = height;

    int mx = -1, index = -1, wt = -1;
    for(int i = head[st]; i != -1; i = edge[i].next){
        int x = edge[i].to, w = edge[i].wt;
        if (vis[x]) continue;
        computeSize(x,st,height+1);
        subtree[st] += subtree[x];
        if (subtree[x] > mx)
            mx = subtree[x], index = x ,wt = w;
    }

    bestSub[st] = index;
    bestWt[st] = wt;
    vis[st] = false;
}

void computeParent(){
    for(int i = 1; (1 << i) < N; ++i) for(int j = 1; j <= N; ++j)
        if (P[i-1][j] != -1)
            P[i][j] = P[i-1][P[i-1][j]];
}

int getLCA(int x,int y){
    if (H[x] < H[y]) swap(x,y);
    for(int i = LOG; i >= 0; --i)
        if (H[x] - (1 << i) >= H[y]) x = P[i][x];
    if (x == y) return x;
    for(int i = LOG; i >= 0; --i)
        if (P[i][x] != -1 and P[i][x] != P[i][y])
            x = P[i][x], y = P[i][y];
    return P[0][x];
}

int chainId[MAX],posInBase[MAX],chainSize[MAX];
int chainHead[MAX],chainCost[MAX],headCost[MAX];
int chainNo = 0,totalSize = 0;

void HLD(int st,int cost){
    if (chainHead[chainNo] == -1)
        chainHead[chainNo] = st, headCost[chainNo] = cost;

    chainId[st] = chainNo;
    chainCost[totalSize] = cost;
    posInBase[st] = totalSize++;
    ++chainSize[chainNo];
    vis[st] = true;

    if (bestSub[st] != -1)
        HLD(bestSub[st],bestWt[st]);
    for(int i = head[st]; i != -1; i = edge[i].next){
        int x = edge[i].to, wt = edge[i].wt;
        if (vis[x] || x == bestSub[st]) continue;
        ++chainNo;
        HLD(x,wt);
    }
    vis[st] = false;
}

int segMax[3*MAX];
void build(int node,int st,int en){
    if (st == en){
        segMax[node] = chainCost[st];
        return;
    }

    build(LT,st,MID);
    build(RT,MID+1,en);
    segMax[node] = max(segMax[LT],segMax[RT]);
}

void update(int node,int st,int en,int index,int newCost){
    if (st == en){
        segMax[node] = newCost;
        return;
    }

    if (MID >= index) update(LT,st,MID,index,newCost);
    else update(RT,MID+1,en,index,newCost);
    segMax[node] = max(segMax[LT],segMax[RT]);
}

int query(int node,int st,int en,int id1,int id2){
    if (st >= id1 && en <= id2) return segMax[node];
    int ans1 = 0,ans2 = 0;
    if (MID >= id1) ans1 = query(LT,st,MID,id1,id2);
    if (MID+1 <= id2) ans2 = query(RT,MID+1,en,id1,id2);
    return max(ans1,ans2);
}

int query(int id1,int id2){
    if (id1 == id2) return 0;
    int res = query(1,0,N-1,id1+1,id2);
    return res;
}

int getMaxEdge(int a,int b){
    if (H[a] < H[b]) swap(a,b);
    int res = -1;
    while(chainId[a] != chainId[b]){
        int ans = query(posInBase[chainHead[chainId[a]]],posInBase[a]);
        ans = max(ans,headCost[chainId[a]]);
        res = max(res,ans);
        a = P[0][chainHead[chainId[a]]];
    }

    int ans = query(posInBase[b],posInBase[a]);
    res = max(res,ans);
    return res;
}

char str[100];
void solve(){
    memset(head,-1,sizeof(head));
    memset(P,-1,sizeof(P));
    memset(chainHead,-1,sizeof(chainHead));
    memset(chainSize,0,sizeof(chainSize));

    chainNo = totalSize = e = 0;
    scanf("%d",&N);
    assert(N < MAX);
    int a,b,c;
    for(int i = 0; i < N-1; ++i)
        scanf("%d%d%d",&a,&b,&c), addEdge(a,b,c), addEdge(b,a,c), assert(c>=0 && c<= 1000000);

    computeSize(1,-1,0);
    computeParent();
    HLD(1,-1);

    assert(totalSize == N);
    build(1,0,N-1);

    while(scanf("%s",str) and str[0] != 'D'){
        scanf("%d%d",&a,&b);
        if (str[0] == 'C'){
            a = 2*a-1;
            assert(b>=0 && b<= 1000000);
            int x = edge[a].to, y = edge[a].from;
            if (H[x] < H[y]) swap(x,y);
            if (chainId[x] == chainId[y])
                update(1,0,N-1,posInBase[x],b);
            else
                headCost[chainId[x]] = b;
        } else {
            assert(a != b);
            int ancestor = getLCA(a,b);
            int ans = max(getMaxEdge(a,ancestor),getMaxEdge(b,ancestor));
            printf("%d\n",ans);
        }
    }
}

int main()
{
    int t; scanf("%d",&t);
    while(t--) solve();
    return 0;
}
