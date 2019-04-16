#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

const int ha=998244353,N=15;
int n,k,e[N][N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

namespace Task1
{
    int main()
    {
        int m=n*(n-1),ans=0;
        for(int s=0;s<=(1<<m);s++)
        {
            static bool g[5][5];
            memset(g,0,sizeof(g));
            int psb=1,cnt=0;
            for(int i=0;i<n;i++)
                for(int j=0;j<n;j++)
                    if(i!=j)
                    {
                        if(s>>cnt&1) psb=1ll*psb*e[i][j]%ha,g[i][j]=1;
                        else psb=1ll*psb*(1-e[i][j]+ha)%ha;
                        cnt++;
                    }
            static int dis[5];
            static bool vis[5];
            memset(vis,0,sizeof(vis));
            memset(dis,0x3f,sizeof(dis));
            queue<int> q;
            q.push(0);vis[0]=1;dis[0]=0;
            while(!q.empty())
            {
                int u=q.front();q.pop();
                for(int v=0;v<n;v++)
                    if(g[u][v]&&!vis[v])
                        dis[v]=dis[u]+1,vis[v]=1,q.push(v);
            }
            bool flag=1;
            for(int i=0;i<n;i++)
                if(dis[i]>k) flag=0;
            if(flag) ans=(ans+psb)%ha;
        }
        printf("%d\n",ans);
        return 0;
    }
}

namespace Task2
{
    int main()
    {
        int ans=1;
        for(int i=1;i<n;i++)
            ans=1ll*ans*e[0][i]%ha;
        printf("%d\n",ans);
        return 0;
    }
}

int main()
{
    freopen("graph_example_1.in","r",stdin);
    n=read();k=read();
    for(int i=1;i<=n*(n-1);i++)
    {
        static int u,v,p,q;
        u=read()-1;v=read()-1;p=read();q=read();
        e[u][v]=1ll*p*Pow(q,ha-2)%ha;
    }
    if(k==1) return Task2::main();
    else return Task1::main();
}
