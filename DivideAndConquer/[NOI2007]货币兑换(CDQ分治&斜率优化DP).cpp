#include<bits/stdc++.h>
#define INF 1e20
using namespace std;

const int N=100010;
const double eps=1e-9;
struct PNT{double x,y,k,a,b,r;int id;};
PNT p[N],t[N];
double f[N];
int sta[N],top;
int n;

bool cmp (const PNT &m,const PNT &n){return m.k>n.k;}

double slope(int a,int b)
{
	if(b==0) return -INF;
	if(fabs(p[a].x-p[b].x)<eps) return INF;
	return (p[b].y-p[a].y)/(p[b].x-p[a].x);
}

void CDQ(int L,int R)
{
	if(L==R)
	{
		f[L]=max(f[L],f[L-1]);
		p[L].y=f[L]/(p[L].a*p[L].r+p[L].b);
		p[L].x=p[L].y*p[L].r;
		return;
	}
	int M=(L+R)/2;
	int p1=L,p2=M+1;
	for(int i=L;i<=R;i++)
		if(p[i].id<=M) t[p1++]=p[i];
		else t[p2++]=p[i];
	for(int i=L;i<=R;i++) p[i]=t[i];
	CDQ(L,M);
	top=0;
	for(int i=L;i<=M;i++)
	{
		while(top>1&&slope(sta[top-1],sta[top])<slope(sta[top-1],i)+eps) top--;
		sta[++top]=i;
	}
	sta[++top]=0;
	int j=1;
	for(int i=M+1;i<=R;i++)
	{
		while(j<top&&slope(sta[j],sta[j+1])+eps>p[i].k) j++;
		f[p[i].id]=max(f[p[i].id],p[sta[j]].x*p[i].a+p[sta[j]].y*p[i].b);
	}
	CDQ(M+1,R);
	p1=L,p2=M+1;
	for(int i=L;i<=R;i++)
		if(p1<=M&&(p2>R||p[p1].x<p[p2].x||fabs(p[p1].x-p[p2].x)<eps&&p[p1].y<p[p2].y))
			t[i]=p[p1++];
		else t[i]=p[p2++];
	for(int i=L;i<=R;i++) p[i]=t[i];
}

int main()
{
	scanf("%d%lf",&n,f);
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf%lf",&p[i].a,&p[i].b,&p[i].r);
		p[i].k=-p[i].a/p[i].b;p[i].id=i;
	}
	sort(p+1,p+1+n,cmp);
	CDQ(1,n);
	printf("%.3lf\n",f[n]);
	return 0;
}
