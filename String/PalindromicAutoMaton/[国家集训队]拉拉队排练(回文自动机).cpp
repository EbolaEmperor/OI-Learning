#include<bits/stdc++.h>
#define Mod 19930726
using namespace std;

typedef long long LL;
const int MAXN=1000010;
int s[MAXN],n;
int ch[MAXN][26],sz;
int fail[MAXN],lst;
int len[MAXN];
char ss[MAXN];
LL f[MAXN],cnt[MAXN];

int newnode(int l){len[++sz]=l;return sz;}

void init()
{
	n=lst=0;
	s[0]=-1;
	sz=-1;
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
		ch[cur][c]=now;
	}
	lst=ch[cur][c];
	cnt[lst]++;
}

LL QuickPow(LL a,LL b)
{
	LL ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%Mod;
		a=a*a%Mod;
		b>>=1;
	}
	return ans;
}

int main()
{
	int l;LL k;
	scanf("%d%lld%s",&l,&k,ss);
	init();
	for(int i=0;i<l;i++)
		insert(ss[i]-'a');
	LL sum=0;
	for(int i=sz;i>=2;i--)
	{
		cnt[fail[i]]+=cnt[i];
		f[len[i]]+=cnt[i];
		sum+=cnt[i];
	}
	if(sum<k){puts("-1");return 0;}
	LL ans=1;
	for(LL i=l;i>=1;i--)
	{
		if(i%2==0) continue;
		if(f[i]>=k){ans=ans*QuickPow(i,(LL)k)%Mod;break;}
		else ans=ans*QuickPow(i,f[i])%Mod,k-=f[i];
	}
	cout<<ans<<endl;
	return 0;
}
