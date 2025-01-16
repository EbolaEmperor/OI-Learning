#include<bits/stdc++.h>
using namespace std;

int n,K,a[25],sum[25];
double f[25][10],ave=0.0,ans=1e18;

double sqr(const double &x){return x*x;}
int calc()
{
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
    for(int i=0;i<=n;i++)
        for(int k=0;k<=K;k++)
            f[i][k]=1e18;
    f[0][0]=0.0;
    for(int i=1;i<=n;i++)
        for(int k=1;k<=K;k++)
            for(int j=0;j<i;j++)
                f[i][k]=min(f[i][k],f[j][k-1]+sqr(sum[i]-sum[j]-ave));
    ans=min(ans,f[n][K]);
    return f[n][K];
}

double RAND(){return (double)rand()/RAND_MAX;}
bool accept(double dta,double tem){return dta<0||RAND()<exp(-dta/tem);}
void anneal(double tem,double delta,double end)
{
    double res=calc();
    while(tem>end)
    {
        int x=rand()%n+1,y=rand()%n+1;
        while(x==y) x=rand()%n+1,y=rand()%n+1;
        swap(a[x],a[y]);
        double nxt=calc();
        if(accept(nxt-res,tem)) res=nxt;
        else swap(a[x],a[y]);
        tem*=delta;
    }
}

int main()
{
    srand(time(0));
    scanf("%d%d",&n,&K);
    for(int i=1;i<=n;i++) scanf("%d",a+i),ave+=a[i];
    ave/=K;anneal(1e9,0.997,1e-14);
    printf("%.2lf\n",sqrt(ans/K));
    return 0;
}