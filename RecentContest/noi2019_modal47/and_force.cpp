#include<bits/stdc++.h>
using namespace std;

const int N=10;
int n,a[N],p[N];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i),p[i]=i;
    long long ans=0;
    do{
        int cur=(1<<20)-1;
        long long sum=0;
        for(int i=1;i<=n;i++)
            cur&=a[p[i]],sum+=cur;
        ans=max(ans,sum);
    }while(next_permutation(p+1,p+1+n));
    printf("%lld\n",ans);
    return 0;
}