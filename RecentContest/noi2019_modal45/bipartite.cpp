#include<bits/stdc++.h>
#define ls ch[x][0]
#define rs ch[x][1]
using namespace std;

const int N=200010;
int fa[N],ch[N][2],flip[N];
int val[N],mnp[N],sz[N];
int stk[N],top=0;
struct Edge{int u,v,w;} e[N];
struct OPT{int id,ty;} opt[N];
map<int,int> pre[N];
int n,m,odd=0;
bool istree[N],isodd[N];

inline bool nroot(int y){return ch[fa[y]][0]==y||ch[fa[y]][1]==y;}
inline void pushr(int x){swap(ls,rs);flip[x]^=1;}
inline void pushdown(int x)
{
    if(!flip[x]) return;
    if(ls) pushr(ls);
    if(rs) pushr(rs);
    flip[x]=0;
}

void maintain(int x)
{
    mnp[x]=x;
    if(ls&&val[mnp[ls]]<val[mnp[x]]) mnp[x]=mnp[ls];
    if(rs&&val[mnp[rs]]<val[mnp[x]]) mnp[x]=mnp[rs];
    sz[x]=sz[ls]+sz[rs]+(x>n);
}

void rotate(int x)
{
    int y=fa[x],z=fa[y];
    int k=(ch[y][1]==x),w=ch[x][k^1];
    if(nroot(y)) ch[z][ch[z][1]==y]=x;
    ch[x][k^1]=y;ch[y][k]=w;
    if(w) fa[w]=y;
    fa[x]=z;fa[y]=x;
    maintain(y);
    maintain(x);
}

void splay(int x)
{
    int y=x,z;
    stk[++top]=y;
    while(nroot(y)) y=fa[y],stk[++top]=y;
    while(top) pushdown(stk[top--]);
    while(nroot(x))
    {
        y=fa[x];z=fa[y];
        if(nroot(y)) rotate((ch[y][0]==x)^(ch[z][0]==y)?x:y);
        rotate(x);
    }
    maintain(x);
}

inline void access(int x){for(int y=0;x;y=x,x=fa[x]) splay(x),rs=y,maintain(x);}
inline int find(int x){access(x);splay(x);while(ls) pushdown(x),x=ls;return x;}
inline void makeroot(int x){access(x);splay(x);pushr(x);}
inline void split(int x,int y){makeroot(x);access(y);splay(y);}
inline void link(int x,int y){makeroot(x);fa[x]=y;}
inline void cut(int x,int y){split(x,y);fa[x]=ch[y][0]=0;}

void insert(int x)
{
    int u=e[x].u,v=e[x].v,y;
    if(find(u)!=find(v)) istree[x]=1,link(u,x+n),link(v,x+n);
    else
    {
        split(u,v);y=mnp[v]-n;
        if(e[x].w>e[y].w)
        {
            istree[x]=1;istree[y]=0;
            if(~sz[v]&1) odd++,isodd[y]=1;
            cut(e[y].u,y+n);cut(e[y].v,y+n);
            link(u,x+n);link(v,x+n);
        }
        else if(~sz[v]&1) odd++,isodd[x]=1;
    }
}

void remove(int x)
{
    if(istree[x]) istree[x]=0,cut(e[x].u,x+n),cut(e[x].v,x+n);
    else if(isodd[x]) isodd[x]=0,odd--;
}

int main()
{
    scanf("%d%d",&n,&m);
    memset(val,0x3f,sizeof(val));
    for(int i=1;i<=m;i++) val[n+i]=m+1;
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        if(u>v) swap(u,v);
        if(pre[u][v])
        {
            e[pre[u][v]].w=i;
            val[pre[u][v]+n]=i;
            opt[i]={pre[u][v],2};
            pre[u][v]=0;
        }
        else e[i]={u,v,m+1},pre[u][v]=i,opt[i]={i,1};
    }
    for(int i=1;i<=m;i++)
    {
        if(opt[i].ty==1) insert(opt[i].id);
        if(opt[i].ty==2) remove(opt[i].id);
        puts(odd?"NO":"YES");
    }
    return 0;
}