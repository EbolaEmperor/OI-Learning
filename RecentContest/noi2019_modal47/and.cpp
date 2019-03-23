#include<bits/stdc++.h>
using namespace std;

const int N=1<<20;
long long cnt[N+5],f[N+5];
int n;

int main()
{
    scanf("%d",&n);
    for(int i=1,x;i<=n;i++)
        scanf("%d",&x),cnt[x]++;
    for(int i=1;i<N;i<<=1)
        for(int j=0;j<N;j+=i<<1)
            for(int k=0;k<i;k++)
                cnt[j+k]+=cnt[i+j+k];
    for(int i=N-1;i>=0;i--)
        for(int k=0;k<20;k++)
            if(!(i>>k&1)) f[i]=max(f[i],f[i|1<<k]+(cnt[i]-cnt[i|1<<k])*i);
    printf("%lld\n",f[0]);
    return 0;
}