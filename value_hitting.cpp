//Subset sum

#include <iostream>
#include <cstdio>
#include <conio.h>
#include <cstring>

using namespace std;



int func(int a[], int n, int k)
{
    int sum = 0,i,j;
    for ( i = 0; i < n; i++ ) {
        sum += a[i];
    }
    int dp[sum+10];
    for ( i = 1; i <= sum+10; i++ ) dp[i] = 0;
    dp[0] = 1;
    
    for ( i = 0; i < n; i++ ) {
        for ( j = sum; j >= a[i]; j-- ) {
            dp[j] |= dp[j-a[i]];
        }
    }
    
    return dp[k];        
    
}
    

int main()
{
    int n,k,a[100000],i;
    
    scanf("%d%d", &n, &k);
    
    for ( i = 0; i < n; i++ ) scanf("%d", &a[i]);

    // to determine if amy subset can be hit to give a value of K
        
    printf("%d\n", func(a,n,k));
    
    return 0;
    getch();
}
