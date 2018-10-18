#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;

struct Point{double x,y;} a,b;

int main()
{
	scanf("%lf%lf%lf%lf",&a.x,&a.y,&b.x,&b.y);
	a.x+=0.5;
	a.y+=0.5;
	b.x+=0.5;
	b.y+=0.5;
	double ans1=(a.x-b.x)*(a.x-b.x)+(a.y+b.y+1.0)*(a.y+b.y+1.0);
	double ans2=(a.x-b.x)*(a.x-b.x)+((1.0-a.y)+(1.0-b.y)+1.0)*((1.0-a.y)+(1.0-b.y)+1.0);
	double ans3=(a.x+b.x+1.0)*(a.x+b.x+1.0)+(a.y-b.y)*(a.y-b.y);
	double ans4=((1.0-a.x)+(1.0-b.x)+1.0)*((1.0-a.x)+(1.0-b.x)+1.0)+(a.y-b.y)*(a.y-b.y);
	double ans5=(a.y+b.x+1.0)*(a.y+b.x+1.0)+(a.x+b.y)*(a.x+b.y);
	double ans6=(a.y+(1.0-b.x)+1.0)*(a.y+(1.0-b.x)+1.0)+((1.0-a.x)+b.y)*((1.0-a.x)+b.y);
	double ans7=(a.x+b.y+1.0)*(a.x+b.y+1.0)+(a.y+b.x)*(a.y+b.x);
	double ans8=(a.x+(1.0-b.y)+1.0)*(a.x+(1.0-b.y)+1.0)+((1.0-a.y)+b.x)*((1.0-a.y)+b.x);
	double ans9=(a.x+(1.0-b.y))*(a.x+(1.0-b.y))+((1.0-a.y)+1.0+b.x)*((1.0-a.y)+1.0+b.x);
	double ans10=((1.0-a.x)+(1.0-b.y))*((1.0-a.x)+(1.0-b.y))+((1.0-a.y)+(1.0-b.x)+1.0)*((1.0-a.y)+(1.0-b.x)+1.0);
	double ans11=((1.0-a.x)+b.y+1.0)*((1.0-a.x)+b.y+1.0)+(a.y+(1.0-b.x))*(a.y+(1.0-b.x));
	double ans12=((1.0-a.x)+(1.0-b.y)+1.0)*((1.0-a.x)+(1.0-b.y)+1.0)+((1.0-a.y)+(1.0-b.x))*((1.0-a.y)+(1.0-b.x));
	double minn=min(min(min(min(ans1,ans2),min(ans3,ans4)),min(min(ans5,ans6),min(ans7,ans8))),min(min(ans9,ans10),min(ans11,ans12)));
	printf("%.3lf\n",sqrt(minn));
	return 0;
}
