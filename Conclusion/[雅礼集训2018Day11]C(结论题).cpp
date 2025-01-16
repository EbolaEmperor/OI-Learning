#include<bits/stdc++.h>
using namespace std;

const int N=100010;
int deg[N],n;

int main()
{
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        deg[u]++;deg[v]++;
    }
    int ans=0;
    sort(deg+1,deg+1+n);
    for(int i=1;i<=n;i++)
        ans+=(i&1)?-deg[i]:deg[i];
    printf("%d\n",ans/2+(n&1));
    return 0;
}