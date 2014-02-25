
//LINK :- http://www.codechef.com/IGNS2014/problems/IGNUS14A
//STILL TO SUBMIT 

#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

void solve(){
    int N,D,num,res;
    cin >> N >> D;
    deque<pii> dq;

    for(int i = 0; i < N; ++i){
        cin >> num;
        res = num;
        while(!dq.empty() && dq.front().second < i-D)
            dq.pop_front();
        res += (dq.empty()) ? 0 : dq.front().first;
        while(!dq.empty() && dq.back().first > res)
            dq.pop_back();
        dq.push_back(pii(res,i));
    }
    cout << res << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--) { solve(); }
    return 0;
}
