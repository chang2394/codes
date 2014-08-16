#include <bits/stdc++.h>
using namespace std;

//Uzumaki Naruto :)
#define TRACE

#ifdef TRACE
#define trace(a,n)   for(int i = 0; i < n; ++i) cerr << a[i] << " ";cerr << endl;
#define dbg(args...) {debug,args; cerr<<endl;}
#define pause()      cin.get();cin.get();

#else
#define trace(a,n)
#define dbg(args...)
#define pause()

#endif

struct debugger {
    template<typename T> debugger& operator , (const T& v) {
        cerr<<v<<" "; return *this;
    }
} debug;

template <typename T1, typename T2>
inline ostream& operator << (ostream& os, const pair<T1, T2>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}

template<typename T>
inline ostream &operator << (ostream & os,const vector<T>& v) {
    bool first = true; os << "[";
    for (typename vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
        os << *ii; first = false;
    }
    return os << "]";
}

typedef long long LL;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int MM = 1001;
const int NN = MM*MM;

struct node{
    int suff,par,word_no;
    char c;
    map<char,int> go;
    node(){
        suff = -1, par = -1;
        word_no = -1;
    }
};

node trie[NN];
int nodes = 1;
vector<int> same[MM];

void add_str(string &msg,int ind){
    int no = 0;
    for(int i = 0; i < (int)msg.size(); ++i){
        if (!trie[no].go.count(msg[i])){
            trie[nodes].par = no;
            trie[nodes].c = msg[i];
            trie[no].go[msg[i]] = nodes++;
        }
        no = trie[no].go[msg[i]];
    }
    if (trie[no].word_no != -1)
        same[trie[no].word_no].push_back(ind);
    else
        trie[no].word_no = ind;
}

int go(int k,char c);

int getLink(int no){
    if (trie[no].suff != -1)
        return trie[no].suff;
    if (trie[no].par == 0)
        return (trie[no].suff = 0);

    char ch = trie[no].c;
    int p = trie[no].par;
    return (trie[no].suff = go(getLink(p),ch));
}

int go(int no,char ch){
    if (trie[no].go.count(ch) > 0)
        return trie[no].go[ch];
    if (trie[no].par == 0)
        return (trie[no].go[ch] = 0);

    int nxt = getLink(no);
    return (trie[no].go[ch] = go(nxt,ch));
}

void build(){
    queue<int> q;
    q.push(0);
    while(!q.empty()){
        int no = q.front();
        q.pop();
        for(map<char,int> :: iterator it = trie[no].go.begin(); it != trie[no].go.end(); ++it)
            q.push(it->second);
        trie[no].suff = getLink(no);
    }
}

bool is_sub[NN],vis[NN];
void solve(){
    memset(is_sub,false,sizeof(is_sub));
    memset(vis,false,sizeof(vis));

    int k;
    string txt,msg;
    cin >> txt >> k;

    trie[0].par = 0;
    for(int i = 0; i < k; ++i){
        cin >> msg;
        add_str(msg,i);
        is_sub[i] = false;
    }

    build();
    int no = 0;
    queue<int> q;
    for(int i = 0; i < (int)txt.size(); ++i){
        no = go(no,txt[i]);
        q.push(no);
    }

    while(!q.empty()){
        int x = q.front(), y = trie[x].word_no;
        q.pop();

        vis[x] = true;
        if (y != -1) is_sub[y] = true;
        for(int i = 0; y != -1 and i < (int)same[y].size(); ++i)
            is_sub[same[y][i]] = true;
        if (trie[x].suff != -1 and !vis[trie[x].suff])
            q.push(trie[x].suff);
    }

    for(int i = 0; i < k; ++i)
        puts(is_sub[i] ? "y": "n");
    for(int i = 0; i < nodes; ++i)
        trie[i] = node();
    nodes = 1;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}
