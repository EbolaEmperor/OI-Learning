#include<bits/stdc++.h>
using namespace std;

typedef __float128 LLF;
typedef __int128 LLL;
typedef long long LL;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline LL read()
{
    LL x=0,fg=1;char c=Get();
    while(!isdigit(c)&&c!='-') c=Get();
    if(c=='-') fg=-1,c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x*fg;
}

const int N=1000010;
struct Point
{
    LL x,y;
    Point(LL _x=0,LL _y=0):x(_x),y(_y){}
    bool operator < (const Point &a) const{return x<a.x||x==a.x&&y<a.y;}
    Point operator - (const Point &a){return Point(x-a.x,y-a.y);}
    LLL operator * (const Point &a){return (LLL)x*a.y-(LLL)y*a.x;}
    friend ostream& operator << (ostream &out,const Point &a){out<<"("<<a.x<<","<<a.y<<")";return out;}
} p[N<<1],ans(0,1);
struct M1{int l,r,id;} m1[N];
struct M2{int x,id;} m2[N];
map<Point,int> hp;
vector<int> trp[N<<2],trq[N<<2];
int m,n,t,c,c1,c2,cnt[N],st[N],ed[N];

void gao(vector<int> &pt,vector<int> &qr)
{
    static int stk[N];
    int head=1,tail=0,pos=0;
    for(int pp : qr)
    {
        while(pos<pt.size()&&p[pt[pos]].x<=p[pp].x)
        {
            while(head<tail&&(p[stk[tail]]-p[stk[tail-1]])*(p[pt[pos]]-p[stk[tail-1]])<=0) tail--;
            stk[++tail]=pt[pos];
            pos++;
        }
        if(head<=tail)
        {
            while(head<tail&&(p[stk[head+1]]-p[stk[head]])*(p[pp]-p[stk[head]])>=0) head++;
            Point tmp=p[stk[head]]-p[pp];
            if(ans*tmp>=0) ans=tmp;
        }
    }
}

void modifyp(int o,int l,int r,int nl,int nr,int x)
{
    if(l>=nl&&r<=nr){trp[o].push_back(x);return;}
    int mid=(l+r)/2;
    if(nl<=mid) modifyp(o<<1,l,mid,nl,nr,x);
    if(nr>mid) modifyp(o<<1|1,mid+1,r,nl,nr,x);
}

void modifyq(int o,int l,int r,int k,int x)
{
    trq[o].push_back(x);
    if(l==r) return;
    int mid=(l+r)/2;
    if(k<=mid) modifyq(o<<1,l,mid,k,x);
    else modifyq(o<<1|1,mid+1,r,k,x);
}

void dfs(int o,int l,int r)
{
    gao(trp[o],trq[o]);
    if(l==r) return;
    int mid=(l+r)/2;
    dfs(o<<1,l,mid);
    dfs(o<<1|1,mid+1,r);
}

LLF sqr(LL x){return (LLF)x*x;}
LLF sqrt(LLF x)
{
    LLF s=x/(LLF)2;
    for(int i=0;i<10000;i++)
        s=(s+x/s)/(LLF)2;
    return s;
}
void print(LLF x,int c)
{
    bool fg=0;
    static int dig[200];
    if(x<(LLF)0) fg=1,x=-x;
    for(int i=0,j;i<=c+1;i++)
    {
        for(j=9;(LLF)j>x;j--);
        dig[i]=j;
        x=(x-(LLF)j)*(LLF)10;
    }
    if(dig[c+1]>=5) dig[c]++;
    for(int i=c;i>0;i--)
        if(dig[i]==10) dig[i]=0,dig[i-1]++;
    if(fg) putchar('-');
    printf("%d.",dig[0]);
    for(int i=1;i<=c;i++)
        printf("%d",dig[i]);
}

int main()
{
    read();m=read();c=read();
    for(int i=1;i<=m;i++)
    {
        static int opt;
        static LL x,y;
        opt=read();x=read();y=read();
        Point tmp(x,y);
        if(opt==1)
        {
            if(!hp.count(tmp))
                p[hp[tmp]=++n]=tmp;
            int id=hp[tmp];
            if(!cnt[id]) st[id]=++t;
            cnt[id]++;
        }
        if(opt==2)
        {
            int id=hp[tmp];
            if(!--cnt[id]) m1[++c1]={st[id],t++,id},st[id]=0;
        }
        if(opt==3)
        {
            if(!hp.count(tmp))
                p[hp[tmp]=++n]=tmp;
            m2[++c2]={t,hp[tmp]};
        }
    }
    for(int i=1;i<=n;i++)
        if(st[i]) m1[++c1]={st[i],t,i};
    sort(m1+1,m1+1+c1,[](M1 a,M1 b){return p[a.id]<p[b.id];});
    sort(m2+1,m2+1+c2,[](M2 a,M2 b){return p[a.id]<p[b.id];});
    for(int i=1;i<=c1;i++)
        modifyp(1,1,t,m1[i].l,m1[i].r,m1[i].id);
    for(int i=1;i<=c2;i++)
        modifyq(1,1,t,m2[i].x,m2[i].id);
    dfs(1,1,n);
    if(!ans.x&&!ans.y) printf("%.*lf\n",c,1.0);
    else print((LLF)-ans.y/sqrt(sqr(ans.x)+sqr(ans.y)),c);
    return 0;
}
