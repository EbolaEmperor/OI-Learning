#include<bits/stdc++.h>
using namespace std;

int son[100010][2];
int dis[100010],val[100010];
int fa[100010];

int find(int x){return fa[x]==x?x:find(fa[x]);}

int Merge(int a,int b)
{
	if(a==0||b==0) return a+b;
	if(val[b]<val[a]||(val[b]==val[a]&&b<a)) swap(a,b);
	son[a][1]=Merge(son[a][1],b);
	fa[son[a][1]]=a;
	if(dis[son[a][0]]<dis[son[a][1]]) swap(son[a][0],son[a][1]);
	dis[a]=dis[son[a][1]]+1;
	return a;
}

int Delete(int a)
{
	int ans=val[a];
	val[a]=-1;
	fa[son[a][0]]=son[a][0];
	fa[son[a][1]]=son[a][1];
	Merge(son[a][0],son[a][1]);
	return ans;
}

int main()
{
	int n,m,x,y,opt;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",val+i);
		fa[i]=i;
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d%d",&x,&y);
			if(val[x]==-1||val[y]==-1) continue;
			x=find(x);y=find(y);
			if(x==y) continue;
			Merge(x,y);
		}
		else
		{
			scanf("%d",&x);
			if(val[x]==-1){puts("-1");continue;}
			x=find(x);
			printf("%d\n",Delete(x));
		}
	}
	return 0;
}
