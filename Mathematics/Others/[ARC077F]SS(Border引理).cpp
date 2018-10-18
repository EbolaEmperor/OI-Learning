#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=200010;
char s[N];
int nxt[N];
LL l,r;
LL f[100][27];
LL sum[100],ans[27];
int mx=90;

void getnext()
{
	int n=strlen(s+1)/2,j=0;
	for(int i=2;i<=n;i++)
	{
		while(j&&s[i]!=s[j+1]) j=nxt[j];
		if(s[i]==s[j+1]) j++;
		nxt[i]=j;
	}
}

void initfib()
{
	for(int i=2;i<=mx;i++)
	{
		for(int j=0;j<26;j++)
			f[i][j]=f[i-1][j]+f[i-2][j];
		sum[i]=sum[i-1]+sum[i-2];
		if(sum[i]>LL(1e18)){mx=i;break;}
	}
}

void gao(LL x,int fg)
{
	int p;
	for(p=0;p<=mx;p++)
		if(sum[p]>x) break;
	for(;p>=0;p--)
		if(x>=sum[p])
		{
			for(int i=0;i<26;i++)
				ans[i]+=fg*f[p][i];
			x-=sum[p];
		}
	for(int i=1;i<=x;i++) ans[s[i]-'a']+=fg;
}

int main()
{
	scanf("%s%lld%lld",s+1,&l,&r);
	int n=strlen(s+1);
	for(int i=1;i<=n/2;i++)
		f[0][s[i]-'a']++;
	getnext();
	sum[0]=n/2;sum[1]=n-nxt[n/2];
	for(int i=0;i<26;i++) f[1][i]=f[0][i];
	for(int i=1;i<=n/2-nxt[n/2];i++)
		f[1][s[i]-'a']++;
	initfib();gao(r,1);gao(l-1,-1);
	for(int i=0;i<26;i++) printf("%lld ",ans[i]);
	return 0;
}
