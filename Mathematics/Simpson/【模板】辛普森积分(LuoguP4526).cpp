#include<bits/stdc++.h>
using namespace std;

const double eps=1e-12;
double a;

double F(double x){return pow(x,a/x-x);}
double simpson(double a,double b)
{
	double mid=(a+b)/2;
	return (F(a)+4*F(mid)+F(b))*(b-a)/6;
}
double asr(double a,double b,double A)
{
	double mid=(a+b)/2;
	double L=simpson(a,mid),R=simpson(mid,b);
	if(fabs(L+R-A)<=15*eps) return L+R+(L+R-A)/15.0;
	return asr(a,mid,L)+asr(mid,b,R);
}
double asr(double a,double b){return asr(a,b,simpson(a,b));}

int main()
{
	cin>>a;
	if(a<0) puts("orz");
	else printf("%.5lf\n",asr(eps,20.0));
	return 0;
}
