// Code for timus 1486
// Link of code :- https://bitbucket.org/deamoon/olymp/src/35d31487cc3a938379c94f3fb076c2bcafd47250/1486/main.cpp?at=master

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

int n, m, a[502][502];
const long long Q1 = 17, Q2 = 23, P = 1000*1000*100;
long long b[502][502];
long long Q1_st[502], Q2_st[502];

struct khash {
    int i;
    int j;
    long long h;
    khash(int i1, int j1, int k1) : i(i1), j(j1), h(k1) {};
};

struct ans {
    int i1, i2;
    int j1, j2;
    int k;
    ans() : k(-1) {};
    ans(int i3, int j3, int i4, int j4, int k1) : i1(i3), j1(j3), k(k1), i2(i4), j2(j4) {};
};

bool myfunction (khash i, khash j) { return (i.h < j.h); }

long long modP(long long c) {
    return ((c % P) + P) % P;
}

long long myPow(long long q, int k) {
    if (q == Q1) {
        return Q1_st[k];
    } else {
        return Q2_st[k];
    }
}

void calcHashPrefix() {
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=m;++j) {
            b[i][j] = modP(modP(b[i-1][j]*Q2) + modP(b[i][j-1]*Q1) - modP(b[i-1][j-1]*modP(Q1*Q2)) + a[i][j]);
        }
    }
}

long long myHash(int i, int j, int k) {
    return modP(b[i+k-1][j+k-1] - modP(b[i-1][j+k-1]*myPow(Q2, k)) - modP(b[i+k-1][j-1]*myPow(Q1, k)) + modP(b[i-1][j-1]*modP(myPow(Q1, k)*myPow(Q2, k))));
}

bool equalT(int k, int i1, int j1, int i2, int j2) {
    for (int i=0;i<k;++i) {
        for (int j=0;j<k;++j) {
            if (a[i1+i][j1+j] != a[i2+i][j2+j]) {
                return false;
            }
        }
    }
    return true;
}

ans calcAnswer(int k) {
    ans res;
    vector<khash> q;
    for (int i=k;i<=n;++i) {
        for (int j=k;j<=m;++j) {
            q.push_back(khash(i-k+1, j-k+1, myHash(i-k+1, j-k+1, k)));
        }
    }

    sort(q.begin(), q.end(), myfunction);

    if (q.size()==1) {
        return res;
    }
    for (int i=1;i<q.size();++i) {
        if (q[i].h == q[i-1].h) {
            if (equalT(k, q[i-1].i, q[i-1].j, q[i].i, q[i].j)) {
                res.k = k; res.i1 = q[i-1].i; res.j1 = q[i-1].j;
                res.i2 = q[i].i; res.j2 = q[i].j;
                return res;
            }
        }
    }
    return res;
}

ans res;

void binSearch(int l, int r) {
    int t = (l+r)/2;
    //printf("%d %d %d\n", l, r, t);
    if (r<l) return;
    ans answer = calcAnswer(t);
    if (answer.k != -1) {
        if (res.k < answer.k) {
            res = answer;
            //printf("++ %d %d %d %d %d\n", res.i1, res.j1, res.i2, res.j2, res.k);
        }
        binSearch(t+1, r);
    } else {
        binSearch(l, t-1);
    }
}

int main() {
    //freopen("1.in", "r", stdin);
    memset(b, 0, sizeof(b));
    char c;

    int t1 = 1, t2 = 1;
    for(int i=0;i<=501;++i) {
        Q1_st[i]=t1; Q2_st[i]=t2;
        t1 = (t1*Q1) % P; t2 = (t2*Q2) % P;
    }

    cin>>n>>m;
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=m;++j) {
            cin>>c;
            a[i][j] = (int) c;
        }
    }
    calcHashPrefix();

    //cout<<myHash(1,1,3)<<"\n";
    //cout<<myHash(3,3,3)<<"\n";

    int k;
    if (n<m) k = n; else k = m;
    binSearch(1, k);

    if (res.k == -1) {
        cout<<"0";
    } else {
        printf("%d\n%d %d\n%d %d", res.k, res.i1, res.j1, res.i2, res.j2);
    }

    return 0;
}



