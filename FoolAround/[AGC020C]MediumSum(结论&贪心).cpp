#include<bits/stdc++.h>
using namespace std;

const int N=2010;
int x,n,sum=0,ans;
bitset<N*N> S;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&x),S|=S<<x,S[x]=1,sum+=x;
    for(ans=(sum+1)/2;ans<=sum;ans++) if(S[ans]) break;
    printf("%d\n",ans);
    return 0;
}