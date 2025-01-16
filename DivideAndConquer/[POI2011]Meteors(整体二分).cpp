#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
using namespace std;

typedef long long LL;
const int N=300010;
LL bit[N];
int n,m,K;
void Add(int p,int x){for(;p<=m;p+=lowbit(p)) bit[p]+=x;}
LL Sum(int p){LL res=0;for(;p>0;p-=lowbit(p)) res+=bit[p];return res;}

vector<int> seg[N];
struct Node{int l,r,a;} p[N];
int ans[N],need[N],now=0;
int q[N],q1[N],q2[N];

void Add(Node p,int k)
{
	if(p.l<=p.r) Add(p.l,k*p.a),Add(p.r+1,-k*p.a);
	else Add(1,k*p.a),Add(p.r+1,-k*p.a),Add(p.l,k*p.a);
}

void gao(int ql,int qr,int l,int r)
{
	if(l==r)
	{
		for(int i=ql;i<=qr;i++)
			ans[q[i]]=l;
		return;
	}
	int mid=(l+r)/2,s1=0,s2=0;
	while(now<mid) now++,Add(p[now],1);
	while(now>mid) Add(p[now],-1),now--;
	for(int i=ql;i<=qr;i++)
	{
		int x=q[i];LL res=0;
		for(int j=0;j<seg[x].size();j++)
		{
			res+=Sum(seg[x][j]);
			if(res>=need[x]) break;
		}
		if(res>=need[x]) q1[++s1]=x;
		else q2[++s2]=x;
	}
	for(int i=1;i<=s1;i++) q[ql+i-1]=q1[i];
	for(int i=1;i<=s2;i++) q[ql+s1+i-1]=q2[i];
	if(s1) gao(ql,ql+s1-1,l,mid);
	if(s2) gao(ql+s1,qr,mid+1,r);
}

int main()
{
	int x;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&x);
		seg[x].push_back(i);
	}
	for(int i=1;i<=n;i++)
		scanf("%d",need+i);
	scanf("%d",&K);
	for(int i=1;i<=K;i++)
		scanf("%d%d%d",&p[i].l,&p[i].r,&p[i].a);
	p[++K]=Node{1,m,int(1e9)};
	for(int i=1;i<=n;i++) q[i]=i;
	gao(1,n,1,K);
	for(int i=1;i<=n;i++)
		if(ans[i]!=K) printf("%d\n",ans[i]);
		else puts("NIE");
	return 0;
}
