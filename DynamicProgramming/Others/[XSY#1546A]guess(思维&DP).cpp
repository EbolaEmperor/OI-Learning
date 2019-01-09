#include<bits/stdc++.h>
using namespace std;

const int N=510;
int f[N],g[N][N];
int n,p,pw2[N*N];

int C2(int n){return n*(n-1)/2;}

int main()
{
    scanf("%d%d",&n,&p);
    g[0][0]=pw2[0]=1;
    for(int i=1;i<=n*n;i++)
        pw2[i]=2ll*pw2[i-1]%p;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++)
        {
            g[i][j]=g[i-1][j-1];
            for(int k=0;k<=i-j-1;k++)
                g[i][j]=(g[i][j]+1ll*g[i-k-2][j-1]*pw2[C2(k+1)])%p;
        }
    for(int i=1;i<=n;i++)
    {
        f[i]=pw2[C2(i+1)];
        for(int j=1;j<i;j++)
            f[i]=(f[i]-1ll*f[j]*g[i][j])%p;
    }
    printf("%d\n",(f[n]+p)%p);
    return 0;
}