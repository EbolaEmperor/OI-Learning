#include<bits/stdc++.h>
using namespace std;

const int MAXN=100010,N=4;
int ch[MAXN][N],fail[MAXN];
int len[MAXN];
int sz,n,lst;
int s[MAXN];
char ss[MAXN];
int f[MAXN],g[MAXN];

int get(char c)
{
	if(c=='A') return 0;
	if(c=='G') return 1;
	if(c=='C') return 2;
	if(c=='T') return 3;
}

int newnode(int l)
{
	len[++sz]=l;
	fail[sz]=0;
	for(int i=0;i<N;i++) ch[sz][i]=0;
	f[sz]=g[sz]=0;
	return sz;
}

void init()
{
	n=lst=0;
	sz=-1;
	s[0]=-1;
	newnode(0);
	newnode(-1);
	fail[0]=1;
}

int find(int p)
{
	while(s[n]!=s[n-len[p]-1]) p=fail[p];
	return p;
}

void insert(int c)
{
	s[++n]=c;
	int cur=find(lst);
	if(!ch[cur][c])
	{
		int now=newnode(len[cur]+2);
		fail[now]=ch[find(fail[cur])][c];
		if(len[now]<=2)
			g[now]=fail[now];
		else
		{
			int p=g[cur];
			while(s[n]!=s[n-len[p]-1]||(len[p]+2)*2>len[now]) p=fail[p];
			g[now]=ch[p][c];
		}
		ch[cur][c]=now;
	}
	lst=ch[cur][c];
}

int main()
{
	int T;
	for(scanf("%d",&T);T;T--)
	{
		scanf("%s",ss);
		init();
		int l=strlen(ss);
		for(int i=0;i<l;i++) insert(get(ss[i]));
		for(int i=2;i<=sz;i++)
			if(len[i]&1) f[i]=len[i];
		f[0]=1;
		queue<int> q;
		q.push(0);
		int ans=n;
		while(!q.empty())
		{
			int u=q.front();
			for(int i=0;i<N;i++)
				if(ch[u][i])
				{
					int v=ch[u][i];
					f[v]=min(f[u]+1,len[v]/2-len[g[v]]+f[g[v]]+1);
					ans=min(ans,n-len[v]+f[v]);
					q.push(v);
				}
			q.pop();
		}
		printf("%d\n",ans);
	}
	return 0;
}
