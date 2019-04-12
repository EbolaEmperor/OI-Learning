#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=5010;
unordered_map<unsigned,int> hs;
struct Dsub{int pos;unsigned val;} dsub[N];
unsigned sub[N],h[N],base[N];
int n,k,idx[N],tot,cv[200],sum[N];
LL deg[N],ans,lst;
char s[N];

inline unsigned subhash(int l,int r){return (l<=r)?h[r]-h[l-1]*base[r-l+1]:0;}

void string_init()
{
    cv['o']=cv['i']=cv['e']=cv['a']=cv['s']=cv['t']=cv['b']=cv['g']=1;
    for(int i=1;i<=n;i++)
        sum[i]=sum[i-1]+cv[s[i]];
    base[0]=1;
    for(int i=1;i<=n;i++)
        base[i]=base[i-1]*233u;
    for(int i=1;i<=n;i++)
        h[i]=h[i-1]*233u+s[i];
    for(int i=1;i+k-2<=n;i++)
    {
        unsigned val=subhash(i,i+k-2);
        if(!hs.count(val))
        {
            hs[val]=++tot;
            dsub[tot].val=val;
            dsub[tot].pos=i;
        }
        sub[i]=hs[val];
    }
}

void graph_init()
{
    static bool e[N][N];
    for(int i=1;i+k-1<=n;i++)
    {
        LL w=1ll<<(sum[i+k-1]-sum[i-1]);
        if(!e[sub[i]][sub[i+1]])
        {
            e[sub[i]][sub[i+1]]=1;
            deg[sub[i]]-=w;
            deg[sub[i+1]]+=w;
            ans+=w;
        }
    }
}

void gaogaogaogaogao()
{
    for(int d=k-1;d>=0;d--)
    {
        static unordered_map<unsigned,vector<int>> P;
        P.clear();
        for(int i=1;i<=tot;i++)
            if(deg[i]<0) P[dsub[i].val].push_back(i);
        for(int i=1;i<=tot;i++)
            if(deg[i]>0&&P.count(dsub[i].val))
            {
                vector<int> &v=P[dsub[i].val];
                while(deg[i]&&!v.empty())
                {
                    LL flow=min(deg[i],-deg[v.back()]);
                    deg[i]-=flow;
                    deg[v.back()]+=flow;
                    if(!deg[v.back()]) v.pop_back();
                    ans+=flow*(k-1-d);
                    lst=k-1-d;
                }
            }
        if(!d) break;
        for(int i=1;i<=tot;i++)
            if(deg[i]<0) dsub[i].val=subhash(dsub[i].pos,dsub[i].pos+d-2);
            else if(deg[i]>0) dsub[i].val=subhash(dsub[i].pos+k-d,dsub[i].pos+k-2);
    }
}

int main()
{
    scanf("%d%s",&k,s+1);
    n=strlen(s+1);
    string_init();
    graph_init();
    gaogaogaogaogao();
    printf("%lld\n",k-1+ans-lst);
    return 0;
}
