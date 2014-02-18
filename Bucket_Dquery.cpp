//Implementation of spoj DQUERY using BUCKET technique.
// Overall Complexity - O(Nsqrt(N))
// :)

#include <bits/stdc++.h>
using namespace std;
#define MAX1 31234
#define MAX2 1123456
#define SQ 175

struct event{
    int l,r,idx;
    event(){}
    event(int a,int b,int c):l(a),r(b),idx(c){}
} q[212345];

bool operator < (event a,event b){
    if (a.l/SQ != b.l/SQ) return (a.l/SQ < b.l/SQ);
    return (a.r < b.r);
}

int arr[MAX1],N,Q;
int cnt[MAX2],ans = 0;
int res[212345];

void solve(){
    cin >> N;
    for(int i = 1; i <= N; ++i)
        cin >> arr[i];
    cin >> Q;
    for(int i = 0; i < Q; ++i)
        cin >> q[i].l >> q[i].r , q[i].idx = i;
    sort(q,q+Q);
    int i = 0;
    int l = 1, r = 1;
    cnt[arr[1]]++;
    ans++;
    while(i < Q){
        int st = q[i].l , en = q[i].r;
        while(r > en){
            cnt[arr[r]]--;
            ans -= (cnt[arr[r]] == 0);
            --r;
        }
        while(r < en){
            ++r;
            cnt[arr[r]]++;
            ans += (cnt[arr[r]] == 1);
        }
        while(l < st){
            cnt[arr[l]]--;
            ans -= (cnt[arr[l]] == 0);
            ++l;
        }
        while(l > st){
            --l;
            cnt[arr[l]]++;
            ans += (cnt[arr[l]] == 1);
        }
        res[q[i++].idx] = ans;
    }
    for(int i = 0; i < Q; ++i)
        cout << res[i] << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    solve();
    return 0;
}
