//LINK :- http://www.spoj.com/problems/ARRAYSUB/
//Code By SNIGGA :)

#include <bits/stdc++.h>
using namespace std;
#define MAX 1123456
typedef pair<int,int> pii;
int arr[MAX];

void solve(){
    int N,D,num,res;
    cin >> N;
    deque<pii> dq;

    for(int i = 0; i < N; ++i) cin >> arr[i];
    cin >> D;
    for(int i = 0; i < N; ++i){
        num = arr[i];
        while(!dq.empty() && dq.front().second <= i-D)
            dq.pop_front();
        while(!dq.empty() && dq.back().first < num)
            dq.pop_back();
        dq.push_back(pii(num,i));
        if (i >= D-1)
            cout << dq.front().first << " ";
    }
    cout << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    int t = 1;//; cin >> t;
    while(t--) { solve(); }
    return 0;
}
