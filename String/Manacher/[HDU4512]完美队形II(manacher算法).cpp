#include<bits/stdc++.h>
using namespace std;

int s[100010],ss[200010];
int p[200010];

int read()
{
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x;
}

int manacher(int l)
{
	int len=0;
	ss[len++]=-2;ss[len++]=-1;
	for(int i=0;i<l;i++)
		ss[len++]=s[i],ss[len++]=-1;
	ss[len]=-3;
	int id=0,mx=0,ans=-1;
	for(int i=1;i<len;i++)
	{
		if(i<mx) p[i]=min(p[2*id-i],mx-i);
		else p[i]=1;
		while(ss[i-p[i]]==ss[i+p[i]]&&ss[i-p[i]]<=ss[i-p[i]+2]) p[i]++;
		if(i+p[i]>mx) mx=i+p[i],id=i;
		ans=max(ans,p[i]-1);
	}
	return ans;
}

int main()
{
	for(int T=read();T;T--)
	{
		int n=read();
		for(int i=0;i<n;i++) s[i]=read();
		printf("%d\n",manacher(n));
	}
	return 0;
}
