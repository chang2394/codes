// Link :- (Build machine prefix function part) http://translate.yandex.net/tr-url/ru-en.en/e-maxx.ru/algo/prefix_function 
// Code for SSU 284(Grammer) :- http://acm.sgu.ru/problem.php?contest=0&problem=284
// Not AC (Reason :- http://codeforces.com/blog/entry/13232)

#include <bits/stdc++.h>
using namespace std;

// Uzumaki Naruto :)

#define DEBUG
#ifdef DEBUG
	#define dbg(a) cerr << __LINE__ << ": " << #a << " = " << (a) << endl
	#define dbg_all(a,sz) cerr << "_____ " << #a << " = "; for(LL i = 0; i < sz; ++i) cerr << a[i] << " "; cerr << "\n"
	#define pause() cin.get();cin.get();
#else
	#define dbg(a)
	#define dbg_all(a,sz)
	#define pause()
#endif

typedef unsigned long long LL;
typedef pair<LL,LL> pii;
typedef vector<LL> vi;

const LL NN = 112;
const LL MM = 512;

string msg[NN][MM],pat;
LL Len[NN],N,M;

LL LPS[NN],aut[NN][2];
LL G[NN][NN],K[NN][NN];

/*
   G[i][j] -> next state if cur state i and string j encountered (state = match)
   K[i][j] -> no of matches found if state = i, and string = j encountered
*/

bool alpha(string ch){ return (ch.size() <= 1 and (ch[0] == 'a' or ch[0] == 'b')); }
LL conv(char x){
    if (x == 'a' or x == 'b') return (LL)(x-'a');
    return (LL)(x-'0');
}

LL conv(string x){
    if (alpha(x))
        return conv(x[0]);
    LL ans = 0;
    for(LL i = 0; i < (LL)x.size(); ++i)
        ans = ans*10 + conv(x[i]);
    assert(ans >= 1 and ans <= N);
    return ans;
}

void build_kmp(LL n){
    LL k = LPS[0] = 0;
    for(LL i = 1; i < n; ++i){
        while(k > 0 and pat[k] != pat[i])
            k = LPS[k-1];
        LPS[i] = (k += (pat[k] == pat[i]));
    }
}

void build_aut(LL n){
    for(LL i = 0; i <= n; ++i) for(LL k = 0; k < 2; ++k){
        if (i > 0 and k != conv(pat[i]))
            aut[i][k] = aut[LPS[i-1]][k];
        else
            aut[i][k] = i + (k == conv(pat[i]));
    }
}

void build_nxt(LL n,LL m){
    for(LL i = 1; i <= n; ++i) for(LL j = 0; j <= m; ++j){
        LL ans = j, cnt = 0;
        for(LL k = 0; k < Len[i]; ++k){
            LL inp = conv(msg[i][k]);
            if (alpha(msg[i][k])){
                ans = aut[ans][inp];
                cnt += (ans == m);
            } else {
                cnt += K[ans][inp];
                ans = G[ans][inp];
            }
        }
        G[j][i] = ans, K[j][i] = cnt;
    }
}

void solve(){
    cin >> N >> pat;
    M = (LL)(pat.size());
    pat.push_back('$');

    for(LL i = 1; i <= N; ++i){
        cin >> Len[i];
        for(LL j = 0; j < Len[i]; ++j)
            cin >> msg[i][j];
    }

    build_kmp(M);
    build_aut(M);
    build_nxt(N,M);
    cout << K[0][N] << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
