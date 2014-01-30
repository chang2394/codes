//Subset sum

#include <iostream>
#include <cstdio>
#include <conio.h>
#include <cstring>
#define INF 1e9

using namespace std;

static int dp[1000];

int func(int a[], int n, int k)
{
      dp[0] = 0;
      int i,j;
      for ( i = 1; i <= k; i++ ) dp[i] = INF;
      for ( i = 1; i <= k; i++ ) {
          for ( j = 0; j < n; j++ ) {
              if ( i-a[j] >= 0 ) dp[i] = min(dp[i], 1 + dp[i-a[j]]);
          }
      }
      
      return dp[k];
}
    

int main()
{
    int n,k,a[100000],i;
    
    scanf("%d%d", &n, &k);
    
    for ( i = 0; i < n; i++ ) scanf("%d", &a[i]);
    
    printf("%d\n", func(a,n,k));
    
    return 0;
    getch();
}
