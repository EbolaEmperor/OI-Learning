#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=100010;
LL sum[N],x[N];
struct PNT
{
	LL x,y;
	PNT(LL a=0,LL b=0):x(a),y(b){}
} pnt[N],ch[N];
int top=0;

double slope(const PNT &a,const PNT &b){return (double)(a.y-b.y)/(double)(a.x-b.x);}
PNT operator - (const PNT &a,const PNT &b){return PNT(a.x-b.x,a.y-b.y);}
LL Cross(const PNT &a,const PNT &b){return a.x*b.y-a.y*b.x;}

double solve(PNT &p)
{
	int l=0,r=top-1;
	while(r-l>2)
	{
		int mid1=(2*l+r)/3,mid2=(l+2*r)/3;
		if(slope(p,ch[mid1])<slope(p,ch[mid2])) l=mid1;
		else r=mid2;
	}
	double ans=0;
	for(int i=l;i<=r;i++)
		ans=max(ans,slope(p,ch[i]));
	return ans;
}

int main()
{
	int n;LL d;
	scanf("%d%lld",&n,&d);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",sum+i,x+i);
		sum[i]+=sum[i-1];
		pnt[i]=PNT(d*i,sum[i]);
	}
	pnt[0]=PNT(0,0);
	double ans=0;
	for(int i=1;i<=n;i++)
	{
		PNT p=PNT(x[i]+d*(i-1),sum[i]);
		while(top>1&&Cross(ch[top-1]-ch[top-2],pnt[i-1]-ch[top-2])<=0) top--;
		ch[top++]=pnt[i-1];
		ans+=solve(p);
	}
	printf("%lld\n",(LL)round(ans));
	return 0;
}
