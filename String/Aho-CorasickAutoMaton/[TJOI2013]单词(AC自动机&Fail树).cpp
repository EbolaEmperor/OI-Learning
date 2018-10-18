#include<bits/stdc++.h>
using namespace std;

int ch[1000010][26],fail[1000010],sz=0;
int sum[1000010];
int q[1000010],head=0,tail=0;
char s[1000010];
int word[1000010];

void insert(char *s,int k)
{
	int p=0,len=strlen(s);
	for(int i=0;i<len;i++)
	{
		int j=s[i]-'a';
		if(!ch[p][j]) ch[p][j]=++sz;
		p=ch[p][j];
		sum[p]++;
	}
	word[k]=p;
}

void getfail()
{
	q[tail++]=0;
	while(head<tail)
	{
		int u=q[head++];
		for(int i=0;i<26;i++)
			if(ch[u][i])
			{
				int v=ch[u][i];
				if(u) fail[v]=ch[fail[u]][i];
				q[tail++]=v;
			}
			else ch[u][i]=ch[fail[u]][i];
	}
	for(int i=tail-1;i>=0;i--)
		sum[fail[q[i]]]+=sum[q[i]];
}

int main()
{
	int n;cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%s",s),insert(s,i);
	getfail();
	for(int i=1;i<=n;i++)
		printf("%d\n",sum[word[i]]);
	return 0;
}