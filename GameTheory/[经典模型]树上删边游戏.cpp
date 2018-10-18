#include<bits/stdc++.h>
using namespace std;

const int N=1000010;
struct Edge{int to,next;} e[N<<1];
int h[N],sum=0,n;

void add_edge(int u,int v)
{
    e[++sum].to=v;
    e[sum].next=h[u];
    h[u]=sum;
}

int dfs(int u,int fa)
{
    int res=0;
    for(int tmp=h[u];tmp;tmp=e[tmp].next)
        if(e[tmp].to!=fa) res^=dfs(e[tmp].to,u)+1;
    return res;
}

int main()
{
    int u,v;
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        add_edge(u,v);
        add_edge(v,u);
    }
    puts(dfs(1,0)?"First Win":"First Lost");
    return 0;
}