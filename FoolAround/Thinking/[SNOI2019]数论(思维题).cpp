#include<bits//stdc++.h>
using namespace std;

typedef long long LL;
const int N=1000010;
int a[N],b[N],n,m,P,Q;LL T;
int rk[N],sum[N],val[N],tot[N],vis[N];

int main()
{
    scanf("%d%d%d%d%lld",&P,&Q,&n,&m,&T);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=m;i++) scanf("%d",b+i),sum[b[i]]=val[b[i]]=1;
    for(int i=0;i<Q;i++)
    {
        if(vis[i]) continue;
        vis[i]=1;rk[i]=1;int x,pre;
        for(x=(i+P)%Q,pre=i;x!=i;pre=x,x=(x+P)%Q)
        {
            vis[x]=1;
            rk[x]=rk[pre]+1;
            sum[x]+=sum[pre];
        }
        tot[i]=sum[pre];
        for(x=(i+P)%Q;x!=i;x=(x+P)%Q) tot[x]=tot[i];
    }
    int len=Q/__gcd(P,Q);LL ans=0;
    for(int i=1;i<=n;i++)
    {
        LL step=(T-1-a[i])/P;
        ans+=step/len*tot[a[i]%Q];
        int l=a[i]%Q,r=(a[i]+step%len*P)%Q;
        if(rk[l]<=rk[r]) ans+=sum[r]-sum[l]+val[l];
        else ans+=tot[l]-(sum[l]-sum[r]-val[l]);
    }
    cout<<ans<<endl;
    return 0;
}