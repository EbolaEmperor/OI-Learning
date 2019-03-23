#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int N=100010,S=315;
map<int,int> anrm[N],bnrm[N];
int n,m,q,col[N],c[N],cnt[N],cnt1=0,cnt2=0;
vector<pii> anr[N],bnr[N];
bool isbig[N],on[N];
int cntn[N];

void prework()
{
    int tot=0;
    for(int i=1;i<=n;i++)
        if(col[i]!=col[i-1])
            c[++tot]=col[i],cnt[col[i]]++;
    n=tot;
    for(int i=1;i<=m;i++)
        if(cnt[i]>=S) isbig[i]=1;
    for(int i=1;i<n;i++)
    {
        anrm[c[i]][c[i+1]]++;
        anrm[c[i+1]][c[i]]++;
        if(isbig[c[i+1]]) bnrm[c[i]][c[i+1]]++;
        if(isbig[c[i]]) bnrm[c[i+1]][c[i]]++;
    }
    for(int i=1;i<=m;i++)
    {
        for(auto pr : anrm[i])
            anr[i].emplace_back(pr);
        for(auto pr : bnrm[i])
            bnr[i].emplace_back(pr);
    }
}

void gao_big(int x)
{
    int k=on[x]?-1:1;
    cnt1+=k*cnt[x];
    cnt2+=k*cntn[x];
    for(auto pr : bnr[x])
        cntn[pr.first]+=k*pr.second;
    on[x]^=1;
}

void gao_small(int x)
{
    int k=on[x]?-1:1;
    cnt1+=k*cnt[x];
    for(auto pr : anr[x])
        if(on[pr.first]) cnt2+=k*pr.second;
    for(auto pr : bnr[x])
        cntn[pr.first]+=k*pr.second;
    on[x]^=1;
}

int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)
        scanf("%d",col+i);
    prework();
    int x;
    while(q--)
    {
        scanf("%d",&x);
        if(isbig[x]) gao_big(x);
        else gao_small(x);
        printf("%d\n",cnt1-cnt2);
    }
    return 0;
}