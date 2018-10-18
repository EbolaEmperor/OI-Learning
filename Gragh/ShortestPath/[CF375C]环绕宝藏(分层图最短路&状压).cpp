#include<bits/stdc++.h>
using namespace std;

const int N=25;
int mp[N][N],n,m,sx,sy,tot=0;
int val[9],pos[9][2],pp[9];
bool inq[N][N][265];
int cost[N][N][265];
struct S{int x,y,s;};
int mov[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

void add_obj(int i,int j)
{
    mp[i][j]=++tot;
    pos[tot][0]=i;
    pos[tot][1]=j;
}

void spfa()
{
    queue<S> q;
    q.push({sx,sy,0});
    inq[sx][sy][0]=1;
    memset(cost,0x7f,sizeof(cost));
    cost[sx][sy][0]=0;
    while(!q.empty())
    {
        S tmp=q.front();
        int x=tmp.x,y=tmp.y,s=tmp.s;
        for(int i=0;i<4;i++)
        {
            int tx=x+mov[i][0],ty=y+mov[i][1],ts=s;
            if(tx<1||tx>n||ty<1||ty>m||mp[tx][ty]) continue;
            if(ty!=y)
            {
                for(int j=1;j<=tot;j++)
                    if(pos[j][0]<tx&&pos[j][1]==max(y,ty))
                        ts^=1<<j-1;
            }
            if(cost[x][y][s]+1<cost[tx][ty][ts])
            {
                cost[tx][ty][ts]=cost[x][y][s]+1;
                if(inq[tx][ty][ts]) continue;
                inq[tx][ty][ts]=1;
                q.push({tx,ty,ts});
            }
        }
        q.pop();inq[x][y][s]=0;
    }
}

int main()
{
    static char s[N];
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s+1);
        for(int j=1;j<=m;j++)
        {
            if(s[j]=='B') add_obj(i,j),val[tot]=-1000;
            else if(isdigit(s[j])) add_obj(i,j),pp[s[j]-'0']=tot;
            else if(s[j]=='#') mp[i][j]=-1;
            else if(s[j]=='S') sx=i,sy=j;
        }
    }
    for(int i=1;pp[i];i++)
        scanf("%d",val+pp[i]);
    spfa();int ans=0;
    for(int s=0;s<(1<<tot);s++)
    {
        int tmp=-cost[sx][sy][s];
        for(int i=1;i<=tot;i++)
        {
            if(!(s&(1<<i-1))) continue;
            if(val[i]==-1000) goto fuck;
            tmp+=val[i];
        }
        ans=max(ans,tmp);
        fuck: ;
    }
    cout<<ans<<endl;
    return 0;
}