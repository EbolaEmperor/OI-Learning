#include<bits/stdc++.h>
using namespace std;

const int N=200010;
int n,m,a[N];

bool check(int p)
{
    for(int i=p;i<=n*2;i++)
        if(a[i]+a[n*2-i+p]<m) return 0;
    return 1;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n*2;i++) scanf("%d",a+i);
    sort(a+1,a+1+n*2);
    int l=-1,r=n,mid;
    while(r-l>1)
    {
        mid=(l+r)/2;
        if(check(mid*2+1)) r=mid;
        else l=mid;
    }
    r<<=1;
    int ans=0;
    for(int i=1;i<=r;i++)
        ans=max(ans,a[i]+a[r-i+1]);
    for(int i=r+1;i<=n*2;i++)
        ans=max(ans,a[i]+a[n*2-i+r+1]-m);
    printf("%d\n",ans);
    return 0;
}