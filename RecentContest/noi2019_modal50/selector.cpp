#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL INF=0x3f3f3f3f3f3f3f3fll;
inline void upmin(LL &x,const LL &y){if(y<x) x=y;}
inline void upmax(LL &x,const LL &y){if(y>x) x=y;}

const int N=300010;
int n,a[N];
LL m,sum[N],f[N];

void cdq(int l,int r)
{
    static LL mnf[N];
    static int mxa[N];
    if(l==r) return;
    int mid=(l+r)/2;
    cdq(l,mid);
    mxa[mid]=a[mid];mxa[mid+1]=a[mid+1];mnf[mid]=f[mid];
    for(int i=mid-1;i>=l;i--) mnf[i]=min(mnf[i+1],f[i]);
    for(int i=mid-1;i>=l;i--) mxa[i]=max(mxa[i+1],a[i]);
    for(int i=mid+2;i<=r;i++) mxa[i]=max(mxa[i-1],a[i]);
    int p1=l,p2=mid+1;
    for(int i=mid+1;i<=r;i++)
    {
        while(sum[i]-sum[p1]>m) p1++;
        while(p2-1>l&&mxa[p2-1]<=mxa[i]) p2--;
        if(p1>mid) break;
        upmin(f[i],mxa[i]+mnf[max(p1,p2-1)]);
    }
    p1=r;p2=mid;
    for(int i=mid+1;i<=r;i++) mnf[i]=INF;
    for(int i=mid;i>l;i--)
    {
        while(sum[p1]-sum[i-1]>m) p1--;
        while(p2<r&&mxa[p2+1]<=mxa[i]) p2++;
        if(p1<=mid) break;
        upmin(mnf[min(p1,p2)],f[i-1]+mxa[i]);
    }
    for(int i=r;i>mid;i--)
        upmin(f[i],mnf[i]),upmin(mnf[i-1],mnf[i]);
    cdq(mid+1,r);
}

int main()
{
    scanf("%d%lld",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i),sum[i]=sum[i-1]+a[i];
    memset(f,0x3f,sizeof(f));
    f[0]=0;cdq(0,n);
    printf("%lld\n",f[n]);
    return 0;
}