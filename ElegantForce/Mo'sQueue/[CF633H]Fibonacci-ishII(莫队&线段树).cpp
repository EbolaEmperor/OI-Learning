#include<bits/stdc++.h>
using namespace std;

const int N=30010;
int n,ha,block,hs;
int a[N],Hash[N];
int size[N<<2],cnt[N],ans[N];
struct Qry{int l,r,id;} q[N];

bool operator < (const Qry &a,const Qry &b){return a.l/block<b.l/block||a.l/block==b.l/block&&a.r<b.r;}

struct Matrix
{
	int a[2][2],m,n;
	Matrix(){memset(a,0,sizeof(a));m=2;n=1;}
	int* operator [] (const int &x){return a[x];}
	
	friend Matrix operator * (Matrix A,Matrix B)
	{
		Matrix C;C.m=A.m;C.n=B.n;
		for(int i=0;i<A.m;i++)
			for(int j=0;j<B.n;j++)
				for(int k=0;k<A.n;k++)
					C[i][j]=(C[i][j]+A[i][k]*B[k][j])%ha;
		return C;
	}
	
	friend Matrix operator + (Matrix A,Matrix B)
	{
		Matrix C;C.m=A.m;C.n=A.n;
		for(int i=0;i<C.m;i++)
			for(int j=0;j<C.n;j++)
				C[i][j]=(A[i][j]+B[i][j])%ha;
		return C;
	}
} f[N],sum[N<<2];

void Modify(int o,int l,int r,int k,int v)
{
	if(l==r)
	{
		size[o]=v;
		sum[o][1][0]=0;
		sum[o][0][0]=Hash[k]*v%ha;
		return;
	}
	int mid=(l+r)/2;
	if(k<=mid) Modify(o<<1,l,mid,k,v);
	else Modify(o<<1|1,mid+1,r,k,v);
	size[o]=size[o<<1]+size[o<<1|1];
	sum[o]=sum[o<<1]+f[size[o<<1]]*sum[o<<1|1];
}

void Add(int x){if(++cnt[x]==1) Modify(1,1,hs,x,1);}
void Del(int x){if(--cnt[x]==0) Modify(1,1,hs,x,0);}

int main()
{
	scanf("%d%d",&n,&ha);
	block=sqrt(n);
	for(int i=1;i<=n;i++) scanf("%d",a+i),Hash[i]=a[i];
	sort(Hash+1,Hash+1+n);
	hs=unique(Hash+1,Hash+1+n)-(Hash+1);
	for(int i=1;i<=n;i++) a[i]=lower_bound(Hash+1,Hash+1+hs,a[i])-Hash;
	f[0].m=f[0].n=f[1].m=f[1].n=2;
	f[0][0][0]=f[0][1][1]=1;
	f[1][0][0]=f[1][1][0]=f[1][0][1]=1;
	for(int i=2;i<=hs;i++) f[i]=f[i-1]*f[1];
	int Q,pl=0,pr=0;
	scanf("%d",&Q);
	for(int i=1;i<=Q;i++) scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i;
	sort(q+1,q+1+Q);
	for(int i=1;i<=Q;i++)
	{
		while(pl<q[i].l) Del(a[pl++]);
		while(pl>q[i].l) Add(a[--pl]);
		while(pr>q[i].r) Del(a[pr--]);
		while(pr<q[i].r) Add(a[++pr]);
		ans[q[i].id]=sum[1][0][0];
	}
	for(int i=1;i<=Q;i++) printf("%d\n",ans[i]);
	return 0;
}
