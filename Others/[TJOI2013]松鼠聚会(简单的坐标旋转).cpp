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
const int N=100010;
struct Point
{
    int x,y,id;
    Point(int _x=0,int _y=0,int _id=0):x(_x),y(_y),id(_id){}
    void rotate(){*this=Point(x+y,y-x,id);}
} pt[N];
LL sum[N],res[N];

int main()
{
    int n=read();
    for(int i=1;i<=n;i++)
    {
        pt[i].x=read();
        pt[i].y=read();
        pt[i].id=i;
        pt[i].rotate();
    }
    sort(pt+1,pt+1+n,[](Point a,Point b){return a.x<b.x;});
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+pt[i].x;
    for(int i=1;i<=n;i++)
    {
        int p=pt[i].id;
        res[p]=1ll*(i-1)*pt[i].x-sum[i-1];
        res[p]+=(sum[n]-sum[i])-1ll*(n-i)*pt[i].x;
    }
    sort(pt+1,pt+1+n,[](Point a,Point b){return a.y<b.y;});
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+pt[i].y;
    for(int i=1;i<=n;i++)
    {
        int p=pt[i].id;
        res[p]+=1ll*(i-1)*pt[i].y-sum[i-1];
        res[p]+=(sum[n]-sum[i])-1ll*(n-i)*pt[i].y;
    }
    LL ans=INT64_MAX;
    for(int i=1;i<=n;i++) ans=min(ans,res[i]);
    printf("%lld\n",ans/2ll);
    return 0;
}