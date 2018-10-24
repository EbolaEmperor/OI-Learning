#include<bits/stdc++.h>
using namespace std;

const int ha=1e9+7;
int f[2000010],n;

void add(int &x,const int &y){x=(x+y>=ha)?(x+y-ha):(x+y);}
void dev(int &x,const int &y){x=(x-y<0)?(x-y+ha):(x-y);}

int main()
{
    scanf("%d",&n);
    int sum=n-1;f[n]=n;
    for(int i=n+1;i<=2*n;i++) f[i]=1;
    for(int i=n-1;i>=1;i--)
    {
        add(f[i],f[i+1]);
        f[i]=(f[i]+1ll*(n-1)*(n-1))%ha;
        add(f[i],sum);
        dev(sum,f[i+n+1]);
        add(sum,f[i+2]);
    }
    printf("%d\n",f[1]);
    return 0;
}