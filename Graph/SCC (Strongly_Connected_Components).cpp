//Author : SNIGGA :)
//Code for Strongly Connected Components
//Algorithm : Kosaraju’s algorithm
//Complexity : 0(V+E)
//Checked on Problem : http://codeforces.com/contest/402/problem/E

#include <bits/stdc++.h>
using namespace std;
const int V = 2000;
const int E = V*V;

struct edge
{
    int to,next;
} Edge[E], invEdge[E];

int Head[V],e;
int invHead[V],ie;

int g[V][V],N;
bool vis[V];

stack<int> order;
// This stack stores the elemets in order of dfs traversal so that we can later use
// it to find the sink vertex(leaf nodes) and construct our SCC's from there

void init(){
    e = ie = 0;
    memset(Head,-1,sizeof(Head));
    memset(invHead,-1,sizeof(invHead));
    memset(vis,false,sizeof(vis));
}

void addEdge(int a,int b){
    Edge[e].to = b;
    Edge[e].next = Head[a];
    Head[a] = e++;

    //For adding reverse edge
    invEdge[ie].to = a;
    invEdge[ie].next = invHead[b];
    invHead[b] = ie++;
}

void dfs1(int st){
    //This dfs is used to find the order of vertices
    vis[st] = true;
    for(int i = Head[st]; i != -1; i = Edge[i].next){
        int to = Edge[i].to;
        if (vis[to]) continue;
        dfs1(to);
    }
    order.push(st);
}

void dfs2(int st){
    //This dfs is to mark all the elements correspoding to a SCC
    vis[st] = true;
    for(int i = invHead[st]; i != -1; i = invEdge[i].next){
        int to = invEdge[i].to;
        if (vis[to]) continue;
        dfs2(to);
    }
}

void solve(){
    init();
    int num;
    cin >> N;
    for(int i = 0; i < N; ++i) for(int j = 0; j < N; ++j)
        if (cin >> num && num != 0)
            addEdge(i,j);

    for(int i = 0; i < N; ++i)
        if (!vis[i]) dfs1(i);

    memset(vis,false,sizeof(vis));
    int res = 0;
    while(!order.empty()){
        int st = order.top(); order.pop();
        if (vis[st]) continue;
        dfs2(st);
        ++res; // Final value of res sotres the total no of SCC's
    }

    puts((res == 1)?"YES":"NO");
}

int main()
{
    ios_base::sync_with_stdio(0);
    solve();
    return 0;
}
