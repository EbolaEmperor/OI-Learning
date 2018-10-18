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
    inline void prints(const char *s)
    {
        int len=strlen(s);
        for(int i=0;i<len;i++) putc(s[i]);
        putc('\n');
    }
}

using namespace IO;
const int N=200010;
const int P=20000010;
int tot,root,cnt;
int sz[P],tag[P];
int lc[P],rc[P];
int rt[N];

inline int newnode(int x=1)
{
    int o=++tot;
    tag[o]=x-1;
    sz[o]=1<<tag[o];
    lc[o]=rc[o]=0;
    return tot;
}

inline void pushdown(int o)
{
    if(!tag[o]) return;
    lc[o]=newnode(tag[o]);
    rc[o]=newnode(tag[o]);
    tag[o]=0;
}

int split(int o,int x)
{
    int now=++tot,res=now;
    pushdown(o);
    while(lc[o]||rc[o])
    {
        tag[now]=0;sz[now]=x;sz[o]-=x;
        if(x<=sz[lc[o]])
        {
            lc[now]=newnode();rc[now]=0;
            now=lc[now];o=lc[o];
        }
        else
        {
            rc[now]=newnode();lc[now]=lc[o];
            x-=sz[lc[o]];lc[o]=0;
            now=rc[now];o=rc[o];
        }
        pushdown(o);
    }
    tag[now]=tag[o]=0;
    sz[now]=x;sz[o]-=x;
    return res;
}

int merge(int x,int y)
{
    if(!x||!y) return x|y;
    lc[x]=merge(lc[x],lc[y]);
    rc[x]=merge(rc[x],rc[y]);
    sz[x]+=sz[y];
    return x;
}

int query(int x,int k)
{
    int o=rt[x],res=0;
    if(x>cnt||k>=sz[o]) return -1;
    while(lc[o]||rc[o])
    {
        res<<=1;
        if(lc[o]&&k<sz[lc[o]]) o=lc[o];
        else k-=sz[lc[o]],res|=1,o=rc[o];
    }
    return res*(1<<tag[o])+k;
}

bool alloc(int k)
{
    rt[++cnt]=0;
    if(sz[root]<k) return 0;
    rt[cnt]=split(root,k);
    return 1;
}

bool free(int k)
{
    if(k>cnt||!rt[k]) return 0;
    root=merge(root,rt[k]);
    rt[k]=0;return 1;
}

int main()
{
    for(int T=read();T;T--)
    {
        cnt=tot=0;
        root=newnode(31);
        for(int n=read();n;n--)
        {
            int ty=read();
            if(ty==1) prints(alloc(read())?"ok":"failed");
            if(ty==2) prints(free(read())?"ok":"failed");
            if(ty==3)
            {
                int x=read(),k=read();
                int ans=query(x,k);
                if(~ans) print(ans);
                else prints("failed");
            }
        }
    }
    flush();
    return 0;
}