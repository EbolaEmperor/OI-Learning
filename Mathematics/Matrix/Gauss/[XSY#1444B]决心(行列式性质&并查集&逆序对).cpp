#include<bits/stdc++.h>
#define L first
#define R second
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

typedef pair<int,int> pii;
const int ha=1e9+7;
const int N=100010;
pii X[N],Y[N],*A;
int n,fa[N],val[N],idx[N];
int bit[N];

inline int lowbit(const int &x){return x&-x;}
void add(int p){for(;p<=n;p+=lowbit(p)) bit[p]^=1;}
int sum(int p){int res=0;for(;p;p-=lowbit(p)) res^=bit[p];return res;}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

int gao(pii *gg)
{
    A=gg;
    for(int i=0;i<=n;i++) fa[i]=i;
    for(int i=1;i<=n;i++) idx[i]=i;
    sort(idx+1,idx+1+n,[](int x,int y){return A[x]<A[y];});
    for(int i=n;i>=1;i--)
    {
        int pos=idx[i];
        int t=find(A[pos].R);
        if(t<A[pos].L) return 0;
        val[pos]=t;
        fa[t]=A[pos].L-1;
    }
    int res=1;
    memset(bit,0,sizeof(bit));
    for(int i=n;i>=1;i--)
    {
        if(sum(val[i]))
            res=ha-res;
        add(val[i]);
    }
    for(int i=1;i<=n;i++)
        res=1ll*res*(A[i].R-A[i].L+1)%ha;
    return Pow(res,ha-2);
}

int main()
{
    for(int T=read();T;T--)
    {
        n=read();
        for(int i=1;i<=n;i++)
            X[i].L=read(),X[i].R=read(),Y[i].L=read(),Y[i].R=read();
        int ans=1ll*gao(X)*gao(Y)%ha;
        printf("%d\n",ans);
    }
    return 0;
}