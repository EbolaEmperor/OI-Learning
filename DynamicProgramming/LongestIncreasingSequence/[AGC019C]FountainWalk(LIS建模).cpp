#include<bits/stdc++.h>
#define X first
#define Y second
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
const double pi=acos(-1);
const int N=200010;
const int MX=1e8+5;
int x1,yy1,x2,yy2,n,tot=0,lis;
int g[N],idx[N],a[N],f[N],gx[N],ax[N];
pii pnt[N];
bool deled[N];

int LIS()
{
    int res=0;
    memset(g,0x7f,sizeof(g));
    for(int i=1;i<=tot;i++)
    {
        auto it=lower_bound(g+1,g+1+n,a[i]);
        if(*it==0x7f7f7f7f) res++;
        *it=a[i];
    }
    return res;
}

int main()
{
    x1=read();yy1=read();x2=read();yy2=read();n=read();
    for(int i=1;i<=n;i++) pnt[i].X=read(),pnt[i].Y=read();
    if(x2<x1||yy2<yy1)
    {
        if(x1<=x2) goto swap2;
        x1=MX-x1;x2=MX-x2;
        for(int i=1;i<=n;i++) pnt[i].X=MX-pnt[i].X;
        if(yy1<=yy2) goto work;
        swap2: yy1=MX-yy1;yy2=MX-yy2;
        for(int i=1;i<=n;i++) pnt[i].Y=MX-pnt[i].Y;
    }
    work: sort(pnt+1,pnt+1+n);
    for(int i=1;i<=n;i++)
        if(pnt[i].X>=x1&&pnt[i].X<=x2&&pnt[i].Y>=yy1&&pnt[i].Y<=yy2) a[++tot]=pnt[i].Y;
    double ans=100.0*(x2-x1+yy2-yy1)+(pi*5-20)*(lis=LIS());
    if(lis==min(x2-x1,yy2-yy1)+1) ans+=pi*5;
    output: printf("%.12lf\n",ans);
    return 0;
}