// When I first wrote these, only I and God know what I'm doing.
// Now, only God knows.
#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int N=1010;
vector<int> anc[N],g[N];
vector<pii> branch;
set<int> son[N],split;
bool cmp[N][N],lim2[N][N],isb[N],vis[N];
int n,m1,m2,p[N],fa[N],tot=0,deg[N];
int dep[N],idfn[N],odfn[N],dfc;

void dfs0(int u)
{
    vis[u]=1;
    p[++tot]=u;
    for(int v : g[u])
        if(!--deg[v]) dfs0(v);
}

void dfs(int u)
{
    idfn[u]=++dfc;
    for(int v : son[u])
        dep[v]=dep[u]+1,dfs(v);
    odfn[u]=dfc;
}

void dfs2(int u)
{
    for(int a : anc[u])
        if(split.find(a)!=split.end())
            {split.insert(u);break;}
    for(int v : son[u]) dfs2(v);
}

int main()
{
    scanf("%d%d%d",&n,&m1,&m2);
    for(int i=1,u,v;i<=m1;i++)
        scanf("%d%d",&u,&v),cmp[u][v]=1,anc[v].emplace_back(u);
    for(int i=1,u,v;i<=m2;i++)
        scanf("%d%d",&u,&v),lim2[u][v]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(lim2[i][j]&&lim2[j][i])
            {
                branch.emplace_back(pii(i,j));
                lim2[i][j]=lim2[j][i]=0;
                isb[i]=isb[j]=1;
            }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(lim2[i][j]) cmp[j][i]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(cmp[i][j]) g[i].emplace_back(j),deg[j]++;
    for(int i=1;i<=n;i++)
        if(!deg[i]&&!isb[i])
            {dfs0(i);break;}
    //for(int i=1;i<=tot;i++) cerr<<p[i]<<" ";cerr<<endl;
    for(int i=1;i<=n;i++)
        if(!vis[i]) dfs0(i);
    //for(int i=1;i<=n;i++) cerr<<p[i]<<" ";cerr<<endl;
    for(int i=2;i<=n;i++) fa[p[i]]=p[i-1],son[p[i-1]].insert(p[i]);
    fa[p[1]]=0;dep[p[1]]=1;dfs(p[1]);
    while(!branch.empty())
    {
        sort(branch.begin(),branch.end(),[](pii a,pii b){return min(dep[a.first],dep[a.second])>min(dep[b.first],dep[b.second]);});
        pii pr=branch.back();branch.pop_back();
        int u=pr.first,v=pr.second;
        if(dep[u]>dep[v]) swap(u,v);
        if(idfn[v]<idfn[u]||idfn[v]>odfn[u]) continue;
        split.clear();split.insert(v);dfs2(v);
        static int tmp[N];int tot=0;
        for(int x : split) tmp[++tot]=x;
        sort(tmp+1,tmp+1+tot,[](int a,int b){return idfn[a]<idfn[b];});
        for(int i=1;i<=tot;i++)
        {
            son[fa[tmp[i]]].erase(tmp[i]);
            for(int x : son[tmp[i]])
                fa[x]=fa[tmp[i]],son[fa[tmp[i]]].insert(x);
        }
        for(int i=2;i<=tot;i++) fa[tmp[i]]=tmp[i-1];
        //cerr<<tmp[1]<<" "<<fa[u]<<endl;
        fa[tmp[1]]=fa[u];
        dfc=0;dfs(p[1]);
        // for(int i=1;i<=n;i++)
        //     printf("%d ",fa[i]);puts("");
    }
    for(int i=1;i<=n;i++)
        printf("%d ",fa[i]);puts("");
    return 0;
}