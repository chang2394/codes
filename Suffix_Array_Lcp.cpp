// LINK :- http://codeforces.com/contest/128/submission/867117

#pragma warning(disable:4786)
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<functional>
#include<string>
#include<cstring>
#include<cstdlib>
#include<queue>
#include<utility>
#include<fstream>
#include<sstream>
#include<cmath>
#include<stack>
#include<cstdio>
#include<cassert>


using namespace std;

#define MEM(a,b) memset(a,(b),sizeof(a))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b)  ((a) < (b) ? (a) : (b))
#define istr(S) istringstream sin(S)
#define MP make_pair
#define pb push_back
#define inf 1000000000

typedef pair<int,int> pi;
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<double> vd;
typedef vector<pi> vpi;

#define inf 1000000000

//typedef long long  LL;
typedef __int64 LL;

#define MAXN 100005
#define MAXLG 19


char S[2*MAXN];
int N,m,ln=0;
int o[MAXLG][2*MAXN], t[2*MAXN][2];
int A[2*MAXN], B[2*MAXN], C[2*MAXN], D[2*MAXN],id[MAXN],lj,ljj;

void build()
{
    int i, j, jj, x, k;

    N=strlen(S);

    S[N] = '\0';

    memset(A, 0, sizeof(A));
    for (i = 0; i < N; ++i) A[(int)S[i]] = 1;
    for (i = 1; i < 300; ++i) A[i] += A[i-1];
    for (i = 0; i < N; ++i) o[0][i] = A[(int)S[i]];

    for (j = 0, jj = 1, k = 0; jj < N ; ++j, jj <<= 1)
    {

        memset(A, 0, sizeof(A));
        memset(B, 0, sizeof(B));

        for (i = 0; i < N; ++i)
            ++A[ t[i][0] = o[j][i] ], ++B[ t[i][1] = (i+jj<N) ? o[j][i+jj] : 0 ];

        for (i = 1; i <= N; ++i)
            A[i] += A[i-1], B[i] += B[i-1];

        for (i = N-1; i >= 0; --i)
            C[--B[t[i][1]]] = i;

        for (i = N-1; i >= 0; --i)
            D[--A[t[C[i]][0]]] = C[i];

        o[j+1][D[0]] = k = 1;
        for (i = 1; i < N; ++i)
            o[j+1][D[i]] = (k += (t[D[i]][0] != t[D[i-1]][0] || t[D[i]][1] != t[D[i-1]][1]));

    }

    lj = j; ljj = jj;   
}

int lcp(int x, int y)
{
    int k,j,jj, prf = 0;
    
    for (j = lj, jj = ljj; j >= 0; --j, jj >>= 1)
        if (x<N && y<N && o[j][x] == o[j][y]) 
        {
            x   += jj;
            y   += jj;
            prf += jj;
        }
    return prf;
}

void check_bf(LL K)
{
    int i,j;
    vector<string> all;
    string s=(string)S;

    for(i=0;i<s.size();i++)
        for(j=1;i+j-1<s.size();j++) all.pb(s.substr(i,j));
            
    sort(all.begin(),all.end());
    printf("%d %s\n",all.size(),all[K-1].c_str());
}

int comm[100005];

int main()
{
    int i,j,k,cs=0,tests;
    LL K;

    
        scanf("%s%I64d",S,&K);

        build();

        for(i=0;i<N;i++)
            id[o[lj][i]]=i;

        LL t=(LL)N*(N+1)/2;
        if(K>t) 
        {
            puts("No such line.");
            return 0;
        }
    
        LL dist=0;

        for(i=2;i<=N;i++)
            comm[i]=lcp(id[i],id[i-1]);

        for(i=1;i<=N;i++)
            dist+=N-id[i]-comm[i];


        LL lo=1,hi=dist;

        int ii=-1,ll=-1;

        while(lo<=hi)
        {
            LL mid=(lo+hi)/2,tot=mid;
            int l=-1,x;

            for(i=1;i<=N;i++)
            {
                int len=N-id[i]-comm[i];
            
                if(tot-len<=0) 
                {
                    x=i;
                    l=comm[i]+tot;
                    break;
                }
                tot-=len;
            }
            

            LL cnt=0;

            for(i=1;i<=N;i++)
            {
                if(i<=x)
                {
                    if(i<x) cnt+=N-id[i];
                    else cnt+=l;
                    continue;
                }

                int lc=lcp(id[i],id[x]);
                int add=MIN(lc,l);
                cnt+=add;
                if(!add) break;
            }

            if(cnt>=K)
                ii=id[x],ll=l,hi=mid-1;
            else
                lo=mid+1;
        }

    

        for(i=0;i<ll;i++)
            printf("%c",S[ii+i]);
        puts("");           

    
    return 0;
}
