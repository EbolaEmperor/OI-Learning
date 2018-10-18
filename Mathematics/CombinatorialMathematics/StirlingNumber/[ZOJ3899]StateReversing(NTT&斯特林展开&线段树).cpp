#include<bits/stdc++.h>
#define ha 880803841
using namespace std;

int read()
{
	int x=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	return x;
}
void write(int x)
{
	if(x/10) write(x/10);
	putchar(x%10+'0');
}

const int N=270010;
int A[N],B[N],f[N];
int ifac[N],r[N];

int Pow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%ha)
		if(b&1) ans=1ll*ans*a%ha;
	return ans;
}

void NTT(int *A,int n,int IDFT)
{
	for(int i=0;i<n;i++) r[i]=(r[i>>1]>>1)|((i&1)*(n>>1));
	for(int i=0;i<n;i++) if(i<r[i]) swap(A[i],A[r[i]]);
	for(int i=1;i<n;i<<=1)
	{
		int wn=Pow(26,(ha-1)/(i<<1));
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

void Init(int n,int k)
{
	int facn=1,len;
	for(int i=1;i<=n;i++)
		facn=1ll*facn*i%ha;
	ifac[n]=Pow(facn,ha-2);
	for(int i=n-1;i>=0;i--)
		ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
	memset(A,0,sizeof(A));
	memset(B,0,sizeof(B));
	memset(f,0,sizeof(f));
	for(int i=0;i<=n;i++)
	{
		A[i]=1ll*(i&1?ha-1:1)*ifac[i]%ha;
		B[i]=1ll*Pow(i,k)*ifac[i]%ha;
	}
	for(len=1;len<=(n<<1);len<<=1);
	NTT(A,len,0);NTT(B,len,0);
	for(int i=0;i<len;i++)
		f[i]=1ll*A[i]*B[i]%ha;
	NTT(f,len,1);
}

int val[N<<1];
bool tag[N<<1];

void pushdown(int o,int l,int r)
{
	tag[o]=0;
	tag[o<<1]^=1;
	tag[o<<1|1]^=1;
	int mid=(l+r)/2;
	val[o<<1]=mid-l+1-val[o<<1];
	val[o<<1|1]=r-mid-val[o<<1|1];
}

void Build(int o,int l,int r)
{
	if(l==r){val[o]=1;return;}
	int mid=(l+r)/2;
	Build(o<<1,l,mid);
	Build(o<<1|1,mid+1,r);
	val[o]=val[o<<1]+val[o<<1|1];
}

void Change(int o,int l,int r,int nl,int nr)
{
	if(l>=nl&&r<=nr)
	{
		val[o]=r-l+1-val[o];
		tag[o]^=1;return;
	}
	if(tag[o]) pushdown(o,l,r);
	int mid=(l+r)/2;
	if(nl<=mid) Change(o<<1,l,mid,nl,nr);
	if(nr>mid) Change(o<<1|1,mid+1,r,nl,nr);
	val[o]=val[o<<1]+val[o<<1|1];
}

int main()
{
	int T,n,m,Q,l,r;
	for(T=read();T;T--)
	{
		n=read();m=read();Q=read();
		Init(m,n);Build(1,1,m);
		memset(tag,0,sizeof(tag));
		while(Q--)
		{
			l=read();r=read();
			Change(1,1,m,l,r);
			write(f[val[1]]);
			putchar('\n');
		}
	}
	return 0;
}
