#include<bits/stdc++.h>
using namespace std;

const int N=2000010;
int son[N][26],fa[N],sz=0,state[N];
char s[N];

void trie(int k)
{
	int p=0,l=strlen(s);
	for(int i=0;i<l;i++)
	{
		if(s[i]=='<') p=fa[p];
		else
		{
			int j=s[i]-'a';
			if(!son[p][j])
				son[p][j]=++sz,
				fa[son[p][j]]=p;
			p=son[p][j];
		}
		state[p]|=1<<(k-1);
	}
}

int ch[N][26],prt[N],len[N],S[N],pp[N],tot=1;

int insert(int p,int c,int st)
{
	int np=++tot;len[np]=len[p]+1;S[np]=st;
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

void BFS()
{
	queue<int> q;
	q.push(0);pp[0]=1;
	while(!q.empty())
	{
		int u=q.front();
		for(int i=0;i<26;i++)
			if(son[u][i])
			{
				int v=son[u][i];
				pp[v]=insert(pp[u],i,state[v]);
				q.push(v);
			}
		q.pop();
	}
}

int c[N],a[N],f[N];

void count()
{
	for(int i=1;i<=tot;i++) c[len[i]]++;
	for(int i=1;i<tot;i++) c[i+1]+=c[i];
	for(int i=1;i<=tot;i++) a[c[len[i]]--]=i;
	for(int i=tot;i>=1;i--)
	{
		int p=a[i];
		S[prt[p]]|=S[p];
		f[S[p]]=max(f[S[p]],len[p]);
	}
}

int main()
{
	int n;scanf("%d",&n);
	for(int T=1;T<=n;T++)
		scanf("%s",s),trie(T);
	BFS();count();
	int mx=(1<<n)-1;
	for(int i=mx;i>=0;i--)
		for(int j=1;j<=n;j++)
			if(i&(1<<(j-1)))
				f[i^(1<<(j-1))]=max(f[i^(1<<(j-1))],f[i]);
	int Q;scanf("%d",&Q);
	while(Q--)
	{
		scanf("%s",s);int x=0;
		for(int i=0;i<n;i++)
			x|=(1<<i)*(s[i]-'0');
		printf("%d\n",f[x]);
	}
	return 0;
}
