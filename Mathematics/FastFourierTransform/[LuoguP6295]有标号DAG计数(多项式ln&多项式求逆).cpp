#include<bits/stdc++.h>
#define Mod 998244353
using namespace std;

const int N=800000;
int a[N+10],b[N+10];
int fk[N+10],t[N+10],s[N+10];
int r[N+10],iv[N+10],fac[N+10];

void init()
{
	iv[1]=fac[0]=fac[1]=1;
	for(int i=2;i<N;i++){
		iv[i]=(-1ll*(Mod/i)*iv[Mod%i]%Mod+Mod)%Mod;
		fac[i]=1ll*fac[i-1]*i%Mod;
	}
}

int Pow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%Mod)
		if(b&1) ans=1ll*ans*a%Mod;
	return ans;
}

void NTT(int *a,int n,bool IDFT)
{
	for(int i=0;i<n;i++) r[i]=(r[i/2]/2)|((i&1)*(n/2));
	for(int i=0;i<n;i++) if(i<r[i]) swap(a[i],a[r[i]]);
	for(int i=1;i<n;i<<=1)
	{
		int p=(i<<1);
		int wn=Pow(3,(Mod-1)/p);
		if(IDFT) wn=Pow(wn,Mod-2);
		for(int j=0;j<n;j+=p)
		{
			int w=1;
			for(int k=0;k<i;k++)
			{
				int x=a[j+k],y=1ll*w*a[i+j+k]%Mod;
				a[j+k]=(x+y)%Mod;
				a[i+j+k]=(x-y+Mod)%Mod;
				w=1ll*w*wn%Mod;
			}
		}
	}
	int inv=IDFT?Pow(n,Mod-2):0;
	if(IDFT) for(int i=0;i<n;i++) a[i]=1ll*a[i]*inv%Mod;
}

void Inv(int n,int *a,int *b)
{
	if(n==1){b[0]=Pow(a[0],Mod-2);return;}
	Inv(n>>1,a,b);n<<=1;
	for(int i=0;i<n/2;i++) t[i]=a[i],t[i+n/2]=0;
	NTT(t,n,0);NTT(b,n,0);
	for(int i=0;i<n;i++)
		b[i]=(2ll-1ll*t[i]*b[i]%Mod+Mod)*b[i]%Mod;
	NTT(b,n,1);
	for(int i=n/2;i<n;i++) b[i]=0;
}

void Derivate(int n,int *a)
{
	a[n]=0;
	for(int i=0;i<n;i++)
		a[i]=1ll*a[i+1]*(i+1)%Mod;
}

void Integral(int n,int *a)
{
	for(int i=n-1;i>=1;i--)
		a[i]=1ll*a[i-1]*iv[i]%Mod;
	a[0]=0;
}

void Ln(int n,int *a)
{
	int m;for(m=1;m<(n<<1);m<<=1);
	for(int i=0;i<n;i++) fk[i]=a[i],fk[n+i]=0;
	memset(s,0,sizeof(s));
	Derivate(n,fk);Inv(m/2,a,s);
	NTT(fk,m,0);NTT(s,m,0);
	for(int i=0;i<m;i++)
		a[i]=1ll*fk[i]*s[i]%Mod;
	NTT(a,m,1);
	Integral(n,a);
	for(int i=n;i<m;i++) a[i]=0;
}

int Cn2(int n){
	return n >= 2 ? 1ll * n * (n - 1) / 2 % (Mod - 1) : 0;
}

int main()
{
	init();
    const int n = 1 << 17;
	for(int i = 1; i < n; i++){
		a[i] = Pow(1ll * Pow(2, Cn2(i)) * fac[i] % Mod, Mod - 2);
		if(i & 1) a[i] = (Mod - a[i]) % Mod;
	}
	a[0] = 1;
	Inv(n, a, b);
	for(int i = 1; i < n; i++)
		b[i] = 1ll * b[i] * Pow(2, Cn2(i)) % Mod;
	Ln(n, b);
	int T; cin >> T;
	for(int i = 1; i <= T; i++)
		cout << 1ll * b[i] * fac[i] % Mod << endl;
	return 0;
}
