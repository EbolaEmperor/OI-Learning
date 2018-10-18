#include<bits/stdc++.h>
using namespace std;

const int N=3000010;
int s[2*N],ss[2*N];
int p[2*N];
long long f[N];

int main()
{
	int n,len=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",ss+i);
	s[len]=5;s[++len]=-1;
	for(int i=1;i<=n;i++)
		s[++len]=ss[i],s[++len]=-1;
	s[len+1]=6;
	int mx=0,id=0,mxa=0;
	for(int i=1;i<=len;i++)
	{
		if(i<mx) p[i]=min(p[2*id-i],mx-i);
		else p[i]=1;
		while(s[i+p[i]]==s[i-p[i]]&&(p[i]<2||s[i-p[i]]<=s[i-p[i]+2])) p[i]++;
		f[p[i]-1]++;
		mxa=max(mxa,p[i]-1);
		if(i+p[i]>mx) mx=i+p[i],id=i;
	}
	for(int i=mxa;i>=2;i--) f[i-2]+=f[i];
	for(int i=1;i<mxa;i++) f[i+1]+=f[i];
	f[0]=0;
	int Q,opt,x;
	for(cin>>Q;Q;Q--)
	{
		scanf("%d%d",&opt,&x);
		if(opt==1926) printf("%d\n",lower_bound(f+1,f+1+mxa,x)-f);
		else printf("%lld\n",f[x-1]+1);
	}
	return 0;
}
