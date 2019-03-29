#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
const int N=100010;
struct OPT{int x1,x2,y1,y2;} opt[N*20];
vector<int> g[N],col[N];
int n,idfn[N],odfn[N],dfc=0,tot=0;
int go[20][N],dep[N];

void dfs(int u,int fa)
{
    for(int k=1;k<=17;k++)
        go[k][u]=go[k-1][go[k-1][u]];
    idfn[u]=++dfc;
    for(int v : g[u])
        if(v!=fa) go[0][v]=u,dep[v]=dep[u]+1,dfs(v,u);
    odfn[u]=dfc;
}

int jump(int x,int y)
{
    for(int k=17;k>=0;k--)
        if(dep[go[k][x]]>dep[y]) x=go[k][x];
    return x;
}

void add(int x,int y)
{
    if(idfn[x]>idfn[y]) swap(x,y);
    if(idfn[y]>=idfn[x]&&idfn[y]<=odfn[x])
    {
        int z=jump(y,x);
        opt[++tot]={1,idfn[z]-1,idfn[y],odfn[y]};
        opt[++tot]={idfn[y],odfn[y],odfn[z]+1,n};
    }
    else opt[++tot]={idfn[x],odfn[x],idfn[y],odfn[y]};
}

struct OPTS{int l,r,x;};
vector<OPTS> opts[N];
int val[N<<4],tag[N<<4];

void update(int o,int l,int r,int nl,int nr,int x)
{
    if(l>=nl&&r<=nr)
    {
        tag[o]+=x;
        val[o]=tag[o]?(r-l+1):(val[o<<1]+val[o<<1|1]);
        return;
    }
    int mid=(l+r)/2;
    if(nl<=mid) update(o<<1,l,mid,nl,nr,x);
    if(nr>mid) update(o<<1|1,mid+1,r,nl,nr,x);
    val[o]=tag[o]?(r-l+1):(val[o<<1]+val[o<<1|1]);
}

LL gao()
{
    LL res=0;
    for(int i=1;i<=tot;i++)
    {
        if(opt[i].y1>opt[i].y2) continue;
        opts[opt[i].x1].push_back({opt[i].y1,opt[i].y2,1});
        opts[opt[i].x2+1].push_back({opt[i].y1,opt[i].y2,-1});
    }
    for(int x=1;x<=n;x++)
    {
        for(auto p : opts[x])
            update(1,1,n,p.l,p.r,p.x);
        res+=val[1];
    }
    return res;
}

int main()
{
    scanf("%d",&n);
    for(int i=1,x;i<=n;i++)
        scanf("%d",&x),col[x].push_back(i);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dep[1]=1;dfs(1,0);
    for(int x=1;x<=n;x++)
        for(int i=0;i<col[x].size();i++)
            for(int j=i+1;j<col[x].size();j++)
                add(col[x][i],col[x][j]);
    LL ans=(LL)n*(n-1)/2-gao()+n;
    printf("%lld\n",ans);
    return 0;
}