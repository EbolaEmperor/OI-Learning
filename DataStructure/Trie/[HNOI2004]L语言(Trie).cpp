#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;

char ch[2000][30];
int sz=0,maxlen=0;
char s[2000005];
int val[2000];
bool dp[2000005];

void insert(char *s)
{
	int u=0,n=strlen(s);
	if(n>maxlen) maxlen=n;
	for(int i=0;i<n;i++)
	{
		int idx=s[i]-'a';
		if(ch[u][idx]==0)
		{
			sz++;
			ch[u][idx]=sz;
			val[sz]=0;
			memset(ch[sz],0,sizeof(ch[sz]));
		}
		u=ch[u][idx];
	}
	val[u]=1;
}

bool search(int st,int ed)
{
	int u=0;
	for(int i=st;i<=ed;i++)
	{
		int idx=s[i]-'a';
		if(ch[u][idx]==0) return 0;
		u=ch[u][idx];
	}
	return val[u];
}

int main()
{
	int n,m,ans=0;
	memset(ch[0],0,sizeof(ch[0]));
	val[0]=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s);
		insert(s);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%s",s);
		memset(dp,0,sizeof(dp));
		ans=0;
		int l=strlen(s);
		for(int j=0;j<l;j++)
			for(int k=max(j-maxlen,-1);k<=j;k++)
				if((k==-1||dp[k])&&search(k+1,j))
				{
					dp[j]=1;
					ans=j+1;
					break;
				}
		printf("%d\n",ans);
	}
	return 0;
}
