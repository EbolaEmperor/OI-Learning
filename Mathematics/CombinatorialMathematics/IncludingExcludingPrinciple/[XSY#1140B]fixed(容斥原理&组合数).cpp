#include<bits/stdc++.h>
#define ha 1000000007
using namespace std;

const int N=3010;
int C[N][N],n,m;
int g[N],f[N],h[N];
int pm[N*N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

int main()
{
    cin>>n>>m;
    if(n==1&&m==1){puts("0");return 0;}
    else if(n==1&&m==2){puts("1");return 0;}
    for(int i=0;i<=n;i++)
    {
        C[i][0]=1;
        for(int j=1;j<=i;j++)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%ha;
    }
    pm[0]=1;
    for(int i=1;i<=n*n;i++) pm[i]=1ll*pm[i-1]*m%ha;
    for(int i=1;i<=n;i++) h[i]=pm[i*(i-1)];
    g[1]=f[1]=1;
    for(int i=2;i<=n;i++)
    {
        g[i]=h[i];
        for(int j=1;j<i;j++)
            g[i]=(g[i]-1ll*C[i][j]*pm[j*(i-j)]%ha*h[i-j]%ha*g[j]%ha+ha)%ha;
        f[i]=g[i];
        for(int j=1;j<i;j++)
            f[i]=(f[i]+1ll*C[i-1][j-1]*f[j]%ha*g[i-j])%ha;
    }
    int ans=1ll*(h[n]-f[n]+ha)*pm[n]%ha;
    cout<<ans<<endl;
    return 0;
}