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
typedef unsigned long long ull;
const int N=50010;
struct Edge{int to,next;} e[N<<1];
int h[N],dep[N],fa[17][N],sum=0,n,B;
ull lg2[65550];
 
struct bit
{
    ull s[785];
    bit(){memset(s,0,sizeof(s));}
    void add(int p){s[p>>6]|=1ull<<(p&63);}
    ull& operator [] (const int &p){return s[p];}
    bit operator ~ (){bit t;for(int i=0;i<B;i++) t.s[i]=~s[i];return t;}
    bit& operator |= (const bit &a){for(int i=0;i<B;i++) s[i]|=a.s[i];return *this;}
    bit& operator &= (const bit &a){for(int i=0;i<B;i++) s[i]&=a.s[i];return *this;}
    bit operator ^ (bit a){for(int i=0;i<B;i++) a.s[i]^=s[i];return a;}
} son[N],path[N],pre[N];
 
void add_edge(int u,int v)
{
    e[++sum].to=v;
    e[sum].next=h[u];
    h[u]=sum;
}
 
void dfs(int u,int la)
{
    son[u].add(u);
    path[u]=path[la];
    path[u].add(u);
    for(int i=1;i<=15;i++)
        fa[i][u]=fa[i-1][fa[i-1][u]];
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==la) continue;
        dep[v]=dep[u]+1;
        fa[0][v]=u;dfs(v,u);
        son[u]|=son[v];
    }
}
 
int lca(int x,int y)
{
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=15;i>=0;i--)
        if(dep[fa[i][x]]>=dep[y])
            x=fa[i][x];
    for(int i=15;i>=0;i--)
        if(fa[i][x]!=fa[i][y])
            x=fa[i][x],y=fa[i][y];
    if(x!=y) x=fa[0][x];
    return x;
}
 
struct mushroom
{
    bit weed;
    void merge(mushroom &A){weed|=A.weed;}
    void cut1(int x){weed&=~son[x];}
    void cut2(int x){weed&=son[x];}
    void cut3(int x,int y){bit tmp=path[x]^path[y];tmp.add(lca(x,y));weed&=~tmp;}
    void cut4(int x,int y){bit tmp=path[x]^path[y];tmp.add(lca(x,y));weed&=tmp;}
    void cut5(int r,int l){weed&=~(pre[l-1]^pre[r]);}
    void cut6(int r,int l){weed&=pre[l-1]^pre[r];}
    int query(int w)
    {
        int ans=0;
        for(ull i=1;i<=n;)
        {
            ull tmp=(~0ull)>>(i&63)<<(i&63);
            if(weed[i>>6]&tmp)
            {
                ull s=weed[i>>6]&tmp,k=s&-s,p=0;
                while(k>65536) k>>=16,p+=16;p+=lg2[k];
                i=(i>>6<<6)+p+w+1;ans++;
            }
            else i=(i>>6)+1<<6;
        }
        return ans;
    }
};
vector<mushroom*> mr;
map<mushroom*,int> cnt;
 
int main()
{
    for(ull i=0;i<=16;i++) lg2[1ull<<i]=i;
    B=((n=read())+64)>>6;
    for(int i=1;i<n;i++)
    {
        int u=read(),v=read();
        add_edge(u,v);
        add_edge(v,u);
    }
    mr.resize(1);mr[0]=new mushroom;cnt[mr[0]]++;
    for(int i=1;i<=n;i++) mr[0]->weed.add(i);
    for(int i=1;i<=n;i++) pre[i].add(i),pre[i]|=pre[i-1];
    fa[0][1]=1;dep[1]=1;dfs(1,0);
    for(int Q=read();Q;Q--)
    {
        int opt=read(),u=read()-1;
        if(opt==1) mr.push_back(mr[u]),cnt[mr[u]]++;
        if(opt>=2&&opt<=8)
        {
            mushroom* p=mr[u];
            if(cnt[p]>1)
            {
                mr[u]=new mushroom;
                *mr[u]=*p;
                cnt[p]--;
                cnt[mr[u]]++;
            }
        }
        if(opt==2) mr[u]->merge(*mr[read()-1]);
        if(opt==3) mr[u]->cut1(read());
        if(opt==4) mr[u]->cut2(read());
        if(opt==5) mr[u]->cut3(read(),read());
        if(opt==6) mr[u]->cut4(read(),read());
        if(opt==7) mr[u]->cut5(read(),read());
        if(opt==8) mr[u]->cut6(read(),read());
        if(opt==9) print(mr[u]->query(read()));
    }
    flush();
    return 0;
}