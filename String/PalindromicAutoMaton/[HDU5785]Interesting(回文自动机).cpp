#include<bits/stdc++.h>
#define Mod 1000000007
using namespace std;

typedef long long LL;
const int MAXN=1000010;
int ch[MAXN][26],fail[MAXN];
int len[MAXN],num[MAXN],sum[MAXN];
int lst,sz,n;
int s[MAXN];
char ss[MAXN];
int f[MAXN];

int newnode(int l)
{
	len[++sz]=l;
	memset(ch[sz],0,sizeof(ch[sz]));
	num[sz]=sum[sz]=0;
	return sz;
}

void init()
{
	sz=-1;
	lst=n=0;
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
		num[now]=num[fail[now]]+1;
		sum[now]=(sum[fail[now]]+len[now])%Mod;
		ch[cur][c]=now;
	}
	lst=ch[cur][c];
}

int main()
{
	while(~scanf("%s",ss))
	{
		init();
		int l=strlen(ss);
		for(LL i=0;i<l;i++)
		{
			insert(ss[i]-'a');
			f[i+1]=((i+2)*num[lst]%Mod-sum[lst]+Mod)%Mod;
		}
		init();
		LL ans=0;
		for(LL i=l-1;i>=0;i--)
		{
			insert(ss[i]-'a');
			ans=(ans+f[i]*(i*num[lst]%Mod+sum[lst])%Mod)%Mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
