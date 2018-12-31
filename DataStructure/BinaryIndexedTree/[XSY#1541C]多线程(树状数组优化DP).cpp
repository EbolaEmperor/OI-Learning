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

const int N=500010;
int ToT,n,m,a[N],h[N];

struct BIT
{
    int b[N];vector<int> used;
    inline int lowbit(const int &x){return x&-x;}
    void reset(){memset(b,0,sizeof(b));used.clear();}
    void add(int k,int x){for(k++;k<=m+1;k+=lowbit(k)) b[k]+=x,used.push_back(k);}
    int presum(int x){int res=0;for(x++;x;x-=lowbit(x)) res+=b[x];return res;}
    int sufsum(int x){return presum(m)-presum(x-1);}
    void clear(){for(int x : used) b[x]=0;used.clear();}
} f,g;

void gao(int x,int y)
{
    int s1=f.sufsum(x);
    int s2=g.presum(x);
    (x>y)?g.clear():f.clear();
    g.add(y,s1);f.add(y,s2);
}

int main()
{
    for(ToT=read();ToT;ToT--)
    {
        n=read();f.reset();g.reset();
        if(n==0){puts("1");continue;}
        for(int i=1;i<=n;i++) h[i]=a[i]=read();
        sort(h+1,h+1+n);
        m=unique(h+1,h+1+n)-h;
        f.add(m,1);g.add(0,1);
        for(int i=1;i<=n;i++) a[i]=lower_bound(h+1,h+m,a[i])-h;
        for(int i=2;i<=n;i++) gao(a[i],a[i-1]);
        printf("%d\n",f.presum(m)+g.presum(m));
    }
    return 0;
}