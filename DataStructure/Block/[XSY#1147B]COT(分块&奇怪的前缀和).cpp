#include<bits/stdc++.h>
using namespace std;

namespace IO
{
    const int S=(1<<16)+5;
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
inline int mymin(const int &x,const int &y){return x<y?x:y;}
inline int mymax(const int &x,const int &y){return x>y?x:y;}

typedef long long LL;
const int N=1010,M=2510;
int xx[M],yy[M],aa[M];
int num[N][N],cur[N][N];
int add[N][N],dev[N][N];
LL sumTri[N][N],sumRec[N][N];
int n,Q,cnt=0;

void gao()
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++)
        {
            add[i][j]+=add[i-1][j];
            dev[i][j]+=dev[i-1][j-1];
            cur[i][j]=cur[i][j-1]+add[i][j]-dev[i][j];
            num[i][j]+=cur[i][j];
            sumRec[i][j]=sumRec[i-1][j]+sumRec[i][j-1]-sumRec[i-1][j-1]+num[i][j];
            sumTri[i][j]=sumTri[i-1][j-1]+sumRec[i][j-1]-sumRec[i-1][j-1]+num[i][j];
        }
    memset(add,0,sizeof(add));
    memset(dev,0,sizeof(dev));
}

int main()
{
    n=read();Q=read();
    while(Q--)
    {
        int opt=read(),x=read(),y=read(),a=read();
        if(opt==1)
        {
            add[x][y]++;add[x+a][y]--;
            dev[x][y+1]++;dev[x+a][y+a+1]--;
            xx[++cnt]=x;yy[cnt]=y;aa[cnt]=a;
            if(cnt==2500) gao(),cnt=0;
        }
        else
        {
            LL ans=sumTri[x+a-1][y+a-1]-sumTri[x-1][y-1];
            ans-=sumRec[x+a-1][y-1]-sumRec[x-1][y-1];
            for(int i=1;i<=cnt;i++)
            {
                int X=mymin(xx[i]+aa[i]-1,x+a-1);
                int Z=mymax(xx[i]-yy[i],x-y);
                int Y=mymax(yy[i],y),len=X-Z-Y+1;
                if(len>0) ans+=1ll*len*(len+1)/2;
            }
            print(ans);
        }
    }
    flush();
    return 0;
}