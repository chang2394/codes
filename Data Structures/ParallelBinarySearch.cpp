/**
                                    _ooOoo_
                                   o8888888o
                                   88" . "88
                                   (| -_- |)
                                    O\ = /O
                                ____/`---'\____
                              .   ' \\| |// `.
                               / \\||| : |||// \
                             / _||||| -:- |||||- \
                               | | \\\ - /// | |
                             | \_| ''\---/'' | |
                              \ .-\__ `-` ___/-. /
                           ___`. .' /--.--\ `. . __
                        ."" '< `.___\_<|>_/___.' >'"".
                       | | : `- \`.;`\ _ /`;.`/ - ` : | |
                         \ \ `-. \_ __\ /__ _/ .-` / /
                 ======`-.____`-.___\_____/___.-`____.-'======
                                    `=---='
                 .............................................
                          佛祖保佑             永无BUG
**/

/**
    Problem: https://www.hackerrank.com/contests/may-world-codesprint/challenges/davaro-and-travelling
    Algorithm: Parallel Binary Search + DSU 
    Reference: http://codeforces.com/blog/entry/45578 
**/

#define LOCAL
#ifdef LOCAL
#   define TRACE
#else
#   define NDEBUG
#endif

#include <cstdio>
#include <sstream>
#include <iostream>
#include <cassert>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cstring>
#include <bitset>
#include <deque>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>
#include <cmath>

using namespace std;

/* aliases */
using vi  = vector<int>;
using pi  = pair<int, int>;
using vs  = vector<string>;
using vpi = vector<pi>;
using ll  = long long int;

/* shortcut macros */
#define mp              make_pair
#define fi              first
#define se              second
#define mt              make_tuple
#define gt(t, i)        get<i>(t)
#define all(x)          (x).begin(), (x).end()
#define ini(a, v)       memset(a, v, sizeof(a))
#define re(i, s, n)     for(auto i = s, _##i = (n); i < _##i; ++i)
#define rep(i, s, n)    re(i, s, (n) + 1)
#define fo(i, n)        re(i, 0, n)
#define si(x)           (int)(x.size())
#define pb              push_back
#define is1(mask,i)     ((mask >> i) & 1)

/* trace macro */
#ifdef TRACE
#   define dbg(a,n)     fo(i,n) cerr << a[i] << " "; cerr << "\n";
#   define trace(v...)  {cerr << __func__ << ":" << __LINE__ << ": " ;_dt(#v, v);}
#else
#   define trace(...)
#   define dbg(a,n)
#endif

#ifdef TRACE
pi _gp(string s) {
    pi r(0, si(s) - 1);
    int p = 0, s1 = 0, s2 = 0, start = 1;
    fo(i, si(s)) {
        int x = (s1 | s2);
        if(s[i] == ' ' && start) {
            ++r.fi;
        } else {
            start = 0;
            if(s[i] == ',' && !p && !x) {
                r.se = i - 1;
                return r;
            }
            if(x && s[i] == '\\') ++i;
            else if(!x && s[i] == '(') ++p;
            else if(!x && s[i] == ')') --p;
            else if(!s2 && s[i] == '\'') s1 ^= 1;
            else if(!s1 && s[i] == '"') s2 ^= 1;
        }
    }
    return r;
}

template<typename H> void _dt(string u, H&& v) {
    pi p = _gp(u);
    cerr << u.substr(p.fi, p.se - p.fi + 1) << " = " << forward<H>(v) << " |" << endl;
}

template<typename H, typename ...T> void _dt(string u, H&& v, T&&... r) {
    pi p = _gp(u);
    cerr << u.substr(p.fi, p.se - p.fi + 1) << " = " << forward<H>(v) << " | ";
    _dt(u.substr(p.se + 2), forward<T>(r)...);
}

template<typename T> 
ostream &operator <<(ostream &o, vector<T> v) { // print a vector
    o << "{";
    fo(i, si(v) - 1) o << v[i] << ", ";
    if(si(v)) o << v.back();
    o << "}";
    return o;
}

template<typename T1, typename T2> 
ostream &operator <<(ostream &o, map<T1, T2> m) { // print a map
    o << "[";
    for(auto &p: m) {
        o << " (" << p.fi << " -> " << p.se << ")";
    }
    o << " ]";
    return o;
}

template <size_t n, typename... T>
typename enable_if<(n >= sizeof...(T))>::type
    print_tuple(ostream&, const tuple<T...>&) {} 

template <size_t n, typename... T>
typename enable_if<(n < sizeof...(T))>::type
    print_tuple(ostream& os, const tuple<T...>& tup) {
    if (n != 0)
        os << ", ";
    os << get<n>(tup);
    print_tuple<n+1>(os, tup);
}

template <typename... T>
ostream& operator<<(ostream& os, const tuple<T...>& tup) { // print a tuple
    os << "(";
    print_tuple<0>(os, tup);
    return os << ")";
}

template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { // print a pair
    return os << "(" << p.fi << ", " << p.se << ")";
}
#endif
    
/* util functions */

template<typename T>
string tostr(T x) {
    ostringstream oss;
    oss << x;
    return oss.str();
}

template<typename T1, typename T2, typename T3>
T1 modpow(T1 a, T2 p, T3 mod) {
    T1 ret = 1;

    a %= mod;
    for(; p > 0; p /= 2) {
        if(p & 1) ret = 1ll * ret * a % mod;
        a = 1ll * a * a % mod;
    }

    return ret;
}

#define x1 _asdfzx1
#define y1 _ysfdzy1

inline int scan(){
	int x;
	scanf("%d",&x);
	return x;
}

int dx[] {-1, 0, 1, 0, 1, 1, -1, -1};
int dy[] {0, -1, 0, 1, 1, -1, 1, -1};

/* constants */
constexpr auto PI  = 3.14159265358979323846L;
constexpr auto oo  = numeric_limits<int>::max() / 2 - 10;
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;

/* code */

const int ND = 1e5+10;
int n1[ND], n2[ND], cost[ND];
int type[ND], crowd[ND], rc[ND];

int qx[ND], qy[ND], qk[ND];
int low[ND], high[ND];
vi edges[ND], tocheck[ND];

int parent[ND], rnk[ND], found[ND];
set<int> raised[ND];

void cleanup(int n){
    for(int i = 0; i < n; ++i){
        parent[i] = i, rnk[i] = 1;
        raised[i].clear();
        raised[i].insert(type[i]);
    }
}

int normalize(int arr[], int a[], int n){
    map<int,int> compress;
    for(int i = 0; i < n; ++i)
        compress[arr[i]] = 1;

    int cnt = 0;
    for(auto it = compress.begin(); it != compress.end(); ++it){
        a[cnt] = it->fi;
        it->se = cnt++;
    }

    for(int i = 0; i < n; ++i)
        arr[i] = compress[arr[i]];
    return cnt;
}

int get(int x){
    if (x != parent[x]) 
        parent[x] = get(parent[x]);
    return parent[x];
}

void join(int x,int y){
    x = get(x), y = get(y);
    if (x == y) return;
    if (rnk[x] > rnk[y]){
        parent[y] = x;
        raised[x].insert(all(raised[y]));
        raised[y].clear();
    } else {
        parent[x] = y;
        raised[y].insert(all(raised[x]));
        raised[x].clear();
    }

    rnk[y] += (rnk[x] == rnk[y]);
}

void parallelBinarySearch(int q,int n,int limit){
    for(int i = 0; i < q; ++i){
        low[i] = 0;
        found[i] = limit;
        high[i] = limit-1;
    }

    bool go = true;
    while(go) {
        go = false;
        cleanup(n);

        for(int i = 0; i < q; ++i){
            if (low[i] > high[i]) continue;
            int mid = (low[i] + high[i])/2;
            tocheck[mid].pb(i);
        }

        for(int i = 0; i < limit; ++i){
            for(auto j : edges[i]){
                int x = n1[j], y = n2[j];
                join(x,y);
            }

            while(si(tocheck[i])){
                go = true;
                int id = tocheck[i].back();
                tocheck[i].pop_back();

                int x = qx[id], y = qy[id];
                int xp = get(x), yp = get(y);

                if (xp == yp and raised[xp].size() >= qk[id]){
                    high[id] = i-1;
                    found[id] = min(found[id],i);
                }
                else 
                    low[id] = i+1;
            }
        }
    }
}

void solve(){
    int n = scan();
    int m = scan();
    int q = scan();

    for(int i = 0; i < n; ++i)
        type[i] = scan();
    for(int i = 0; i < m; ++i){
        n1[i] = scan()-1;
        n2[i] = scan()-1;
        crowd[i] = scan();
    }

    normalize(type,rc,n);
    int limit = normalize(crowd,rc,m);
    rc[limit] = -1;
    for(int i = 0; i < m; ++i)
        edges[crowd[i]].pb(i);

    for(int i = 0; i < q; ++i){
        qx[i] = scan()-1;
        qy[i] = scan()-1;
        qk[i] = scan();
    }

    parallelBinarySearch(q,n,limit);
    for(int i = 0; i < q; ++i)
        printf("%d\n", rc[found[i]]);
}

int main() {
    solve();
    return 0;
}
