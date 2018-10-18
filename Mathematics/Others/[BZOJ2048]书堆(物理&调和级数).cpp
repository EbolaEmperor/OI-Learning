#include<bits/stdc++.h>
using namespace std;

const int N=10000;
const double r=0.5772156649;
const double eps=1e-6;

int main()
{
    long long n,m;double ans=0;cin>>n>>m;
    if(n<=N) for(int i=1;i<=n;i++) ans+=0.5/i;
    else ans=(log(n+1.0)+r)/2.0;
    cout<<(int)(ans*m-eps)<<endl;
    return 0;
}