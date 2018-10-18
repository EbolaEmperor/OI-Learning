#include<bits/stdc++.h>
using namespace std;

const int N=50010;
int pc[60];
int p1[10010][30];  // c^i mod base[j]
int p2[10010][30];  // c^(10000*i) mod base[j]
int base[30];  //phi[phi[...phi[p]...]]
int n,m,p,c;
int a[N];

inline int phi(int x)
{
	int s=x;
	for(int i=2;i*i<=x;i++)
		if(x%i==0)
		{
			s=s/i*(i-1);
			while(x%i==0) x/=i;
		}
	if(x!=1) s=s/x*(x-1);
	return s;
}

inline int Pow(int a,int b,int p)
{
	int ans=1;
	while(b)
	{
		if(b&1) ans=1ll*ans*a%p;
		a=1ll*a*a%p;
		b>>=1;
	}
	return ans;
}

inline void Init()
{
	base[0]=p;
	for(int i=1;i<=28;i++)
		base[i]=phi(base[i-1]);
	pc[0]=1;
	for(int i=1;i<=50;i++)
		if(pow(1ll*c,1ll*i)<=1e9) pc[i]=pc[i-1]*c;
		else pc[i]=-1;
	for(int i=0;i<=28;i++)
	{
		p1[0][i]=1%base[i];
		for(int j=1;j<=10000;j++)
			p1[j][i]=1ll*p1[j-1][i]*c%base[i];
		p2[0][i]=1%base[i];
		for(int j=1;j<=10000;j++)
			p2[j][i]=1ll*p2[j-1][i]*p1[10000][i]%base[i];
	}
}

inline int powc(int b,int x){return 1ll*p2[b/10000][x]*p1[b%10000][x]%base[x];}

int val[N<<2],power[N<<2];

inline void maintain(int o)
{
	val[o]=(val[o*2]+val[o*2+1])%p;
	power[o]=min(power[o*2],power[o*2+1]);
}

void build(int o,int l,int r)
{
	if(l==r)
	{
		val[o]=a[l];
		power[o]=0;
		return;
	}
	int mid=(l+r)/2;
	build(o*2,l,mid);
	build(o*2+1,mid+1,r);
	maintain(o);
}

void work(int o,int x)
{
	int now=a[x],s=a[x];
	power[o]++;
	for(int i=power[o]-1;i>=0;i--)
		if(now<0||now>=base[i+1])
		{
			now=-1;
			s=powc(s%base[i+1]+base[i+1],i);
		}
		else
		{
			now=(now<40)?pc[now]:-1;
			s=powc(s%base[i+1],i);
		}
	val[o]=s;
}

void Modify(int o,int l,int r,int nl,int nr)
{
	if(power[o]>27) return;
	if(l==r){work(o,l);return;}
	int mid=(l+r)/2;
	if(nl<=mid) Modify(o*2,l,mid,nl,nr);
	if(nr>mid) Modify(o*2+1,mid+1,r,nl,nr);
	maintain(o);
}

int Query(int o,int l,int r,int nl,int nr)
{
	if(l>=nl&&r<=nr) return val[o];
	int mid=(l+r)/2,res=0;
	if(nl<=mid) res+=Query(o*2,l,mid,nl,nr);
	if(nr>mid) res+=Query(o*2+1,mid+1,r,nl,nr);
	return res%p;
}

void dfs(int o,int l,int r)
{
	if(l==r){printf("%d ",val[o]);return;}
	int mid=(l+r)/2;
	dfs(o*2,l,mid);
	dfs(o*2+1,mid+1,r);
}

int main()
{
	scanf("%d%d%d%d",&n,&m,&p,&c);
	Init();
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	build(1,1,n);
	int opt,l,r;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&opt,&l,&r);
		if(l>r) swap(l,r);
		if(opt==0) Modify(1,1,n,l,r);
		else printf("%d\n",Query(1,1,n,l,r));
	}
	return 0;
}
