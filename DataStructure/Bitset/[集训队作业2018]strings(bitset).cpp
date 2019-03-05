#include<bits/stdc++.h>
using namespace std;

const int N=1<<15,B=10;
bitset<N> b[110],c[12][1<<11];
__int128 a[N+3],o=1;
char s[110];
int n,q;

int main()
{
    scanf("%d%d",&n,&q);
    int m=n/2,mm=n-m;
    for(int i=0;i<q;i++)
    {
        scanf("%s",s);
        for(int t=0;t<(1<<m);t++)
        {
            bool flag=1;
            for(int j=0;j<m;j++)
                flag&=(s[j]=='?'||(s[j]-'0')==(t>>j&1));
            if(flag) a[t]|=o<<i;
        }
        for(int t=0;t<(1<<mm);t++)
        {
            bool flag=1;
            for(int j=0;j<mm;j++)
                flag&=(s[m+j]=='?'||(s[m+j]-'0')==(t>>j&1));
            if(flag) b[i][t]=1;
        }
    }
    for(int i=0,k=0;i<q;i+=B,k++)
    {
        int tot=min(q,i+B)-i;
        for(int t=1;t<(1<<tot);t++)
            c[k][t]=c[k][t&(t-1)]|b[__builtin_ctz(t)+i];
    }
    int ans=0;
    for(int t=0;t<(1<<m);t++)
    {
        bitset<N> res;
        for(int i=0,k=0;i<q;i+=B,k++)
        {
            int tot=min(q,i+B)-i;
            res|=c[k][(a[t]>>i)&((1<<tot)-1)];
        }
        ans+=res.count();
    }
    printf("%d\n",ans);
    return 0;
}