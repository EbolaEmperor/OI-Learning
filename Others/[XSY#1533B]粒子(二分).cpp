#include<bits/stdc++.h>
using namespace std;

const int N=50010;
struct INFO{int v,t,id;} px[N],py[N];
bool donex[N],doney[N];
int n,L,k;

void getans(double t)
{
    int ansx=0,ansy=0;
    double maxx=0,maxy=0;
    for(int i=1;i<=n;i++)
    {
        if(!donex[i]&&px[i].t<=t)
            if(px[i].v*(t-px[i].t)>maxx)
                maxx=px[i].v*(t-px[i].t),ansx=i;
        if(!doney[i]&&py[i].t<=t)
            if(py[i].v*(t-py[i].t)>maxy)
                maxy=py[i].v*(t-py[i].t),ansy=i;
    }
    donex[ansx]=doney[ansy]=1;
    printf("%d %d\n",px[ansx].id,py[ansy].id);
}

bool check(double t)
{
    double maxx=0,maxy=0;
    for(int i=1;i<=n;i++)
    {
        if(!donex[i]&&px[i].t<=t) maxx=max(maxx,px[i].v*(t-px[i].t));
        if(!doney[i]&&py[i].t<=t) maxy=max(maxy,py[i].v*(t-py[i].t));
        if(maxx+maxy>=L) return 1;
    }
    return 0;
}

double gao()
{
    double l=0,r=0,mid;
    for(int i=1;i<=n;i++)
    {
        if(!donex[i]) r=max(r,px[i].t+1.0*L/px[i].v);
        if(!doney[i]) r=max(r,py[i].t+1.0*L/py[i].v);
    }
    for(int tms=0;tms<30;tms++)
    {
        mid=(l+r)/2;
        if(check(mid)) r=mid;
        else l=mid;
    }
    return r;
}

int main()
{
    scanf("%d%d%d",&n,&L,&k);
    for(int i=1;i<=n;i++) scanf("%d%d",&px[i].t,&px[i].v),px[i].id=i;
    for(int i=1;i<=n;i++) scanf("%d%d",&py[i].t,&py[i].v),py[i].id=i;
    sort(px+1,px+1+n,[](INFO a,INFO b){return a.t+1.0*L/a.v<b.t+1.0*L/b.v;});
    sort(py+1,py+1+n,[](INFO a,INFO b){return a.t+1.0*L/a.v<b.t+1.0*L/b.v;});
    for(int i=1;i<=k;i++) getans(gao());
    return 0;
}