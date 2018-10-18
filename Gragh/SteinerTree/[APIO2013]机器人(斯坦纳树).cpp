#include<bits/stdc++.h>
#define FR first
#define SE second
using namespace std;

typedef pair<int,int> pii;
const int INF=0x3f3f3f3f;
const int N=510;
int mp[N][N],n,m,tot;
int f[10][10][N][N];
pii trans[N][N][4];
bool vis[N][N][4];
bool done[N][N];
struct node
{
    int x,y,w;
    node(int _x=0,int _y=0,int _w=0):x(_x),y(_y),w(_w){}
    bool operator < (const node &b) const{return w<b.w;}
} que[N*N];
queue<pii> q1,q2;

pii dfs(int x,int y,int t)  // t = 0(up), 1(left), 2(down), 3(right)
{
    pii &res=trans[x][y][t];int r=t;
    if(vis[x][y][t]) return res=pii(-1,-1);
    if(res.FR) return res;
    if(mp[x][y]==1) t=(t+1)&3;
    if(mp[x][y]==2) t=(t+3)&3;
    if(t==0&&mp[x-1][y]==-1) return res=pii(x,y);
    if(t==1&&mp[x][y-1]==-1) return res=pii(x,y);
    if(t==2&&mp[x+1][y]==-1) return res=pii(x,y);
    if(t==3&&mp[x][y+1]==-1) return res=pii(x,y);
    vis[x][y][r]=1;
    if(t==0) res=dfs(x-1,y,t);
    if(t==1) res=dfs(x,y-1,t);
    if(t==2) res=dfs(x+1,y,t);
    if(t==3) res=dfs(x,y+1,t);
    vis[x][y][r]=0;
    return res;
}

void ShortestPath(int dis[N][N])
{
    memset(done,0,sizeof(done));
    while(!q1.empty()||!q2.empty())
    {
        pii tmp;
        if(q1.empty()) tmp=q2.front(),q2.pop();
        else if(q2.empty()) tmp=q1.front(),q1.pop();
        else
        {
            pii t1=q1.front(),t2=q2.front();
            int x1=t1.FR,y1=t1.SE,x2=t2.FR,y2=t2.SE;
            if(dis[x1][y1]<dis[x2][y2]) tmp=q1.front(),q1.pop();
            else tmp=q2.front(),q2.pop();
        }
        int x=tmp.FR,y=tmp.SE;
        if(done[x][y]) continue;
        done[x][y]=1;
        for(int t=0;t<4;t++)
        {
            pii tmp2=trans[x][y][t];
            if(tmp2.FR<=0) continue;
            int vx=tmp2.FR,vy=tmp2.SE;
            if(dis[x][y]+1<dis[vx][vy])
            {
                dis[vx][vy]=dis[x][y]+1;
                q2.push(pii(vx,vy));
            }
        }
    }
}

int main()
{
    static char ss[N];
    scanf("%d%d%d",&tot,&m,&n);
    memset(f,0x3f,sizeof(f));
    for(int i=0;i<=n+1;i++) mp[i][0]=mp[i][m+1]=-1;
    for(int i=0;i<=m+1;i++) mp[0][i]=mp[n+1][i]=-1;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",ss+1);
        for(int j=1;j<=m;j++)
        {
            if(isdigit(ss[j]))
            {
                int x=ss[j]-'0';
                f[x][x][i][j]=0;
                mp[i][j]=0;
            }
            if(ss[j]=='x') mp[i][j]=-1;
            if(ss[j]=='.') mp[i][j]=0;
            if(ss[j]=='A') mp[i][j]=1;
            if(ss[j]=='C') mp[i][j]=2;
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            if(mp[i][j]==-1) continue;
            for(int k=0;k<4;k++)
            {
                if(trans[i][j][k].FR) continue;
                trans[i][j][k]=dfs(i,j,k);
            }
        }
    for(int len=0;len<tot;len++)
        for(int l=1,r=l+len;r<=tot;l++,r++)
        {
            int cnt=0;
            for(int k=l;k<r;k++)for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
                f[l][r][i][j]=min(f[l][r][i][j],f[l][k][i][j]+f[k+1][r][i][j]);
            for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
                if(f[l][r][i][j]<INF) que[++cnt]=node(i,j,f[l][r][i][j]);
            sort(que+1,que+1+cnt);
            for(int i=1;i<=cnt;i++)
            {
                node tmp=que[i];
                q1.push(pii(tmp.x,tmp.y));
            }
            ShortestPath(f[l][r]);
        }
    int ans=INF;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            ans=min(ans,f[1][tot][i][j]);
    if(ans==INF) puts("-1");
    else printf("%d\n",ans);
    return 0;
}