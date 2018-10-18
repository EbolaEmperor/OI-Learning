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
    inline void reads(char *s)
    {
        char c=Get();int tot=0;
        while(c<'0'||c>'1') c=Get();
        while(c>='0'&&c<='1') s[++tot]=c,c=Get();
        s[++tot]='\0';
    }
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    template <class I>inline void print(I x)
    {
        if(!x) putc('0');
        if(x<0) putc('-'),x=-x;
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
    }
}

using namespace IO;
const int N=2010;
int sump[N][N],sume1[N][N],sume2[N][N];
bool mp[N][N];

int main()
{
    static char s[N];
    int n=read(),m=read(),q=read();
    for(int i=1;i<=n;i++)
    {
        reads(s);
        for(int j=1;j<=m;j++)
            mp[i][j]=(s[j]=='1');
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            sump[i][j]=sump[i-1][j]+sump[i][j-1]-sump[i-1][j-1]+mp[i][j];
            sume1[i][j]=sume1[i-1][j]+sume1[i][j-1]-sume1[i-1][j-1]+(mp[i][j]&&mp[i][j+1]);
            sume2[i][j]=sume2[i-1][j]+sume2[i][j-1]-sume2[i-1][j-1]+(mp[i][j]&&mp[i+1][j]);
        }
    while(q--)
    {
        int x1=read(),y1=read(),x2=read(),y2=read();
        int n=sump[x2][y2]-sump[x1-1][y2]-sump[x2][y1-1]+sump[x1-1][y1-1];
        int m=sume1[x2][y2-1]-sume1[x2][y1-1]-sume1[x1-1][y2-1]+sume1[x1-1][y1-1];
        m+=sume2[x2-1][y2]-sume2[x2-1][y1-1]-sume2[x1-1][y2]+sume2[x1-1][y1-1];
        print(n-m);putc('\n');
    }
    flush();
    return 0;
}