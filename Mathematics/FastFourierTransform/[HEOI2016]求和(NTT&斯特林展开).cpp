#include<bits/stdc++.h>
#define ha 998244353
using namespace std;

const int N=270010;
int A[N],B[N],C[N],r[N];
int fac[N],ifac[N],pw[N];

int Pow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%ha)
		if(b&1) ans=1ll*ans*a%ha;
	return ans;
}

void NTT(int *A,int n,bool IDFT)
{
	for(int i=0;i<n;i++) r[i]=(r[i>>1]>>1)|((i&1)*(n/2));
	for(int i=0;i<n;i++) if(i<r[i]) swap(A[i],A[r[i]]);
	for(int i=1;i<n;i<<=1)
	{
		int wn=Pow(3,(ha-1)/(i<<1));
		if(IDFT) wn=Pow(wn,ha-2);
		for(int j=0;j<n;j+=(i<<1))
			for(int k=0,w=1;k<i;k++)
			{
				int x=A[j+k],y=1ll*w*A[i+j+k]%ha;
				A[j+k]=(x+y)%ha;
				A[i+j+k]=(x-y+ha)%ha;
				w=1ll*w*wn%ha;
			}
	}
	int inv=IDFT?Pow(n,ha-2):0;
	if(IDFT) for(int i=0;i<n;i++) A[i]=1ll*A[i]*inv%ha;
}

void InitFac(int n)
{
	fac[0]=1;
	for(int i=1;i<=n;i++)
		fac[i]=1ll*fac[i-1]*i%ha;
	ifac[n]=Pow(fac[n],ha-2);
	for(int i=n-1;i>=0;i--)
		ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
}

void InitABC(int n)
{
	for(int i=0;i<=n;i++)
		A[i]=1ll*(i&1?ha-1:1)*ifac[i]%ha;
	B[0]=1;B[1]=n+1;
	for(int i=2;i<=n;i++)
		B[i]=1ll*(Pow(i,n+1)-1)*Pow(i-1,ha-2)%ha*ifac[i]%ha;
	int len;
	for(len=1;len<=(n<<1);len<<=1);
	NTT(A,len,0);NTT(B,len,0);
	for(int i=0;i<len;i++)
		C[i]=1ll*A[i]*B[i]%ha;
	NTT(C,len,1);
}

int main()
{
	int n,ans=0;
	scanf("%d",&n);
	InitFac(n);
	InitABC(n);
	pw[0]=1;
	for(int i=1;i<=n;i++)
		pw[i]=2ll*pw[i-1]%ha;
	for(int i=0;i<=n;i++)
		ans=(ans+1ll*pw[i]*fac[i]%ha*C[i])%ha;
	printf("%d\n",ans);
	return 0;
}
