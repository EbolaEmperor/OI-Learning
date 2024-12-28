#include<bits/stdc++.h>
using namespace std;

const int N=105,M=20005;
int s,n,m,a[N][N];
int f[2][M];

int main()
{
    scanf("%d%d%d",&s,&n,&m);
    for(int i=1;i<=s;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",a[i]+j);
    int pp=0;
    for(int i=1;i<=n;i++,pp^=1)
    {
        static int sum[M],key[N];
        int tot=0;
        memset(sum,0,sizeof(int)*(m+1));
        for(int j=1;j<=s;j++)
            if(a[j][i]*2<m) key[++tot]=a[j][i]*2+1,sum[a[j][i]*2+1]+=i;
        for(int i=1;i<=m;i++) sum[i]+=sum[i-1];
        memcpy(f[pp^1],f[pp],sizeof(int)*(m+1));
        for(int k=1;k<=tot;k++)
            for(int j=m-key[k];j>=0;j--)
                f[pp^1][j+key[k]]=max(f[pp^1][j+key[k]],f[pp][j]+sum[key[k]]);
    }
    int ans=0;
    for(int i=0;i<=m;i++)
        ans=max(ans,f[pp][i]);
    printf("%d\n",ans);
    return 0;
}
