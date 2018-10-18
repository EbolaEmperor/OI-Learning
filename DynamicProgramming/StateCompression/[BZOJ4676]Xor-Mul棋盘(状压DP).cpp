#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=7,M=100010;
int a[N][M],b[N][M],n,m;
int c1[N][M],c2[N][M],w[35];
LL f[M][35],ans=0;

void gao(int bit)
{
    memset(f,0,sizeof(f));
    for(int i=0;i<m;i++)
    {
        if(i>=1)
        {
            memset(w,0,sizeof(w));
            for(int s=0;s<(1<<n);s++)
                for(int j=1;j<=n;j++)
                    if(s&(1<<j-1)) w[s]+=c1[j][i];
        }
        for(int s=0;s<(1<<n);s++)
        {
            LL tmp=0;
            for(int j=0;j<n;j++)
            {
                if((s>>j&1)^(a[j+1][i+1]>>bit&1)) tmp+=b[j+1][i+1];
                if((s>>j&1)^(s>>(j+1)%n&1)) tmp+=c2[j+1][i+1];
            }
            if(!i){f[i+1][s]=tmp;continue;}
            f[i+1][s]=INT64_MAX;
            for(int t=0;t<(1<<n);t++)
                f[i+1][s]=min(f[i+1][s],f[i][t]+tmp+w[s^t]);
        }
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&a[i][j]);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&b[i][j]);
    for(int i=1;i<=n;i++) for(int j=1;j<m;j++) scanf("%d",&c1[i][j]);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&c2[i][j]);
    for(int i=0;i<=19;i++)
    {
        gao(i);
        LL res=INT64_MAX;
        for(int s=0;s<(1<<n);s++)
            res=min(res,f[m][s]);
        ans+=res<<i;
    }
    cout<<ans<<endl;
    return 0;
}