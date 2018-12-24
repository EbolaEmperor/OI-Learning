#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int ha=19260817;
const int N=510;
int a[N][N],b[N],n,m;
pii p[N];

void gao()
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<i;j++)
        {
            if(a[i][j]>=0) continue;
            a[i][j]=rand()%ha;
            a[j][i]=ha-a[i][j];
        }
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
    for(int i=1;i<=n;i++)
    {
        if(!a[x][i]) continue;
        if(!b[i]){b[i]=x;return 1;}
        int y=b[i],k=1ll*a[x][i]*Pow(a[y][i],ha-2)%ha;
        for(int j=1;j<=n;j++)
            a[x][j]=(a[x][j]-1ll*k*a[y][j]%ha+ha)%ha;
    }
    return 0;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&p[i].first),p[i].second=i;
    sort(p+1,p+1+n);
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        a[u][v]=a[v][u]=-1;
    }
    gao();
    long long ans=0;
    for(int i=n;i>=1;i--)
        if(insert(p[i].second))
            ans+=p[i].first;
    printf("%lld\n",ans);
    return 0;
}