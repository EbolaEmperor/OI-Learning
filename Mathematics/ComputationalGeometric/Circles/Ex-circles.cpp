#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

const double PI=acos(-1);
const double eps=1e-6;

double Heron(double a,double b,double c)
{
	double p=(a+b+c)/2;
	return sqrt(p*(p-a)*(p-b)*(p-c));
}
double angle(double a,double b,double c){return acos((b*b+c*c-a*a)/(2*b*c));}

int main()
{
	double a,b,c;
	int cnt=0;
	while(scanf("%lf%lf%lf",&a,&b,&c)&&a>eps&&b>eps&&c>eps)
	{
		double S=Heron(a,b,c);
		double A=angle(a,b,c);
		double B=angle(b,c,a);
		double C=angle(c,a,b);
		double ra=(2*S)/(b+c-a);
		double rb=(2*S)/(a+c-b);
		double rc=(2*S)/(a+b-c);
		double ans1=S+a*ra/2+b*rb/2+c*rc/2;
		double ans2=(ra*ra*(PI/2-A/2)+rb*rb*(PI/2-B/2)+rc*rc*(PI/2-C/2))/2;
		printf("Case %d: %.2lf %.2lf\n",++cnt,ans1,ans2);
	}
	return 0;
}
