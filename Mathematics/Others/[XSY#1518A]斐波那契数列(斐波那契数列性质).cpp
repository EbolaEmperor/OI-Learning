#include<bits/stdc++.h>
using namespace std;

const int N=100010;
int a[N],n;
map<int,bool> num;
int fib[N];

int main()
{
    fib[0]=0;fib[1]=1;
    for(int i=2;i<=46;i++)
        fib[i]=fib[i-1]+fib[i-2];
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    int ans=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=46;j++)
            if(num.count(fib[j]-a[i]))
                {num.clear();ans++;break;}
        num[a[i]]=1;
    }
    printf("%d\n",ans);
    return 0;
}