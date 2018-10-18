#include<bits/stdc++.h>
#define ha 1000000007
using namespace std;

const int N=2010;
int ch[N][2],n;
bool leaf[N];
int dep[N],sz[N];
int f[N][N];
int pw[N],iv[N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void Init()
{
    pw[0]=1;pw[1]=Pow(2,ha-2);
    for(int i=2;i<=n+1;i++) pw[i]=1ll*pw[i-1]*pw[1]%ha;
    for(int i=1;i<=n+1;i++) iv[i]=Pow((1-pw[i]+ha)%ha,ha-2);
}

void dfs(int u)
{
    if(leaf[u])
    {
        sz[u]=1;
        f[u][0]=Pow(2,dep[u]);
        return;
    }
    dfs(ch[u][0]);dfs(ch[u][1]);
    sz[u]=sz[ch[u][0]]+sz[ch[u][1]];
    dep[u]=min(dep[ch[u][0]],dep[ch[u][1]])-1;
    for(int i=0;i<sz[ch[u][0]];i++)
        for(int j=0;j<sz[ch[u][1]];j++)
            (f[u][i+j+1]+=1ll*f[ch[u][0]][i]*f[ch[u][1]][j]%ha)%=ha;
    for(int i=0;i<sz[u];i++) f[u][i]=1ll*f[u][i]*pw[2]%ha;
    for(int i=1;i<=sz[u];i++)
    {
        f[u][0]=(f[u][0]-1ll*Pow(pw[i],dep[u]+1)*iv[i]%ha*f[u][i]%ha+ha)%ha;
        f[u][i]=1ll*f[u][i]*pw[i]%ha*iv[i]%ha;
    }
}

int main()
{
    int Type;
    scanf("%d",&n);Init();
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&Type);
        if(Type) scanf("%d",dep+i),leaf[i]=1;
        else scanf("%d%d",&ch[i][0],&ch[i][1]);
    }
    dfs(1);
    int ans=0;
    for(int i=sz[1]-1;i>=0;i--)
        ans=(2ll*ans+f[1][i])%ha;
    printf("%d\n",ans);
    return 0;
}