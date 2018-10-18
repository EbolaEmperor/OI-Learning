#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

struct Point
{
	int x,y;
	Point(int _x=0,int _y=0):x(_x),y(_y){}
} p1[510],p2[510],ch1[510],ch2[510];
typedef Point Vector;

bool operator == (Point a,Point b){return a.x==b.x&&a.y==b.y;}
bool operator < (Point a,Point b){return a.x<b.x||(a.x==b.x&&a.y<b.y);}
Vector operator - (Vector a,Vector b){return Vector(a.x-b.x,a.y-b.y);}
int Cross(Vector a,Vector b){return a.x*b.y-a.y*b.x;}
int Dot(Vector a,Vector b){return a.x*b.x+a.x*b.x;}

int ConvexHull(Point p[],int n,Point ch[])
{
	sort(p,p+n);
	int m=0;
	for(int i=0;i<n;i++)
	{
		while(m>1&&Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
		ch[m++]=p[i];
	}
	int k=m;
	for(int i=n-2;i>=0;i--)
	{
		while(m>k&&Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
		ch[m++]=p[i];
	}
	if(n>1) m--;
	return m;
}

bool PointInSegment(Point p,Point a,Point b){return Cross(b-p,a-p)==0&&Dot(b-p,a-p)<0;}

bool PointInPolygon(Point p,Point* res,int cnt)
{
    int wn=0;
    for (int i=0;i<cnt;i++)
	{
        if(res[i]==p||res[(i+1)%cnt]==p||PointInSegment(p,res[i],res[(i+1)%cnt]))
            return 1;
        int k=Cross(res[(i+1)%cnt]-res[i],p-res[i]);
        int d1=res[i].y-p.y;
        int d2=res[(i+1)%cnt].y-p.y;
        if(k>0&&d1<=0&&d2>0) wn++;
        if(k<0&&d2<=0&&d1>0) wn--;
    }
    if(wn) return 1;
    return 0;
}

bool NoPointsInConvex(Point p[],int n,Point ch[],int m)
{
	bool flag=true;
	for(int i=0;i<n;i++)
		if(PointInPolygon(p[i],ch,m)){flag=false;break;}
	return flag;
}

bool SegmentProperIntersection(Point a1,Point a2,Point b1,Point b2)
{
	long long c1=Cross(b1-a1,a2-a1),c2=Cross(b2-a1,a2-a1);
	long long c3=Cross(a1-b1,b2-b1),c4=Cross(a2-b1,b2-b1);
	return c1*c2<0&&c3*c4<0;
}

int main()
{
	int n,m;
	while(~scanf("%d%d",&n,&m)&&n&&m)
	{
		for(int i=0;i<n;i++) scanf("%d%d",&p1[i].x,&p1[i].y);
		for(int i=0;i<m;i++) scanf("%d%d",&p2[i].x,&p2[i].y);
		int cnt1=ConvexHull(p1,n,ch1);
		int cnt2=ConvexHull(p2,m,ch2);
		bool flag=NoPointsInConvex(ch1,cnt1,ch2,cnt2);
		if(flag) flag=NoPointsInConvex(ch2,cnt2,ch1,cnt1);
		if(flag)
			for(int i=0;i<cnt1;i++)
			{
				for(int j=0;j<cnt2;j++)
					if(SegmentProperIntersection(ch1[i],ch1[(i+1)%cnt1],ch2[j],ch2[(j+1)%cnt2])){flag=false;break;}
				if(!flag) break;
			}
		puts(flag?"Yes":"No");
	}
	return 0;
}
