#include<bits/stdc++.h>
using namespace std;

const int N=100010;
vector<int> g[N];
int id[N],sz[N],cnum=0;
int lens[N],lenn=0;
int ans[N],n,nxt[N];
int vis[N],c[N],mxd;
int s[450][N],h[450];

void dfs(int u,int d)
{
    c[d]++;
    mxd=max(mxd,d);
    for(int v : g[u])
        if(!vis[v]) dfs(v,d+1);
}

void prework()
{
    cnum=0;
    memset(vis,0,sizeof(int)*(n+1));
    memset(ans,0,sizeof(int)*(n+1));
    memset(h,0,sizeof(int)*(sqrt(2*n)+1));
    for(int i=1;i<=n;i++) g[nxt[i]].emplace_back(i);
    for(int i=1;i<=n;i++)
    {
        if(vis[i]) continue;
        int x=i;for(;!vis[x];x=nxt[x]) vis[x]=i;
        if(vis[x]==i)
        {
            int cnt=1;
            for(int u=nxt[x];u!=x;u=nxt[u]) cnt++;
            id[++cnum]=x;sz[x]=lens[cnum]=cnt;
        }
    }
    lens[cnum+1]=1;
    sort(lens+1,lens+2+cnum);
    lenn=unique(lens+1,lens+2+cnum)-(lens+1);
}

void gao1(int x)
{
    int m=sz[x];
    static int rs[N],d[N];
    static vector<int> cdep[N];
    for(int i=1,u=x;i<=m;i++,u=nxt[u]) vis[rs[i]=u]=1;
    reverse(rs+1,rs+1+m);
    for(int i=1;i<=m;i++)
    {
        mxd=0;
        dfs(rs[i],0);
        cdep[i].resize(mxd+1);
        for(int j=0;j<=mxd;j++)
            cdep[i][j]=c[j],c[j]=0;
    }
    for(int t=1;t<=lenn;t++)
    {
        int ts=lens[t],res=0,lim=0;
        for(int i=1;i<=m;i++)
            for(int j=0;j<cdep[i].size();j++)
                if((d[(i+j)%ts]+=cdep[i][j])>res) res=d[(i+j)%ts];
        for(int i=1;i<m;i++)
        {
            for(int j=0;j<cdep[i].size();j++)
                d[(i+j)%ts]-=cdep[i][j];
            for(int j=0;j<cdep[i].size();j++)
                if((d[(i+j+m)%ts]+=cdep[i][j])>res) res=d[(i+j+m)%ts];
        }
        s[t][res]++;
        if(ts==m) h[t]=max(h[t],res);
        memset(d,0,sizeof(int)*ts);
    }
}

void gao2()
{
    for(int i=1;i<=lenn;i++)
    {
        int ts=h[i],tmp=0;
        if(h[i]) s[i][h[i]]--;
        ans[0]=max(ans[0],ts);
        for(int j=n;j;j--)
        {
            if(!s[i][j]) continue;
            int t=s[i][j];s[i][j]=0;
            for(int k=1;k<=t;k++)
                if((ts+=j)>ans[tmp+k]) ans[tmp+k]=ts;
            tmp+=t;
        }
    }
    int k=ans[cnum-1]==n?cnum-1:cnum;
    printf("%d\n",k);
    for(int i=0;i<=k;i++)
        printf("%d ",ans[i]);
    puts("");
}

void _main_()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) g[i].clear();
    for(int i=1;i<=n;i++) scanf("%d",nxt+i);
    prework();
    memset(vis,0,sizeof(int)*(n+1));
    for(int i=1;i<=cnum;i++)
        gao1(id[i]);
    gao2();
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--) _main_();
    return 0;
}