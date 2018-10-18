#include<bits/stdc++.h>
using namespace std;

const int MAXN=5000010;
char ss[MAXN];
int s[MAXN],n;
int ch[MAXN][26],sz;
int fail[MAXN],lst;
int len[MAXN],cnt[MAXN];
int g[MAXN],f[MAXN];
long long ans[MAXN];

int newnode(int l){len[++sz]=l;return sz;}

void init()
{
	sz=-1;
	n=lst=0;
	newnode(0);
	newnode(-1);
	fail[0]=1;
	s[0]=-1;
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
	cnt[lst]++;
}

int main()
{
	scanf("%s",ss);
	init();
	int l=strlen(ss);
	for(int i=0;i<l;i++)
		insert(ss[i]-'a');
	for(int i=sz;i>=2;i--)
		cnt[fail[i]]+=cnt[i];
	for(int i=2;i<=sz;i++)
	{
		if(len[i]/2==len[g[i]])
			f[i]=f[g[i]]+1;
		else f[i]=1;
		ans[f[i]]+=cnt[i];
	}
	for(int i=l;i>=1;i--)
		ans[i]+=ans[i+1];
	for(int i=1;i<=l;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
