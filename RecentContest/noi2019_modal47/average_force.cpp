#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=5010;
bool mark[N];
int a[N],inv[N],n,ans=0;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    inv[1]=1;
    for(int i=2;i<=n;i++)
        inv[i]=1ll*(ha-ha/i)*inv[ha%i]%ha;
    for(int l=1;l<=n;l++)
    {
        memset(mark,0,sizeof(mark));
        int cur=0;
        for(int r=l;r<=n;r++)
        {
            if(a[r]<=n) mark[a[r]]=1;
            while(mark[cur]) cur++;
            ans=(ans+1ll*cur*inv[r-l+1])%ha;
        }
    }
    printf("%d\n",ans);
    return 0;
}