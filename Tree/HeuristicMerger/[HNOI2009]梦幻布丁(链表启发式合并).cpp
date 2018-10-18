#include<bits/stdc++.h>
using namespace std;

const int MAXN=100000,MAXM=1000000;
int a[MAXN+5],n,m;
int nxt[MAXN+5],h[MAXM+5];
int sz[MAXM+5];
int def[MAXM+5];
int ans=1;

void merge(int &x,int &y)
{
	if(x==y) return;
	if(sz[x]>sz[y]) swap(x,y);
	int p=0;
	for(int i=h[x];i;i=nxt[i])
	{
		ans-=(a[i-1]==y)+(a[i+1]==y);
		if(!nxt[i]){p=nxt[i]=h[y];h[y]=h[x];break;}
	}
	for(int i=h[x];i!=p;i=nxt[i]) a[i]=y;
	h[x]=0;sz[y]+=sz[x];sz[x]=0;
}

int main()
{
	int opt,x,y;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",a+i);
		nxt[i]=h[a[i]];
		h[a[i]]=i;
		sz[a[i]]++;
	}
	for(int i=2;i<=n;i++)
		if(a[i]!=a[i-1]) ans++;
	for(int i=1;i<=MAXM;i++) def[i]=i;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&opt);
		if(opt==2) printf("%d\n",ans);
		else{scanf("%d%d",&x,&y);merge(def[x],def[y]);}
	}
	return 0;
}
