#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=100010;
int n,f[2][N],p=0;
char s[N];
LL T;

int main()
{
    cin>>n>>T>>s;
    for(int i=0;i<n;i++) f[0][i]=s[i]-'0';
    for(int k=0;k<60;k++)if(T&(1ll<<k))
    {
        int pr=(1ll<<k)%n,pl=(n-pr)%n;
        for(int i=0;i<n;i++)
        {
            f[p^1][i]=f[p][pl]^f[p][pr];
            if(++pl>=n) pl-=n;
            if(++pr>=n) pr-=n;
        }
        p^=1;
    }
    for(int i=0;i<n;i++)
        printf("%d",f[p][i]);
    return 0;
}