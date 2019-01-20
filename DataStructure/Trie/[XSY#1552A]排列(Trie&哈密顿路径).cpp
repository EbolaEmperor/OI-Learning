#include<bits/stdc++.h>
using namespace std;

const int N=300010;
int ch[N*32][2],tot=1,cnt=0;
int n,a[N],bel[N],v[N],mn=2e9,mx=-2e9,D,xmn=2e9;
unordered_map<int,int> h;
vector<int> edge[N][2];
set<int> s[2];
long long brg=0;

void insert(int x)
{
    int o=1;
    for(int d=30;d>=0;d--)
    {
        int c=(x>>d)&1;
        if(!ch[o][c]) ch[o][c]=++tot;
        o=ch[o][c];
    }
}

int query(int x)
{
    int o=1,res=0;
    for(int d=30;d>=0;d--)
    {
        int c=(x>>d)&1;
        if(ch[o][c]) o=ch[o][c];
        else res|=1<<d,o=ch[o][c^1];
    }
    return res;
}

bool check(int p)
{
    if(!brg) return s[bel[p]^1].empty();
    if(brg==edge[v[p]][bel[p]^1].size())
        return s[bel[p]].size()==1;
    return 1;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",a+i);
        mn=min(mn,a[i]);
        mx=max(mx,a[i]);
    }
    if(mn==mx){for(int i=1;i<=n;i++) printf("%d ",i);return 0;}
    for(D=30;(mx>>D)==(mn>>D);D--);
    for(int i=1;i<=n;i++) bel[i]=(a[i]>>D)&1;
    for(int i=1;i<=n;i++) if(bel[i]==0) insert(a[i]);
    for(int i=1;i<=n;i++) if(bel[i]==1) xmn=min(xmn,query(a[i]));
    for(int i=n;i>=1;i--)
    {
        if(bel[i]==1) continue;
        if(!h.count(a[i])) h[a[i]]=++cnt;
        edge[h[a[i]]][0].push_back(i);
        v[i]=h[a[i]];
    }
    for(int i=n;i>=1;i--)
    {
        if(bel[i]==0) continue;
        if(!h.count(a[i]^xmn)) continue;
        edge[h[a[i]^xmn]][1].push_back(i);
        v[i]=h[a[i]^xmn];
    }
    for(int i=1;i<=cnt;i++) brg+=1ll*edge[i][0].size()*edge[i][1].size();
    for(int i=1;i<=n;i++) s[bel[i]].insert(i);
    int p=1;while(!check(p)) p++;
    for(int i=1,t,c;i<=n;i++)
    {
        printf("%d ",p);
        if(i==n) break;
        c=v[p];t=bel[p];s[t].erase(p);
        if(c) brg-=edge[c][t^1].size(),edge[c][t].pop_back();
        int p1=N,p2=N,p3=N;
        if(v[p]&&!edge[c][t^1].empty()) if(!check(p1=edge[c][t^1].back())) p1=N;
        if(!s[t].empty()) if(!check(p2=*s[t].begin())) p2=N;
        if(s[t].size()>1) if(!check(p3=*next(s[t].begin()))) p3=N;
        p=min(p1,min(p2,p3));
    }
    puts("");
    return 0;
}