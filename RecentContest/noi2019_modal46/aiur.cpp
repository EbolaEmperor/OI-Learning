#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0,fg=1;char c=Get();
    while(!isdigit(c)&&c!='-') c=Get();
    if(c=='-') fg=-1,c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x*fg;
}

const int ha=1e9+7;
const int N=500010;
struct Point
{
    int x,y;
    Point(int _x=0,int _y=0):x(_x),y(_y){}
    bool operator < (const Point &a) const{return y<a.y||y==a.y&&x<a.x;}
} p[N];
int n,m,ty,hx[N];
int sum[N],pos[N];
int fac[N],ifac[N];
int mx[N*3],val[N*3],leaf=1;
int ans1,ans2,ans3;

inline int mymin(const int &x,const int &y){return x<y?x:y;}
inline int mymax(const int &x,const int &y){return x>y?x:y;}
inline void add(int &x,const int &y){x=(x+y>=ha)?(x+y-ha):(x+y);}

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void init(int n)
{
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=1ll*fac[i-1]*i%ha;
    ifac[n]=Pow(fac[n],ha-2);
    for(int i=n-1;i>=0;i--)
        ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
}

inline int C(const int &n){return (n>=ans1)?(1ll*fac[n]*ifac[ans1]%ha*ifac[n-ans1]%ha):0;}

void updatec(int k,int x)
{
    val[leaf+k]=x;
    for(int i=(leaf+k)>>1;i;i>>=1)
        val[i]=val[i<<1],add(val[i],val[i<<1|1]);
}

void update(int k,int x)
{
    mx[leaf+k]=x;val[leaf+k]=(x>=ans1);
    for(int i=(leaf+k)>>1;i;i>>=1)
    {
        mx[i]=mymax(mx[i<<1],mx[i<<1|1]);
        val[i]=val[i<<1];
        add(val[i],val[i<<1|1]);
    }
}

int qmax(int nl,int nr)
{
    int res=0;
    if(nl>nr) return res;
    for(int l=leaf+nl-1,r=leaf+nr+1;l^r^1;l>>=1,r>>=1)
    {
        if(~l&1) res=mymax(res,mx[l^1]);
        if(r&1) res=mymax(res,mx[r^1]);
    }
    return res;
}

int qcnt(int nl,int nr)
{
    int res=0;
    if(nl>nr) return res;
    for(int l=leaf+nl-1,r=leaf+nr+1;l^r^1;l>>=1,r>>=1)
    {
        if(~l&1) add(res,val[l^1]);
        if(r&1) add(res,val[r^1]);
    }
    return res;
}

int gao1()
{
    int res=0,cur=0,cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(p[i].y!=p[i-1].y)
            for(cur=cnt=1;p[i+cnt].y==p[i].y;cnt++);
        else
        {
            int tmp1=mymin(mymin(cur,cnt-cur),qmax(p[i-1].x+1,p[i].x-1));
            int tmp2=mymin(mymin(cur,cnt-cur-1),mymin(pos[p[i].x],sum[p[i].x]-pos[p[i].x]-1));
            res=mymax(res,mymax(tmp1,tmp2));cur++;
        }
        pos[p[i].x]++;
        update(p[i].x,mymin(pos[p[i].x],sum[p[i].x]-pos[p[i].x]));
    }
    return res;
}

int gao2()
{
    memset(mx,0,sizeof(mx));
    memset(val,0,sizeof(val));
    memset(pos,0,sizeof(pos));
    int res=0,cur=0,cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(p[i].y!=p[i-1].y)
            for(cur=cnt=1;p[i+cnt].y==p[i].y;cnt++);
        else
        {
            int tmp1=mymin(mymin(cur,cnt-cur),qmax(p[i-1].x+1,p[i].x-1));
            int tmp2=mymin(mymin(cur,cnt-cur-1),mymin(pos[p[i].x],sum[p[i].x]-pos[p[i].x]-1));
            if(tmp1==ans1) add(res,qcnt(p[i-1].x+1,p[i].x-1));
            if(tmp2==ans1) add(res,1);
            cur++;
        }
        pos[p[i].x]++;
        update(p[i].x,mymin(pos[p[i].x],sum[p[i].x]-pos[p[i].x]));
    }
    return res;
}

int gao3()
{
    memset(val,0,sizeof(val));
    memset(pos,0,sizeof(pos));
    int res=0,cur=0,cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(p[i].y!=p[i-1].y)
            for(cur=cnt=1;p[i+cnt].y==p[i].y;cnt++);
        else
        {
            int tmp1=1ll*C(cur)*C(cnt-cur)%ha*qcnt(p[i-1].x+1,p[i].x-1)%ha;
            int tmp2=1ll*C(cur)*C(cnt-cur-1)%ha*C(pos[p[i].x])%ha*C(sum[p[i].x]-pos[p[i].x]-1)%ha;
            add(res,tmp1);add(res,tmp2);cur++;
        }
        pos[p[i].x]++;
        updatec(p[i].x,1ll*C(pos[p[i].x])*C(sum[p[i].x]-pos[p[i].x])%ha);
    }
    return res;
}

int main()
{
    init(n=read());ty=read();
    for(int i=1;i<=n;i++)
        hx[i]=p[i].x=read(),p[i].y=read();
    sort(hx+1,hx+1+n);
    m=unique(hx+1,hx+1+n)-(hx+1);
    while(leaf<=(m+5)) leaf<<=1;
    for(int i=1;i<=n;i++)
        sum[p[i].x=lower_bound(hx+1,hx+1+m,p[i].x)-hx]++;
    sort(p+1,p+1+n);
    printf("%d ",ans1=gao1());
    if(ty>=2) printf("%d ",ans2=gao2());
    if(ty>=3) printf("%d ",ans3=gao3());
    return puts(""),0;
}