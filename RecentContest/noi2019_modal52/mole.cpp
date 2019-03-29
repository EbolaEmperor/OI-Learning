#include<bits/stdc++.h>
using namespace std;

const double pi=acos(-1);
const int N=5000;
bool hole[N][N],vis[N][N];
double alpha,ans=0,co,si,ta;
int n,a;

double calc(double h)
{
    if(si<=co)
    {
        if(h<=si) return 0.5*h*h;
        if(h<=co) return si*h-0.5*si*si;
        return co*si-0.5*(si+co-h)*(si+co-h);
    }
    else
    {
        if(h<=co) return 0.5*h*h;
        if(h<=si) return co*h-0.5*co*co;
        return co*si-0.5*(si+co-h)*(si+co-h);
    }
}

void dfs(int x,int y,double h)
{
    if(vis[x][y]||!hole[x][y]||h<=0) return;
    h=min(h,si+co);vis[x][y]=1;
    ans+=a?calc(h):1;
    dfs(x,y+1,h-co);
    dfs(x,y-1,h+co);
    dfs(x+1,y,h-si);
    dfs(x-1,y,h+si);
}

int main()
{
    scanf("%d%d",&n,&a);
    alpha=(double)a/180.0*pi;
    si=sin(alpha);
    co=cos(alpha);
    ta=tan(alpha);
    hole[1][1]=1;
    for(int k=1;k<n;k++)
    {
        for(int i=1;i<(1<<k);i++)
        {
            for(int j=1;j<(1<<k);j++)
            {
                hole[i|1<<k][j]=hole[i][j];
                hole[(1<<k)-j][i|1<<k]=hole[i][j]^1;
                hole[(1<<k)+j][i|1<<k]=hole[i][j]^1;
            }
            hole[i][1<<k]=1;
            hole[i|1<<k][1<<k]=1;
            hole[1<<k][i|1<<k]=1;
        }
        hole[1<<k][1<<k]=1;
    }
    for(int i=1;i<(1<<n);i++)
        dfs(i,(1<<n)-1,co);
    if(a) ans/=si*co;
    printf("%.6lf\n",ans);
    return 0;
}