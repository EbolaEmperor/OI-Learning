#include<bits/stdc++.h>
using namespace std;

int calc(int x)
{
    int res=0;
    while(x)
    {
        int c=x%10;
        if(c==4||c==7) res++;
        x/=10;
    }
    return res;
}

int inc(int);
int dec(int n)
{
    int c=n%10;
    if(calc(n)==0) return -1;
    if(c==4||c==7) return n+1;
    return dec(n/10)*10;
}
int nxt(int n)
{
    int c=n%10;
    if(c<3||c==5||c==8) return n+1;
    if(c==3||c==6) return n+2;
    if(c==4) return n+3;
    if(c==7) return min(nxt(n/10)*10+4,inc(n/10)*10);
    if(calc(n)==0) return nxt(n/10)*10;
    return min(nxt(n/10)*10,dec(n/10)*10+4);
}
int inc(int n)
{
    int c=n%10;
    if(c<4) return n/10*10+4;
    if(c>4&&c<7) return n/10*10+7;
    if(c==4||c==7) return inc(n/10)*10+4;
    return min(inc(n/10)*10,nxt(n/10)*10+4);
}

int gao(int n,int k)
{
    int m=nxt(n),p;
    while("STO lyy orz")
    {
        for(p=0;p<k&&calc(n+p)==calc(m+p);p++);
        if(p==k) return m;
        int x=calc(n+p);
        int y=calc(m+p);
        if(x>y) while(x>y) m=inc(m+p)-p,y++;
        else while(x<y) m=dec(m+p)-p,y--;
    }
}

int main()
{
    int T,n,k;
    for(scanf("%d",&T);T;T--)
    {
        scanf("%d%d",&n,&k);
        int delnum=0,pw=1;
        bool flag,fuck=k>10;
        while(k>=10)
        {
            delnum+=(n%10)*pw;pw*=10;
            flag=(n%10+k%10>=10)&&!(n%100+k%10==10&&k<100);
            n/=10;k=k/10+flag;
        }
        k+=fuck;
        int ans=gao(n,k)*pw+delnum;
        printf("%d\n",ans);
    }
    return 0;
}