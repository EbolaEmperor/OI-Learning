#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,LL> pil;
const int N=100000,M=N+5;
vector<pil> ans;
LL n,cx[M],cpx[M],cpfac[M];
int prm[M],idx[M],mnp[M],mark[M],tot=0;
int mx,cur;

void sieve()
{
    for(int i=2;i<=N;i++)
    {
        if(!mark[i]) mnp[i]=prm[idx[i]=++tot]=i;
        for(int j=1;j<=tot&&i*prm[j]<=N;j++)
        {
            mark[i*prm[j]]=1;
            mnp[i*prm[j]]=prm[j];
            if(i%prm[j]==0) break;
        }
    }
}

bool check()
{
    for(;cur;cur--)
        if(cpx[cur]<cpfac[cur])
            return 0;
    return 1;
}

LL calc()
{
    LL res=INT_MAX;
    for(int i=1;i<=mx;i++)
        res=min(res,cpx[i]/cpfac[i]);
    return res;
}

int main()
{
    sieve();
    scanf("%lld",&n);
    for(int i=1,x;i<=n;i++)
        scanf("%lld",&x),cx[x]++;
    for(int i=N;i>1;i--)
        cx[i]+=cx[i+1];
    for(int i=2;i<=N;i++)
        for(int j=i;j>1;j/=mnp[j])
            cpx[idx[mnp[j]]]+=cx[i];
    for(int i=2;i<=N;i++)
        for(int j=i;j>1;j/=mnp[j])
            cpfac[idx[mnp[j]]]++;
    for(mx=tot;!cpfac[mx];mx--);cur=mx;
    for(int i=N;i>1;i--)
    {
        if(check())
        {
            LL pw=calc();
            ans.emplace_back(i,pw);
            for(int j=1;j<=mx;j++)
                cpx[j]-=cpfac[j]*pw;
            cur=mx;
        }
        for(int j=i;j>1;j/=mnp[j])
            cpfac[idx[mnp[j]]]--;
        while(!cpfac[mx]) mx--;
        cur=min(cur,mx);
    }
    printf("%lu\n",ans.size());
    for(pil pr : ans)
        printf("%d %lld\n",pr.first,pr.second);
    return 0;
}