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

typedef long long LL;
const int N=120000,B=700;
struct Edge{int to,next;} e[N<<1];
int h[N],etot=0;
vector<int> gg[N],chs;
int n,m,cn,num[N],deg[N];
int idx[N],bvt[B],bn,dis[B][N];
int *prenum[B],*sufnum[B],*chainv[B],sz[B];
LL *prelen[B],*suflen[B];
int L[B],R[B],cid[N],cinid[N];
LL ans=0;

void add_edge(int u,int v)
{
    e[++etot].to=v;
    e[etot].next=h[u];
    h[u]=etot;
}

void gao1()  //Delete the vertex which degree=1
{
    queue<int> q;
    for(int i=1;i<=n;i++)
        if(deg[i]==1) q.push(i);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        if(!deg[u]) continue;
        deg[u]=0;
        for(int v : gg[u])
            if(deg[v])
            {
                deg[v]--;
                ans+=(LL)num[u]*(n-num[u]);
                num[v]+=num[u];num[u]=0;
                if(deg[v]==1) q.push(v);
            }
    }
    for(int u=1;u<=n;u++)
        if(deg[u])for(int v : gg[u])
            if(deg[v]) add_edge(u,v);
}

void gao2()  //Solve the path(u,v) which u is a big vertex
{
    for(int i=1;i<=n;i++)
        if(deg[i]>2) bvt[idx[i]=++bn]=i;
    for(int i=1;i<=bn;i++)
    {
        static int q[N];
        static bool vis[N];
        memset(vis,0,sizeof(bool)*(n+1));
        int *d=::dis[i],s=bvt[i],head=1,tail=0;
        vis[s]=1;q[++tail]=s;
        while(head<=tail)
        {
            int u=q[head++];
            for(int i=h[u];i;i=e[i].next)
            {
                int v=e[i].to;
                if(vis[v]) continue;
                d[v]=d[u]+1;vis[v]=1;q[++tail]=v;
            }
        }
        for(int j=1;j<=n;j++)
            if(!idx[j]) ans+=(LL)num[s]*num[j]*d[j];
            else if(j<s) ans+=(LL)num[s]*num[j]*d[j];
    }
}

void dfs(int u,int la)
{
    if(idx[u]){R[cn]=u;return;}
    chs.push_back(u);
    cid[u]=cn;
    for(int i=h[u];i;i=e[i].next)
        if(e[i].to!=la) dfs(e[i].to,u);
}

void gao3()  //Find all chains
{
    for(int i=1;i<=n;i++)
        if(deg[i]>2) for(int jj=h[i];jj;jj=e[jj].next)
        {
            int j=e[jj].to;
            if(!idx[j]&&!cid[j])
            {
                L[++cn]=i;chs.clear();dfs(j,i);
                int tot=chs.size();sz[cn]=tot;
                chainv[cn]=new int[tot];
                prenum[cn]=new int[tot];
                prelen[cn]=new LL[tot];
                sufnum[cn]=new int[tot];
                suflen[cn]=new LL[tot];
                for(int i=0;i<tot;i++)
                    cinid[chainv[cn][i]=chs[i]]=i;
                prenum[cn][0]=num[chainv[cn][0]];
                prelen[cn][0]=num[chainv[cn][0]];
                for(int i=1;i<tot;i++)
                {
                    prenum[cn][i]=prenum[cn][i-1]+num[chainv[cn][i]];
                    prelen[cn][i]=prelen[cn][i-1]+(LL)num[chainv[cn][i]]*(i+1);
                }
                sufnum[cn][tot-1]=num[chainv[cn][tot-1]];
                suflen[cn][tot-1]=num[chainv[cn][tot-1]];
                for(int i=tot-2;i>=0;i--)
                {
                    sufnum[cn][i]=sufnum[cn][i+1]+num[chainv[cn][i]];
                    suflen[cn][i]=suflen[cn][i+1]+(LL)num[chainv[cn][i]]*(tot-i);
                }
            }
        }
}

void gao4()  //Solve the path(u,v) which both u and v is small vertex, and they're in different chains
{
    for(int u=1;u<=n;u++)
        if(!idx[u]&&num[u])for(int p=1;p<=cid[u];p++)
            if(cid[u]!=p)
            {
                int a=dis[idx[L[p]]][u],b=dis[idx[R[p]]][u],l=sz[p];
                int x=l+b-a-1;
                if(x<0) ans+=(LL)num[u]*((LL)b*sufnum[p][0]+suflen[p][0]);
                else
                {
                    x=min(x/2,l-1);
                    ans+=(LL)num[u]*((LL)a*prenum[p][x]+prelen[p][x]);
                    if(x<l-1) ans+=(LL)num[u]*((LL)b*sufnum[p][x+1]+suflen[p][x+1]);
                }
            }
            else if(cinid[u]<sz[p]/2)
            {
                int pos=cinid[u];
                if(pos) ans+=(LL)num[u]*((LL)(pos+1)*prenum[p][pos-1]-prelen[p][pos-1]);
            }
            else
            {
                int pos=cinid[u],d=dis[idx[L[p]]][R[p]],tot=sz[p];
                if(tot-pos+d+1<pos)
                {
                    int x=(2*pos-tot-d-1)/2,a=tot-pos+d;
                    ans+=(LL)num[u]*((LL)a*prenum[p][x]+prelen[p][x]);
                    ans+=(LL)num[u]*((LL)(pos+1)*(prenum[p][pos-1]-prenum[p][x])-(prelen[p][pos-1]-prelen[p][x]));
                }
                else if(pos) ans+=(LL)num[u]*((LL)(pos+1)*prenum[p][pos-1]-prelen[p][pos-1]);
            }
}

int main()
{
    n=read();m=read();
    for(int i=1,u,v;i<=m;i++)
    {
        u=read();v=read();
        gg[u].push_back(v);
        gg[v].push_back(u);
        deg[u]++;deg[v]++;
    }
    for(int i=1;i<=n;i++) num[i]=1;
    gao1();
    int cnt=0;
    for(int i=1;i<=n;i++)
        if(deg[i]>2) cnt++;
    if(!cnt)for(int i=1;i<=n;i++)
        if(deg[i]==2){deg[i]=3;break;}
    gao2();gao3();gao4();
    cout<<ans<<endl;
    return 0;
}
