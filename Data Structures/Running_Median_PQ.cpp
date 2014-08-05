//Code for spoj Running Median Again
//LINK :- http://www.spoj.com/problems/RMID2/
//Code By SNIGGA :)

#include <bits/stdc++.h>
using namespace std;

void solve(){
    priority_queue<int> mxq;
    priority_queue<int, vector<int>, greater<int> > mnq;
    int num,ct = 0;
    while(scanf("%d",&num) && num != 0){
        if (num == -1){
            int res = mxq.top();
            mxq.pop();
            if (!(ct & 1))
                mxq.push(mnq.top()), mnq.pop();
            --ct;
            printf("%d\n",res);
            continue;
        }
        int res; ct++;
        if ((ct & 1) && !mnq.empty())
            res = mnq.top(), mnq.pop(), mxq.push(min(res,num)), mnq.push(max(res,num));
        else if (ct & 1)
            mxq.push(num);
        else if (num < mxq.top())
            mnq.push(mxq.top()), mxq.pop(), mxq.push(num);
        else
            mnq.push(num);
    }
}

int main()
{
    //ios_base::sync_with_stdio(0);
    int t;scanf("%d",&t);
    while(t--) { solve(); }
    return 0;
}
