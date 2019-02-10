#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int N=100010;
int go[N][4],idx[N][4],X[N],Y[N];
int tot=0,n,m,p[N];
int cnt[N<<1];

int getd(int u,int v)
{
    if(X[u]==X[v]) return Y[u]<Y[v]?1:3;
    else return X[u]<X[v]?0:2;
}

void add_edge(int u,int v)
{
    go[u][getd(u,v)]=v;
    go[v][getd(v,u)]=u;
    idx[u][getd(u,v)]=++tot;
    idx[v][getd(v,u)]=tot;
}

bool exist(int k)
{
    int x=p[k];
    for(int j=0;j<4;j++)
        if(go[x][j]) return 1;
    return 0;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",X+i,Y+i);
    scanf("%d",&m);
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        add_edge(u,v);
    }
    for(int i=1;i<=n;i++) p[i]=i;
    sort(p+1,p+1+n,[](int a,int b){return X[a]<X[b]||X[a]==X[b]&&Y[a]<Y[b];});
    for(int i=1;i<=n;i++)while(exist(i))
    {
        vector<pii> path;
        int d=0,pos=p[i];
        do{
            while(!go[pos][d]) d=(d+1)&3;
            cnt[idx[pos][d]]++;
            path.push_back(pii(pos,go[pos][d]));
            pos=go[pos][d];
            d=(d+3)&3;
        }while(pos!=p[i]);
        for(pii pr : path)
        {
            int u=pr.first,v=pr.second;
            go[u][getd(u,v)]=0;
            go[v][getd(v,u)]=0;
        }
    }
    int ans=0;
    for(int i=1;i<=m;i++) ans+=(cnt[i]==2);
    printf("%d\n",ans);
    for(int i=1;i<=m;i++)
        if(cnt[i]==2) printf("%d\n",i);
    return 0;
}