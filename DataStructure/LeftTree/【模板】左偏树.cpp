#include<bits/stdc++.h>
using namespace std;

const int N=200010;
int n,m,fa[N],val[N],dis[N],ch[N][2];

int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int merge(int a,int b)
{
    if(!a||!b) return a|b;
    if(val[b]<val[a]||val[b]==val[a]&&b<a) swap(a,b);
    fa[ch[a][1]=merge(ch[a][1],b)]=a;
    if(dis[ch[a][1]]>dis[ch[a][0]]) swap(ch[a][0],ch[a][1]);
    dis[a]=dis[ch[a][1]]+1;
    return a;
}
int pop(int a)
{
    int rec=val[a];val[a]=-1;
    fa[ch[a][0]]=ch[a][0];
    fa[ch[a][1]]=ch[a][1];
    fa[a]=merge(ch[a][0],ch[a][1]);
    return rec;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",val+i),fa[i]=i;
    int opt,x,y;
    while(m--)
    {
        scanf("%d%d",&opt,&x);
        if(opt==1)
        {
            scanf("%d",&y);
            if(val[x]<0||val[y]<0) continue;
            x=find(x);y=find(y);
            if(x!=y) merge(x,y);
        }
        else printf("%d\n",val[x]<0?-1:pop(find(x)));
    }
    return 0;
}
