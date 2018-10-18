#include<bits/stdc++.h>
using namespace std;

namespace IO
{
	const int S=1<<20;
	//Input Correlation
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
	//Output Correlation
	char obuf[S],*oS=obuf,*oT=oS+S-1,qu[55];int qr;
	inline void flush()
	{
		fwrite(obuf,1,oS-obuf,stdout);
		oS=obuf;
	}
	inline void putc(char x)
	{
		*oS++ =x;
		if(oS==oT) flush();
	}
	template <class I>
	inline void print(I x)
	{
		if(!x) putc('0');
		while(x) qu[++qr]=x%10+'0',x/=10;
		while(qr) putc(qu[qr--]);
		putc('\n');
	}
}

using namespace IO;
typedef long long LL;
const double pi=acos(-1);
const int N=150010;
struct Comp
{
	double r,i;
	Comp(double a=0,double b=0):r(a),i(b){}
	friend Comp operator + (const Comp &a,const Comp &b){return Comp(a.r+b.r,a.i+b.i);}
	friend Comp operator - (const Comp &a,const Comp &b){return Comp(a.r-b.r,a.i-b.i);}
	friend Comp operator * (const Comp &a,const Comp &b){return Comp(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r);}
} A[N],B[N];
int a[N],b[N],r[N];
LL c[N];

void FFT(Comp *a,int n,int v)
{
	for(int i=0;i<n;i++) if(i<r[i]) swap(a[i],a[r[i]]);
	for(int i=1;i<n;i<<=1)
	{
		Comp wn=Comp(cos(pi/i),v*sin(pi/i));
		for(int j=0;j<n;j+=i<<1)
		{
			Comp w=Comp(1,0);
			for(int k=0;k<i;k++,w=w*wn)
			{
				Comp x=a[j+k],y=w*a[i+j+k];
				a[j+k]=x+y;a[i+j+k]=x-y;
			}
		}
	}
	if(v==-1) for(int i=0;i<n;i++) a[i].r/=n;
}

void CDQ(int L,int R)
{
	if(L==R) return;
	int M=(L+R)/2,len=1;
	for(;len<R-L;len<<=1);
	for(int i=0;i<len;i++) r[i]=(r[i>>1]>>1)|((i&1)*(len>>1));
	
	for(int i=0;i<len;i++) A[i]=B[i]=Comp(0,0);
	for(int i=L;i<=M;i++) A[i-L].r=a[i];
	for(int i=M+1;i<=R;i++) B[i-M-1].r=b[i];
	FFT(A,len,1);FFT(B,len,1);
	for(int i=0;i<len;i++) A[i]=A[i]*B[i];
	FFT(A,len,-1);
	for(int i=0;i<len;i++) c[i+L+M+1]+=LL(A[i].r+0.5);
	
	for(int i=0;i<len;i++) A[i]=B[i]=Comp(0,0);
	for(int i=M+1;i<=R;i++) A[i-M-1].r=a[i];
	for(int i=L;i<=M;i++) B[M-i].r=b[i];
	FFT(A,len,1);FFT(B,len,1);
	for(int i=0;i<len;i++) A[i]=A[i]*B[i];
	FFT(A,len,-1);
	for(int i=0;i<len;i++) c[i+1]+=LL(A[i].r+0.5);
	
	CDQ(L,M);CDQ(M+1,R);
}

int main()
{
	int T,n,m,Q,x,mx=0;
	for(T=read();T;T--,mx=0)
	{
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(c,0,sizeof(c));
		n=read();m=read();Q=read();
		for(int i=1;i<=n;i++) x=read(),a[x]++,mx=max(mx,x);
		for(int i=1;i<=m;i++) x=read(),b[x]++,mx=max(mx,x);
		for(int i=0;i<=mx;i++) c[0]+=1ll*a[i]*b[i];
		CDQ(0,mx);while(Q--) print(c[read()]);
	}
	flush();
	return 0;
}
