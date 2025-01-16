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
    inline void reads(char *s)
    {
        char c=Get();int tot=0;
        while(c!='#'&&c!='.') c=Get();
        while(c=='#'||c=='.') s[++tot]=c,c=Get();
        s[++tot]='\0';
    }
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    inline void prints(const char *s)
    {
        int len=strlen(s);
        for(int i=0;i<len;i++) putc(s[i]);
        putc('\n');
    }
}

using namespace IO;
const int N=510;
char A[N][N],B[N][N],C[N][N];
int n,m;

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            B[i][j]=C[i][j]='.';
    for(int i=1;i<=n;i++)
    {
        reads(A[i]);
        for(int j=1;j<=m;j++)
            if(A[i][j]=='#') B[i][j]=C[i][j]='#';
    }
    for(int i=2;i<n;i++)
        for(int j=1;j<=m;j+=2)
            B[i][j]='#';
    for(int i=2;i<n;i++)
        for(int j=2;j<=m;j+=2)
            C[i][j]='#';
    for(int i=1;i<=m;i++)
        B[1][i]=C[n][i]='#';
    for(int i=1;i<=n;i++)
        B[i][m+1]='\0',prints(B[i]+1);
    putc('\n');
    for(int i=1;i<=n;i++)
        C[i][m+1]='\0',prints(C[i]+1);
    flush();
    return 0;
}