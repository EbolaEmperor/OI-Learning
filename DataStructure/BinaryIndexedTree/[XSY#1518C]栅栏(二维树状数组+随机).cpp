#include<bits/stdc++.h>
#define FR first
#define SE second
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
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

const int N=2010;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<pii,pii> ppp;
map<ppp,int> keys[3];
int n,m,q;

struct BIT_2D
{
    LL b[N][N];
    BIT_2D(){memset(b,0,sizeof(b));}
    inline int lowbit(const int &x){return x&-x;}
    void add(int x,int y,int k)
    {
        for(int i=x;i<=n;i+=lowbit(i))
            for(int j=y;j<=m;j+=lowbit(j))
                b[i][j]+=k;
    }
    void add(int x1,int y1,int x2,int y2,int k)
    {
        add(x1,y1,k);
        add(x1,y2+1,-k);
        add(x2+1,y1,-k);
        add(x2+1,y2+1,k);
    }
    LL query(int x,int y)
    {
        LL res=0;
        for(int i=x;i;i-=lowbit(i))
            for(int j=y;j;j-=lowbit(j))
                res+=b[i][j];
        return res;
    }
} bit[3];

void add(int x1,int y1,int x2,int y2)
{
    for(int i=0;i<3;i++)
    {
        int key=rand()+1;
        keys[i][ppp(pii(x1,y1),pii(x2,y2))]=key;
        bit[i].add(x1,y1,x2,y2,key);
    }
}

void del(int x1,int y1,int x2,int y2)
{
    for(int i=0;i<3;i++)
    {
        int key=keys[i][ppp(pii(x1,y1),pii(x2,y2))];
        bit[i].add(x1,y1,x2,y2,-key);
    }
}

bool query(int x1,int y1,int x2,int y2)
{
    for(int i=0;i<3;i++)
    {
        int t1=bit[i].query(x1,y1);
        int t2=bit[i].query(x2,y2);
        if(t1!=t2) return 0;
    }
    return 1;
}

int main()
{
    int opt,x1,x2,y1,y2;
    n=read();m=read();q=read();
    while(q--)
    {
        opt=read();
        x1=read();y1=read();
        x2=read();y2=read();
        if(opt==1) add(x1,y1,x2,y2);
        if(opt==2) del(x1,y1,x2,y2);
        if(opt==3) puts(query(x1,y1,x2,y2)?"Yes":"No");
    }
    return 0;
}