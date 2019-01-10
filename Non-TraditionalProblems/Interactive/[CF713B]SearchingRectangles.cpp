#include<iostream>
#include<cstdio>
using namespace std;

struct Matrix
{
	int x1,y1,x2,y2;
	Matrix(int a=0,int b=0,int c=0,int d=0):x1(a),y1(b),x2(c),y2(d){}
};
int n;

int Query(int x1,int y1,int x2,int y2)
{
	if(x1>x2||y1>y2) return 0;
	if(x2>n||y2>n) return 0;
	printf("? %d %d %d %d\n",x1,y1,x2,y2);
	fflush(stdout);
	int ans;
	scanf("%d",&ans);
	return ans;
}

void Pre(int n,Matrix &x,Matrix &y)
{
	int l=0,r=n+1,mid;
	while(l<r)
	{
		mid=(l+r)/2;
		int a=Query(1,1,mid,n);
		int b=Query(mid+1,1,n,n);
		if(a==1&&b==1)
		{
			x=Matrix(1,1,mid,n);
			y=Matrix(mid+1,1,n,n);
			return;
		}
		else if(a==0&&b==0) break;
		else if(a>=1) r=mid;
		else l=mid+1;
	}
	l=0,r=n+1;
	while(l<r)
	{
		mid=(l+r)/2;
		int a=Query(1,1,n,mid);
		int b=Query(1,mid+1,n,n);
		if(a==1&&b==1)
		{
			x=Matrix(1,1,n,mid);
			y=Matrix(1,mid+1,n,n);
			return;
		}
		else if(a==0&&b==0) break;
		else if(a>=1) r=mid;
		else l=mid+1;
	}
}

void find(Matrix &x)
{
	int l=0,r=x.x2-x.x1+2,mid;
	Matrix ans;
	while(l<r)
	{
		mid=(l+r)/2;
		int a=Query(x.x1+mid,x.y1,x.x2,x.y2);
		if(a==1) l=mid+1;
		else r=mid;
	}
	ans.x1=x.x1+r-1;
	l=0,r=x.x2-x.x1+2;
	while(l<r)
	{
		mid=(l+r)/2;
		int a=Query(x.x1,x.y1,x.x1+mid-1,x.y2);
		if(a==1) r=mid;
		else l=mid+1;
	}
	ans.x2=x.x1+r-1;
	l=0,r=x.y2-x.y1+2;
	while(l<r)
	{
		mid=(l+r)/2;
		int a=Query(x.x1,x.y1+mid,x.x2,x.y2);
		if(a==1) l=mid+1;
		else r=mid;
	}
	ans.y1=x.y1+r-1;
	l=0,r=x.y2-x.y1+2;
	while(l<r)
	{
		mid=(l+r)/2;
		int a=Query(x.x1,x.y1,x.x2,x.y1+mid-1);
		if(a==1) r=mid;
		else l=mid+1;
	}
	ans.y2=x.y1+r-1;
	x=ans;
}

int main()
{
	cin>>n;
	Matrix x,y;
	Pre(n,x,y);
	find(x);
	find(y);
	printf("! %d %d %d %d %d %d %d %d\n",x.x1,x.y1,x.x2,x.y2,y.x1,y.y1,y.x2,y.y2);
	fflush(stdout);
	return 0;
}
