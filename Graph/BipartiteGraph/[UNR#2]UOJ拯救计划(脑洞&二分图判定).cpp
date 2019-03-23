#include<bits/stdc++.h>
using namespace std;

const int N=100010;
vector<int> g[N];
int T,n,m,k;
int col[N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=a*a%6)
        if(b&1) ans=ans*a%6;
    return ans;
}

bool check(int u)
{
    for(int v : g[u])
    {
        if(col[v]==col[u]) return 0;
        if(!col[v])
        {
            col[v]=3-col[u];
            if(!check(v)) return 0;
        }
    }
    return 1;
}

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=n;i++) g[i].clear();
        for(int i=1,u,v;i<=m;i++)
        {
            scanf("%d%d",&u,&v);
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        if(k==1) printf("%d\n",m?0:1);
        else
        {
            int res=m?0:k%6;
            memset(col,0,sizeof(int)*(n+1));
            bool flag=1;int cnt=0;
            for(int i=1;i<=n;i++)
                if(!col[i]) col[i]=1,flag&=check(i),cnt++;
            if(flag) res=(res+k*(k-1)/2*(Pow(2,cnt)-(m?0:2)))%6;
            printf("%d\n",(res+6)%6);
        }
    }
    return 0;
}