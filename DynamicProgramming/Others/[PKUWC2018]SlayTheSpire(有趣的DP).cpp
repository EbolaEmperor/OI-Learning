#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=3010;
int C[N][N];
int mul[N],add[N];
int f[N][N],g[N][N];
int n,m,k;

// f(i,j) : 用了i张加强卡，最后一张是第j大的，此时的所有方案加强的倍数之和
// g(i,j) : 用了i张攻击卡，最后一张是第j大的，此时的所有方案造成的伤害之和
// F(i,j) : 选了i张加强卡，用了j张，此时所有方案加强的倍数之和。F(i,j)=sum(k=1~n){f(j,k)*C(n-k,i-j)}
// G(i,j) : 选了i张攻击卡，用了j张，此时所有方案造成的伤害之和。G(i,j)=sum(k=1~n){g(j,k)*C(n-k,i-j)}

int F(int x,int y)
{
    int res=0;
    if(y==0) return C[n][x];
    for(int i=1;i<=n;i++)
        res=(res+1ll*f[y][i]*C[n-i][x-y])%ha;
    return res;
}

int G(int x,int y)
{
    int res=0;
    for(int i=1;i<=n;i++)
        res=(res+1ll*g[y][i]*C[n-i][x-y])%ha;
    return res;
}

int gao()
{
    f[0][0]=1;
    static int sumf[N],sumg[N];
    for(int i=1;i<=m;i++)
    {
        sumf[0]=f[i-1][0];
        sumg[0]=g[i-1][0];
        for(int j=1;j<=n;j++)
        {
            sumf[j]=(sumf[j-1]+f[i-1][j])%ha;
            sumg[j]=(sumg[j-1]+g[i-1][j])%ha;
        }
        for(int j=1;j<i;j++) f[i][j]=g[i][j]=0;
        for(int j=i;j<=n;j++)
        {
            f[i][j]=1ll*mul[j]*sumf[j-1]%ha;
            g[i][j]=(1ll*add[j]*C[j-1][i-1]+sumg[j-1])%ha;
        }
    }
    int ans=0;
    for(int i=0;i<k;i++)
        ans=(ans+1ll*F(i,i)*G(m-i,k-i))%ha;
    for(int i=k;i<=m;i++)
        ans=(ans+1ll*F(i,k-1)*G(m-i,1))%ha;
    return ans;
}

int main()
{
    for(int i=0;i<=3000;i++)
    {
        C[i][0]=1;
        for(int j=1;j<=i;j++)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%ha;
    }
    int T;
    for(scanf("%d",&T);T;T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=n;i++) scanf("%d",mul+i);
        for(int i=1;i<=n;i++) scanf("%d",add+i);
        sort(mul+1,mul+1+n);reverse(mul+1,mul+1+n);
        sort(add+1,add+1+n);reverse(add+1,add+1+n);
        printf("%d\n",gao());
    }
    return 0;
}