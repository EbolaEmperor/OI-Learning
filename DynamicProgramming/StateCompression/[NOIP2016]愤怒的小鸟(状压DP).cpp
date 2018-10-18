#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

double a,b;
double pigx[20],pigy[20];
int f[1000];
int ans[1<<20];

bool equal(double t1,double t2)
{
    double tmp=t1-t2;
    if(tmp<0) tmp=-tmp;
    return tmp<1e-6;
}

int main()
{
    int t;
    int n;
    int tot;
    int tmp;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        scanf("%d%*d",&n);
        for(int j=0;j<n;j++)
            scanf("%lf%lf",&pigx[j],&pigy[j]);
        tot=0;
        for(int j=0;j<n;j++)
            for(int k=j+1;k<n;k++)
            {
                if(equal(pigx[j],pigx[k])) continue;
                a=(pigy[j]*pigx[k]-pigy[k]*pigx[j])/(pigx[j]*pigx[j]*pigx[k]-pigx[k]*pigx[k]*pigx[j]);
                if(a>-1e-6) continue;
                b=(pigy[k]*pigx[j]*pigx[j]-pigy[j]*pigx[k]*pigx[k])/(pigx[j]*pigx[j]*pigx[k]-pigx[k]*pigx[k]*pigx[j]);
                f[tot]=0;
                for(int l=0;l<n;l++)
                    if(equal(a*pigx[l]*pigx[l]+b*pigx[l],pigy[l])) f[tot]|=1<<l;
                tot++;
            }
        for(int j=0;j<n;j++)
        {
            int mmm=(1<<j);
            f[tot]=mmm;
            tot++;
        }
        sort(f,f+tot);
        tot=unique(f,f+tot)-f;
        tmp=1<<n;
        for(int j=1;j<tmp;j++)
            ans[j]=1<<30;
        for(int j=0;j<tmp;j++)
            for(int k=0;k<tot;k++)
                if(ans[j]+1<ans[j|f[k]]) ans[j|f[k]]=ans[j]+1;
        cout<<ans[tmp-1]<<endl;
    }
    return 0;
}
