#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const int N=20;
ull n,ans=0;
int dig[N],len=0;
int sum[N],a[N],b[N];

void gao1(int len)
{
    for(int i=1;i<=len;i++)
        if(sum[i]!=sum[len-i+1]) return;
    ull res=1;
    for(int i=1;i<=(len+1)/2;i++)
        res*=min(9,sum[i]-(i==1))-max((int)(i==1),sum[i]-9)+1;
    ans+=res;
}

void gao2(int len)
{
    for(int lenb=1;lenb<len;lenb++)
    {
        memset(a,-1,sizeof(a));
        memset(b,-1,sizeof(b));
        for(int i=len;i>lenb;i--)
        {
            int x=i,v=sum[i];
            while(a[x]==-1)
            {
                a[x]=v;a[x=len-x+1]=v;
                if(x>lenb||b[x]!=-1) break;
                v=b[x]=sum[x]-a[x];
                b[x=lenb-x+1]=v;
                v=sum[x]-v;
            }
        }
        for(int i=1;i<=lenb;i++) if(b[i]<0||b[i]>9||b[i]!=b[lenb-i+1]) goto nice;
        for(int i=1;i<=len;i++) if(a[i]<0||a[i]>9||a[i]!=a[len-i+1]) goto nice;
        for(int i=lenb+1;i<=len;i++) if(a[i]!=sum[i]) goto nice;
        for(int i=1;i<=lenb;i++) if(a[i]+b[i]!=sum[i]) goto nice;
        if(a[len]==0||b[lenb]==0) goto nice;
        ans+=2;
        nice : ;
    }
}

int main()
{
    cin>>n;ull x=n;
    while(x) dig[++len]=x%10,x/=10;
    for(int s=0,tlen;s<(1<<len-1);s++)
    {
        memcpy(sum,dig,sizeof(dig));
        for(int i=1;i<len;i++) if(s&(1<<i-1)) sum[i]+=10,sum[i+1]--;
        for(int i=1;i<=len;i++) if(sum[i]<0||sum[i]>18) goto fuck;
        tlen=len;if(!sum[tlen]) tlen--;
        gao1(tlen);gao2(tlen);
        fuck : ;
    }
    cout<<ans<<endl;
    return 0;
}