#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<queue>
using namespace std;

int n;
char s[1000005];
int val[500010],f[500010];
int ch[500010][26];
int sz=0;

void insert()
{
	int u=0,len=strlen(s);
	for(int i=0;i<len;i++)
	{
		int idx=s[i]-'a';
		if(ch[u][idx]==0)
		{
			sz++;
			memset(ch[sz],0,sizeof(ch[sz]));
			ch[u][idx]=sz;
		}
		u=ch[u][idx];
	}
	val[u]++;
}

void GetFail()
{
	queue<int> q;
	f[0]=0;
	for(int c=0;c<26;c++)
	{
		int u=ch[0][c];
		if(u!=0) f[u]=0,q.push(u);
	}
	while(!q.empty())
	{
		int o=q.front();
		for(int c=0;c<26;c++)
		{
			int u=ch[o][c];
			if(u==0) continue;
			q.push(u);
			int v=f[o];
			while(v!=0&&ch[v][c]==0) v=f[v];
			f[u]=ch[v][c];
		}
		q.pop();
	}
}

int search()
{
	int n=strlen(s);
	int p=0,ans=0;
	for(int i=0;i<n;i++)
	{
		int idx=s[i]-'a';
		while(p!=0&&ch[p][idx]==0) p=f[p];
		p=ch[p][idx];
		if(val[p]>0)
		{
			int q=p;
			ans+=val[p];
			val[p]=0;
			while(f[q]!=0)
			{
				q=f[q];
				ans+=val[q];
				val[q]=0;
			}
		}
	}
	return ans;
}

int main()
{
	memset(val,0,sizeof(val));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s);
		insert();
	}
	GetFail();
	scanf("%s",s);
	printf("%d\n",search());
	return 0;
}
