#include<bits/stdc++.h>
#define FR first
#define SE second
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
    int x=0,fg=1;char c=Get();
    while(!isdigit(c)&&c!='-') c=Get();
    if(c=='-') fg=-1,c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x*fg;
}

const int N=1000010;
int mx[N<<2],leaf;
int n,L,R,a[N],sum[N];
int eql[N],eqr[N],f[N];
pair<int,int> Hash[N];

void maintain(int o){mx[o]=max(mx[o<<1],mx[o<<1|1]);}
void build()
{
    for(leaf=1;leaf<=n+2;leaf<<=1);
    for(int i=0;i<=(leaf<<1|1);i++) mx[i]=-INT_MAX;
}
void modify(int k,int x)
{
    mx[leaf+k]=x;
    for(int i=(leaf+k)>>1;i;i>>=1) maintain(i);
}
int query(int l,int r)
{
    int res=-INT_MAX;
    if(r<l) return res;
    for(l=leaf+l-1,r=leaf+r+1;l^r^1;l>>=1,r>>=1)
    {
        if(~l&1) res=max(res,mx[l^1]);
        if(r&1) res=max(res,mx[r^1]);
    }
    return res;
}

int main()
{
    n=read();L=read();R=read();build();
    for(int i=1;i<=n;i++) a[i]=read();
    Hash[1]=make_pair(0,0);
    for(int i=1;i<=n;i++)
    {
        sum[i]=sum[i-1]+a[i];
        Hash[i+1].FR=sum[i];
        Hash[i+1].SE=i;
    }
    sort(Hash+1,Hash+2+n);
    for(int i=1;i<=n+1;i++)
    {
        if(Hash[i].FR!=Hash[i-1].FR) eql[i]=i;
        else eql[i]=eql[i-1];
    }
    for(int i=n+1;i>=1;i--)
    {
        if(Hash[i].FR!=Hash[i+1].FR) eqr[i]=i;
        else eqr[i]=eqr[i+1];
    }
    for(int i=1;i<=n+1;i++) sum[Hash[i].SE]=i;
    for(int i=1;i<=n;i++)
    {
        if(i-R-1>=0) modify(sum[i-R-1],-INT_MAX);
        if(i-L>=0) modify(sum[i-L],f[i-L]);
        int x=sum[i];
        int f1=query(1,eql[x]-1);
        int f2=query(eql[x],eqr[x]);
        int f3=query(eqr[x]+1,n+1);
        if(f1>-INT_MAX) f1++;
        if(f3>-INT_MAX) f3--;
        f[i]=max(max(f1,f2),f3);
    }
    if(f[n]==-INT_MAX) puts("Impossible");
    else printf("%d\n",f[n]);
    return 0;
}