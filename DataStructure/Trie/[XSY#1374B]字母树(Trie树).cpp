#include<bits/stdc++.h>
using namespace std;

const int N=4010;
struct Edge{int to,capa,next;} e[N<<1];
int h[N],n,Q,sum=0;
int ch[N<<1][26],tot=0;
vector<int> vtx[N<<1];
int ans[N][N],dfn=0,rt;

void add_edge(int u,int v,int w)
{
    e[++sum].to=v;
    e[sum].capa=w;
    e[sum].next=h[u];
    h[u]=sum;
}

void build(int u,int fa,int trie)
{
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to,c=e[t].capa;
        if(v==fa) continue;
        if(!ch[trie][c]) ch[trie][c]=++tot;
        vtx[ch[trie][c]].push_back(v);
        build(v,u,ch[trie][c]);
    }
}

void dfs(int u)
{
    for(int v : vtx[u]) ans[rt][v]=dfn;
    dfn+=vtx[u].size();
    for(int c=0;c<26;c++)
        if(ch[u][c]) dfs(ch[u][c]);
}

int main()
{
    int u,v;char w;
    scanf("%d%d",&n,&Q);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        w=getchar();
        while(w<'a'||w>'z') w=getchar();
        add_edge(u,v,w-'a');
        add_edge(v,u,w-'a');
    }
    for(int i=1;i<=n;i++)
    {
        for(int i=1;i<=tot;i++) vtx[i].clear();
        memset(ch,0,sizeof(ch));
        tot=1;dfn=0;rt=i;
        build(rt,0,1);dfs(1);
    }
    while(Q--)
    {
        scanf("%d%d",&u,&v);
        printf("%d\n",ans[u][v]);
    }
    return 0;
}