#include<bits/stdc++.h>
using namespace std;
 
int main()
{
    int n;cin>>n;
    double res=0,tmp=1;
    for(int i=100000;i>n;i--)
        res=(1-res)/i;
    printf("%.4lf\n",res);
    return 0;
}