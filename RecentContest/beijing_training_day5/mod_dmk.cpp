#include<bits/stdc++.h>
using namespace std;

long long Rand(){return ((long long)rand()<<30|rand()<<15|rand())%10000000000000ll;}
long long a[200010];

int main()
{
    freopen("mod2.in","w",stdout);
    srand(time(0));
    int n=200000;
    printf("%d\n",n);
    for(int i=1;i<=n;i++) a[i]=Rand();
    sort(a+1,a+1+n);
    for(int i=n;i>=1;i--)
        printf("%lld ",a[i]);puts("");
    return 0;
}
