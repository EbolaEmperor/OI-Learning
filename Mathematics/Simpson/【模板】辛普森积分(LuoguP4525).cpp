#include<bits/stdc++.h>
using namespace std;

const double eps=1e-12;
double a,b,c,d;

double F(double x){return (c*x+d)/(a*x+b);}
double simpson(double l,double r)
{
	double mid=(l+r)/2;
	return (F(l)+4*F(mid)+F(r))*(r-l)/6;
}
double asr(double l,double r,double A)
{
	double mid=(l+r)/2;
	double L=simpson(l,mid),R=simpson(mid,r);
	if(fabs(L+R-A)<=15*eps) return L+R+(L+R-A)/15.0;
	return asr(l,mid,L)+asr(mid,r,R);
}
double asr(double l,double r){return asr(l,r,simpson(l,r));}

int main()
{
	double l,r;
	cin>>a>>b>>c>>d>>l>>r;
	printf("%.6lf\n",asr(l,r));
	return 0;
}
