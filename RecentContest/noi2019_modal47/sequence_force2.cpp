// O(n^4)
#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=105;
int f[2][N*N/2][N]; //前i个数的总和是j，第i个数为k的概率，第一维滚动
int n,pre,p[N];

inline void add(int &x,const int &y){x=(x+y>=ha)?(x+y-ha):(x+y);}

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

int main()
{
    scanf("%d",&n);
    int inv=Pow(100,ha-2);
    for(int i=1;i<=n;i++)
        scanf("%d",p+i),p[i]=1ll*p[i]*inv%ha;
    f[pre=0][0][0]=1;
    for(int i=1;i<=n;i++,pre^=1)
    {
        memset(f[pre^1],0,sizeof(f[pre^1]));
        int m=i*(i+1)/2;
        for(int j=0;j<=m;j++)
            for(int k=0;k<=i;k++)
            {
                add(f[pre^1][j+k+1][k+1],1ll*f[pre][j][k]*p[i]%ha);
                add(f[pre^1][j][0],1ll*f[pre][j][k]*(1-p[i]+ha)%ha);
            }
    }
    int m=n*(n+1)/2,ans=0;
    for(int i=0;i<=m;i++)
    {
        int sum=0;
        for(int j=0;j<=n;j++)
            add(sum,f[pre][i][j]);
        add(ans,1ll*sum*i*i%ha);
    }
    printf("%d\n",ans);
    return 0;
}