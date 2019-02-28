#include<bits/stdc++.h>
using namespace std;

const int N=100010;
int n,L[N],R[N];

struct Line
{
    double k,b;
    Line(double _k=0,double _b=0):k(_k),b(_b){}
    double operator () (const double &x){return k*x+b;}
};

struct SegmentTree
{
    Line line[N*50];
    int lc[N*50],rc[N*50],tot,rt;
    SegmentTree(){rt=tot=0;}
    void insert(int &o,int l,int r,Line t)
    {
        if(!o){line[o=++tot]=t;return;}
        int mid=(l+r)/2;
        if(t(mid)>line[o](mid)) swap(t,line[o]);
        if(l==r) return;
        if(t(l)>line[o](l)) insert(lc[o],l,mid,t);
        if(t(r)>line[o](r)) insert(rc[o],mid+1,r,t);
    }
    double qmax(int o,int l,int r,int x)
    {
        if(!o) return -1e18;
        double res=line[o](x);
        if(l==r) return res;
        int mid=(l+r)/2;
        if(x<=mid) res=max(res,qmax(lc[o],l,mid,x));
        else res=max(res,qmax(rc[o],mid+1,r,x));
        return res;
    }
    void insert(double k,double b){insert(rt,1,1e9,Line(k,b));}
    double operator () (const int &x){return qmax(rt,1,1e9,x);}
} T1,T2;

int main()
{
    scanf("%d",&n);
    for(int i=n;i>=1;i--)
        scanf("%d%d",L+i,R+i);
    double D=0;
    int ans=0,lst=0,W=0;
    for(int i=1;i<=n;i++)
    {
        W+=(R[i]-L[i]);
        D+=0.5*(L[i]+R[i])*(R[i]-L[i]);
        if(T1(W)<=D&&T2(W)<=-D) ans=max(ans,i-lst),lst=i;
        T1.insert(L[i],D-1.0*W*L[i]);
        T2.insert(-R[i],1.0*W*R[i]-D);
    }
    printf("%d\n",ans);
    return 0;
}