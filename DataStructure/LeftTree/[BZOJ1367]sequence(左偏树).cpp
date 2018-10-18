#include<bits/stdc++.h>
using namespace std;

int read()
{
	int x=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	return x;
}

const int N=1000010;
int ch[N][2],dis[N],tot=0;
int a[N],val[N],size[N];
int rt[N],L[N],R[N];

int New(int x)
{
	val[++tot]=x;
	dis[tot]=0;size[tot]=1;
	ch[tot][0]=ch[tot][1]=0;
	return tot;
}
int Merge(int a,int b)
{
	if(a==0||b==0) return a+b;
	if(val[b]>=val[a]) swap(a,b);
	ch[a][1]=Merge(ch[a][1],b);
	if(dis[ch[a][0]]<dis[ch[a][1]]) swap(ch[a][0],ch[a][1]);
	dis[a]=dis[ch[a][1]]+1;
	size[a]=size[ch[a][0]]+size[ch[a][1]]+1;
	return a;
}

int main()
{
	int n=read(),now=0;
	for(int i=1;i<=n;i++)
	{
		a[i]=read()-i;
		rt[++now]=New(a[i]);
		L[now]=R[now]=i;
		while(now>1&&val[rt[now-1]]>val[rt[now]])
		{
			rt[now-1]=Merge(rt[now-1],rt[now]);
			now--;R[now]=R[now+1];
			while(size[rt[now]]>(R[now]-L[now]+2)/2)
				rt[now]=Merge(ch[rt[now]][0],ch[rt[now]][1]);
		}
	}
	long long ans=0;
	for(int i=1;i<=now;i++)
		for(int j=L[i];j<=R[i];j++)
			ans+=abs(a[j]-val[rt[i]]);
	printf("%lld\n",ans);
	return 0;
}
