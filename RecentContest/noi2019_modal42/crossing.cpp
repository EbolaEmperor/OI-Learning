#include<bits/stdc++.h>
using namespace std;

const int N=100010;
bool vis1[N],vis2[N];
int *v[N],d[N];
int n,m;

void dfs(int u)
{
    for(int j=0;j<m;j++)
    {
        if(!v[j][u]) continue;
        if(vis2[j]) continue;
        vis2[j]=1;
        for(int x=0;x<n;x++)
        {
            if(!v[j][x]) continue;
            int tmp=d[u]+v[j][x]-v[j][u];
            if(!vis1[x]) vis1[x]=1,d[x]=tmp,dfs(x);
            else if(d[x]!=tmp) printf("%d\n",abs(d[x]-tmp)),exit(0);
        }
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        v[i]=new int[n];
        for(int j=0;j<n;j++)
            scanf("%d",v[i]+j);
    }
    for(int i=0;i<n;i++)
        if(!vis1[i]) vis1[i]=1,d[i]=0,dfs(i);
    return puts("-1"),0;
}