#include<bits/stdc++.h>
#define Mod 1000000007
using namespace std;

char b[1000010],s[1000010];
int nxt[1000010];
int a[1000010];
int chk[1000010],cnt=0;

int main()
{
	int n,p,j=0;
	scanf("%d%d",&n,&p);
	scanf("%s",b+1);
	int m=strlen(b+1);
	for(int i=2;i<=m;i++)
	{
		while(j&&b[i]!=b[j+1]) j=nxt[j];
		if(b[i]==b[j+1]) j++;
		nxt[i]=j;
	}
	for(int i=1;i<=p;i++) scanf("%d",a+i);
	sort(a+1,a+1+p);
	p=unique(a+1,a+1+p)-(a+1);
	for(int i=1;i<=p;i++)
	{
		int l=a[i],r=min(a[i]+m-1,n);
		if(i<p) r=min(r,a[i+1]);
		for(int k=l;k<=r;k++) s[k]=b[k-l+1];
	}
	j=0;
	for(int i=1;i<=n;i++)
	{
		while(j&&s[i]!=b[j+1]) j=nxt[j];
		if(s[i]==b[j+1]) j++;
		if(j==m) chk[++cnt]=i-m+1,j=nxt[j];
	}
	j=1;
	for(int i=1;i<=p;i++)
	{
		while(a[i]!=chk[j]&&j<=cnt) j++;
		if(j>cnt){puts("0");return 0;}
	}
	int res=0;
	for(int i=1;i<=n;i++)
		if(s[i]<'a'||s[i]>'z') res++;
	long long ans=1;
	for(int i=1;i<=res;i++)
		ans=ans*26%Mod;
	cout<<ans<<endl;
	return 0;
}
