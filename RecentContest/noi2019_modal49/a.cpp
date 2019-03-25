#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=100010;
struct OPT{int ty,x,id;};
// ty=1: 出现一个迷茫，目标位置为x
// ty=2: 消失一个迷茫
vector<OPT> g[N];
// g[i]: 目前为止，i坐标处出现/消失的所有迷茫
struct OPT2{int x,y,id;};
// x处出现一个迷茫，目标位置为y
vector<OPT2> h[N];
// h[t]: t时刻会出现的所有迷茫
int sum[N],n,m,done=0,pos=1,dr;
LL ans[N];

int lowbit(const int &x){return x&-x;}
void add(int p,int k){for(;p<=m;p+=lowbit(p)) sum[p]+=k;}
int presum(int p){int res=0;for(;p;p-=lowbit(p)) res+=sum[p];return res;}

void gao()
{
    set<int> S;
    LL t=100001;
    for(int i=1;i<=m;i++)
        if(!g[i].empty()) S.insert(i);
    while(done<n)
    {
        int nxt=*(dr?S.lower_bound(pos):--S.upper_bound(pos));
        t+=abs(nxt-pos);pos=nxt;
        for(auto p : g[pos])
            if(p.ty==1)
            {
                add(pos,-1);
                g[p.x].push_back((OPT){2,0,p.id});
                add(p.x,1);S.insert(p.x);
            }
            else
            {
                ans[p.id]=t;
                done++;
                add(pos,-1);
            }
        g[pos].clear();S.erase(nxt);t++;
        int tmp1=presum(pos),tmp2=(n-done)-tmp1;
        if(tmp2>=tmp1) pos++,dr=1;
        else pos--,dr=0;
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,t,x,y;i<=n;i++)
    {
        scanf("%d%d%d",&t,&x,&y);
        h[t].push_back((OPT2){x,y,i});
    }
    int cnt=0;
    for(int t=1;t<=100000&&done<n;t++)
    {
        for(auto p : h[t])
        {
            g[p.x].push_back((OPT){1,p.y,p.id});
            add(p.x,1);cnt++;
        }
        for(auto p : g[pos])
            if(p.ty==1)
            {
                add(pos,-1);
                g[p.x].push_back((OPT){2,0,p.id});
                add(p.x,1);
            }
            else
            {
                ans[p.id]=t;
                done++,cnt--;
                add(pos,-1);
            }
        g[pos].clear();
        if(!cnt) continue;
        int tmp1=presum(pos),tmp2=cnt-tmp1;
        if(tmp2>=tmp1) pos++,dr=1;
        else pos--,dr=0;
    }
    if(done<n) gao();
    for(int i=1;i<=n;i++)
        printf("%lld\n",ans[i]);
    return 0;
}