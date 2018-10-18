#include<bits/stdc++.h>
using namespace std;

char s[500010];
int ss[1000010];
int p[1000010];

int manacher(int l)
{
	int len=0;
	ss[len++]=3;ss[len++]=1;
	for(int i=0;i<l;i++)
	{
		if(s[i]=='0') ss[len++]=0;
		else ss[len++]=2;
		ss[len++]=1;
	}
	ss[len]=3;
	int id=0,mx=0;
	for(int i=1;i<len;i+=2)
	{
		if(i<mx) p[i]=min(p[2*id-i],mx-i);
		else p[i]=1;
		while(ss[i-p[i]]+ss[i+p[i]]==2) p[i]++;
		if(i+p[i]>mx) mx=i+p[i],id=i;
	}
	return len;
}

int main()
{
	int n;
	long long ans=0;
	scanf("%d%s",&n,s);
	int len=manacher(n);
	for(int i=1;i<len;i+=2) ans+=p[i]/2;
	cout<<ans<<endl;
	return 0;
}
