//Subset sum 

#include <iostream>
#include <cstdio>
#include <conio.h>
#include <cstring>
#include <algorithm>

using namespace std;

static int dp[1000];

int func(int a[], int n, int k)
{
    int i,j,t;
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for ( i = 0; i < n; i++ ) {
        for ( j = a[i]; j <= k; j++ ) {
            dp[j] += dp[j-a[i]];
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

    getch();
    return 0;
}
