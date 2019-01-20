#include<bits/stdc++.h>
using namespace std;

const int ha=1e9+7;
typedef long long LL;
typedef pair<int,int> pii;
const int N=55;
struct POS{int x,y,w;} p[N];
map<LL,LL> f[N][N];
int n,k,all[N],hx[N],hy[N],mx,my,ans=0;
vector<pii> g[N];
int fac[100010];

void prework()
{
    sort(hx+1,hx+1+k);
    sort(hy+1,hy+1+k);
    mx=unique(hx+1,hx+1+k)-(hx+1);
    my=unique(hy+1,hy+1+k)-(hy+1);
    for(int i=1;i<=k;i++)
    {
        p[i].x=lower_bound(hx+1,hx+1+mx,p[i].x)-hx;
        p[i].y=lower_bound(hy+1,hy+1+my,p[i].y)-hy;
        g[p[i].x].push_back(pii(p[i].y,p[i].w));
    }
    for(int i=mx;i>=1;i--)
    {
        all[i]=all[i+1];
        for(pii pr : g[i])
            all[i]|=1ll<<pr.first-1;
    }
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=1ll*fac[i-1]*i%ha;
}

void falun_dafa_is_good()
{
    f[0][0][0]=1;
    for(int i=0;i<mx;i++)
        for(int j=0;j<=i;j++)
            for(auto it : f[i][j])
            {
                (f[i+1][j][it.first&all[i+1]]+=f[i][j][it.first])%=ha;
                for(pii pr : g[i+1])
                {
                    if(it.first&(1ll<<pr.first-1)) continue;
                    (f[i+1][j+1][(it.first^(1ll<<pr.first-1))&all[i+1]]+=1ll*it.second*pr.second%ha)%=ha;
                }
            }
    for(int i=0;i<=mx;i++)
    {
        int sum=0;
        for(auto v : f[mx][i]) (sum+=v.second)%=ha;
        ans=(ans+1ll*fac[n-i]*sum)%ha;
    }
}

int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1,x,y,w;i<=k;i++)
    {
        scanf("%d%d%d",&x,&y,&w);
        p[i]=(POS){x,y,w-1};
        hx[i]=x;hy[i]=y;
    }
    prework();
    falun_dafa_is_good();
    printf("%d\n",ans);
    return 0;
}