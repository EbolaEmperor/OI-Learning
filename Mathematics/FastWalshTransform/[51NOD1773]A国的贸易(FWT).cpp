#include<bits/stdc++.h>
#define Mod 1000000007
#define inv2 500000004
using namespace std;

inline int read()
{
	int x=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	return x;
}

inline void put(int x)
{
    if(x>9) put(x/10);
    putchar(x%10+'0');
}

const int N=2097162;
int f[N],g[N],ans[N];

void FWT(int *a,int n,bool flag)
{
	for(int i=1;i<n;i<<=1)
		for(int j=0;j<n;j+=(i<<1))
			for(int k=0;k<i;k++)
			{
				int x=a[j+k],y=a[i+j+k];
				if(flag) a[j+k]=(x+y)%Mod,a[i+j+k]=(x-y+Mod)%Mod;
				else a[j+k]=1ll*(x+y)*inv2%Mod,a[i+j+k]=1ll*(x-y+Mod)*inv2%Mod;
			}
}

int main()
{
	int n=read(),t=read();
	int len=1<<n;
	for(int i=0;i<len;i++) f[i]=read();
	if(t==0){for(int i=0;i<len;i++) put(f[i]),putchar(' ');return 0;}
	for(int i=0;i<n;i++) g[1<<i]=1;g[0]=1;
	FWT(f,len,1);FWT(g,len,1);
	for(int i=0;i<len;i++) ans[i]=g[i];
	for(t--;t;t>>=1)
	{
		if(t&1) for(int i=0;i<len;i++) ans[i]=1ll*ans[i]*g[i]%Mod;
		for(int i=0;i<len;i++) g[i]=1ll*g[i]*g[i]%Mod;
	}
	for(int i=0;i<len;i++) ans[i]=1ll*ans[i]*f[i]%Mod;
	FWT(ans,len,0);
	for(int i=0;i<len;i++) put(ans[i]),putchar(' ');
	return 0;
}
