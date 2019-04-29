#include<bits/stdc++.h>
using namespace std;

const int N=100010;
int s[N],n,m,k,p;

int main()
{
    scanf("%d%d%d",&k,&p,&n);
    for(int i=0;i<n;i++) scanf("%d",s+i);
    for(int i=n;i<=k;i++) s[i]=s[i%n];
    scanf("%d",&m);
    for(int i=1,j,v;i<=m;i++)
        scanf("%d%d",&j,&v),s[j]=v;
    int a=0,b=1;
    for(int i=2;i<=k;i++)
    {
        int c=(1ll*b*s[i-1]+1ll*a*s[i-2])%p;
        cerr<<c<<" ";
        a=b;b=c;
    }
    cerr<<endl;
    cout<<b<<endl;
    return 0;
}