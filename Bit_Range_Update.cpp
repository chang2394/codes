//BIT - RANGE UPDATION
//Code created by Mr.BLACK :)
//Link -> http://zobayer.blogspot.in/2013/11/various-usage-of-bit.html
//Code for spoj HORRIBLE

//SUM array is the value with which we have to multiply the index.
//T stores the value which we have to subtract from the SUM value to get
//   the final value.
// For each range update [a,b] with value V update (a,V) and (b+1,-V) in SUM
//    and in T update (a,V*(a-1)) and (b+1,-V*b)
// To find result for range(0,x) , res = querySUM(x)*x - queryT(x);

#include <bits/stdc++.h>
using namespace std;
#define MAX 112345
typedef long long LL;

LL SUM[MAX],T[MAX],v;
int N,K,a,b,q;

void update(int idx,LL val,int k){
    for(;idx <= N; idx += idx & -idx)
        if (k == 0) SUM[idx] += val;
        else T[idx] += val;
}

LL query(int idx,int k){
    LL res = 0;
    for(; idx > 0; idx -= idx & -idx)
        if (k == 0) res += SUM[idx];
        else res += T[idx];
    return res;
}

void range_update(int id1,int id2,LL val){
    update(id1,val,0);
    update(id2+1,-val,0);

    LL v1 = val*((LL)(id1-1)), v2 = val*((LL)id2);
    update(id1,v1,1);
    update(id2+1,-v2,1);
}

LL range_query(int id1,int id2){
    LL v1 = (query(id1-1,0)*(LL)(id1-1)) - query(id1-1,1);
    LL v2 = (query(id2,0)*(LL)(id2)) - query(id2,1);
    return (v2-v1);
}

void solve(){
    memset(SUM,0,sizeof(SUM));
    memset(T,0,sizeof(T));
    cin >> N >> K;
    while(K--){
        cin >> q >> a >> b;
        if (q == 0)
            cin >> v, range_update(a,b,v);
        else
            cout << range_query(a,b) << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    int t;cin >> t;
    while(t--) { solve(); }
    return 0;
}
