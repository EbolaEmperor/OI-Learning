#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int N=300010;
struct Point
{
    int x,y,id;
    Point(int _x=0,int _y=0,int _id=0):x(_x),y(_y),id(_id){}
    bool operator < (const Point &a) const{return y>a.y||y==a.y&&id<a.id;}
} p[N<<1];
int n,m,sz[N],fa[N],prt[N],ans[N];
set<pii> s;

int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}

void merge(int x,int y)
{
    x=find(x);y=find(y);
    if(x==y) return;
    fa[x]=y;sz[y]+=sz[x];
}

int main(int argc,char* argv[])
{
    if(argc>1) freopen(argv[1],"r",stdin);
    if(argc>2) freopen(argv[2],"w",stdout);
    scanf("%d",&n);
    for(int i=1,x,y;i<=n;i++)
    {
        scanf("%d%d",&x,&y);
        p[i]=Point(x,y,i);
    }
    scanf("%d",&m);
    for(int i=1,x,y;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        p[i+n]=Point(x,y,-i);
    }
    sort(p+1,p+1+n+m);
    for(int i=1;i<=n+m;i++)
    {
        int x=p[i].x,id=p[i].id;
        if(id>0)
        {
            auto it=s.lower_bound(pii(x,0));
            if(it!=s.end()) sz[it->second]++;
        }
        else
        {
            id=-id;
            auto it=s.insert(pii(x,id)).first;
            if(next(it)!=s.end()) prt[id]=next(it)->second;
            while(it!=s.begin()&&prev(it)->second>id) s.erase(prev(it));
        }
    }
    for(int i=1;i<=m;i++) fa[i]=i;
    for(int i=m;i>=1;i--)
    {
        ans[i]=sz[i];
        merge(i,prt[i]);
    }
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    return 0;
}