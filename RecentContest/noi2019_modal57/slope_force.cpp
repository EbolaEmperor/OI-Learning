#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1010;
LL sum[N];
int n;

int main()
{
    scanf("%d",&n);
    for(int i=1,x;i<=n;i++)
        scanf("%d",&x),sum[i]=sum[i-1]+x;
    LL ans=INT64_MAX;
    for(int i=1;i<=n;i++)
        for(int j=1;j<i;j++)
            ans=min(ans,(LL)(i-j)*(i-j)+(sum[i]-sum[j])*(sum[i]-sum[j]));
    cout<<ans<<endl;
    return 0;
}