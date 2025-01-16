#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const double pi=acos(-1);

int main()
{
    int n,m;cin>>n>>m;
    LL lcm=1ll*n*m/__gcd(n,m);
    printf("%.7lf\n",cos(pi/lcm)/sin(pi/n)*tan(pi/m));
    return 0;
}