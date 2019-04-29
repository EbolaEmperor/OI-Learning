#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1000010;
struct FISH{int x,a;} fish[N];
LL sum[N<<2],sz[N<<2];
int n,m,p;
LL ans=0;

void insert(int o,int l,int r,int x,int c)
{
    if(l==r){sz[o]+=c;sum[o]+=(LL)x*c;return;}
    int mid=(l+r)/2;
    if(x<=mid) insert(o<<1,l,mid,x,c);
    else insert(o<<1|1,mid+1,r,x,c);
    sum[o]=sum[o<<1]+sum[o<<1|1];
    sz[o]=sz[o<<1]+sz[o<<1|1];
}

LL query(int o,int l,int r,LL k)
{
    if(l==r) return k*l;
    int mid=(l+r)/2;
    if(k<=sz[o<<1|1]) return query(o<<1|1,mid+1,r,k);
    else return sum[o<<1|1]+query(o<<1,l,mid,k-sz[o<<1|1]);
}

int main()
{
    scanf("%d%d%d",&n,&m,&p);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&fish[i].x,&fish[i].a);
    LL num=0,all=0;int j=1;
    for(int i=1;i<=m;i++)
    {
        int y,b,c;
        scanf("%d%d%d",&y,&b,&c);
        for(;j<=n&&fish[j].x<y;j++)
            ans=max(ans,query(1,1,1e6,min(num+=fish[j].a,all))-(LL)fish[j].x*p);
        all+=b;insert(1,1,1e6,c,b);
        ans=max(ans,query(1,1,1e6,min(num,all))-(LL)y*p);
    }
    for(;j<=n;j++)
        ans=max(ans,query(1,1,1e6,min(num+=fish[j].a,all))-(LL)fish[j].x*p);
    cout<<ans<<endl;
}