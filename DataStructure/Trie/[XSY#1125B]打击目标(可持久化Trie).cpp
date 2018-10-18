#include<bits/stdc++.h>
using namespace std;

namespace IO
{
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
    inline void reads(char *s)
    {
        char c=Get();int tot=0;
        while(c<'a'||c>'z') c=Get();
        while(c>='a'&&c<='z') s[++tot]=c,c=Get();
        s[++tot]='\0';
    }
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    template <class I>inline void print(I x)
    {
        if(!x) putc('0');
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
        putc('\n');
    }
}

using namespace IO;
const int N=100010;
const int P=1100010;
struct Edge{int to,next;} e[N];
int h[N],n,sum=0,root[N];
int ch[P][26],val[P],sz=0;
int s[15],len,ans;
int fa[20][N],dep[N];
char sv[N][15];

void insert(int &o,int p,int c)
{
    val[o=++sz]=val[p];
    memcpy(ch[o],ch[p],sizeof(ch[o]));
    if(c>len){val[o]++;return;}
    insert(ch[o][s[c]],ch[p][s[c]],c+1);
}
void find(int L,int R,int c)
{
    if(val[R]-val[L]>0) ans=max(ans,c-1);
    if(c>len) return;
    find(ch[L][s[c]],ch[R][s[c]],c+1);
}

void add_edge(int u,int v)
{
    e[++sum].to=v;
    e[sum].next=h[u];
    h[u]=sum;
}
void dfs(int u,int la)
{
    len=strlen(sv[u]+1);
    for(int i=1;i<=len;i++)
        s[i]=sv[u][i]-'a';
    insert(root[u],root[la],1);
    for(int i=1;i<=16;i++)
        fa[i][u]=fa[i-1][fa[i-1][u]];
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        dep[v]=dep[u]+1;
        dfs(v,u);
    }
}
int getlca(int x,int y)
{
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=16;i>=0;i--)
        if(dep[fa[i][x]]>=dep[y])
            x=fa[i][x];
    if(x==y) return x;
    for(int i=16;i>=0;i--)
        if(fa[i][x]!=fa[i][y])
            x=fa[i][x],y=fa[i][y];
    return fa[0][x];
}

int main()
{
    int online,Q,x,y;
    n=read();online=read();
    for(int i=1;i<=n;i++) reads(sv[i]);
    for(int i=2;i<=n;i++)
    {
        fa[0][i]=read();
        add_edge(fa[0][i],i);
    }
    dep[1]=1;dfs(1,0);
    static char ss[N];
    for(Q=read();Q;Q--)
    {
        x=read();y=read();reads(ss);
        int lens=strlen(ss+1);
        if(online) x^=ans,y^=ans;
        int lca=getlca(x,y);
        lca=fa[0][lca];ans=0;
        for(int i=1;i<=lens;i++)
        {
            len=min(10,lens-i+1);
            for(int k=1;k<=len;k++)
                s[k]=ss[i+k-1]-'a';
            find(root[lca],root[x],1);
            find(root[lca],root[y],1);
        }
        print(ans);
    }
    flush();
    return 0;
}