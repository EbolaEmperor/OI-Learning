#include<bits/stdc++.h>
using namespace std;

const int N=200010;
int ch[N][26],prt[N],len[N];
int lst=1,tot=1;
set<int> S[N];
set<int>::iterator it;
char s[N];
int sum[N];
string str[N];

void insert(int c,int x)
{
	int p=lst,np=++tot;
	len[np]=len[p]+1;
	S[np].insert(x);
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
	lst=np;
}

struct Edge{int to,next;} e[2*N];
int h[N],ss=0;

void add_edge(int u,int v){e[++ss].to=v;e[ss].next=h[u];h[u]=ss;}

void dfs(int u)
{
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		dfs(v);
		for(it=S[v].begin();it!=S[v].end();it++)
			S[u].insert(*it);
	}
	sum[u]=S[u].size();
}

int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int T=1;T<=n;T++)
	{
		scanf("%s",s);str[T]=s;
		int l=strlen(s);lst=1;
		for(int i=0;i<l;i++)
			insert(s[i]-'a',T);
	}
	for(int i=1;i<=tot;i++)
		add_edge(prt[i],i);
	dfs(1);
	for(int T=1;T<=n;T++)
	{
		int l=str[T].size(),p=1;
		long long ans=0;
		for(int i=0;i<l;i++)
		{
			int c=str[T][i]-'a';
			p=ch[p][c];
			while(sum[p]<k) p=prt[p];
			ans+=len[p];
		}
		printf("%lld ",ans);
	}
	return 0;
}
