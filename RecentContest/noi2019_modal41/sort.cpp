#include<bits/stdc++.h>
using namespace std;

const int N=1010;
int f[2][N][N],p[N][N];
int cnt[55][N][2];
char num[N][55];
int n,B;

void prework()
{
    for(int i=1;i<=B;i++)
        for(int j=1;j<=n;j++)
        {
            cnt[i][j][num[j][i]-'0']++;
            cnt[i][j][0]+=cnt[i][j-1][0];
            cnt[i][j][1]+=cnt[i][j-1][1];
        }
}

int gao()
{
    int pp=0;
    for(int i=B;i>=1;i--,pp^=1)
    {
        memset(f[pp],0x3f,sizeof(f[pp]));
        for(int j=0;j<=n;j++)
            f[pp][j][j]=0,p[j][j]=j,f[pp^1][j+1][j]=0;
        for(int len=2;len<=n;len++)
            for(int l=1;l<=n-len+1;l++)
            {
                int r=l+len-1;
                for(int k=p[l][r-1];k<=p[l+1][r];k++)
                {
                    int tmp=f[pp^1][l][k]+f[pp^1][k+1][r]+(cnt[i][k][1]-cnt[i][l-1][1])+(cnt[i][r][0]-cnt[i][k][0]);
                    if(tmp<f[pp][l][r]) f[pp][l][r]=tmp,p[l][r]=k;
                }
                f[pp][l][r]=min(f[pp][l][r],f[pp^1][l][r]+min(cnt[i][r][0]-cnt[i][l-1][0],cnt[i][r][1]-cnt[i][l-1][1]));
            }
    }
    return f[pp^1][1][n];
}

int main()
{
    scanf("%d%d",&n,&B);
    for(int i=1;i<=n;i++)
        scanf("%s",num[i]+1);
    prework();
    printf("%d\n",gao());
    return 0;
}