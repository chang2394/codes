// Implementedd Manacher's Algorithm using hashing
// Complexity -> O(NlogN)
// Checked on http://acm.timus.ru/problem.aspx?space=1&num=1297

#include <bits/stdc++.h>
using namespace std;
#define debug(arr,sz) for(int i = 0; i < sz; ++i) cerr << arr[i] << " "; cerr << endl;
typedef long long LL;

const LL base = 153LL;
const LL MOD = 1000000009LL;
const int MAX = 112345;

LL Hash[MAX],revHash[MAX],b[MAX];
string s,str;
int N;

// Hash[i] = str[i] * base^0 + str[i+1] * base^1 ..... str[Len-1] * base^(Len-i)
// Get Hash Value of str[i...j]
LL getHash(int i,int j){
    if (i > j) swap(i,j);
    int Len = j-i+1;

    LL ans = (Hash[i] - b[Len]*Hash[j+1])%MOD;
    while(ans < 0) ans += MOD;
    return ans;
}

// Get Hash Value of reverse(str[i....j])
LL getRHash(int i,int j){
    if (i > j) swap(i,j);
    int Len = (j-i+1);

    LL sub = (i == 0) ? 0 : revHash[i-1];
    LL ans = (revHash[j] - b[Len]*sub)%MOD;
    while(ans < 0) ans += MOD;
    return ans;
}

//Checking whether a Palindrome of size Len can be constructed with id as Median
bool Check(int id,int Len){
    if (Len <= 1) return true;
    LL mid = Len/2;
    int st1 = id - (Len & 1), st2 = id+1;
    int en1 = st1 - mid + 1, en2 = st2 + mid - 1;

    if (en1 < 0 or en2 >= N) return false;
    LL ans1 = getRHash(en1,st1), ans2 = getHash(st2,en2);
    return (ans1 == ans2);
}

void solve()
{
    getline(cin,s,'\n');
    str = "";

    for(int i = 0; i < s.size(); ++i)
        if (s[i] != '!' and s[i] != ' ') str.push_back(s[i]);
    N = (int)str.size();

    // Computing Forward Hash Array
    b[0] = 1,b[1] = base;
    Hash[N-1] = (LL)(str[N-1]);
    for(int i = N-2; i >= 0; --i)
        Hash[i] = ((LL)(str[i]) + base*Hash[i+1])%MOD, b[N-i] = (base*b[N-i-1])%MOD;

    // Computing Reverse Hash Array
    revHash[0] = (LL)(str[0]);
    for(int i = 1; i < N; ++i)
        revHash[i] = ((LL)(str[i]) + base*revHash[i-1])%MOD;

    int Max = 0, st;
    for(int i = 0; i < N; ++i){
        // (k == 0) -> Even length Palindrome
        // (k == 1) -> Odd Length Palindrome
        for(int k = 0; k < 2; ++k){
            int lo = 0, hi = N/2;
            while(lo < hi){
                int mid = ((hi+lo) >> 1) + 1;
                int sz = 2*mid + k;

                if (Check(i,sz))
                    lo = mid;
                else hi = mid - 1;
            }

            int Len = 2*lo + k;
            if (Len > Max) Max = Len , st = i - lo + (k == 0);
        }
    }
    cout << str.substr(st,Max) << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    solve();
    return 0;
}
