#include <bits/stdc++.h>
#define DB(a) cerr << __LINE__ << ": " << #a << " = " << (a) << endl;

using namespace std;
const int MAX = 112345;

int Len[2][MAX],st[2],en[2];
int Max[2],beg[2];
string str,s;

// This code finds the Longest Palindrome
// WARNING :- For odd length, actual length of palindrome with center at i is (Len[1][i] + 1);
// Even -> 0 , Odd -> 1

void solve(){
    getline(cin,s,'\n');
    str = "";

    for(int i = 0; i < s.size(); ++i)
        if (s[i] != '!' and s[i] != ' ') str.push_back(s[i]);
    int N = (int)str.size();

    st[0] = st[1] = 0;
    en[0] = en[1] = -1;
    Max[0] = Max[1] = -1;

    for(int i = 0; i < N; ++i) for(int k = 0,add = 1; k < 2; ++k, add ^= 1){
        int dR = en[k]-i; // Distance of Index from end of the rightmost palindrome
        int sz = (i > en[k] ? 0 : min(dR+add,Len[k][st[k]+dR+add])) + 1;

        while(i+sz-add < N and i-sz >= 0 and str[i+sz-add] == str[i-sz]) ++sz;

        Len[k][i] = --sz;
        if (i+sz-add > en[k])
            en[k] = i+sz-add, st[k] = i-sz;
        if ((2*sz + k) > Max[k])
            Max[k] = 2*sz + k, beg[k] = i-sz;
    }

    int k = (Max[0] > Max[1]) ? 0 : 1;
    cout << str.substr(beg[k],Max[k]) << endl;
}

int main()
{
	ios_base::sync_with_stdio(0);
	solve();
	return 0;
}
