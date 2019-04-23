#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int ha=998244353,inv2=499122177,N=505;

inline int add(const int &x,const int &y){return (x+y>=ha)?(x+y-ha):(x+y);}
inline int mns(const int &x,const int &y){return (x-y<0)?(x-y+ha):(x-y);}
int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}
int fac(int n)
{
    int ans=1;
    for(int i=1;i<=n;i++)
        ans=1ll*ans*i%ha;
    return ans;
}

namespace Task1
{
    struct Comp
    {
        int r,i;
        Comp(int _r=0,int _i=0):r(_r),i(_i){}
        bool operator == (const Comp &a){return r==a.r&&i==a.i;}
        Comp operator + (const int &a){return Comp(add(r,a),i);}
        Comp operator + (const Comp &a){return Comp(add(r,a.r),add(i,a.i));}
        Comp operator - (const int &a){return Comp(mns(r,a),i);}
        Comp operator - (const Comp &a){return Comp(mns(r,a.r),mns(i,a.i));}
        Comp operator * (const int &a){return Comp(1ll*r*a%ha,1ll*i*a%ha);}
        Comp operator * (const Comp &a){return Comp((1ll*r*a.r+5ll*i*a.i)%ha,(1ll*r*a.i+1ll*i*a.r)%ha);}
        friend Comp operator ^ (Comp a,LL b)
        {
            bool fg=0;
            if(b<0) b=-b,fg=1;
            Comp ans(1,0);
            for(;b;b>>=1,a=a*a)
                if(b&1) ans=ans*a;
            if(fg)
            {
                int tmp=mns(1ll*ans.r*ans.r%ha,5ll*ans.i*ans.i%ha);
                ans.i=ha-ans.i;
                ans=ans*Pow(tmp,ha-2);
            }
            return ans;
        }
        friend ostream& operator << (ostream& out,Comp &a){out<<"("<<a.r<<","<<a.i<<")";return out;}
    };
    LL l,r;
    int strl[N][N],C[N][N],k;
    void init(int n=501)
    {
        strl[0][0]=1;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                strl[i][j]=(strl[i-1][j-1]+1ll*(i-1)*strl[i-1][j])%ha;
        for(int i=0;i<=n;i++)
            for(int j=C[i][0]=1;j<=i;j++)
                C[i][j]=add(C[i-1][j-1],C[i-1][j]);
    }
    int fib(LL n,int k)
    {
        n++;
        Comp ans;
        Comp a=Comp(1,1)*inv2;
        Comp b=Comp(1,ha-1)*inv2;
        for(int i=0;i<=k;i++)
        {
            Comp t=(a^i)*(b^(k-i));
            Comp tmp=(t==Comp(1,0))?(t*(n%ha)):((t^(n+1))-t)*((t-1)^(-1));
            if((k-i)&1) ans=ans-tmp*C[k][i];
            else ans=ans+tmp*C[k][i];
        }
        ans=ans*(Comp(0,1)^(-k));
        assert(ans.i==0);
        return ans.r;
    }
    int main(int T)
    {
        init();
        while(T--)
        {
            cin>>l>>r>>k;
            int ans=0;
            for(int i=0;i<=k;i++)
            {
                int tmp=mns(fib(r,i),fib(l-1,i));
                tmp=1ll*tmp*strl[k][i]%ha;
                if((k-i)&1) tmp=ha-tmp;
                ans=add(ans,tmp);
            }
            ans=1ll*ans*Pow((r-l+1)%ha*fac(k)%ha,ha-2)%ha;
            cout<<ans<<endl;
        }
        return 0;
    }
}

namespace Task2
{
    struct Comp
    {
        int r,i;
        Comp(int _r=0,int _i=0):r(_r),i(_i){}
        bool operator == (const Comp &a){return r==a.r&&i==a.i;}
        Comp operator + (const int &a){return Comp(add(r,a),i);}
        Comp operator + (const Comp &a){return Comp(add(r,a.r),add(i,a.i));}
        Comp operator - (const int &a){return Comp(mns(r,a),i);}
        Comp operator - (const Comp &a){return Comp(mns(r,a.r),mns(i,a.i));}
        Comp operator * (const int &a){return Comp(1ll*r*a%ha,1ll*i*a%ha);}
        Comp operator * (const Comp &a){return Comp((1ll*r*a.r+3ll*i*a.i)%ha,(1ll*r*a.i+1ll*i*a.r)%ha);}
        friend Comp operator ^ (Comp a,LL b)
        {
            bool fg=0;
            if(b<0) b=-b,fg=1;
            Comp ans(1,0);
            for(;b;b>>=1,a=a*a)
                if(b&1) ans=ans*a;
            if(fg)
            {
                int tmp=mns(1ll*ans.r*ans.r%ha,3ll*ans.i*ans.i%ha);
                ans.i=ha-ans.i;
                ans=ans*Pow(tmp,ha-2);
            }
            return ans;
        }
        friend ostream& operator << (ostream& out,Comp &a){out<<"("<<a.r<<","<<a.i<<")";return out;}
    };
    LL l,r;
    int strl[N][N],C[N][N],k;
    void init(int n=501)
    {
        strl[0][0]=1;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                strl[i][j]=(strl[i-1][j-1]+1ll*(i-1)*strl[i-1][j])%ha;
        for(int i=0;i<=n;i++)
            for(int j=C[i][0]=1;j<=i;j++)
                C[i][j]=add(C[i-1][j-1],C[i-1][j]);
    }
    int g(LL n,int k)
    {
        n=(n/2)+1;
        Comp ans;
        Comp a(2,1),b(2,ha-1);
        Comp c=Comp(3,1)^(-1);
        Comp d=Comp(3,ha-1)^(-1);
        for(int i=0;i<=k;i++)
        {
            Comp t=(a^i)*(b^(k-i));
            Comp tmp=(t==Comp(1,0))?(t*(n%ha)):((t^(n+1))-t)*((t-1)^(-1));
            ans=ans+tmp*(c^i)*(d^(k-i))*C[k][i];
        }
        assert(ans.i==0);
        return ans.r;
    }
    int main(int T)
    {
        init();
        while(T--)
        {
            cin>>l>>r>>k;
            int ans=0;
            for(int i=0;i<=k;i++)
            {
                int tmp=mns(g(r,i),g(l-1,i));
                tmp=1ll*tmp*strl[k][i]%ha;
                if((k-i)&1) tmp=ha-tmp;
                ans=add(ans,tmp);
            }
            ans=1ll*ans*Pow((r-l+1)%ha*fac(k)%ha,ha-2)%ha;
            cout<<ans<<endl;
        }
        return 0;
    }
}

int main()
{
    int T,qwq;
    cin>>T>>qwq;
    if(qwq==2) return Task1::main(T);
    else return Task2::main(T);
}
