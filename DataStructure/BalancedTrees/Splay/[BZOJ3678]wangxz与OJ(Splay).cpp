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
        int x=0,fg=1;char c=Get();
        while(!isdigit(c)&&c!='-') c=Get();
        if(c=='-') fg=-1,c=Get();
        while(isdigit(c)) x=x*10+c-'0',c=Get();
        return x*fg;
    }
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    template <class I>inline void print(I x)
    {
        if(!x) putc('0');
        if(x<0) putc('-'),x=-x;
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
        putc('\n');
    }
}

using namespace IO;
const int N=1000010;
int ch[N][2],L[N],R[N],tot=0;
int fa[N],sz[N],val[N],rt=0;

inline void maintain(int x){sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+R[x]-L[x]+1;}

void build(int &x,int l,int r)
{
    int mid=(l+r)/2;
    sz[x=++tot]=1;
    L[x]=R[x]=val[mid-1];
    if(l==r) return;
    if(l<mid) build(ch[x][0],l,mid-1);
    if(r>mid) build(ch[x][1],mid+1,r);
    if(ch[x][0]) fa[ch[x][0]]=x;
    if(ch[x][1]) fa[ch[x][1]]=x;
    maintain(x);
}

inline void rotate(int x,int &falun)
{
    int y=fa[x],z=fa[y];
    int k=(ch[y][1]==x),w=ch[x][k^1];
    if(y!=falun) ch[z][ch[z][1]==y]=x;
    else falun=x;
    fa[x]=z;fa[y]=x;
    if(w) fa[w]=y;
    ch[y][k]=w;
    ch[x][k^1]=y;
    maintain(y);
    maintain(x);
}

void splay(int x,int &falun)
{
    while(x!=falun)
    {
        int y=fa[x],z=fa[y];
        if(y!=falun) rotate((ch[y][0]==x)^(ch[z][0]==y)?x:y,falun);
        rotate(x,falun);
    }
}

int find(int x,int k)
{
    int szl=sz[ch[x][0]],szr=sz[ch[x][1]];
    if(k<=szl) return find(ch[x][0],k);
    else if(k>sz[x]-szr) return find(ch[x][1],k-(sz[x]-szr));
    else
    {
        k-=szl;
        if(k>1)
        {
            int o=++tot;
            L[o]=L[x];R[o]=L[x]+k-2;L[x]=R[o]+1;
            ch[o][0]=ch[x][0];
            if(ch[x][0]) fa[ch[x][0]]=o;
            ch[x][0]=o;fa[o]=x;
            maintain(o);k=1;
        }
        if(k<R[x]-L[x]+1)
        {
            int o=++tot;
            R[o]=R[x];L[o]=L[x]+k;R[x]=L[o]-1;
            ch[o][1]=ch[x][1];
            if(ch[x][1]) fa[ch[x][1]]=o;
            ch[x][1]=o;fa[o]=x;
            maintain(o);
        }
        return x;
    }
}

int split(int x,int y)
{
    int t1=find(rt,x);
    int t2=find(rt,y);
    splay(t1,rt);
    splay(t2,ch[rt][1]);
    return t2;
}

int main()
{
    int n=read(),m=read(),opt,a,b,p;
    for(int i=1;i<=n;i++) val[i]=read();
    build(rt,1,n+2);
    while(m--)
    {
        opt=read();
        if(opt==0)
        {
            p=read();a=read();b=read();
            int t=split(p+1,p+2),o=++tot;
            L[o]=a;R[o]=b;sz[o]=b-a+1;
            ch[t][0]=o;fa[o]=t;
            maintain(t);
            maintain(rt);
        }
        if(opt==1)
        {
            a=read();b=read();
            int t=split(a,b+2);
            fa[ch[t][0]]=0;
            ch[t][0]=0;
            maintain(t);
            maintain(rt);
        }
        if(opt==2)
        {
            p=read();
            int t=find(rt,p+1);
            print(L[t]);
        }
    }
    flush();
    return 0;
}