//Checked on :- http://lightoj.com/volume_showproblem.php?problem=1314

/*
   Input :- abracadabra0AbRa4Cad14abra
   Sorted Suffix :- 11 20 16 21 12 17 14 25 10 15 22 7 0 3 18 5 13 23 8 1 4 19 6 24 9 2
*/

#include <bits/stdc++.h>
using namespace std;

// Uzumaki Naruto :)

#define DB(a) cerr << __LINE__ << ": " << #a << " = " << (a) << endl
#define dbg(A,sz) for(int i = 0; i < sz; ++i) cerr << A[i] << " "; cerr << "\n"
#define reset(A,sz) memset(A,0,sz*sizeof(int))
#define pause() cin.get();cin.get();

typedef long long LL;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int NN = 11234;

/* pos  -> contains suffixes in sorted order
   rank -> contains positon of suffixes in pos
*/

int rank[NN],pos[NN];
int cnt[NN],next[NN];
int height[NN];
bool bh[NN],b2h[NN];

char str[NN];
bool cmp_char(int i,int j){
    return (str[i] < str[j]);
}

void build_sa(int n){
    for(int i = 0; i < n; ++i)
        pos[i] = i;

    sort(pos,pos+n,cmp_char);
    for(int i = 0; i < n; ++i)
        bh[i] = (i == 0 or str[pos[i]] != str[pos[i-1]]), b2h[i] = false;

    for(int h = 1 ; h < n; h <<= 1){
        int buckets = 0;
        for(int i = 0,j; i < n; i = j){
            rank[pos[i]] = i;
            cnt[i] = 0;
            for(j = i+1; j < n and !bh[j]; ++j)
                rank[pos[j]] = i;
            next[i] = j;
            ++buckets;
        }

        if (buckets == n) break;

        cnt[rank[n-h]]++;
        b2h[rank[n-h]] = true;
        for(int i = 0; i < n; i = next[i]){
            for(int j = i; j < next[i]; ++j){
                int s = pos[j]-h;
                if (s < 0) continue;
                int head = rank[s];
                rank[s] = head + cnt[head]++;
                b2h[rank[s]] = true;
            }

            for(int j = i; j < next[i]; ++j){
                int s = pos[j]-h;
                if (s < 0 or !b2h[rank[s]]) continue;
                for(int k = rank[s]+1; !bh[k] and b2h[k]; ++k) b2h[k] = false;
            }
        }

        for(int i = 0; i < n; ++i)
            pos[rank[i]] = i, bh[i] |= b2h[i];
    }

    for(int i = 0; i < n; ++i)
        rank[pos[i]] = i;
}

void getHeight(int n){
    height[0] = 0;
    for(int i = 0, h = 0; i < n; ++i){
        if (rank[i] <= 0) continue;
        int j = pos[rank[i]-1];
        while(i+h < n and j+h < n and str[i+h] == str[j+h]) ++h;
        height[rank[i]] = h;
        h -= (h > 0);
    }
}

int solve(){
    int p,q,n;
    scanf("%s%d%d",str,&p,&q);
    n = (int)strlen(str);

    build_sa(n);
    getHeight(n);

    int ans = 0;
    for(int i = 0; i < n; ++i){
        int x = pos[i], com = height[i];
        int mn = max(com,p-1), mx = min(n-x,q);
        ans += max(0,mx-mn);
    }
    return ans;
}

int main()
{
    //ios_base::sync_with_stdio(0);
    //cin.tie(NULL);
    int t; scanf("%d",&t);
    for(int i = 1; i <= t; ++i)
        printf("Case %d: %d\n",i,solve());
    return 0;
}
