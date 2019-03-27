#include<bits/stdc++.h>
using namespace std;

const int N=100010,P=N*32;
int rt=0,tot=0,lc[P],rc[P],col[P];
int n,m,k;

void insert(int &o,int l,int r,int nl,int nr,int v)
{
    if(!o) o=++tot;
    if(l>=nl&&r<=nr){col[o]=v;return;}
    int mid=(l+r)/2;
    if(nl<=mid) insert(lc[o],l,mid,nl,nr,v);
    if(nr>mid) insert(rc[o],mid+1,r,nl,nr,v);
}

pair<int,vector<int>> dfs(int o)
{
    if(col[o]) return { 0,{col[o]} };
    int ans1,ans2;vector<int> tmp1,tmp2,tmp;
    tie(ans1,tmp1)=dfs(lc[o]);
    tie(ans2,tmp2)=dfs(rc[o]);
    set_intersection(tmp1.begin(),tmp1.end(),tmp2.begin(),tmp2.end(),back_insert_iterator<vector<int>>(tmp));
    if(tmp.empty())
    {
        tmp.clear();
        merge(tmp1.begin(),tmp1.end(),tmp2.begin(),tmp2.end(),back_insert_iterator<vector<int>>(tmp));
        return {ans1+ans2+1,tmp};
    }
    else return {ans1+ans2,tmp};
}

int main()
{
    scanf("%d%d%d",&k,&n,&m);
    for(int i=1,now=0,c,v;i<=n;i++)
    {
        scanf("%d%d",&c,&v);
        if(!c) continue;
        insert(rt,0,(1<<k)-1,now,now+c-1,v);
        now+=c;
    }
    int ans=dfs(rt).first;
    printf("%d\n",ans+1);
    return 0;
}