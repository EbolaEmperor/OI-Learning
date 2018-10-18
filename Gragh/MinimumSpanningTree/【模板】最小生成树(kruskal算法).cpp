#include<bits/stdc++.h>
using namespace std;

struct Edge{int from,to,capa,next;} e[200010];
int fa[5010],ans=0,n,m;

bool operator < (Edge a,Edge b){return a.capa<b.capa;}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}

void kruskal()
{
	int cnt=0;
	sort(e+1,e+1+m);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		int u=e[i].from,v=e[i].to;
		u=find(u);v=find(v);
		if(u==v) continue;
		fa[v]=u;cnt++;
		ans+=e[i].capa;
		if(cnt==n-1) break;
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&e[i].from,&e[i].to,&e[i].capa);
	kruskal();
	int cnt=0;
	for(int i=1;i<=n;i++) cnt+=(fa[i]==i);
	if(cnt>1) puts("orz");
	else printf("%d\n",ans);
	return 0;
}
