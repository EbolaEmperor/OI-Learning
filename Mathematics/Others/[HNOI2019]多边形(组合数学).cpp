#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int ha=1e9+7,N=100010;
map<pii,int> eid;
vector<int> g[N];
int qwq,n,m,num,deg[N],ans=1;
int rt[N],ch[N][2],fa[N],sz[N],tot=0;
int fac[N],ifac[N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void init()
{
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=1ll*fac[i-1]*i%ha;
    ifac[n]=Pow(fac[n],ha-2);
    for(int i=n-1;i>=0;i--)
        ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
}

inline int C(int n,int m){return 1ll*fac[n]*ifac[m]%ha*ifac[n-m]%ha;}
inline int iC(int n,int m){return 1ll*ifac[n]*fac[m]%ha*fac[n-m]%ha;}

void solve(int &o,int l,int r)
{
    if(r<l+2) return;
    int p=upper_bound(g[r].begin(),g[r].end(),l)-g[r].begin();
    sz[o=++tot]=1;
    eid[pii(l,r)]=tot;
    solve(ch[o][0],l,g[r][p]);
    solve(ch[o][1],g[r][p],r);
    if(ch[o][0]) fa[ch[o][0]]=o;
    if(ch[o][1]) fa[ch[o][1]]=o;
    sz[o]+=sz[ch[o][0]]+sz[ch[o][1]];
    ans=1ll*ans*C(sz[o]-1,sz[ch[o][0]])%ha;
}

void query(int u,int v)
{
    int res1=num,res=ans,x=eid[pii(u,v)],y=fa[x];
    if(!y)
    {
        res1--;
        res=1ll*res*iC(sz[x]-1,sz[ch[x][0]])%ha;
        res=1ll*res*ifac[num]%ha*fac[res1]%ha;
        res=1ll*res*fac[sz[x]]%ha*ifac[sz[ch[x][0]]]%ha*ifac[sz[ch[x][1]]]%ha;
    }
    else
    {
        int k=(x==ch[y][1]);
        res=1ll*res*iC(sz[x]-1,sz[ch[x][k]])%ha;
        res=1ll*res*iC(sz[y]-1,sz[ch[y][k]])%ha;
        res=1ll*res*C(sz[y]-1,sz[ch[x][k]])%ha;
        res=1ll*res*C(sz[ch[x][k^1]]+sz[ch[y][k^1]],sz[ch[x][k^1]])%ha;
    }
    if(qwq) printf("%d %d\n",res1,res);
    else printf("%d\n",res1);
}

int main()
{
    scanf("%d%d",&qwq,&n);
    int u,v;
    for(int i=1;i<=n-3;i++)
    {
        scanf("%d%d",&u,&v);
        deg[u]++;deg[v]++;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i=1;i<=n;i++)
    {
        int u=i,v=(i<n)?(i+1):1;
        deg[u]++;deg[v]++;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    num=(n-1)-deg[n];
    for(int i=1;i<=n;i++)
        sort(g[i].begin(),g[i].end());
    int tmp=1;init();
    for(int i=0;i<g[n].size()-1;i++)
        solve(rt[i],g[n][i],g[n][i+1]),tmp=1ll*tmp*fac[sz[rt[i]]]%ha;
    ans=1ll*ans*fac[num]%ha*Pow(tmp,ha-2)%ha;
    if(qwq) printf("%d %d\n",num,ans);
    else printf("%d\n",num);
    scanf("%d",&m);
    while(m--)
    {
        scanf("%d%d",&u,&v);
        if(u>v) swap(u,v);
        query(u,v);
    }
    return 0;
}
