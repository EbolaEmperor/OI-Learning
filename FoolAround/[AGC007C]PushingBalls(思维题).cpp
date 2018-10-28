#include<bits/stdc++.h>
using namespace std;
typedef long double LD;

LD gao(int n,LD d,LD x)
{
    if(n==1) return (d*2+x)/2.0;
    LD d1=(d*(2*n-2)+(d+x*2)+(d*3+x*3));
    LD x1=x/d1*(2*n+4),cur=(d*n*2+x*n*(2*n-1))/(2.0*n);
    return cur+d1/(2.0*n)*gao(n-1,1.0,x1);
}

int main()
{
    int n,d,x;
    scanf("%d%d%d",&n,&d,&x);
    printf("%.10Lf\n",gao(n,d,x));
    return 0;
}