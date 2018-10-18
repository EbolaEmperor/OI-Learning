#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    return H==T?-1:*H++;
}
template<typename I> inline void read(I &x)
{
    x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
}

typedef long long LL;
const int N=100010;
LL ha,w,a[N];
map<LL,LL> val;
vector<LL> ks;

inline LL mul(LL x,LL y)
{
    LL ans=0;
    for(;y;y>>=1,x=(x+x)%ha)
        if(y&1) ans=(ans+x)%ha;
    return ans;
}

struct Comp
{
    LL r,i;
    Comp(LL a=0,LL b=0):r(a),i(b){}
    Comp operator * (const Comp &a){return Comp((mul(r,a.r)+mul(mul(i,a.i),w))%ha,(mul(r,a.i)+mul(i,a.r))%ha);}
    friend Comp operator ^ (Comp a,LL b)
    {
        Comp ans(1,0);
        for(;b;b>>=1,a=a*a)
            if(b&1) ans=ans*a;
        return ans;
    }
};

LL Pow(LL a,LL b)
{
    LL ans=1;
    for(;b;b>>=1,a=mul(a,a))
        if(b&1) ans=mul(ans,a);
    return ans;
}

LL Sqrt(LL n)
{
    if(n==0) return 0;
    if(Pow(n,(ha-1)/2)==ha-1) return -1;
    LL a;
    do{
        a=rand()%ha;
        w=(mul(a,a)-n+ha)%ha;
    }while(Pow(w,(ha-1)/2)!=ha-1);
    Comp t=Comp(a,1)^((ha+1)/2);
    return t.r;
}

int main()
{
    int T,n;
    for(read(T);T;T--)
    {
        read(n);read(ha);
        for(int i=1;i<=n;i++) read(a[i]);
        if(ha==2){puts("0");continue;}
        LL root=Sqrt(ha-3),inv2=Pow(2ll,ha-2);
        if(root==-1){puts("0");continue;}
        ks.clear();
        ks.push_back(mul((-1+root+ha)%ha,inv2));
        ks.push_back(mul((-1-root+ha)%ha,inv2));
        if(ks[0]==ks[1]) ks.pop_back();
        val.clear();if(a[1]) val[a[1]]++;
        LL ans=0;
        for(int i=2;i<=n;i++)
        {
            if(!a[i]) continue;
            for(LL k : ks)
                ans+=val[mul(k,a[i])];
            val[a[i]]++;
        }
        printf("%lld\n",ans);
    }
    return 0;
}