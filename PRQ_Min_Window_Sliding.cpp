//LINK to the Problem :- http://www.codechef.com/IGNS2014/problems/IGNUS14A

#include <bits/stdc++.h>
#define INF 1000000000
#define MAX 100005

using namespace std;
typedef pair<int,int> pii;
int n,d;
int money[MAX];

inline void fi(int *a)
{
 register char c=0;
 while (c<33) c=getchar_unlocked();
 *a=0;
 int tmp = 0;
 while (c>33)
 {
     if ( c == 45 ) tmp = 1;
     else *a=*a*10+c-'0';
     c=getchar_unlocked();
 }
 if ( tmp == 1 ) *a = 0-(*a);
}

int main()
{
    int t;
    fi(&t);
    while ( t-- ) {
    	  fi(&n);
    	  fi(&d);
    	  
    	  //Window size is d-1 here ...
    	  int sum = 0;
          for ( int i = 0; i < n; i++ ) {
              fi(&money[i]);
              sum += money[i];
          }
          if ( d == 1 ) {
               printf("%d\n", sum);
               continue;
          }
       
          priority_queue<pii,vector<pii>, greater<pii> > pq;
          pq.push(pii(money[0],0));
        
          int res = money[0];
          for ( int i = 1; i < n; i++ ) {
              if (i < d-1){
                  int ans = money[0] + money[i];
                  res = ans;
                  pq.push(pii(ans,i));
                  continue;     
              }
              while(pq.top().second < i-d)
                  pq.pop();
              int ans = pq.top().first + money[i];
              pq.push(pii(ans,i));
              res = ans;
          }
          printf("%d\n", res);
    }
    return 0;
}
