#include<bits/stdc++.h>
using namespace std;

const int N=110,M=27;
int n,m,ch[N][M],pos[N];
bool vis[N][N];
int ans[N*N*N],cnt=0;

int dfs(int x,int y)
{
    vis[x][y]=1;
    if(x==0&&y==0) return 1;
    for(int i=0;i<m;i++)
    {
        if(vis[ch[x][i]][ch[y][i]]) continue;
        ans[++cnt]=i;
        if(dfs(ch[x][i],ch[y][i])) return 1;
        cnt--;
    }
    return 0;
}

int main()
{
    scanf("%d%d",&n,&m);
    if(n==1){puts("a");return 0;}
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&ch[i][j]);
    for(int i=0;i<n;i++) pos[i]=i;
    while(true)
    {
        memset(vis,0,sizeof(vis));
        int pre=cnt;
        if(!dfs(pos[0],pos[1]))
        {
            puts("[impossible]");
            return 0;
        }
        for(int i=pre+1;i<=cnt;i++)
            for(int u=0;u<n;u++)
                pos[u]=ch[pos[u]][ans[i]];
        sort(pos,pos+n);
        n=unique(pos,pos+n)-pos;
        if(n==1) break;
    }
    for(int i=1;i<=cnt;i++) putchar(ans[i]+'a');
    return 0;
}