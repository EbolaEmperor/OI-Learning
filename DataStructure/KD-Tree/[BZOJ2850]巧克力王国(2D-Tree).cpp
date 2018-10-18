#include<bits/stdc++.h>
using namespace std;

namespace IO
{
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
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    template <class I>inline void print(I x)
    {
        if(!x) putc('0');
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
        putc('\n');
    }
}
using namespace IO;
typedef long long LL;
inline void upmin(int &x,const int &y){if(y<x) x=y;}
inline void upmax(int &x,const int &y){if(y>x) x=y;}

const int N=50010;
int falun;
struct Point
{
    int d[2];LL v;
    Point(int x=0,int y=0,LL z=0){d[0]=x;d[1]=y;v=z;}
    bool operator < (const Point &a) const{return d[falun]<a.d[falun];}
} pt[N];

struct KD_Tree
{
    int d[2],mn[2],mx[2];
    LL v,sum;KD_Tree *lc,*rc;
    KD_Tree(int x=0,int y=0,LL z=0)
    {
        sum=v=z;
        d[0]=mn[0]=mx[0]=x;
        d[1]=mn[1]=mx[1]=y;
        lc=rc=NULL;
    }
    void maintain()
    {
        for(int i=0;i<2;i++)
        {
            if(!lc) goto uprc;
            upmin(mn[i],lc->mn[i]);
            upmax(mx[i],lc->mx[i]);
            uprc: if(!rc) continue;
            upmin(mn[i],rc->mn[i]);
            upmax(mx[i],rc->mx[i]);
        }
        if(lc) sum+=lc->sum;
        if(rc) sum+=rc->sum;
    }
    void build(int l,int r,int d)
    {
        int mid=(l+r)/2;falun=d;
        nth_element(pt+l,pt+mid,pt+r+1);
        *this=KD_Tree(pt[mid].d[0],pt[mid].d[1],pt[mid].v);
        if(l<mid) lc=new KD_Tree,lc->build(l,mid-1,d^1);
        if(r>mid) rc=new KD_Tree,rc->build(mid+1,r,d^1);
        maintain();
    }
    LL query(LL a,LL b,LL c)
    {
        int cnt=0;
        if(a*mn[0]+b*mn[1]<c) cnt++;
        if(a*mn[0]+b*mx[1]<c) cnt++;
        if(a*mx[0]+b*mn[1]<c) cnt++;
        if(a*mx[0]+b*mx[1]<c) cnt++;
        if(!cnt) return 0;
        if(cnt==4) return sum;
        LL res=0;
        if(a*d[0]+b*d[1]<c) res+=v;
        if(lc) res+=lc->query(a,b,c);
        if(rc) res+=rc->query(a,b,c);
        return res;
    }
} *root;

int main()
{
    root=new KD_Tree;
    int n=read(),m=read();
    for(int i=1;i<=n;i++)
    {
        pt[i].d[0]=read();
        pt[i].d[1]=read();
        pt[i].v=read();
    }
    root->build(1,n,0);
    while(m--)
    {
        LL a=read(),b=read(),c=read();
        print(root->query(a,b,c));
    }
    flush();
    return 0;
}