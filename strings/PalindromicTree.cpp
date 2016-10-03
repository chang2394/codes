/**
 * Problem : http://www.spoj.com/problems/NUMOFPAL/
 * Reference : http://adilet.org/blog/25-09-14/
 * Complexity : O(n)
 */

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
                          ä½ç¥ä¿ä½             æ°¸æ BUG
**/

#include <cstdio>
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

#define INF 1000000007
typedef long long ll;
typedef vector<int> vi;
typedef vector<double> vd;
typedef vector<ll> vll;
typedef vector<vector<int> > vvi;
typedef pair<int, int> ii;
typedef vector<pair<int, int> > vii;
typedef vector<vector<pair<int, int> > > vvii;


#define TRACE

#ifdef TRACE
template<class T, class U>
ostream& operator<<(ostream& out, const pair<T, U>& a) {out << "[" << a.first << " " << a.second << "]"; return out;}
template<class T>
ostream& operator<<(ostream& out, const vector<T>& a) {out << "[ "; for (auto &it : a)out << it << " "; out << "]"; return out;}
template<class T>
ostream& operator<<(ostream& out, const set<T>& a) {out << "[ "; for (auto &it : a)out << it << " "; out << "]"; return out;}
template<class T>
ostream& operator<<(ostream& out, const multiset<T>& a) {out << "[ "; for (auto &it : a)out << it << " "; out << "]"; return out;}
template<class T, class U>
ostream& operator<<(ostream& out, const map<T, U>& a) {for (auto &it : a)out << it.first << " -> " << it.second << " | "; return out;}
template<class T, class U>
ostream& operator<<(ostream& out, const multimap<T, U>& a) {for (auto &it : a)out << it.first << " -> " << it.second << " | "; return out;}
#define pra(a,n) cerr<<#a<<" : ";for(int i=0;i<n;++i)cerr<<a[i]<<" ";cerr<<endl;
#define praa(a,n,m) cerr<<#a<<" : "<<endl;for(int i=0;i<n;++i){for(int j=0;j<m;++j)cerr<<a[i][j]<<" ";cerr<<endl;}
#define pr(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1) {
	cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args) {
	const char* comma = strchr(names + 1, ','); cerr.write(names, comma - names) << " : " << arg1 << " | "; __f(comma + 1, args...);
}
#else
#define pr(...)
#define pra(a,n)
#define praa(a,n,m)
#endif

#define all(x) (x).begin(), (x).end()
#define nall(x) (x).rbegin(), (x).rend()
#define sz(a) int((a).size())
#define boost ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define pb push_back
#define rz resize
#define mp make_pair
#define F first
#define S second
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define NFOR(i,a,b) for(int i=(a);i>=(b);--i)
#define TCASE int __T;cin>>__T;FOR(Tc,1,__T)
#define ass(n,l,r) assert(n>=l and n<=r)
inline int add(int a, int b, int m = INF) {a += b; if (a >= m)a -= m; return a;}
inline int mul(int a, int b, int m = INF) {return (int)(((ll)a * (ll)b) % m);}
inline int scan() {int x; scanf("%d",&x); return x;}

int dx[] {-1, 0, 1, 0, 1, 1, -1, -1};
int dy[] {0, -1, 0, 1, 1, -1, 1, -1};

const double PI  = 3.14159265358979323846L;
const int oo  = numeric_limits<int>::max() / 2 - 10;
const double eps = 1e-6;
const int mod = 1000000007;

const int ND = 112345;
const int MD = 26;

int len[ND], link[ND], to[ND][MD];
int last, nodes;

int cnt[ND]; // keeping count of distinct linked palindromes
string msg;

void init(){
  len[0] = -1, len[1] = 0;
  link[0] = link[1] = 0;
  last = 1, nodes = 2;
}

int get_link(int i,int u){
  while(msg[i-len[u]-1] != msg[i])
    u = link[u];
  return u;
}

void add_letter(int i,char ch){
  last = get_link(i,last);
  int d = (int)(ch-'a');

  if (to[last][d]){
    last = to[last][d];
    return;
  }

  int no = nodes++;
  len[no] = len[last] + 2;
  to[last][d] = no;

  if (len[no] == 1) 
    link[no] = 1;
  else 
    link[no] = to[get_link(i,link[last])][d];

  last = to[last][d];
  cnt[last] = 1 + cnt[link[last]];
}

void solve(){
  cin >> msg;
  int n = sz(msg);
  int ans = 0;

  init();
  for(int i = 0; i < n; ++i){
    add_letter(i,msg[i]);
    ans += cnt[last];
  }

  cout << ans << "\n";
}

int main() {
  solve();
  return 0;
}
