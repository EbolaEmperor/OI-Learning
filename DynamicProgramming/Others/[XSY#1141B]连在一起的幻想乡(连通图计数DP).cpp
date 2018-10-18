#include<bits/stdc++.h>
using namespace std;

const int N=2010;
int C[N][N],n,p;
int g0[N],g1[N],g2[N];
int f0[N],f1[N],f2[N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%p)
        if(b&1) ans=1ll*ans*a%p;
    return ans;
}

int main()
{
    cin>>n>>p;
    for(int i=0;i<=n;i++)
    {
        C[i][0]=1;
        for(int j=1;j<=i;j++)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%p;
    }
    g0[0]=g0[1]=1;
    for(int i=2;i<=n;i++)
    {
        int m=i*(i-1)/2;
        g0[i]=Pow(2,m);
        g1[i]=1ll*m*Pow(2,m-1)%p;
        for(int j=0;j<i;j++)
            g2[i]=(g2[i]+1ll*C[i-1][j]*(g2[i-1]+2ll*j*g1[i-1]%p+1ll*j*j*g0[i-1]%p))%p;
    }
    f0[0]=f0[1]=1;
    for(int i=2;i<=n;i++)
    {
        f0[i]=g0[i];f1[i]=g1[i];f2[i]=g2[i];
        for(int j=1;j<i;j++)
        {
            f0[i]=(f0[i]-1ll*C[i-1][j-1]*f0[j]%p*g0[i-j]%p+p)%p;
            f1[i]=(f1[i]-1ll*C[i-1][j-1]*(1ll*f0[j]*g1[i-j]%p+1ll*f1[j]*g0[i-j]%p)%p+p)%p;
            f2[i]=(f2[i]-1ll*C[i-1][j-1]*(1ll*f2[j]*g0[i-j]%p+2ll*f1[j]*g1[i-j]%p+1ll*f0[j]*g2[i-j]%p)%p+p)%p;
        }
    }
    cout<<f2[n]<<endl;
    return 0;
}