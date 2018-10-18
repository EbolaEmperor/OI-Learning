#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=120010;
const int block=100000;
const long double pi=acos(-1);
int a[N],b[N],n;
int r[N*10];

struct Comp
{
    long double r,i;
    Comp(long double _r=0,long double _i=0):r(_r),i(_i){}
    Comp operator + (const Comp &a){return Comp(r+a.r,i+a.i);}
    Comp operator - (const Comp &a){return Comp(r-a.r,i-a.i);}
    Comp operator * (const Comp &a){return Comp(r*a.r-i*a.i,r*a.i+i*a.r);}
} A[N*10],B[N*10];

void FFT(Comp *A,int n,int v)
{
    for(int i=0;i<n;i++) if(i<r[i]) swap(A[i],A[r[i]]);
    for(int i=1;i<n;i<<=1)
    {
        Comp wn(cos(pi/i),v*sin(pi/i));
        for(int j=0;j<n;j+=(i<<1))
        {
            Comp w(1,0);
            for(int k=0;k<i;k++)
            {
                Comp x=A[j+k],y=w*A[i+j+k];
                A[j+k]=x+y;
                A[i+j+k]=x-y;
                w=w*wn;
            }
        }
    }
}

struct bigint
{
    vector<LL> num;
    void destroy(){vector<LL> g;g.swap(num);}
    void init(int n){for(int i=0;i<n;i++) num.push_back(0);}
    bigint& operator = (int x){while(x) num.push_back(x%block),x/=block;}

    void clean()
    {
        for(int i=num.size()-1;i>=0;i--)
            if(!num[i]) num.pop_back();
            else break;
    }

    void print()
    {
        clean();
        if(num.size()) printf("%lld",num[num.size()-1]);
        for(int i=num.size()-2;i>=0;i--)
        {
            if(num[i]>=10000) printf("%lld",num[i]);
            else if(num[i]>=1000) printf("0%lld",num[i]);
            else if(num[i]>=100) printf("00%lld",num[i]);
            else if(num[i]>=10) printf("000%lld",num[i]);
            else printf("0000%lld",num[i]);
        }
        if(num.size()==0) putchar('0');
        putchar('\n');
    }

    void carry()
    {
        for(int i=0;i<num.size();i++)
        {
            LL x=num[i]/block;num[i]%=block;
            if(x&&i==num.size()-1) num.push_back(x);
            else if(x) num[i+1]+=x;
        }
    }

    bigint operator + (bigint &a)
    {
        clean();a.clean();
        int n1=num.size(),n2=a.num.size();
        int n=max(n1,n2),m=min(n1,n2);
        bigint res;
        for(int i=0;i<m;i++)
            res.num.push_back(num[i]+a.num[i]);
        for(int i=m;i<n;i++)
            if(n1<n2) res.num.push_back(a.num[i]);
            else res.num.push_back(num[i]);
        res.carry();res.clean();
        return res;
    }

    bigint operator * (bigint &a)
    {
        clean();a.clean();
        int n=num.size()+a.num.size(),len,l;
        for(len=1,l=0;len<n;len<<=1,l++);
        for(int i=0;i<len;i++) r[i]=(r[i/2]/2)|((i&1)<<(l-1));
        for(int i=0;i<num.size();i++) A[i]=Comp(num[i],0);
        for(int i=num.size();i<len;i++) A[i]=Comp(0,0);
        for(int i=a.num.size();i<len;i++) a.num.push_back(0);
        for(int i=0;i<len;i++) B[i]=Comp(a.num[i],0);
        FFT(A,len,1);FFT(B,len,1);
        for(int i=0;i<len;i++) A[i]=A[i]*B[i];
        FFT(A,len,-1);
        for(int i=0;i<len;i++) a.num[i]=LL(round(A[i].r/len));
        a.carry();a.clean();
        return a;
    }
}d[N<<2],ans[N<<2];

void divide(int o,int L,int R)
{
    if(L==R)
    {
        d[o]=b[L];
        ans[o]=a[L];
        return;
    }
    int mid=(L+R)/2;
    divide(o<<1,L,mid);
    divide(o<<1|1,mid+1,R);
    d[o]=d[o<<1]*d[o<<1|1];
    ans[o]=d[o<<1]*ans[o<<1|1];
    ans[o]=ans[o]+ans[o<<1];
    d[o<<1].destroy();
    d[o<<1|1].destroy();
    ans[o<<1].destroy();
    ans[o<<1|1].destroy();
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",b+i);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    divide(1,1,n);
    ans[1].print();
    return 0;
}