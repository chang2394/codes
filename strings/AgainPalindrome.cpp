// Code for TIMUS 1354 Palindrome. Again Palindrome
// Complexity -> O(N)
// Algorithm -> Manacher's Algorithm

#include <bits/stdc++.h>
#define DB(a) cerr << __LINE__ << ": " << #a << " = " << (a) << endl;

using namespace std;
const int MAX = 11234;

int Len[2][MAX],L[2],R[2],N;
string str;

void Build(){
    memset(R,-1,sizeof(R));
    memset(L,0,sizeof(L));

    for(int i = 0; i < N; ++i) for(int p = 0; p < 2; ++p){
        int dR = R[p] - i;
        int k = (i < R[p] ? min(dR+!p,Len[p][L[p]+dR+!p]) : 0) + 1;

        while(i+k-!p < N and i-k >= 0 and str[i+k-!p] == str[i-k]) ++k;
        Len[p][i] = --k;
        if (i+k-!p > R[p])
            R[p] = i+k-!p, L[p] = i-k;
    }
}

bool isPalindrome(int st,int en){
    int sz = (en-st+1), p = (sz & 1);
    return (Len[p][st+sz/2] >= sz/2);
}

void solve(){
    cin >> str;
    N = (int)str.size();
    if (N == 1) {
        str += str;
        cout << str << endl;
        return;
    }

    Build();
    int id = 1;
    while(!isPalindrome(id,N-1))
        ++id;
    string add = str.substr(0,id);
    reverse(add.begin(),add.end());
    str += add;
    cout << str << endl;
}

int main()
{
	ios_base::sync_with_stdio(0);
	solve();
	return 0;
}
