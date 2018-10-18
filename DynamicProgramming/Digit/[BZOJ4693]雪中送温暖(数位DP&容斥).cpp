#include<bits/stdc++.h>
#define ha 998244353
using namespace std;

const int N=10;
int f[60][520],K;
long long R[N],L[N],lim[N];

int solve(int bit,int nup)  //"nup" means "not upper"
{
    if(bit<0) return 1;
    int &res=f[bit][nup];
    if(res!=-1) return res;
    int one=0;res=0;
    for(int i=0;i<K;i++)
        if(lim[i]&(1ll<<bit)) one|=1<<i;
    for(int i=0;i<K;i++)
        if(one&(1<<i)) res=(res+solve(bit-1,nup|one^(1<<i)))%ha;
        else if(nup&(1<<i)) res=(res+solve(bit-1,nup|one))%ha;
    res=(res+solve(bit-1,nup|one))%ha;
    return res;
}

int main()
{
    int T;
    for(cin>>T;T;T--)
    {
        int ans=0;cin>>K;
        for(int i=0;i<K;i++) cin>>L[i],L[i]--;
        for(int i=0;i<K;i++) cin>>R[i],R[i]--;
        for(int s=0;s<(1<<K);s++)
        {
            int fg=1;
            for(int i=0;i<K;i++)
                if(s&(1<<i)) lim[i]=R[i];
                else
                {
                    lim[i]=L[i]-1;
                    fg=lim[i]>=0?-fg:0;
                }
            if(!fg) continue;
            memset(f,-1,sizeof(f));
            ans=(ans+fg*solve(54,0))%ha;
        }
        cout<<(ans%ha+ha)%ha<<endl;
    }
    return 0;
}