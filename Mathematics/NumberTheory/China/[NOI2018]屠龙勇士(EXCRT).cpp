#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=100010;
int gt[N],atk[N];
LL a[N],p[N];
multiset<LL> A;
multiset<LL>::iterator it;
struct Equ{LL b,m;} equ[N];

LL ExGcd(LL a,LL b,LL &x,LL &y)
{
	if(b==0){x=1;y=0;return a;}
	LL g=ExGcd(b,a%b,x,y);
	LL t=x;x=y;y=t-(a/b)*y;
	return g;
}

LL Mul(LL a,LL b,LL p)
{
	LL ans=0,fg=1;
	if(b<0) fg=-1,b=-b;
	for(;b;b>>=1,a=(a+a)%p)
		if(b&1) ans=(ans+a)%p;
	return ans*fg;
}

bool ExCRT(Equ &a1,Equ a2)
{
	LL k1,k2,g;
	g=ExGcd(a1.m,a2.m,k1,k2);
	LL c=a2.b-a1.b;
	if(c%g) return 0;
	LL t=a2.m/g;
	k1=(Mul(k1,c/g,t)+t)%t;
	LL lcm=a1.m/g*a2.m;
	LL x=Mul(k1,a1.m,lcm)+a1.b;
	a1=Equ{x%lcm,lcm};
	return 1;
}

LL gao(int n)
{
	for(int i=1;i<=n;i++)
	{
		LL x,y,g;
		g=ExGcd(atk[i],p[i],x,y);
		if(a[i]%g) return -1;
		LL m=p[i]/g;
		x=(Mul(x,a[i]/g,m)+m)%m;
		equ[i]=Equ{x,m};
	}
	Equ now=equ[1];
	for(int i=2;i<=n;i++)
	{
		bool ok=ExCRT(now,equ[i]);
		if(!ok) return -1;
	}
	LL x=now.b,add=now.m;
	for(int i=1;i<=n;i++)
		if(x*atk[i]<a[i]) x+=add*(((a[i]-x*atk[i]-1)/atk[i])/add+1);
	return x;
}

int main()
{
	int T,n,m,x;
	for(scanf("%d",&T);T;T--)
	{
		scanf("%d%d",&n,&m);A.clear();
		for(int i=1;i<=n;i++) scanf("%lld",a+i);
		for(int i=1;i<=n;i++) scanf("%lld",p+i);
		for(int i=1;i<=n;i++) scanf("%d",gt+i);
		for(int i=1;i<=m;i++) scanf("%d",&x),A.insert(x);
		for(int i=1;i<=n;i++)
		{
			it=A.lower_bound(a[i]);
			if(it!=A.begin()&&(it==A.end()||*it!=a[i])) it--;
			atk[i]=*it;
			A.erase(it);
			A.insert(gt[i]);
		}
		printf("%lld\n",gao(n));
	}
}
