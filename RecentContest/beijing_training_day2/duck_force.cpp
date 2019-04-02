#include<bits/stdc++.h>
using namespace std;

const int N=1050000;
int n,l[N],r[N],len[N],v[N];
int f[N],cnt[N];

int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d%d%d",l+i,r+i,v+i);
        l[i]--;r[i]--;
        len[i]=r[i]-l[i]+1;
        len[i]=(1<<len[i])-1;
    }
    for(int s=1;s<(1<<n);s++)
        cnt[s]=cnt[s^(s&-s)]+1;
    for(int k=0;k<n;k++)
        for(int s=0;s<(1<<n);s++)
            if(cnt[s]==k)
                for(int i=0;i<n;i++)
                    if(!((s>>i)&1)&&((s>>l[i])&len[i]))
                        f[s|1<<i]=max(f[s|1<<i],f[s]+v[i]);
    printf("%d\n",f[(1<<n)-1]);
    return 0;
}
