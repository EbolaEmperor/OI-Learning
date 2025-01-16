#include<bits/stdc++.h>
using namespace std;

const int N=100010,S=128,M=803,B=200000;
int n,m,online,val[N];
int dfn[N],idx[N],dfc=0;
int fa[N],top[N],hson[N],dep[N],sz[N];
unsigned char num[M][400010];
int st[M],ed[M],dv[N],tag[M],bc=1;
vector<int> g[N];

void dfs1(int u)
{
    sz[u]=1;
    reverse(g[u].begin(),g[u].end());
    for(int v : g[u])
    {
        if(v==fa[u]) continue;
        dep[v]=dep[u]+1;
        fa[v]=u;dfs1(v);
        sz[u]+=sz[v];
        if(sz[v]>sz[hson[u]]) hson[u]=v;
    }
}

void dfs2(int u,int tp)
{
    top[u]=tp;
    idx[dfn[u]=++dfc]=u;
    if(hson[u]) dfs2(hson[u],tp);
    for(int v : g[u])
        if(v!=fa[u]&&v!=hson[u])
            dfs2(v,v);
}

void divide()
{
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(!st[bc]) st[bc]=i;
        dv[i]=bc;cnt++;
        if(cnt==S) ed[bc]=i,bc++,cnt=0;
    }
    ed[bc]=n;
}

void prework(int b)
{
    for(int i=st[b];i<=ed[b];i++)
        num[b][val[i]+B]++;
    for(int i=4e5;i>=0;i--)
        num[b][i]+=num[b][i+1];
}

void update(int l,int r,int w)
{
    if(dv[l]==dv[r])
    {
        for(int i=l;i<=r;i++)
        {
            if(w==1) num[dv[i]][B+val[i]+1]++;
            if(w==-1) num[dv[i]][B+val[i]]--;
            val[i]+=w;
        }
        return;
    }
    for(int i=dv[l]+1;i<dv[r];i++) tag[i]+=w;
    for(int i=ed[dv[l]];i>=l;i--)
    {
        if(w==1) num[dv[i]][B+val[i]+1]++;
        if(w==-1) num[dv[i]][B+val[i]]--;
        val[i]+=w;
    }
    for(int i=st[dv[r]];i<=r;i++)
    {
        if(w==1) num[dv[i]][B+val[i]+1]++;
        if(w==-1) num[dv[i]][B+val[i]]--;
        val[i]+=w;
    }
}

int query(int l,int r)
{
    int res=0;
    if(dv[l]==dv[r])
    {
        for(int i=l;i<=r;i++) res+=(val[i]+tag[dv[i]]>0);
        return res;
    }
    for(int i=dv[l]+1;i<dv[r];i++) res+=num[i][B+1-tag[i]];
    for(int i=ed[dv[l]];i>=l;i--) res+=(val[i]+tag[dv[i]]>0);
    for(int i=st[dv[r]];i<=r;i++) res+=(val[i]+tag[dv[i]]>0);
    return res;
}

void PathUpdate(int x,int y,int w)
{
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        update(dfn[top[x]],dfn[x],w);
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    update(dfn[x],dfn[y],w);
}

int PathQuery(int x,int y)
{
    int res=0;
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        res+=query(dfn[top[x]],dfn[x]);
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    res+=query(dfn[x],dfn[y]);
    return res;
}

int main()
{
    scanf("%d%d%d",&n,&m,&online);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs1(1);dfs2(1,1);divide();
    for(int i=1;i<=n;i++)
    {
        scanf("%d",val+dfn[i]);
        if(val[dfn[i]]>1e5) val[dfn[i]]=1e5;
        if(val[dfn[i]]<-1e5) val[dfn[i]]=-1e5;
    }
    for(int i=1;i<=bc;i++) prework(i);
    int opt,x,y,w,ans=0;
    while(m--)
    {
        scanf("%d%d",&opt,&x);
        if(opt==1)
        {
            scanf("%d%d",&y,&w);
            if(online) x^=ans,y^=ans;
            PathUpdate(x,y,w);
        }
        if(opt==2)
        {
            scanf("%d",&y);
            if(online) x^=ans,y^=ans;
            ans=PathQuery(x,y);
            printf("%d\n",ans);
        }
        if(opt==3)
        {
            if(online) x^=ans;
            ans=query(dfn[x],dfn[x]+sz[x]-1);
            printf("%d\n",ans);
        }
    }
    return 0;
}