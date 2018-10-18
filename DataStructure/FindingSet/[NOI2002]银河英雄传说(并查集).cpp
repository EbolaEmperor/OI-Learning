#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int f[30005],num[30005],dist[30005];

int find(int x)
{
	if(f[x]!=x)
	{
		int k=f[x];
		f[x]=find(f[x]);
		dist[x]+=dist[k];
		num[x]=num[f[x]];
	}
	return f[x];
}

void merge(int x,int y)
{
	int p=find(x),q=find(y);
	if(p!=q)
	{
		f[p]=q;
		dist[p]+=num[q];
		num[p]=num[q]=num[p]+num[q];
	}
}

int query(int x,int y)
{
	int p=find(x),q=find(y);
	if(p!=q) return -1;else return abs(dist[x]-dist[y])-1;
}

int main()
{
	int tt,x,y;
	char c;
	cin>>tt;
	for(int i=1;i<=30000;i++) f[i]=i,num[i]=1;
	for(int T=1;T<=tt;T++)
	{
		c=' ';
		while(c!='M'&&c!='C') c=getchar();
		scanf("%d%d",&x,&y);
		if(c=='M') merge(x,y);
		if(c=='C') printf("%d\n",query(x,y));
	}
	return 0;
}
