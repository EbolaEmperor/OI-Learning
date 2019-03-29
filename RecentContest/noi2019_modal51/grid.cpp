#include<bits/stdc++.h>
using namespace std;

const int N=210;
struct Point{int x,y;} pt[N];
int g[N][N],h[N][N];
int T,n,m,tot,lim,p;
int s1[N][N],s2[N][N];

namespace Combo
{
    const int N=400010;
    int fac[N],ifac[N],fat[20],fatp[N][20],cnt;
    
    int Pow(int a,int b)
    {
        int ans=1;
        for(;b;b>>=1,a=1ll*a*a%p)
            if(b&1) ans=1ll*ans*a%p;
        return ans;
    }

    int exgcd(int a,int b,int &x,int &y)
    {
        if(!b){x=1;y=0;return a;}
        int g=exgcd(b,a%b,x,y);
        int t=x;x=y;y=t-(a/b)*y;
        return g;
    }

    int inv(int a)
    {
        int x,y;
        exgcd(a,p,x,y);
        return (x%p+p)%p;
    }

    void prework(int n)
    {
        int x=p;cnt=0;
        for(int i=2;i*i<=x;i++)
        {
            if(x%i) continue;
            fat[++cnt]=i;
            while(x%i==0) x/=i;
        }
        if(x>1) fat[++cnt]=x;
        fac[0]=ifac[0]=1;
        for(int i=1;i<=n;i++)
        {
            int x=i;
            memcpy(fatp[i],fatp[i-1],sizeof(fatp[i]));
            for(int j=1;j<=cnt;j++)
                while(x%fat[j]==0) x/=fat[j],fatp[i][j]++;
            fac[i]=1ll*fac[i-1]*x%p;
            ifac[i]=inv(fac[i]);
        }
    }

    int C(int n,int m)
    {
        if(n<0||m<0||n<m) return 0;
        int res=1ll*fac[n]*ifac[m]%p*ifac[n-m]%p;
        for(int i=1;i<=cnt;i++)
            res=1ll*res*Pow(fat[i],fatp[n][i]-fatp[m][i]-fatp[n-m][i])%p;
        return res;
    }
}

inline int add(const int &x,const int &y){return (x+y>=p)?(x+y-p):(x+y);}
inline int mns(const int &x,const int &y){return (x-y<0)?(x-y+p):(x-y);}

void dp(int x1,int y1,int x2,int y2,int f[N][N])
{
    pt[1].x=x1;pt[1].y=y1;
    pt[tot].x=x2;pt[tot].y=y2;
    memset(h,0,sizeof(h));
    memset(g,0,sizeof(g));
    memset(f,0,sizeof(g));
    for(int i=1;i<=tot;i++)
        for(int j=1;j<=tot;j++)
            h[i][j]=Combo::C(pt[j].x-pt[i].x+pt[j].y-pt[i].y,pt[j].x-pt[i].x);
    for(int i=1;i<=tot;i++)
        for(int j=i;j<=tot;j++)
        {
            g[i][j]=h[i][j];
            for(int k=i+1;k<j;k++)
                g[i][j]=mns(g[i][j],1ll*g[i][k]*h[k][j]%p);
        }
    f[1][1]=1;
    for(int i=2;i<=tot;i++)
        for(int j=1;j<=i;j++)
            for(int k=j-1;k<i;k++)
                f[i][j]=add(f[i][j],1ll*f[k][j-1]*g[k][i]%p);
}

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d%d",&n,&m,&tot,&lim,&p);
        Combo::prework((n+m)<<1);
        for(int i=1;i<=tot;i++)
            scanf("%d%d",&pt[i+1].x,&pt[i+1].y);
        sort(pt+2,pt+2+tot,[](Point a,Point b){return a.x<b.x||a.x==b.x&&a.y<b.y;});
        int ans=0;tot+=2;
        dp(1,2,n-1,m,s1);
        dp(2,1,n,m-1,s2);
        for(int i=2;i<=lim+2;i++)
            for(int j=2;i+j<=lim+4;j++)
                ans=add(ans,1ll*s1[tot][i]*s2[tot][j]%p);
        dp(1,2,n,m-1,s1);
        dp(2,1,n-1,m,s2);
        for(int i=2;i<=lim+2;i++)
            for(int j=2;i+j<=lim+4;j++)
                ans=mns(ans,1ll*s1[tot][i]*s2[tot][j]%p);
        printf("%d\n",ans);
    }
    return 0;
}
