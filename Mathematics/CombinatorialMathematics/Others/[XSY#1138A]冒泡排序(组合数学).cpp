#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
LL f[25][25];
int ans[25];
bool vis[25];
LL now,t;

int main()
{
    int n,m;LL k;
    scanf("%d%d%lld",&n,&m,&k);
    for(int i=1;i<=n;i++)
    {
        f[0][i]=1;
        for(int j=1;j<=i;j++)
            f[j][i]=f[j-1][i]*j;
    }
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            f[j][i]=(i+1)*f[j-1][i];
    for(int i=1;i<=n;i++)
    {
        LL tmp=0;
        for(int j=1;j<=n;j++)
        {
            if(vis[j]) continue;
            vis[j]=1;
            if(tmp>m) break;
            if(now==m||tmp==m) t=f[n-i][m];
            else t=f[n-i][m]-f[n-i][m-1];
            if(k<=t)
            {
                if(tmp>now) now=tmp;
                ans[i]=j;break;
            }
            else k-=t,vis[j]=0;
            tmp++;
        }
    }
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    return 0;
}