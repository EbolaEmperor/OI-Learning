#include<bits/stdc++.h>
#define vec vector<Comp>
#define Mod 1000000007
#define pb push_back
using namespace std;

typedef long long LL;
struct Comp
{
	double r,i;
	Comp(double x=0,double y=0):r(x),i(y){}
	friend Comp operator + (Comp x,Comp y){return Comp(x.r+y.r,x.i+y.i);}
	friend Comp operator - (Comp x,Comp y){return Comp(x.r-y.r,x.i-y.i);}
	friend Comp operator * (Comp x,Comp y){return Comp(x.r*y.r-x.i*y.i,x.r*y.i+x.i*y.r);}
};
const double pi=acos(-1);
const int N=400000;
vec A,B;
int bin[N+10];
char s[N+10];
LL f[N+10],ans=0;
char ss[N+10];
int p[N+10];

vec FFT(vec a,int v)
{
	int n=a.size();
	if(n==1) return a;
	vec a1,a2;
	for(int i=0;i<n;i++)
		if(i&1) a2.pb(a[i]);
		else a1.pb(a[i]);
	a1=FFT(a1,v);a2=FFT(a2,v);
	Comp wn=Comp(cos(2*pi/n),v*sin(2*pi/n));
	Comp w=Comp(1,0);
	for(int i=0;i<n/2;i++)
	{
		Comp x=a1[i],y=a2[i];
		a[i]=x+w*y;
		a[n/2+i]=x-w*y;
		w=w*wn;
	}
	return a;
}

LL manacher()
{
	int len=strlen(s),tot=0;
	ss[tot++]='@';ss[tot++]='#';
	for(int i=0;i<len;i++)
		ss[tot++]=s[i],ss[tot++]='#';
	ss[tot]='\0';
	int id=0,mx=0;LL res=0;
	for(int i=1;i<tot;i++)
	{
		if(i<mx) p[i]=min(p[2*id-i],mx-i);
		else p[i]=1;
		while(ss[i+p[i]]==ss[i-p[i]]) p[i]++;
		if(i+p[i]>mx) id=i,mx=i+p[i];
		res=(res+p[i]/2)%Mod;
	}
	return res;
}

int main()
{
	bin[0]=1;
	for(int i=1;i<=N;i++)
		bin[i]=bin[i-1]*2%Mod;
	scanf("%s",s);
	int n=strlen(s);
	for(int i=0;i<n;i++)	
		A.pb(Comp(s[i]=='a'?1:0,0));
	int len=1;
	while(len<2*n) len<<=1;
	for(int i=n;i<len;i++) A.pb(Comp(0,0));
	A=FFT(A,1);
	for(int i=0;i<len;i++) B.pb(A[i]*A[i]);
	for(int i=0;i<n;i++)
		A[i]=Comp(s[i]=='b'?1:0,0);
	for(int i=n;i<len;i++) A[i]=Comp(0,0);
	A=FFT(A,1);
	for(int i=0;i<len;i++) B[i]=B[i]+A[i]*A[i];
	B=FFT(B,-1);
	for(int i=2;i<2*n+1;i++) f[i]+=(LL)round(B[i-2].r)/len;
	for(int i=2;i<2*n+1;i++) ans=(ans+bin[(f[i]+1)/2]-1)%Mod;
	printf("%lld\n",(ans-manacher()+Mod)%Mod);
	return 0;
}
