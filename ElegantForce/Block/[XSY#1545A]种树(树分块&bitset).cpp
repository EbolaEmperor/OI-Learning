#include<bits/stdc++.h>
using namespace std;

const int N=100010,S=180,W=30010;
bitset<W> sum[S][S];
int n,m,op,val[N],fa[20][N];
int dep[N],idx[N],rt[S],fart[N],cnt=0;
vector<int> G[N];

void dfs(int u,int la,int lst)
{
    for(int k=1;k<=16;k++)
        fa[k][u]=fa[k-1][fa[k-1][u]];
    if(dep[u]-dep[lst]>=600)
    {
        rt[idx[u]=++cnt]=u;fart[u]=lst;
        for(int x=u;x!=lst;x=fa[0][x]) sum[cnt][0][val[x]]=1;
        for(int i=1,x=lst;x;i++,x=fart[x]) sum[cnt][i]=sum[cnt][i-1]|sum[idx[x]][0];
        lst=u;
    }
    for(int v : G[u])
    {
        if(v==la) continue;
        dep[v]=dep[u]+1;
        fa[0][v]=u;
        dfs(v,u,lst);
    }
}

int getlca(int x,int y)
{
    if(dep[x]<dep[y]) swap(x,y);
    for(int k=16;k>=0;k--)
        if(dep[fa[k][x]]>=dep[y])
            x=fa[k][x];
    if(x==y) return x;
    for(int k=16;k>=0;k--)
        if(fa[k][x]!=fa[k][y])
            x=fa[k][x],y=fa[k][y];
    return fa[0][x];
}

bitset<W> query(int x,int y)
{
    bitset<W> res;
    while(!idx[x]&&dep[x]>=dep[y]) res[val[x]]=1,x=fa[0][x];
    if(dep[x]<dep[y]) return res;
    int rt=x,c=-1;
    while(dep[fart[rt]]>=dep[y]) rt=fart[rt],c++;
    if(c>=0) res|=sum[idx[x]][c];
    while(rt!=y) res[val[rt]]=1,rt=fa[0][rt];
    res[val[y]]=1;
    return res;
}

int main()
{
    scanf("%d%d%d",&n,&m,&op);
    for(int i=1;i<=n;i++) scanf("%d",val+i);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dep[1]=1;dfs(1,0,0);
    int lastans=0;
    while(m--)
    {
        int k,u,v;
        scanf("%d",&k);
        bitset<W> ans;
        for(int i=1;i<=k;i++)
        {
            scanf("%d%d",&u,&v);
            u^=op*lastans;
            v^=op*lastans;
            int lca=getlca(u,v);
            ans|=query(u,lca);
            ans|=query(v,lca);
        }
        int ans1=ans.count();
        int ans2=(~ans)._Find_first();
        printf("%d %d\n",ans1,ans2);
        lastans=ans1+ans2;
    }
    return 0;
}