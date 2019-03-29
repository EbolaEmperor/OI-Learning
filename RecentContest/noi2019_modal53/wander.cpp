#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int ha=998244353,N=65,B=32;
int f[N][N][N]; //f[x][y][t]: 从(0,0)出发，走了t步后第一次到达(x,y)的方案数
int g[N][N][N]; //g[x][y][t]: 从(x,y)出发，走了t步后第一次回到(x,y)的方案数
int h[N][N][N]; //h[x][y][t]: 从(x,y)出发，随便乱走t步的方案数
int t,n,k,bad[N][N];

inline void add(int &x,const int &y){x=(x+y>=ha)?(x+y-ha):(x+y);}

void gao_f()
{
    for(int x=-t;x<=t;x++)
        for(int y=abs(x)-t;y<=t-abs(x);y++)
        {
            if(bad[B+x][B+y]) continue;
            if(x==0&&y==0){f[B+x][B+y][0]=1;continue;}
            static int dp[2][N][N];
            memset(dp[0],0,sizeof(dp[0]));
            int cur=0;dp[cur][B][B]=1;
            for(int i=1;i<=t;i++,cur^=1)
            {
                memset(dp[cur^1],0,sizeof(dp[cur^1]));
                for(int j=-t;j<=t;j++)
                    for(int k=abs(j)-t;k<=t-abs(j);k++)
                    {
                        if(bad[B+j][B+k]) continue;
                        int tmp=dp[cur][B+j-1][B+k];
                        add(tmp,dp[cur][B+j+1][B+k]);
                        add(tmp,dp[cur][B+j][B+k-1]);
                        add(tmp,dp[cur][B+j][B+k+1]);
                        if(j==x&&k==y) f[B+x][B+y][i]=tmp;
                        else dp[cur^1][B+j][B+k]=tmp;
                    }
            }
        }
}

void gao_g()
{
    for(int x=-t;x<=t;x++)
        for(int y=abs(x)-t;y<=t-abs(x);y++)
        {
            if(bad[B+x][B+y]) continue;
            static int dp[2][N][N];
            memset(dp[0],0,sizeof(dp[0]));
            int cur=0;dp[cur][B+x][B+y]=1;
            for(int i=1;i<=t;i++,cur^=1)
            {
                memset(dp[cur^1],0,sizeof(dp[cur^1]));
                for(int j=-t;j<=t;j++)
                    for(int k=abs(j)-t;k<=t-abs(j);k++)
                    {
                        if(bad[B+j][B+k]) continue;
                        int tmp=dp[cur][B+j-1][B+k];
                        add(tmp,dp[cur][B+j+1][B+k]);
                        add(tmp,dp[cur][B+j][B+k-1]);
                        add(tmp,dp[cur][B+j][B+k+1]);
                        if(j==x&&k==y) g[B+x][B+y][i]=tmp;
                        else dp[cur^1][B+j][B+k]=tmp;
                    }
            }
        }
}

void gao_h()
{
    for(int x=-t;x<=t;x++)
        for(int y=abs(x)-t;y<=t-abs(x);y++)
        {
            if(bad[B+x][B+y]) continue;
            static int dp[2][N][N];int cur=0;
            memset(dp[0],0,sizeof(dp[0]));
            dp[0][B+x][B+y]=h[B+x][B+y][0]=1;
            for(int i=1;i<=t;i++,cur^=1)
            {
                memset(dp[cur^1],0,sizeof(dp[cur^1]));
                for(int j=-t;j<=t;j++)
                    for(int k=abs(j)-t;k<=t-abs(j);k++)
                    {
                        if(bad[B+j][B+k]) continue;
                        int tmp=dp[cur][B+j-1][B+k];
                        add(tmp,dp[cur][B+j+1][B+k]);
                        add(tmp,dp[cur][B+j][B+k-1]);
                        add(tmp,dp[cur][B+j][B+k+1]);
                        add(h[B+x][B+y][i],tmp);
                        dp[cur^1][B+j][B+k]=tmp;
                    }
            }
        }
}

void polymul(int *a,int *b,int *res)
{
    static int tmp[N];
    memset(tmp,0,sizeof(int)*(t+1));
    for(int i=0;i<=t;i++)
        for(int j=0;j<=t-i;j++)
            tmp[i+j]=(tmp[i+j]+(LL)a[i]*b[j])%ha;
    memcpy(res,tmp,sizeof(int)*(t+1));
}

void polypow(int *a,int b,int *res)
{
    memset(res,0,sizeof(int)*(t+1));res[0]=1;
    for(;b;b>>=1,polymul(a,a,a))
        if(b&1) polymul(res,a,res);
}

int main()
{
    cin>>t>>n>>k;
    for(int i=1,x,y;i<=n;i++)
        cin>>x>>y,bad[B+x][B+y]=1;
    gao_f();gao_g();gao_h();
    int ans=0;
    for(int x=-t;x<=t;x++)
        for(int y=abs(x)-t;y<=t-abs(x);y++)
        {
            if(bad[B+x][B+y]) continue;
            static int poly[N];
            polypow(g[B+x][B+y],k-1,poly);
            polymul(poly,f[B+x][B+y],poly);
            polymul(poly,h[B+x][B+y],poly);
            add(ans,poly[t]);
        }
    cout<<ans<<endl;
    return 0;
}