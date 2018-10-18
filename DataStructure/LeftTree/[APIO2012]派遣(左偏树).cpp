#include<bits/stdc++.h>
using namespace std;

struct Edge{int to,next;} e[200010];
int h[100010],sum=0;
int son[100010][2];
int cost[100010],dis[100010];
int fa[100010];
int lead[100010];
int s[100010],v[100010];
int father[100010];

void add_edge(int u,int v)
{
	sum++;
	e[sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

int find(int x){return fa[x]==x?x:find(fa[x]);}

int Merge(int a,int b)
{
	if(a==0||b==0) return a+b;
	if(cost[b]>cost[a]) swap(a,b);
	son[a][1]=Merge(son[a][1],b);
	fa[son[a][1]]=a;
	if(dis[son[a][1]]>dis[son[a][0]]) swap(son[a][0],son[a][1]);
	dis[a]=dis[son[a][1]]+1;
	return a;
}

int Delete(int a)
{
	int l=son[a][0],r=son[a][1];
	fa[l]=l;fa[r]=r;
	dis[a]=son[a][0]=son[a][1]=0;
	return Merge(l,r);
}

int main()
{
	int n,m,x;
	long long ans=0;
	cin>>n>>m;
	dis[0]=-1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&x,cost+i,lead+i);
		if(x) add_edge(x,i),add_edge(i,x);
		father[i]=x;
		fa[i]=i;s[i]=cost[i];v[i]=1;
	}
	for(int u=n;u>=1;u--)
	{
		x=find(u);
		for(int tmp=h[u];tmp;tmp=e[tmp].next)
		{
			if(e[tmp].to==father[u]) continue;
			int y=find(e[tmp].to);
			x=Merge(x,y);
			s[u]+=s[e[tmp].to];
			v[u]+=v[e[tmp].to];
			while(s[u]>m)
			{
				s[u]-=cost[x];
				v[u]--;
				int tmp2=x;
				x=Delete(x);
				fa[tmp2]=x;
			}
		}
		ans=max(ans,(long long)lead[u]*v[u]);
	}
	cout<<ans<<endl;
	return 0;
}
