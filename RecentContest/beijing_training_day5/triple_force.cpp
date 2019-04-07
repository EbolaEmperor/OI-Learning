#include<bits/stdc++.h>
using namespace std;

const int N=20;
vector<int> pos[N];
int ans=0,used[N];
int n,m;

void dfs(int d,int cur)
{
    if(d==n+1){ans=max(ans,cur);return;}
    dfs(d+1,cur);
    for(int i=0;i<pos[d].size();i++)if(!used[pos[d][i]])
        for(int j=i+1;j<pos[d].size();j++)if(!used[pos[d][j]])
        {
            used[pos[d][i]]=used[pos[d][j]]=1;
            dfs(d+1,cur+1);
            used[pos[d][i]]=used[pos[d][j]]=0;
        }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        static char s[N];
        scanf("%s",s+1);
        for(int j=1;j<=m;j++)
            if(s[j]=='1') pos[i].push_back(j);
    }
    dfs(1,0);
    printf("%d\n",ans);
    return 0;
}
