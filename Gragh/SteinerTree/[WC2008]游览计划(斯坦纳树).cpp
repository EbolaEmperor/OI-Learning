#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int N=15,S=1050;
const int INF=0x7f7f7f7f;
int n,m,a[N][N],f[S][N][N],tot=0;
struct PRE{int x,y,s;} pre[S][N][N];
int mov[4][2]={ {0,-1},{0,1},{-1,0},{1,0} };
char ans[N][N];
bool inq[N][N];
queue<pii> q;

void spfa(int s)
{
    while(!q.empty())
    {
        pii tmp=q.front();q.pop();
        int x=tmp.first,y=tmp.second;
        for(int i=0;i<4;i++)
        {
            int vx=x+mov[i][0],vy=y+mov[i][1];
            if(vx<1||vx>n||vy<1||vy>m) continue;
            if(f[s][x][y]+a[vx][vy]<f[s][vx][vy])
            {
                f[s][vx][vy]=f[s][x][y]+a[vx][vy];
                pre[s][vx][vy]={x,y,s};
                if(inq[vx][vy]) continue;
                q.push(pii(vx,vy));
                inq[vx][vy]=1;
            }
        }
        inq[x][y]=0;
    }
}

void dfs(int x,int y,int s)
{
    if(!x&&!y) return;
    if(ans[x][y]=='_') ans[x][y]='o';
    PRE tmp=pre[s][x][y];
    int px=tmp.x,py=tmp.y,ps=tmp.s;
    dfs(px,py,ps);
    if(px==x&&py==y) dfs(x,y,s^ps);
}

int main()
{
    int ax,ay;
    scanf("%d%d",&n,&m);
    memset(f,0x7f,sizeof(f));
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            ans[i][j]='_';
            scanf("%d",a[i]+j);
            if(a[i][j]==0)
            {
                f[1<<tot][i][j]=0;
                tot++;ax=i;ay=j;
                ans[i][j]='x';
            }
        }
        ans[i][m+1]='\0';
    }
    for(int s=0;s<(1<<tot);s++)
    {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            {
                for(int t=s&(s-1);t;t=(t-1)&s)
                    if(f[t][i][j]+f[s^t][i][j]-a[i][j]<f[s][i][j])
                    {
                        f[s][i][j]=f[t][i][j]+f[s^t][i][j]-a[i][j];
                        pre[s][i][j]={i,j,t};
                    }
                if(f[s][i][j]<INF) q.push(pii(i,j)),inq[i][j]=1;
            }
        spfa(s);
    }
    printf("%d\n",f[(1<<tot)-1][ax][ay]);
    dfs(ax,ay,(1<<tot)-1);
    for(int i=1;i<=n;i++)
        printf("%s\n",ans[i]+1);
    return 0;
}