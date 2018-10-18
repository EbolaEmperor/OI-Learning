#include<iostream>
#include<cstdio>
using namespace std;

typedef long long LL;
void Ebola(LL a,LL b,LL c,LL &x,LL &y)
{
	if(a==1){x=b+c;y=1;return;}
	Ebola(b%a,a,-c,x,y);
	y=x;x=(c+b*y)/a%b;
}

LL China(LL m[],LL b[],int k)
{
	LL N=1,ans=0;
	for(int i=0;i<k;i++) N*=m[i];
	for(int i=0;i<k;i++)
	{
		LL x=0,y=0,M=N/m[i];
		Ebola(M,m[i],1,x,y);
		if(x<0) x+=m[i];
		ans=(ans+x*b[i]*M%N)%N;
	}
	return ans;
}

int main()
{
	int n;
	LL m[10],b[10];
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%lld%lld",b+i,m+i);
	printf("%lld\n",China(m,b,n));
	return 0;
}