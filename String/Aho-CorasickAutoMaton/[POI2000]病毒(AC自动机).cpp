#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<queue>
#include<cstring>
#include<string>
using namespace std;

char s[30005];
int ch[2000000][5];
int val[2000000],f[2000000];
bool vis[2000000],flag[2000000];
int sz=0;

void Insert()
{
	int u=0,n=strlen(s);
	for(int i=0;i<n;i++)
	{
		int idx=s[i]-'0';
		if(ch[u][idx]==0)
		{
			sz++;
			memset(ch[sz],0,sizeof(ch[sz]));
			ch[u][idx]=sz;
			val[sz]=0;
		}
		u=ch[u][idx];
	}
	val[u]=1;
}

void GetFail()
{
	queue<int> q;
	f[0]=0;
	if(ch[0][0]!=0) q.push(ch[0][0]),f[ch[0][0]]=0;
	if(ch[0][1]!=0) q.push(ch[0][1]),f[ch[0][1]]=0;
	while(!q.empty())
	{
		int o=q.front();
		for(int i=0;i<2;i++)
		{
			int u=ch[o][i];
			if(u==0) ch[o][i]=ch[f[o]][i];
			q.push(u);
			int v=f[u];
			while(v!=0&&ch[v][i]==0) v=f[v];
			f[u]=ch[v][i];
			if(val[f[u]]!=0) val[u]=1;
		}
		q.pop();
	}
}

void DFS(int p)
{
	//cout<<"*"<<p<<endl;
	vis[p]=true;
	for(int i=0;i<2;i++)
		if(vis[ch[p][i]])
		{
			cout<<"TAK"<<endl;
			system("pause");
			exit(0);
		}
		else
			if(val[ch[p][i]]==0&&!flag[ch[p][i]])
			{
				flag[ch[p][i]]=true;
				DFS(ch[p][i]);
			}
	vis[p]=false;
}

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s);
		Insert();
	}
	memset(vis,0,sizeof(vis));
	memset(flag,0,sizeof(flag));
	DFS(0);
	cout<<"NIE"<<endl;
	system("pause");
	return 0;
}
