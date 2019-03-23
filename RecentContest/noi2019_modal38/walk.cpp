#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1000010;
int n,m,a[N];
LL f[N];

inline void upmin(LL &x,const LL &y){if(y<x) x=y;}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",a+i);
    memset(f,0x3f,sizeof(f));
    for(int i=n;i>=1;i--)
    {
        for(int j=m/i;j>=a[i];j--)
            upmin(f[j],f[j-a[i]]+(LL)i*a[i]);
        upmin(f[a[i]],i+i+(LL)i*a[i]);
    }
    f[0]=0;
    for(int i=m;i>=0;i--)
        if(f[i]<=m) return printf("%d\n",i),0;
    return 0;
}