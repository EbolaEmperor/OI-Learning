#include<bits/stdc++.h>
using namespace std;

const int INF=0x3f3f3f3f;
const int N=110;
struct Point
{
    int x,y;
    bool operator < (const Point &p) const{return x<p.x||x==p.x&&y<p.y;}
    bool operator == (const Point &p) const{return x==p.x&&y==p.y;}
} pt[N];
int f[N][N][N];
int Hash[N],tot=0;
int n,S,T;

int geth(int l,int r){return pt[l].x==pt[r].x?INF-1:S/(pt[r].x-pt[l].x);}
int dp(int l,int r,int h)
{
    int &res=f[l][r][h];
    if(~res) return res;res=INF;
    while(pt[l].y<Hash[h]&&l<=r) l++;
    while(pt[r].y<Hash[h]&&l<=r) r--;
    if(l>r) return res=0;
    for(int i=l;i<r;i++) res=min(res,dp(l,i,h)+dp(i+1,r,h));
    int t=upper_bound(Hash+1,Hash+1+tot,geth(l,r))-Hash;
    if(t<=h) return res;
    res=min(res,1+dp(l,r,t));
    return res;
}

int main()
{
    for(scanf("%d",&T);T;T--)
    {
        memset(f,-1,sizeof(f));
        scanf("%d%d",&n,&S);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&pt[i].x,&pt[i].y);
        sort(pt+1,pt+1+n);
        for(int i=1;i<=n;i++)
            Hash[i]=pt[i].y;
        sort(Hash+1,Hash+1+n);
        tot=unique(Hash+1,Hash+1+n)-(Hash+1);
        Hash[++tot]=INF;
        int ans=dp(1,n,1);
        printf("%d\n",ans);
    }
    return 0;
}