#include<bits/stdc++.h>
using namespace std;

const int N=300010;
const double pi=acos(-1);
struct Comp
{
	double r,i;
	Comp(double x=0,double y=0):r(x),i(y){}
	friend Comp operator + (Comp a,Comp b){return Comp(a.r+b.r,a.i+b.i);}
	friend Comp operator - (Comp a,Comp b){return Comp(a.r-b.r,a.i-b.i);}
	friend Comp operator * (Comp a,Comp b){return Comp(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r);}
};
int n,m,l=0,r[N<<2];
Comp a[N<<2],b[N<<2],c[N<<2];
char ss1[N],ss2[N];
int s1[N<<2],s2[N<<2];

void FFT(Comp *a,int n,int v)
{
	for(int i=0;i<n;i++) if(i<r[i]) swap(a[i],a[r[i]]);
	for(int i=1;i<n;i*=2)
	{
		Comp wn=Comp(cos(pi/i),v*sin(pi/i));
		int p=i*2;
		for(int j=0;j<n;j+=p)
		{
			Comp w=Comp(1,0);
			for(int k=0;k<i;k++)
			{
				Comp x=a[j+k],y=w*a[i+j+k];
				a[j+k]=x+y;a[i+j+k]=x-y;
				w=w*wn;
			}
		}
	}
	if(v==-1) for(int i=0;i<n;i++) a[i].r=round(a[i].r/n);
}

int main()
{
	int m,n,len;
	scanf("%d%d",&m,&n);
	scanf("%s%s",ss1,ss2);
	reverse(ss1,ss1+m);
	for(int i=0;i<m;i++) s1[i]=(ss1[i]!='*')?(ss1[i]-'a'+1):0;
	for(int i=0;i<n;i++) s2[i]=(ss2[i]!='*')?(ss2[i]-'a'+1):0;
	for(len=1;len<m+n;len<<=1) l++;
	for(int i=0;i<len;i++) r[i]=(r[i/2]/2)|((i&1)<<(l-1));
	
	for(int i=0;i<len;i++) a[i]=Comp(s1[i]*s1[i]*s1[i],0),b[i]=Comp(s2[i],0);
	FFT(a,len,1);FFT(b,len,1);
	for(int i=0;i<len;i++) c[i]=c[i]+a[i]*b[i];
	
	for(int i=0;i<len;i++) a[i]=Comp(s1[i],0),b[i]=Comp(s2[i]*s2[i]*s2[i],0);
	FFT(a,len,1);FFT(b,len,1);
	for(int i=0;i<len;i++) c[i]=c[i]+a[i]*b[i];
	
	for(int i=0;i<len;i++) a[i]=Comp(s1[i]*s1[i],0),b[i]=Comp(s2[i]*s2[i],0);
	FFT(a,len,1);FFT(b,len,1);
	for(int i=0;i<len;i++) c[i]=c[i]-a[i]*b[i]*Comp(2,0);
	
	FFT(c,len,-1);int ans=0;
	for(int i=m-1;i<n;i++) ans+=(fabs(c[i].r)<=1e-7);
	printf("%d\n",ans);
	for(int i=m-1;i<n;i++) if(fabs(c[i].r)<=1e-7) printf("%d ",i-m+2);
	return 0;
}
