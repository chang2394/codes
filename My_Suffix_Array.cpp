
// Code by SNIGGA :)
// Complexity - 0(NlogN) -> logN improved with Counting Sort

// LINK :- http://www.codechef.com/MARCH14/problems/SSTORY

#include <bits/stdc++.h>
using namespace std;
#define MAX 512345
#define LOG 20
#define CLEAR(arr,sz) for(int i = 0; i < sz; ++i) arr[i] = 0;
#define DEBUG(arr,sz) for(int i = 0; i < sz; ++i) cout << arr[i] << " "; cout << endl;

string s1,s2,str;
int N1,N2,N;
int od[LOG][MAX],t[MAX][2];
int A[MAX],B[MAX],C[MAX],D[MAX];
int FR[MAX],SE[MAX],ac[MAX];
int ct1 = 0,ct2 = 0;

int STEP,CNT;

// Code for Suffix Array starts here ......
void BuildSA(){
    for(int i = 0; i < N; ++i) A[(int)str[i]] = 1;
    for(int i = 1; i < 200; ++i) A[i] += A[i-1];
    for(int i = 0; i < N; ++i)
        od[0][i] = A[(int)str[i]];

    CLEAR(A,200);
    int stp = 1,cnt = 1;
    for(; cnt/2 < N; cnt <<= 1, ++stp){
        ct1 = ct2 = 0;

        // Code for Counting Sort
        CLEAR(A,N+1); CLEAR(B,N+1);
        for(int i = 0; i < N; ++i)
            ++A[t[i][0] = od[stp-1][i]], ++B[t[i][1] = (i+cnt < N) ? od[stp-1][i+cnt] : 0];

        for(int i = 1; i <= N; ++i)
            A[i] += A[i-1] , B[i] += B[i-1];

        for(int i = N-1; i >= 0; --i)
            C[--B[t[i][1]]] = i;

        for(int i = N-1; i >= 0; --i)
            D[--A[t[C[i]][0]]] = C[i];

        int k = od[stp][D[0]] = 1;
        ac[D[0]] = k;
        if (D[0] < N1) FR[ct1++] = D[0];
        else SE[ct2++] = D[0];

        for(int i = 1; i < N; ++i){
            int id1 = D[i], id2 = D[i-1];
            od[stp][id1] = (k += (t[id2][0] != t[id1][0] || t[id1][1] != t[id2][1]));

            ac[id1] = k;
            if (id1 < N1) FR[ct1++] = id1;
            else SE[ct2++] = id1;
        }
        // D array will contain the indexes of elements in sorted order
    }

    STEP = stp-1, CNT = cnt;
}

int LCP(int x,int y){
    int res = 0;
    for(int stp = STEP, cnt = CNT; stp >= 0; --stp,cnt >>= 1){
        if (x < N && y < N && od[stp][x] == od[stp][y])
            res += cnt, x += cnt, y += cnt;
    }
    return res;
}
// End of Code for Suffix Array ...........

void solve(){
    cin >> s1 >> s2;
    str = s1+s2;
    N1 = s1.size(), N2 = s2.size();
    N = N1+N2;

    BuildSA();
    int i = 0, j = 0;
    int ans = 0, idx = MAX;

    while(i < ct2){
        int v = ac[SE[i]];
        while(j < ct1 && ac[FR[j]] < v) ++j;

        int res = 0;
        if (j != ct1)
            res = max(res,LCP(FR[j],SE[i]));
        if (j != 0)
            res = max(res,LCP(FR[j-1],SE[i]));
        if (res > ans)
            ans = res, idx = SE[i];
        else if (res == ans)
            idx = min(idx,SE[i]);
        ++i;
    }

    if (ans != 0){
        for(int i = 0; i < ans; ++i)
            cout << str[i+idx];
        cout << endl;
    }
    cout << ans << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    solve();
    return 0;
}
