#include<bits/stdc++.h>
#define ls ch[x][0]
#define rs ch[x][1]
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

const int N=200010;
struct OPT
{
    int opt,u,v,w;
    OPT(int _opt=0,int _u=0,int _v=0,int _w=0):opt(_opt),u(_u),v(_v),w(_w){}
    bool operator < (const OPT &a) const{return w==a.w?opt<a.opt:w<a.w;}
} q[N<<1];
int n,tot=0;
long long ans=0;
int ch[N][2],fa[N];
int szi[N],szr[N];
int stk[N],top=0;
bool flip[N];

inline bool nroot(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
inline void maintain(int x){szr[x]=szi[ls]+szi[rs]+szr[ls]+szr[rs]+1;}
inline void pushr(int x){swap(ls,rs);flip[x]^=1;}

void pushdown(int x)
{
    if(!flip[x]) return;
    if(ls) pushr(ls);
    if(rs) pushr(rs);
    flip[x]=0;
}

void rotate(int x)
{
    int y=fa[x],z=fa[y];
    int k=(ch[y][1]==x),w=ch[x][k^1];
    if(nroot(y)) ch[z][ch[z][1]==y]=x;
    ch[y][k]=w;ch[x][k^1]=y;
    fa[x]=z;fa[y]=x;
    if(w) fa[w]=y;
    maintain(y);
    maintain(x);
}

void splay(int x)
{
    int y=x,z;stk[top=1]=y;
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

void access(int x)
{
    for(int y=0;x;y=x,x=fa[x])
    {
        splay(x);if(rs) szi[x]+=szi[rs]+szr[rs],szr[x]-=szi[rs]+szr[rs];
        rs=y;if(rs) szi[x]-=szi[rs]+szr[rs],szr[x]+=szi[rs]+szr[rs];
        maintain(x);
    }
}

inline void makeroot(int x){access(x);splay(x);pushr(x);}

void link(int x,int y)
{
    makeroot(x);access(y);splay(y);
    ans+=1ll*(szr[x]+szi[x])*(szr[y]+szi[y]);
    fa[x]=y;szi[y]+=szr[x]+szi[x];
}

void cut(int x,int y)
{
    makeroot(x);access(y);splay(y);
    szr[y]-=szr[x]+szi[x];
    fa[x]=ch[y][0]=0;
}

int main()
{
    n=read();
    for(int i=1;i<n;i++)
    {
        int u=read(),v=read();
        int l=read(),r=read();
        q[i*2-1]=OPT(1,u,v,l);
        q[i*2]=OPT(2,u,v,r);
    }
    sort(q+1,q+1+2*n);
    for(int i=1;i<=2*n;i++)
    {
        if(q[i].opt==1) link(q[i].u,q[i].v);
        if(q[i].opt==2) cut(q[i].u,q[i].v);
    }
    cout<<ans<<endl;
    return 0;
}