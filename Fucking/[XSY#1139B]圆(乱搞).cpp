#include<bits/stdc++.h>
using namespace std;

const int N=1010;
bool mp[N][N];
int sum[N][N],n,m,K;
int x[N*N],y[N*N],cnt=0;
int d[N],now;
int sq[N*N];

int gao2(int x,int y1,int y2)
{
    int ans=y2-y1+1;
    if(x<1||x>n) return ans;
    y2=min(y2,m);
    ans-=sum[x][y2];
    if(y1>=1) ans+=sum[x][y1-1];
    return ans;
}

bool gao1(int x,int y,int r)
{
    int ans=gao2(x,y-r,y+r);
    for(int i=1;ans<=K&&i<=r;i++)
    {
        ans+=gao2(x-i,y-d[i],y+d[i]);
        ans+=gao2(x+i,y-d[i],y+d[i]);
    }
    return ans<=K;
}

bool fuck(int r2)
{
    int r=sq[r2];d[0]=r;
    for(int i=1;i<=r;i++)
    {
        d[i]=d[i-1];
        while(d[i]*d[i]+i*i>r2) d[i]--;
    }
    for(;now<=cnt;now++)
        if(gao1(x[now],y[now],r)) return 0;
    return 1;
}

void gaoZero()
{
    int ans=1;
    while(true)
    {
        int r=sq[ans];d[0]=r;
        for(int i=1;i<=r;i++)
        {
            d[i]=d[i-1];
            while(d[i]*d[i]+i*i>ans) d[i]--;
        }
        int res=2*r+1;
        for(int i=1;i<=r;i++)
            res+=2*(2*d[i]+1);
        if(res<=K) ans++;
        else break;
    }
    printf("%d\n",ans-1);
}

void gaoOne()
{
    int x=n/2,y=m/2,ans=1;
    while(true)
    {
        int r=sq[ans];d[0]=r;
        for(int i=1;i<=r;i++)
        {
            d[i]=d[i-1];
            while(d[i]*d[i]+i*i>ans) d[i]--;
        }
        if(gao1(x,y,r)) ans++;
        else break;
    }
    printf("%d\n",ans-1);
}

int main()
{
    for(int i=1;i<=1000;i++) sq[i*i]=i;
    for(int i=1;i<=1000000;i++) if(!sq[i]) sq[i]=sq[i-1];
    static char s[N];
    scanf("%d%d%d",&n,&m,&K);
    bool zero=1,one=1;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s+1);
        for(int j=1;j<=m;j++)
        {
            mp[i][j]=s[j]-'0';
            sum[i][j]=sum[i][j-1]+mp[i][j];
            x[++cnt]=i;y[cnt]=j;
            if(mp[i][j]) zero=0;
            if(!mp[i][j]) one=0;
        }
    }
    if(zero){gaoZero();return 0;}
    if(one){gaoOne();return 0;}
    int block=100;now=1;
    for(int i=1,cur=now;;i++,cur=now)
        if(fuck(i*block))
        {
            now=cur;
            for(int j=(i-1)*block;;j++)
                if(fuck(j)){printf("%d\n",j-1);return 0;}
        }
    return 0;
}