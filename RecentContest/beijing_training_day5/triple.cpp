#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=550;
int a[N][N],b[N];
int n,m;

void add_edge(int u,int v)
{
    a[u][v]=rand()%ha;
    a[v][u]=ha-a[u][v];
}

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

bool insert(int x)
{
    for(int i=1;i<=n*2+m;i++)
    {
        if(!a[x][i]) continue;
        if(!b[i]){b[i]=x;return 1;}
        int y=b[i],k=1ll*a[x][i]*Pow(a[y][i],ha-2)%ha;
        for(int j=1;j<=n*2+m;j++)
            a[x][j]=(a[x][j]-1ll*k*a[y][j]%ha+ha)%ha;
    }
    return 0;
}

int main()
{
    srand(19260817);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        static char s[N];
        scanf("%s",s+1);
        for(int j=1;j<=m;j++)
            if(s[j]=='1') add_edge(i,n*2+j),add_edge(i+n,n*2+j);
        add_edge(i,n+i);
    }
    int ans=0;
    for(int i=1;i<=n*2+m;i++)
        ans+=insert(i);
    printf("%d\n",ans/2-n);
    return 0;
}
