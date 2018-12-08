#include<bits/stdc++.h>
using namespace std;

const int N=1410;
int e[N][N],n,m,cnt=0;
vector<int> ans,cur,tmp,del;
bool in[N];

int calc(int u)
{
    tmp.clear();del.clear();
    tmp.push_back(u);
    for(int x : cur)
        if(!e[x][u]) tmp.push_back(x);
        else del.push_back(x);
    if(tmp.size()>ans.size()) ans=tmp;
    return tmp.size();
}
double RAND(){return (double)rand()/RAND_MAX;}
bool accept(double dta,double tem){return dta>0||RAND()<exp(dta/tem);}
void anneal(double tem,double dta,double end)
{
    int res=0;cur.clear();
    memset(in,0,sizeof(in));
    while(tem>end)
    {
        int u=rand()%n+1;
        while(in[u]) u=rand()%n+1;
        int nxt=calc(u);
        if(accept(nxt-res,tem))
        {
            res=nxt;cur=tmp;in[u]=1;
            for(int x : del) in[x]=0;
        }
        tem*=dta;
    }
}

int main()
{
    srand(time(0));
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        e[u][v]=e[v][u]=1;
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            e[i][j]^=1;
    while(true)
    {
        anneal(1e5,1-5*1e-6,1e-2);
        printf("%d\n",ans.size());
        for(int x : ans) printf("%d ",x);
        puts("");
    }
    return 0;
}