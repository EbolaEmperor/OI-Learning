#include<bits/stdc++.h>
using namespace std;

struct AC
{
	int ch[26];
	int state;
	int fail;
	AC(){memset(ch,0,sizeof(ch));state=fail=0;}
} t[610];
int sz=0,n;
char s[60];
bool vis[610][4100];
short fromu[610][4100],fromc[610][4100];
int froms[610][4100];

void insert(char *s,int v)
{
	int p=0,len=strlen(s);
	for(int i=0;i<len;i++)
	{
		int j=s[i]-'A';
		if(!t[p].ch[j]) t[p].ch[j]=++sz;
		p=t[p].ch[j];
	}
	t[p].state|=1<<(v-1);
}

void getfail()
{
	queue<int> q;q.push(0);
	while(!q.empty())
	{
		int o=q.front();
		for(int i=0;i<26;i++)
			if(t[o].ch[i])
			{
				int v=t[o].ch[i];
				if(o) t[v].fail=t[t[o].fail].ch[i];
				q.push(v);
			}
			else t[o].ch[i]=t[t[o].fail].ch[i];
		q.pop();
	}
}

void print(int u,int s)
{
	if(!u) return;
	print(fromu[u][s],froms[u][s]);
	printf("%c",fromc[u][s]+'A');
}

void bfs()
{
	queue<int> q1,q2;
	q1.push(0);q2.push(0);
	vis[0][0]=1;
	while(!q1.empty())
	{
		int u=q1.front(),s=q2.front();
		if(s==(1<<n)-1) print(u,s),exit(0);
		for(int i=0;i<26;i++)
		{
			int v=t[u].ch[i],ss=s;
			for(int j=v;j;j=t[j].fail) ss|=t[j].state;
			if(!vis[v][ss])
			{
				vis[v][ss]=1;
				fromu[v][ss]=u;
				froms[v][ss]=s;
				fromc[v][ss]=i;
				q1.push(v);
				q2.push(ss);
			}
		}
		q1.pop();q2.pop();
	}
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%s",s),insert(s,i);
	getfail();
	bfs();
	return 0;
}
