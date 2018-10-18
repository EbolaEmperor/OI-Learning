#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*bH,*bT;
inline char Get()
{
    if(bH==bT) bT=(bH=buf)+fread(buf,1,S,stdin);
    if(bH==bT) return -1;return *bH++;
}
inline int read()
{
    int x=0,fg=1;char c=Get();
    while(!isdigit(c)&&c!='-') c=Get();
    if(c=='-') fg=-1,c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x*fg;
}

typedef long long LL;
const int N=100010;
int num[N<<2];
int a[N],b[N],n,m,k;
LL sum[N],dp[N];
int L[N],R[N],H[N<<1];

void pushdown(int o)
{
    if(!num[o]) return;
    num[o<<1]=num[o<<1|1]=num[o];
    num[o]=0;
}

void Modify(int o,int l,int r,int nl,int nr,int x)
{
    if(nl>nr) return;
    if(l>=nl&&r<=nr){num[o]=x;return;}
    int mid=(l+r)/2;pushdown(o);
    if(nl<=mid) Modify(o<<1,l,mid,nl,nr,x);
    if(nr>mid) Modify(o<<1|1,mid+1,r,nl,nr,x);
}

int Query(int o,int l,int r,int p)
{
    if(l==r) return num[o];
    int mid=(l+r)/2;pushdown(o);
    if(p<=mid) return Query(o<<1,l,mid,p);
    else return Query(o<<1|1,mid+1,r,p);
}

LL gao(int x)
{
    int p=Query(1,1,m,x);
    return p?dp[p]+(H[L[p]]-H[x]+k)%k:0;
}

int main()
{
    n=read();k=read();
    for(int i=1;i<=n;i++)
    {
        a[i]=read();b[i]=read();
        sum[i]=sum[i-1]+a[i];
        if(b[i]==2) continue;
        if(2*a[i]>k){puts("-1");return 0;}
    }
    for(int i=1;i<=n;i++)
    {
        if(b[i]==1)
        {
            L[i]=(k-2ll*sum[i-1]%k)%k;
            R[i]=(k-2ll*sum[i]%k)%k;
        }
        else L[i]=0,R[i]=k-1;
        H[2*i]=L[i];H[2*i-1]=R[i];
    }
    sort(H+1,H+1+2*n);
    m=unique(H+1,H+1+2*n)-(H+1);
    for(int i=1;i<=n;i++)
    {
        L[i]=lower_bound(H+1,H+1+m,L[i])-H;
        R[i]=lower_bound(H+1,H+1+m,R[i])-H;
    }
    for(int i=n;i>=1;i--)
    {
        dp[i]=gao(L[i]);
        if(L[i]>R[i]) Modify(1,1,m,R[i]+1,L[i]-1,i);
        else Modify(1,1,m,1,L[i]-1,i),Modify(1,1,m,R[i]+1,m,i);
    }
    LL ans=dp[1];
    for(int i=m;i>=1;i--) ans=min(ans,gao(i));
    printf("%lld\n",ans+2ll*sum[n]);
    return 0;
}