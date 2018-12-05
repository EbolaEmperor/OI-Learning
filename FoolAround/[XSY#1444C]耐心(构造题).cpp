#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char obuf[S],*oS=obuf,*oT=oS+S-1,qu[55];int qr;
inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
inline void print(int x)
{
    if(!x) putc('0');
    while(x) qu[++qr]=x%10+'0',x/=10;
    while(qr) putc(qu[qr--]);
}

const int N=410;
int ans[N][N],pos[N];
int T,r,c,d,cnt;

void solve(int xl,int xr,int yl,int yr)
{
    int lenx=xr-xl+1,leny=yr-yl+1;
    if(lenx<=0||leny<=0) return;
    if(lenx>=d)
    {
        for(int i=yl;i<=yr;i++)
        {
            cnt++;
            for(int j=xl;j<xl+d;j++)
                ans[j][i]=cnt;
        }
        solve(xl+d,xr,yl,yr);
    }
    else if(leny>=d)
    {
        for(int i=xl;i<=xr;i++)
        {
            cnt++;
            for(int j=yl;j<yl+d;j++)
                ans[i][j]=cnt;
        }
        solve(xl,xr,yl+d,yr);
    }
    else
    {
        if(lenx<leny)
        {
            for(int i=xl;i<=xr;i++)
            {
                cnt++;
                for(int j=yl;j<=yr;j++)
                    ans[i][j]=cnt;
            }
        }
        else
        {
            for(int j=yl;j<=yr;j++)
            {
                cnt++;
                for(int i=xl;i<=xr;i++)
                    ans[i][j]=cnt;
            }
        }
    }
}

void solve(int n,int m)
{
    int k=(n*(m-d)-1)/d+1;
    pos[1]=1;
    for(int i=2;i<=k;i++)
        pos[i]=(pos[i-1]+d-1)%n+1;
    sort(pos+1,pos+1+k);
    for(int i=1;i<=k;i++)
    {
        cnt++;
        for(int j=0;j<d;j++)
            ans[(pos[i]+j+n-1)%n+1][i]=cnt;
    }
    for(int i=1;i<=n;i++)
    {
        cnt++;
        for(int j=1;j<=m;j++)
            if(!ans[i][j]) ans[i][j]=cnt;
    }
}

void gao()
{
    cnt=0;solve(1,r,1,c);
    if(r>=d&&c>=d&&cnt>(r*c-1)/d+1)
    {
        int n=r%d+d,m=c%d+d;cnt=0;
        memset(ans,0,sizeof(ans));
        solve(n+1,r,1,c);
        solve(1,n,m+1,c);
        solve(n,m);
    }
}

int main()
{
    for(scanf("%d",&T);T;T--)
    {
        scanf("%d%d%d",&r,&c,&d);gao();
        for(int i=1;i<=r;i++,putc('\n'))
            for(int j=1;j<=c;j++)
                print(ans[i][j]),putc(' ');
    }
    flush();
    return 0;
}