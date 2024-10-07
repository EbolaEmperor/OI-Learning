// 主要思路：min-max容斥。min的意义是覆盖到任一子集的期望次数，max的意义是覆盖全集的期望次数
#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
char a[7][610];
int f[2][65][1200];
//f[i][s][c]：第i个格子(滚动)，当前轮廓线选择状态为s，覆盖方案数为c时的带容斥系数集合数
int n,m,k=0,inv[1200];

void add(int &x,const int &y){x=(x+y>=ha)?(x+y-ha):(x+y);}

int main()
{
    scanf("%d%d",&n,&m);
    int sum=(n-1)*m+(m-1)*n,all=(1<<n)-1;
    for(int i=1;i<=n;i++)
        scanf("%s",a[i]+1);
    f[0][0][0]=ha-1;
    for(int j=1;j<=m;j++)
        for(int i=1;i<=n;i++,k^=1)
        {
            memset(f[k^1],0,sizeof(f[k^1]));
            for(int s=0;s<=all;s++)
                for(int c=0;c<=sum;c++)
                {
                    if(!f[k][s][c]) continue;
                    add(f[k^1][s&(all-(1<<i-1))][c],f[k][s][c]);
                    //不选择a[i][j]，集合大小、覆盖方案均不变，更新轮廓线状态即可
                    if(a[i][j]=='.') continue;
                    int p=(i<n)+(j<m)+(j>1&&!(s>>i-1&1))+(i>1&&!(s>>i-2&1));
                    //计算选择a[i][j]后新增的覆盖方案数，且不要与之前算重
                    add(f[k^1][s|1<<i-1][c+p],ha-f[k][s][c]);
                    //选择a[i][j]，集合大小奇偶性改变，容斥系数添负号
                }
        }
    inv[1]=1;
    for(int i=2;i<=sum;i++)
        inv[i]=1ll*(ha-ha/i)*inv[ha%i]%ha;
    int ans=0;
    for(int s=0;s<=all;s++)
        for(int c=0;c<=sum;c++)
            add(ans,1ll*f[k][s][c]*inv[c]%ha);
    //覆盖方案数为c的集合，第一次覆盖到任一子集的概率为c/sum，期望次数则为sum/c
    ans=1ll*ans*sum%ha;
    printf("%d\n",ans);
    return 0;
}