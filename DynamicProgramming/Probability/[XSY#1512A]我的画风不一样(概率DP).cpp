#include<bits/stdc++.h>
#define FR first
#define SE second
using namespace std;

typedef pair<double,double> pdd;
pdd f[110][110];
bool vis[110][110];
double C[210][210];
int n,m,R,B;

void Init()
{
    for(int i=0;i<=200;i++)
    {
        C[i][0]=1;
        for(int j=1;j<=i;j++)
            C[i][j]=C[i-1][j]+C[i-1][j-1];
    }
}

pdd dp(int r,int b)
{
    pdd &res=f[r][b];
    if(vis[r][b]) return res;
    vis[r][b]=1;res=pdd(0.0,1.0);
    if(r==0) return res=pdd(1.0,0.0);
    for(int num=1;num<=min(n,r+b);num++)
    {
        pdd tans(0,0);
        for(int i=max(0,num-b);i<=min(num,r);i++)
        {
            pdd tmp=dp(r-i,b-(num-i));
            double prb=C[r][i]/C[r+b][num]*C[b][num-i];
            tans.FR+=prb*tmp.SE;
            tans.SE+=prb*tmp.FR;
        }
        if(tans.FR<res.FR) continue;
        if(tans.FR>res.FR) res=tans;
        else if(tans.SE<res.SE) res=tans;
    }
    return res;
}

int main()
{
    double ans=0;Init();
    cin>>R>>B>>n>>m;
    for(int i=0;i<=m;i++)
    {
        pdd tmp=dp(R-i,B-(m-i));
        double prb=C[R][i]/C[R+B][m]*C[B][m-i];
        ans+=prb*tmp.FR;
    }
    printf("%.7lf\n",ans);
    return 0;
}