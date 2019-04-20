#include<bits/stdc++.h>
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
 
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
const int N=510;
int a[N][N],n,tot=0;
int xl,xr,yl,yr;
LL ss[N][N],len;
pii opt[N*N];
LD s[N],f[N],ans=-1e9;
int posl[N],pr;
 
bool check(LD x)
{
    LD res=-1e18;
    f[0]=-1e18;
    for(int i=1;i<=n;i++)
    {
        LD cur=s[i]-x*2;
        if(f[i-1]+cur>cur) f[i]=f[i-1]+cur,posl[i]=posl[i-1];
        else f[i]=cur,posl[i]=i;
        if(f[i]>res) res=f[i],pr=i;
    }
    return res>=x*2*len;
}
 
void gao()
{
    LD l=ans,r=1e15,mid;
    while(r-l>5e-8)
    {
        mid=(l+r)/2;
        if(check(mid))
        {
            ans=l=mid;
            yl=posl[pr];
            yr=pr;
        }
        else r=mid;
    }
}
 
int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            ss[i][j]=ss[i-1][j]+(a[i][j]=read());
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            opt[++tot]=pii(i,j);
    random_shuffle(opt+1,opt+1+tot);
    for(int i=1;i<=tot;i++)
    {
        int l=opt[i].first,r=opt[i].second;
        len=r-l+1;
        for(int j=1;j<=n;j++)
            s[j]=ss[r][j]-ss[l-1][j];
        if(check(ans+5e-8)) gao(),xl=l,xr=r;
    }
    printf("%.8Lf\n",ans);
    printf("%d %d\n",xl,yl);
    printf("%d %d\n",xr,yr);
    return 0;
}
