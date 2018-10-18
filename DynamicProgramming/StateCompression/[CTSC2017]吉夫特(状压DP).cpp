#include<bits/stdc++.h>
#define Mod 1000000007
using namespace std;

const int S=1<<16;
char buf[S],*H,*T;
inline char Get()
{
	if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
	if(H==T) return -1;return *H++;
}
inline int read()
{
	int x=0;char c=Get();
	while(!isdigit(c)) c=Get();
	while(isdigit(c)) x=x*10+c-'0',c=Get();
	return x;
}
inline void add(int &a,const int &b){a=(a+b>=Mod)?(a+b-Mod):(a+b);}

const int N=250010;
int n,a[N],pre[N],f[N];

int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		pre[a[i]]=i;
		f[a[i]]=1;
	}
	for(int i=1;i<=n;i++)
		for(int j=(a[i]-1)&a[i];j;j=(j-1)&a[i])
			if(pre[j]>i) add(f[j],f[a[i]]);
	int ans=0;
	for(int i=1;i<=n;i++)
		add(ans,f[a[i]]-1);
	printf("%d\n",ans);
	return 0;
}
