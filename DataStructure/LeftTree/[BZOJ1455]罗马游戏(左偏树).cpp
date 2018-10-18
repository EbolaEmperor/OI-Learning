#include<bits/stdc++.h>
using namespace std;

const int N=1000010;
int ch[N][2],dis[N],val[N];
int fa[N];

int find(int x){return fa[x]==x?x:find(fa[x]);}

int Merge(int a,int b)
{
	if(a==0||b==0) return a+b;
	if(val[b]<val[a]||val[b]==val[a]&&b<a) swap(a,b);
	ch[a][1]=Merge(ch[a][1],b);
	fa[ch[a][1]]=a;
	if(dis[ch[a][0]]<dis[ch[a][1]]) swap(ch[a][0],ch[a][1]);
	dis[a]=dis[ch[a][1]]+1;
	return a;
}

int Delete(int a)
{
	int ans=val[a];
	val[a]=-1;
	fa[ch[a][0]]=ch[a][0];
	fa[ch[a][1]]=ch[a][1];
	Merge(ch[a][0],ch[a][1]);
	return ans;
}

int main()
{
	int n,m,a,b;
	static char opt[5];
	scanf("%d",&n);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=n;i++) scanf("%d",val+i);
	scanf("%d",&m);
	while(m--)
	{
		scanf("%s",opt);
		if(opt[0]=='M')
		{
			scanf("%d%d",&a,&b);
			if(val[a]==-1||val[b]==-1) continue;
			a=find(a);b=find(b);
			if(a==b) continue;
			Merge(a,b);
		}
		else
		{
			scanf("%d",&a);
			a=find(a);
			if(val[a]==-1){puts("0");continue;}
			printf("%d\n",Delete(a));
		}
	}
	return 0;
}
