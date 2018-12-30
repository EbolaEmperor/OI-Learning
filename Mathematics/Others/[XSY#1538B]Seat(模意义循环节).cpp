#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=100010;
bool vis[N];

struct Macker
{
    int n,tot,cbegin,cnum,t[N];
    void pre_gao()
    {
        int x,a,b;cin>>x>>a>>b;
        memset(vis,0,sizeof(vis));tot=0;
        while(!vis[x]) t[++tot]=x,vis[x]=1,x=(1ll*a*x+b)%n;
        for(cbegin=1;t[cbegin]!=x;cbegin++);
        cnum=tot-cbegin+1;
    }
    int gao(int x){return x<=tot?t[x]:t[(x-cbegin)%cnum+cbegin];}
} line,colum;
LL cur=0,ans=0,n,m,k;
bool done[N];
set<int> S;

inline LL C2(LL n){return n*(n+1)/2;}
void clear(){S.clear();cur=C2(m);S.insert(-1);S.insert(m);}
inline bool exist(int x){return S.find(x)!=S.end();}

void ins(int x)
{
    if(exist(x)) return;S.insert(x);
    auto it=S.find(x),pre=it,suf=it;
    pre--;suf++;
    cur-=C2(*suf-*pre-1);
    cur+=C2(x-*pre-1)+C2(*suf-x-1);
}

void del(int x)
{
    auto it=S.find(x),pre=it,suf=it;
    if(it==S.end()) return;
    pre--;suf++;
    cur+=C2(*suf-*pre-1);
    cur-=C2(x-*pre-1)+C2(*suf-x-1);
    S.erase(it);
}

int main()
{
    cin>>n>>m>>k;
    line.n=n;line.pre_gao();
    colum.n=m;colum.pre_gao();
    for(LL i=1;i<=k&&i<=line.tot;i++)
    {
        if(i<line.cbegin)
        {
            int x=colum.gao(i);
            ans+=C2(x)+C2(m-x-1);
            continue;
        }
        if(done[line.gao(i)]) continue;
        clear();int step=line.cnum%colum.cnum;
        for(LL l=i,r=i;l<=k&&!done[line.gao(l)];)
        {
            for(;r<=k&&!exist(colum.gao(r));r+=line.cnum) ins(colum.gao(r));
            ans+=cur;done[line.gao(l)]=1;
            del(colum.gao(l));l+=step;r-=line.cnum-step;
            while(l>line.tot) l-=line.cnum,ins(colum.gao(l));
        }
    }
    for(int i=0;i<n;i++) if(!done[i]) ans+=C2(m);
    cout<<ans<<endl;
    return 0;
}
