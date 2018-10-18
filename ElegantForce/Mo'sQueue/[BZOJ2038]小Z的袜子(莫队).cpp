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
    }
}

using namespace IO;
typedef long long LL;
const int N=50010,B=225;
struct Qry{int l,r,id;} q[N];
int col[N],cnt[N],n,m;
LL cur=0,ans[N][2];

inline bool operator < (const Qry &a,const Qry &b)
{
    if(a.l/B!=b.l/B) return a.l<b.l;
    if((a.l/B)&1) return a.r>b.r;
    else return a.r<b.r;
}

void ins(int p){int &x=cnt[col[p]];cur-=1ll*x*(x-1)/2;x++;cur+=1ll*x*(x-1)/2;}
void del(int p){int &x=cnt[col[p]];cur-=1ll*x*(x-1)/2;x--;cur+=1ll*x*(x-1)/2;}

int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++) col[i]=read();
    for(int i=1;i<=m;i++)
    {
        q[i].l=read();
        q[i].r=read();
        q[i].id=i;
    }
    sort(q+1,q+1+m);
    int pl=1,pr=1;cnt[col[1]]=1;
    for(int i=1;i<=m;i++)
    {
        while(pl>q[i].l) ins(--pl);
        while(pr<q[i].r) ins(++pr);
        while(pl<q[i].l) del(pl++);
        while(pr>q[i].r) del(pr--);
        ans[q[i].id][0]=cur;
        int t=q[i].r-q[i].l+1;
        ans[q[i].id][1]=1ll*t*(t-1)/2;
    }
    for(int i=1;i<=m;i++)
    {
        if(ans[i][0]==0)
        {
            putc('0');putc('/');
            putc('1');putc('\n');
            continue;
        }
        LL g=__gcd(ans[i][0],ans[i][1]);
        print(ans[i][0]/g);putc('/');
        print(ans[i][1]/g);putc('\n');
    }
    flush();
    return 0;
}