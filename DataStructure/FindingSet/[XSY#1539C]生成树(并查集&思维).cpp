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
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
        putc('\n');
    }
}

using namespace IO;
typedef pair<int,int> pii;
typedef long long LL;
const int N=100010;
int n,m,en,fa[N<<1];
vector<pii> A,B,eg[35];
LL ans[N],cnt[N];

int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}

void gao(int w)
{
    memset(cnt,0,sizeof(cnt));
    for(int i=1;i<=2*n;i++) fa[i]=i;
    for(int i=1;i<=w;i++)
        for(pii e : eg[i])
        {
            int u=e.first,v=e.second;
            u=find(u);v=find(v);
            if(u==v) continue;
            if(u>v) swap(u,v);fa[u]=v;cnt[1]++;
            if(u>n&&v>n) A.push_back(pii(u-n,v-n));
        }
    for(int i=2;i<=m&&A.size();i++)
    {
        B.clear();
        for(pii e : A)
        {
            int u=e.first,v=e.second;
            u=find(u);v=find(v);
            if(u==v){cnt[i]--;continue;}
            if(u>v) swap(u,v);fa[u]=v;
            if(u>n&&v>n) B.push_back(pii(u-n,v-n));
        }
        swap(A,B);
    }
    for(int i=2;i<=m;i++) cnt[i]+=cnt[i-1];
    for(int i=2;i<=m;i++) cnt[i]+=cnt[i-1];
    for(int i=1;i<=m;i++) ans[i]+=(LL)n*(i+1)-cnt[i]-1;
}

int main()
{
    n=read();m=read();en=read();
    for(int i=1,u,v,w;i<=en;i++)
    {
        u=read();v=read();w=read();
        eg[w].push_back(pii(u,v+n));
    }
    for(int i=0;i<=30;i++) gao(i);
    for(int i=1;i<=m;i++) print(ans[i]);
    return flush(),0;
}
