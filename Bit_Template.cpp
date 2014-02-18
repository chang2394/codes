//This code supports range updation in BIT too :) :)
#include <bits/stdc++.h>
using namespace std;
#define MAX 4123456
typedef long long LL;

class BIT {
    public :
        LL bit[MAX][2];
        void update(int a,LL b,int c);
        LL query(int a,int b);
        void rng_update(int a,int b,LL c);
        LL rng_query(int a,int b);
} X,Y;

void BIT::update(int idx,LL val,int t){
    for(; idx < MAX; idx += idx & -idx)
        bit[idx][t] += val;
}

LL BIT::query(int idx,int t){
    LL res = 0;
    for(; idx > 0; idx -= idx & -idx)
        res += bit[idx][t];
    return res;
}

void BIT::rng_update(int a,int b,LL val){
    update(a,val,0);
    update(b+1,-val,0);

    LL v1 = ((LL)(a-1))*val, v2 = ((LL)b)*val;
    update(a,v1,1);
    update(b+1,-v2,1);
}

LL BIT::rng_query(int a,int b){
    LL res = 0;
    LL v1 = query(a-1,0)*((LL)(a-1)) - query(a-1,1);
    LL v2 = query(b,0)*((LL)b) - query(b,1);
    return (v2-v1);
}
