//模板题号：洛谷P4719
#include<bits/stdc++.h>
using namespace std;

namespace IO
{
    const int S=(1<<23)+5;
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
const int INF=0x3f3f3f3f;
const int N=100010;
struct Edge{int to,next;} e[N<<1];
int h[N],esum=0;
int n,m,a[N],f[N][2];
int fa[N],ch[N][2],tot=0;

void add_edge(int u,int v)
{
    e[++esum].to=v;
    e[esum].next=h[u];
    h[u]=esum;
}

inline int mymax(const int &x,const int &y){return x>y?x:y;}

struct Matrix
{
    int m[2][2];
    Matrix(){m[0][0]=m[0][1]=m[1][0]=m[1][1]=-INF;}
    int* operator [] (const int &x){return m[x];}
    Matrix operator * (const Matrix &B)
    {
        Matrix C;
        C[0][0]=mymax(m[0][0]+B.m[0][0],m[0][1]+B.m[1][0]);
        C[0][1]=mymax(m[0][0]+B.m[0][1],m[0][1]+B.m[1][1]);
        C[1][0]=mymax(m[1][0]+B.m[0][0],m[1][1]+B.m[1][0]);
        C[1][1]=mymax(m[1][0]+B.m[0][1],m[1][1]+B.m[1][1]);
        return C;
    }
} val[N],sum[N];

bool nrt(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
void maintain(int x)
{
    sum[x]=val[x];
    if(ch[x][0]) sum[x]=sum[ch[x][0]]*sum[x];
    if(ch[x][1]) sum[x]=sum[x]*sum[ch[x][1]];
}

void rotate(int x)
{
    int y=fa[x],z=fa[y];
    int k=(ch[y][1]==x),w=ch[x][k^1];
    if(nrt(y)) ch[z][ch[z][1]==y]=x;
    ch[x][k^1]=y;ch[y][k]=w;
    if(w) fa[w]=y;
    fa[x]=z;fa[y]=x;
    maintain(y);
    maintain(x);
}

void splay(int x)
{
    int y=x,z;
    while(nrt(x))
    {
        y=fa[x];z=fa[y];
        if(nrt(y)) rotate((ch[y][0]==x)^(ch[z][0]==y)?x:y);
        rotate(x);
    }
    maintain(x);
}

void access(int x)
{
    for(int y=0;x;y=x,x=fa[x])
    {
        splay(x);
        if(ch[x][1])
        {
            val[x][0][0]+=mymax(sum[ch[x][1]][0][0],sum[ch[x][1]][1][0]);
            val[x][1][0]+=sum[ch[x][1]][0][0];
        }
        ch[x][1]=y;
        if(ch[x][1])
        {
            val[x][0][0]-=mymax(sum[ch[x][1]][0][0],sum[ch[x][1]][1][0]);
            val[x][1][0]-=sum[ch[x][1]][0][0];
        }
        val[x][0][1]=val[x][0][0];
    }
}

int gao(int x,int v)
{
    access(x);splay(x);
    val[x][1][0]+=v-a[x];
    a[x]=v;splay(1);
    return mymax(sum[1][0][0],sum[1][1][0]);
}

void dp(int u)
{
    f[u][1]=a[u];
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==fa[u]) continue;
        fa[v]=u;dp(v);
        f[u][1]+=f[v][0];
        f[u][0]+=max(f[v][0],f[v][1]);
    }
    val[u][0][0]=f[u][0];
    val[u][0][1]=f[u][0];
    val[u][1][0]=f[u][1];
    val[u][1][1]=0;
    sum[u]=val[u];
}

int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1,u,v;i<n;i++)
    {
        u=read();v=read();
        add_edge(u,v);
        add_edge(v,u);
    }
    dp(1);
    int lastans=0,x,v;
    while(m--)
    {
        x=read();v=read();
        lastans=gao(x,v);
        print(lastans);
    }
    flush();
    return 0;
}