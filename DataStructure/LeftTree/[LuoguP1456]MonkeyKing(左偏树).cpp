#include<bits/stdc++.h>
using namespace std;

int son[100010][2];
int val[100010],dis[100010];
int fa[100010];

int find(int x){return fa[x]==x?x:find(fa[x]);}

int Merge(int a,int b)
{
	if(a==0||b==0) return a+b;
	if(val[b]>val[a]) swap(a,b);
	son[a][1]=Merge(son[a][1],b);
	fa[son[a][1]]=a;
	if(dis[son[a][0]]<dis[son[a][1]]) swap(son[a][0],son[a][1]);
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
	int n,m,x,y,a,b;
	while(~scanf("%d",&n))
	{
		memset(dis,0,sizeof(dis));
		memset(son,0,sizeof(son));
		dis[0]=-1;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",val+i);
			fa[i]=i;
		}
		scanf("%d",&m);
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&x,&y);
			x=find(x);y=find(y);
			if(x==y){puts("-1");continue;}
			a=Delete(x);
			b=Delete(y);
			val[x]/=2;val[y]/=2;
			a=Merge(a,x);
			b=Merge(b,y);
			a=Merge(a,b);
			printf("%d\n",val[a]);
		}
	}
	return 0;
}
