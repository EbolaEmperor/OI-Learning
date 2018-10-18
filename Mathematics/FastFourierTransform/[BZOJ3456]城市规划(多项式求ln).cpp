#include<bits/stdc++.h>
#define ha 1004535809
using namespace std;

const int N=270000;
int f[N],tln[N],tinv[N];
int ifac[N],r[N];

int Pow(int a,long long b)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%ha)
		if(b&1) ans=1ll*ans*a%ha;
	return ans;
}

void NTT(int *a,int n,bool IDFT)
{
	for(int i=0;i<n;i++) r[i]=(r[i>>1]>>1)|((i&1)*(n>>1));
	for(int i=0;i<n;i++) if(i<r[i]) swap(a[i],a[r[i]]);
	for(int i=1;i<n;i<<=1)
	{
		int wn=Pow(3,(ha-1)/(i<<1));
		if(IDFT) wn=Pow(wn,ha-2);
		for(int j=0;j<n;j+=i<<1)
			for(int k=0,w=1;k<i;k++)
			{
				int x=a[j+k],y=1ll*w*a[i+j+k]%ha;
				a[j+k]=(x+y)%ha;
				a[i+j+k]=(x-y+ha)%ha;
				w=1ll*w*wn%ha;
			}
	}
	int inv=IDFT?Pow(n,ha-2):0;
	if(IDFT) for(int i=0;i<n;i++) a[i]=1ll*a[i]*inv%ha;
}

void Inv(int *a,int *b,int n)
{
	if(n==1){b[0]=Pow(a[0],ha-2);return;}
	Inv(a,b,n>>1);n<<=1;
	for(int i=0;i<n/2;i++) tinv[i]=a[i],tinv[i+n/2]=0;
	NTT(tinv,n,0);NTT(b,n,0);
	for(int i=0;i<n;i++)
		b[i]=(2ll-1ll*tinv[i]*b[i]%ha+ha)*b[i]%ha;
	NTT(b,n,1);
	for(int i=n/2;i<n;i++) b[i]=0;
}

void Der(int *a,int n)
{
	for(int i=0;i<n-1;i++)
		a[i]=1ll*a[i+1]*(i+1)%ha;
	a[n-1]=0;
}

void Int(int *a,int n)
{
	for(int i=n-1;i>=1;i--)
		a[i]=1ll*a[i-1]*Pow(i,ha-2)%ha;
	a[0]=0;
}

void Ln(int *a,int n)
{
	int len;
	for(len=1;len<(n<<1);len<<=1);
	Inv(a,tln,len/2);Der(a,n);
	NTT(a,len,0);NTT(tln,len,0);
	for(int i=0;i<len;i++)
		a[i]=1ll*a[i]*tln[i]%ha;
	NTT(a,len,1);Int(a,n+1);
}

int main()
{
	int n,facn=1,len;
	scanf("%d",&n);
	for(len=1;len<=n;len<<=1);
	for(int i=1;i<len;i++)
		facn=1ll*facn*i%ha;
	ifac[len-1]=Pow(facn,ha-2);
	for(int i=len-2;i>=0;i--)
		ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
	for(int i=0;i<len;i++)
		f[i]=1ll*Pow(2,1ll*i*(i-1)/2)*ifac[i]%ha;
	Ln(f,len);facn=1;
	for(int i=1;i<=n;i++) facn=1ll*facn*i%ha;
	printf("%d\n",1ll*f[n]*facn%ha);
	return 0;
}
