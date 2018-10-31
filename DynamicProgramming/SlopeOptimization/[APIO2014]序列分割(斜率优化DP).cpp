#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=100010;
struct Line
{
    LL k,b;
    Line(LL _k=0,LL _b=0):k(_k),b(_b){}
    LL get(LL x){return k*x+b;}
    double intersec(Line a){return k==a.k?-1e18:(double)(a.b-b)/(k-a.k);}
};
int n,K,a[N],k;
int trans[210][N];
LL f[2][N],sum[N];

struct deq
{
    int head,tail;
    Line datas[N];int idx[N];
    void clear(){head=1;tail=0;}
    int size(){return tail-head+1;}
    int hid(){return idx[head];}
    Line hf(){return datas[head];}
    Line hs(){return datas[head+1];}
    Line tf(){return datas[tail];}
    Line ts(){return datas[tail-1];}
    void pub(Line x,int y){datas[++tail]=x;idx[tail]=y;}
    void ppb(){tail--;}
    void ppf(){head++;}
} q;

int main()
{
    scanf("%d%d",&n,&K);
    for(int i=1;i<=n;i++) scanf("%d",a+i),sum[i]=sum[i-1]+a[i];
    for(int p=1;p<=K;p++,k^=1)
    {
        q.clear();
        for(int i=1;i<=n;i++)
        {
            while(q.size()>=2&&q.hf().intersec(q.hs())<=sum[i]) q.ppf();
            f[k][i]=q.hf().get(sum[i]);trans[p][i]=q.hid();
            Line tmp(sum[i],f[k^1][i]-sum[i]*sum[i]);
            while(q.size()>=2&&q.ts().intersec(q.tf())>=q.tf().intersec(tmp)) q.ppb();
            q.pub(tmp,i);
        }
    }
    printf("%lld\n",f[k^1][n]);
    for(int i=K,u=n;i>=1;i--)
        printf("%d ",u=trans[i][u]);
    return 0;
}