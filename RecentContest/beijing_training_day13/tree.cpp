#include<bits/stdc++.h>
using namespace std;

const int ha=998244353,N=100010;
int mark[N],phi[N],mu[N],prm[N],tot;
struct Edge{int v,w,nxt;} e[N];
int h[N],esum;
vector<int> g[N];
int anc[20][N],dep[N];
int dfn[N],dfc;
int n,f[N],inv[N],sum[N],alls,res;

void seive(int n)
{
    phi[1]=mu[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!mark[i]) prm[++tot]=i,phi[i]=i-1,mu[i]=-1;
        for(int j=1;j<=tot&&i*prm[j]<=n;j++)
        {
            mark[i*prm[j]]=1;
            if(i%prm[j]) phi[i*prm[j]]=phi[i]*phi[prm[j]],mu[i*prm[j]]=-mu[i];
            else{phi[i*prm[j]]=phi[i]*prm[j];break;}
        }
    }
}

void dfs(int u,int fa)
{
    dfn[u]=++dfc;
    for(int k=1;k<=17;k++)
        anc[k][u]=anc[k-1][anc[k-1][u]];
    for(int v : g[u])
    {
        if(v==fa) continue;
        dep[v]=dep[u]+1;
        anc[0][v]=u;
        dfs(v,u);
    }
}

int lca(int x,int y)
{
    if(dep[x]<dep[y]) swap(x,y);
    for(int k=17;k>=0;k--)
        if(dep[anc[k][x]]>=dep[y])
            x=anc[k][x];
    if(x==y) return x;
    for(int k=17;k>=0;k--)
        if(anc[k][x]!=anc[k][y])
            x=anc[k][x],y=anc[k][y];
    return anc[0][x];
}

void add_edge(int u,int v)
{
    e[++esum].v=v;
    e[esum].w=dep[v]-dep[u];
    e[esum].nxt=h[u];
    h[u]=esum;
}

void dfs(int u)
{
    for(int i=h[u];i;i=e[i].nxt)
    {
        int v=e[i].v,w=e[i].w;dfs(v);
        res=(res+1ll*w*sum[v]%ha*(alls-sum[v]))%ha;
        sum[u]=(sum[u]+sum[v])%ha;
    }
}

void gao(int x)
{
    static int a[N],stk[N],vtx[N];
    static bool chs[N];
    int tot=0,top=0,all=0;
    for(int i=1;i<=n/x;i++)
    {
        vtx[++all]=a[++tot]=i*x;
        alls=(alls+phi[i*x])%ha;
        sum[i*x]=phi[i*x];
        chs[i*x]=1;
    }
    sort(a+1,a+1+tot,[](int x,int y){return dfn[x]<dfn[y];});
    for(int i=1;i<=tot;i++)
        if(!top) stk[++top]=a[i];
        else
        {
            int f=lca(a[i],stk[top]);
            if(!chs[f]) vtx[++all]=f,chs[f]=1;
            while(dep[stk[top]]>dep[f])
            {
                if(dep[f]>=dep[stk[top-1]])
                {
                    add_edge(f,stk[top--]);
                    if(f!=stk[top]) stk[++top]=f;
                    break;
                }
                add_edge(stk[top-1],stk[top]);top--;
            }
            if(a[i]!=stk[top]) stk[++top]=a[i];
        }
    while(top>1) add_edge(stk[top-1],stk[top]),top--;
    dfs(stk[top]);
    f[x]=(res+ha)%ha;
    for(int i=1;i<=all;i++)
        h[vtx[i]]=0,chs[vtx[i]]=0,sum[vtx[i]]=0;
    alls=res=esum=0;
}

int main()
{
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    seive(n);dep[1]=1;dfs(1,0);
    for(int i=1;i<=n;i++) gao(i);
    int ans=0;inv[1]=1;
    for(int i=2;i<=n;i++)
        inv[i]=1ll*(ha-ha/i)*inv[ha%i]%ha;
    for(int d=1;d<=n;d++)
    {
        int tmp=0;
        for(int k=1;k<=n/d;k++)
            tmp=(tmp+mu[k]*f[d*k])%ha;
        ans=(ans+1ll*d*inv[phi[d]]%ha*tmp)%ha;
    }
    ans=(ans<<1)%ha;
    printf("%d\n",ans);
    return 0;
}
