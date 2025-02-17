#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
using namespace std;

int bit[510][510],n;
void Add(int x,int y,int k)
{
	for(int i=x;i<=n;i+=lowbit(i))
		for(int j=y;j<=n;j+=lowbit(j))
			bit[i][j]+=k;
}
int Sum(int x,int y)
{
	int res=0;
	for(int i=x;i>0;i-=lowbit(i))
		for(int j=y;j>0;j-=lowbit(j))
			res+=bit[i][j];
	return res;
}

struct Node{int x,y,v;} p[250010];
bool operator < (const Node &a,const Node &b){return a.v<b.v;}
struct Query{int x1,y1,x2,y2,k,id;} q[60010],q1[60010],q2[60010];
int ans[60010],now=0;

void gao(int ql,int qr,int l,int r)
{
	if(l==r)
	{
		for(int i=ql;i<=qr;i++)
			ans[q[i].id]=l;
		return;
	}
	int mid=(l+r)/2,s1=0,s2=0;
	while(now<mid) now++,Add(p[now].x,p[now].y,1);
	while(now>mid) Add(p[now].x,p[now].y,-1),now--;
	for(int i=ql;i<=qr;i++)
	{
		int x1=q[i].x1,y1=q[i].y1,x2=q[i].x2,y2=q[i].y2;
		int tmp=Sum(x2,y2)-Sum(x1-1,y2)-Sum(x2,y1-1)+Sum(x1-1,y1-1);
		if(q[i].k<=tmp) q1[++s1]=q[i];
		else q2[++s2]=q[i];
	}
	for(int i=1;i<=s1;i++) q[ql+i-1]=q1[i];
	for(int i=1;i<=s2;i++) q[ql+s1+i-1]=q2[i];
	if(s1) gao(ql,ql+s1-1,l,mid);
	if(s2) gao(ql+s1,qr,mid+1,r);
}

int main()
{
	int Q,x1,y1,x2,y2,z,tot=0;
	scanf("%d%d",&n,&Q);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&z);
			p[++tot]=Node{i,j,z};
		}
	sort(p+1,p+1+tot);
	for(int i=1;i<=Q;i++)
	{
		scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&z);
		q[i]=Query{x1,y1,x2,y2,z,i};
	}
	gao(1,Q,1,tot);
	for(int i=1;i<=Q;i++)
		printf("%d\n",p[ans[i]].v);
	return 0;
}
