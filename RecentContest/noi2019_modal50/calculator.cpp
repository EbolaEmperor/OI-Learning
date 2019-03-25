#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

int Pow(int a,int b,int p)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%p)
        if(b&1) ans=1ll*ans*a%p;
    return ans%p;
}

namespace Task2
{
    LL exgcd(LL a,LL b,LL &x,LL &y)
    {
        if(b==0){x=1;y=0;return a;}
        LL g=exgcd(b,a%b,x,y);
        LL t=x;x=y;y=t-(a/b)*y;
        return g;
    }
    int inv(int a,int p)
    {
        LL b,k;
        exgcd(a,p,b,k);
        return (b%p+p)%p;
    }
    int bsgs(int a,int b,int p)
    {
        unordered_map<int,int> lg;
        int m=ceil(sqrt(p)),base=1;
        for(int i=0;i<m;i++)
        {
            lg.insert(make_pair(base,i));
            base=1ll*base*a%p;
        }
        int d=1;
        for(int i=0;i<m;i++)
        {
            int x=1ll*b*inv(d,p)%p;
            if(lg.count(x)) return m*i+lg[x];
            d=1ll*d*base%p;
        }
        return -1;
    }
    int exbsgs(int a,int b,int p)
    {
        if(b==1||p==1) return 0;
        int g=__gcd(a,p);
        if(g==1) return bsgs(a,b,p);
        if(b%g) return -1;
        b/=g;p/=g;
        int res=exbsgs(a,1ll*b*inv(a/g,p)%p,p);
        if(res==-1) return -1;
        else return res+1;
    }
}

namespace Task3
{
    const int N=10000010;
    bool mark[N];
    int prm[N/10],tot=0;
    void prework(int n=10000000)
    {
        for(int i=2;i<=n;i++)
        {
            if(!mark[i]) prm[++tot]=i;
            for(int j=1;j<=tot&&i*prm[j]<=n;j++)
            {
                mark[i*prm[j]]=1;
                if(i%prm[j]==0) break;
            }
        }
    }
    int main(int n,int m,int p)
    {
        if(n<m) return 0;
        int ans=1;
        for(int i=1;i<=tot&&n>=prm[i];i++)
        {
            int a=n,b=m,c=n-m,cnt=0;
            while(a>=prm[i]) cnt+=a/prm[i],a/=prm[i];
            while(b>=prm[i]) cnt-=b/prm[i],b/=prm[i];
            while(c>=prm[i]) cnt-=c/prm[i],c/=prm[i];
            if(cnt>1) ans=1ll*ans*Pow(prm[i],cnt,p)%p;
            if(cnt==1) ans=1ll*ans*prm[i]%p;  //奇妙优化，特判1次方，快了300ms
        }
        return ans%p;
    }
}

int main()
{
    int T,y,z,p,ty;
    Task3::prework();
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d",&ty,&y,&z,&p);
        if(ty==1) printf("%d\n",Pow(y,z,p));
        if(ty==2)
        {
            int ans=Task2::exbsgs(y%p,z%p,p);
            if(ans==-1) puts("Math Error");
            else printf("%d\n",ans);
        }
        if(ty==3) printf("%d\n",Task3::main(z,y,p));
    }
    return 0;
}