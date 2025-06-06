#include<bits/stdc++.h>
using namespace std;

const int M=4000010,N=100010;
int ch[M][10],len[M],prt[M],tot=1;
struct Edge{int to,next;} e[2*N];
int deg[N],w[N],h[N],sum=0;

void add_edge(int u,int v){e[++sum].to=v;e[sum].next=h[u];h[u]=sum;}

int insert(int p,int c)
{
	int np=++tot;len[np]=len[p]+1;
	while(p&&!ch[p][c]) ch[p][c]=np,p=prt[p];
	if(!p) prt[np]=1;
	else
	{
		int q=ch[p][c];
		if(len[q]==len[p]+1) prt[np]=q;
		else
		{
			int nq=++tot;len[nq]=len[p]+1;
			memcpy(ch[nq],ch[q],sizeof(ch[nq]));
			prt[nq]=prt[q];prt[q]=prt[np]=nq;
			while(ch[p][c]==q) ch[p][c]=nq,p=prt[p];
		}
	}
	return np;
}

void dfs(int u,int la,int p)
{
	int t=insert(p,w[u]);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(e[tmp].to==la) continue;
		dfs(e[tmp].to,u,t);
	}
}

int main()
{
	int n,c,u,v;
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++) scanf("%d",w+i);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
		deg[u]++;deg[v]++;
	}
	for(int i=1;i<=n;i++)
		if(deg[i]==1) dfs(i,0,1);
	long long ans=0;
	for(int i=1;i<=tot;i++)
		ans+=len[i]-len[prt[i]];
	cout<<ans<<endl;
	return 0;
}
