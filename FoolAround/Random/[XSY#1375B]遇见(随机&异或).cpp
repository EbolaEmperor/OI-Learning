#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1000010;
int n,a[N],nxt[N],pos[N];
LL rnd[N],sum[N];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",a+i),pos[a[i]]=n+1;
    for(int i=n;i>=1;i--) nxt[i]=pos[a[i]],pos[a[i]]=i;
    for(int i=1;i<=1000000;i++) rnd[i]=(LL)rand()<<30|rand();
    int ans=0;
    for(int i=n;i>=1;i--)
    {
        for(int p=nxt[i];p<=n;p++) sum[p]^=rnd[a[i]];
        for(int p=i;p<=n;p++) if(!sum[p]) ans++;
    }
    printf("%d\n",ans);
    return 0;
}