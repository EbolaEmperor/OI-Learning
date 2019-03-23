#include<bits/stdc++.h>
using namespace std;

const int ha=1e9+7;
const int N=310;
int a[N<<1],b[N<<1],c[N<<1];
int f[N<<1][N][N];
int n,fre=0,cnt=0;

inline void add(int &x,const int &y){x=(x+y>=ha)?(x+y-ha):(x+y);}

int fac(int n)
{
    int res=1;
    for(int i=1;i<=n;i++)
        res=1ll*res*i%ha;
    return res;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n*2;i++) scanf("%d",a+i);
    for(int i=1;i<=n;i++)
    {
        if(a[2*i-1]!=-1&&a[2*i]!=-1) b[a[2*i-1]]=b[a[2*i]]=2;
        else if(a[2*i-1]!=-1) b[a[2*i-1]]=1;
        else if(a[2*i]!=-1) b[a[2*i]]=1;
        else fre++;
    }
    for(int i=1;i<=n*2;i++)
        if(b[i]<2) c[++cnt]=b[i];
    f[cnt][0][0]=1;
    for(int i=cnt;i>=1;i--)
        for(int j=0;j<=min(n,cnt-i);j++)
            for(int k=0;k<=min(n,cnt-i);k++)
                if(c[i]==1)
                {
                    add(f[i-1][j+1][k],f[i][j][k]);
                    if(k) add(f[i-1][j][k-1],f[i][j][k]);
                }
                else
                {
                    add(f[i-1][j][k+1],f[i][j][k]);
                    if(j) add(f[i-1][j-1][k],1ll*j*f[i][j][k]%ha);
                    if(k) add(f[i-1][j][k-1],f[i][j][k]);
                }
    int ans=1ll*f[0][0][0]*fac(fre)%ha;
    printf("%d\n",ans);
    return 0;
}