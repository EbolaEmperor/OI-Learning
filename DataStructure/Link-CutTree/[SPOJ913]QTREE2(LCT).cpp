#include<bits/stdc++.h>
#define ls nd[x].son[0]
#define rs nd[x].son[1]
using namespace std;

struct Node
{
    int s,v,r;
    int son[2],fa;
    int sz;
} nd[300010];
struct Edge{int to,next;} e[300010];
int h[300010],sum;
char opt[10];

inline void add_edge(int u,int v)
{
    sum++;
    e[sum].to=v;
    e[sum].next=h[u];
    h[u]=sum;
}

void dfs(int u,int fa)
{
    for(int tmp=h[u];tmp;tmp=e[tmp].next)
    {
        if(e[tmp].to==fa) continue;
        nd[e[tmp].to].fa=u;
        nd[e[tmp].to].sz=1;
        dfs(e[tmp].to,u);
    }
}

inline bool notroot(int x){return nd[nd[x].fa].son[0]==x||nd[nd[x].fa].son[1]==x;}
inline void pushr(int x){swap(ls,rs);nd[x].r^=1;}
inline void maintain(int x){nd[x].s=nd[ls].s+nd[rs].s+nd[x].v;nd[x].sz=nd[ls].sz+nd[rs].sz+1;}
inline void pushdown(int x)
{
    if(nd[x].r)
    {
        if(ls) pushr(ls);
        if(rs) pushr(rs);
        nd[x].r=0;
    }
}

inline void rotate(int x)
{
    int y=nd[x].fa,z=nd[y].fa;
    int k=(nd[y].son[1]==x),w=nd[x].son[k^1];
    if(notroot(y)) nd[z].son[nd[z].son[1]==y]=x;
    nd[x].son[k^1]=y;
    nd[y].son[k]=w;
    if(w) nd[w].fa=y;
    nd[y].fa=x;
    nd[x].fa=z;
    maintain(y);
    maintain(x);
}

void splay(int x)
{
    int y=x,z;
    stack<int> s;
    s.push(y);
    while(notroot(y)) s.push(nd[y].fa),y=nd[y].fa;
    while(!s.empty()) pushdown(s.top()),s.pop();
    while(notroot(x))
    {
        y=nd[x].fa;
        z=nd[y].fa;
        if(notroot(y)) rotate((nd[y].son[0]==x)^(nd[z].son[0]==y)?x:y);
        rotate(x);
    }
    maintain(x);
}

int kth(int x,int k)
{
    pushdown(x);
    int sz=1;
    if(ls) sz+=nd[ls].sz;
    if(k==sz) return x;
    else if(k<sz) return kth(ls,k);
    else return kth(rs,k-sz);
}

void access(int x)
{
    int y=0;
    while(x)
    {
        splay(x);
        rs=y;
        maintain(x);
        y=x;
        x=nd[x].fa;
    }
}

inline void makeroot(int x){access(x);splay(x);pushr(x);}
inline void split(int x,int y){makeroot(x);access(y);splay(y);}

int main()
{
    int t,n,a,b,c;
    for(cin>>t;t;t--)
    {
        sum=0;
        memset(h,0,sizeof(h));
        memset(nd,0,sizeof(nd));
        cin>>n;
        for(int i=1;i<n;i++)
        {
            scanf("%d%d%d",&a,&b,&c);
            add_edge(a,n+i);
            add_edge(n+i,a);
            add_edge(b,n+i);
            add_edge(n+i,b);
            nd[n+i].v=c;
        }
        dfs(1,0);
        nd[1].sz=1;
        while(true)
        {
            scanf("%s",opt);
            if(opt[1]=='O') break;
            if(opt[0]=='D')
            {
                scanf("%d%d",&a,&b);
                split(a,b);
                printf("%d\n",nd[b].s);
            }
            else
            {
                scanf("%d%d%d",&a,&b,&c);
                split(a,b);
                printf("%d\n",kth(b,2*c-1));
            }
        }
    }
    return 0;
}
