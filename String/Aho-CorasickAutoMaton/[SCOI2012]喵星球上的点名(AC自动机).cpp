#include<bits/stdc++.h>
using namespace std;

map<int,int> ch[100010];
int fail[100010],sz=0;
int word[100010];
int tag[100010];
vector<int> ans[100010];
vector<int> miao[50010];
int s[100010];
int sum[100010];

void insert(int *s,int len,int k)
{
	int p=0;
	for(int i=0;i<len;i++)
	{
		int j=s[i];
		if(!ch[p].count(j)) ch[p][j]=++sz;
		p=ch[p][j];
	}
	tag[p]++;word[k]=p;
}

void getfail()
{
	queue<int> q;
	q.push(0);
	while(!q.empty())
	{
		int u=q.front();
		map<int,int>::iterator it;
		for(it=ch[u].begin();it!=ch[u].end();it++)
		{
			int i=it->first,v=it->second,k=fail[u];
			while(ch[k].count(i)==0&&k) k=fail[k];
			if(u) fail[v]=ch[k].count(i)==0?0:ch[k][i];
			q.push(v);
		}
		q.pop();
	}
}

int serch(vector<int> s,int k)
{
	int p=0,len=s.size(),res=0;
	for(int i=0;i<len;i++)
	{
		int j=s[i];
		while(p&&ch[p].count(j)==0) p=fail[p];
		if(ch[p].count(j)) p=ch[p][j];
		for(int f=p;f;f=fail[f])
			if(tag[f]&&(ans[f].size()==0||ans[f][ans[f].size()-1]!=k))
				ans[f].push_back(k),res+=tag[f];
	}
	return res;
}

int read()
{
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x;
}

int main()
{
	int n,m,l;
	n=read();m=read();
	for(int i=1;i<=n;i++)
	{
		l=read();
		for(int j=1;j<=l;j++) miao[i].push_back(read());
		miao[i].push_back(-1);
		l=read();
		for(int j=1;j<=l;j++) miao[i].push_back(read());
	}
	for(int i=1;i<=m;i++)
	{
		l=read();
		for(int j=0;j<l;j++) s[j]=read();
		insert(s,l,i);
	}
	getfail();
	for(int i=1;i<=n;i++) sum[i]=serch(miao[i],i);
	for(int i=1;i<=m;i++) printf("%d\n",ans[word[i]].size());
	for(int i=1;i<=n;i++) printf("%d ",sum[i]);
	return 0;
}
