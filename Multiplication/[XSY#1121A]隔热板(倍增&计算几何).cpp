#include<bits/stdc++.h>
using namespace std;

const int N=80010;
const double pi=acos(-1);
struct Point{int x,y;} pt[N];
struct Seg
{
    double l,r;
    bool operator == (const Seg &b){return l==b.l&&r==b.r;}
    bool operator < (const Seg &b) const{return r<b.r||r==b.r&&l<b.l;}
} sg[N];
int n,m,cnt,jump[17][N];

double sqr(const double &x){return x*x;}
double dist(const Point &a){return sqrt(sqr(a.x)+sqr(a.y));}

bool check(double x)
{
    cnt=0;
    for(int i=1;i<=n;i++)
    {
        double alpha=acos(x/dist(pt[i]));
        double beta=acos(pt[i].x/dist(pt[i]));
        if(pt[i].y<0) beta=2*pi-beta;
        if(alpha+beta>2*pi) beta-=2*pi;
        sg[i]={beta-alpha,beta+alpha};
    }
    sort(sg+1,sg+1+n);
    for(int i=1;i<n;i++)
        if(sg[i+1].l<=sg[i].l) sg[i+1]=sg[i];
    int tot=unique(sg+1,sg+1+n)-(sg+1);cnt=2*tot;
    for(int i=tot+1;i<=cnt;i++)
        sg[i]={sg[i-tot].l+2*pi,sg[i-tot].r+2*pi};
    int pr=1;
    for(int i=1;i<=cnt;i++)
    {
        while(pr<=cnt&&sg[pr].l<=sg[i].r) pr++;
        jump[0][i]=pr;
    }
    jump[0][cnt+1]=cnt+1;
    for(int j=1;j<=16;j++)
        for(int i=1;i<=cnt+1;i++)
            jump[j][i]=jump[j-1][jump[j-1][i]];
    int ans=tot;
    for(int i=1;i<=tot;i++)
    {
        int x=i,res=0;
        for(int j=16;j>=0;j--)
            if(jump[j][x]-i<tot)
                x=jump[j][x],res|=1<<j;
        ans=min(ans,res+1);
    }
    return ans<=m;
}

int main()
{
    scanf("%d%d",&n,&m);
    double l=0,r=1e9;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&pt[i].x,&pt[i].y);
        r=min(r,dist(pt[i]));
    }
    while(r-l>1e-4)
    {
        double mid=(l+r)/2;
        if(check(mid)) l=mid;
        else r=mid;
    }
    printf("%.2lf\n",l);
    return 0;
}