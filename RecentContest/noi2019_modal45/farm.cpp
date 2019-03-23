#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int P=30;
struct Fact{LL v;int cnt;} pn[P],pm[P],ps[P];
int T,nc,mc,sc;
LL n,m,s;
vector<LL> lim;

void read(vector<LL> &p)
{
    int x;scanf("%d",&x);
    for(int k=2;k*k<=x;k++)
        while(x%k==0) p.emplace_back(k),x/=k;
    if(x>1) p.emplace_back(x);
}

LL factor(Fact *n,int &tot,bool flag=0)
{
    vector<LL> p;
    read(p);read(p);read(p);
    if(flag) p.emplace_back(2);
    sort(p.begin(),p.end());
    LL num=1;tot=0;
    for(int i=0;i<p.size();i++)
    {
        if(!i||p[i]!=p[i-1]) n[++tot]={p[i],1};
        else n[tot].cnt++;
        num*=p[i];
    }
    return num;
}

LL solve1()
{
    LL res=0;
    for(int s=0;s<1<<lim.size();s++)
    {
        LL p=1,fg=1;
        for(int i=0;i<lim.size();i++)
            if(s>>i&1) p*=lim[i],fg=-fg;
        res+=fg*(m/p);
    }
    return res;
}

LL solve2(LL x,int d)
{
    LL res=1;
    for(int i=d;i<=sc;i++)
    {
        LL cur=ps[i].v;
        for(int j=1;j<=ps[i].cnt;j++)
        {
            if(s%(x*cur)||x*cur>n) break;
            res+=solve2(x*cur,i+1);
            cur*=ps[i].v;
        }
    }
    return res;
}

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        lim.clear();
        n=factor(pn,nc);
        m=factor(pm,mc);
        s=factor(ps,sc,1);
        int j=1;
        for(int i=1;i<=sc;i++)
            for(;j<=nc&&pn[j].v<=ps[i].v;j++)
                if(pn[j].v!=ps[i].v) lim.emplace_back(pn[j].v);
                else if(pn[j].cnt>ps[i].cnt) lim.emplace_back(pow(ps[i].v,ps[i].cnt+1));
        for(;j<=nc;j++) lim.emplace_back(pn[j].v);
        printf("%lld\n",solve1()+solve2(1,1));
    }
    return 0;
}