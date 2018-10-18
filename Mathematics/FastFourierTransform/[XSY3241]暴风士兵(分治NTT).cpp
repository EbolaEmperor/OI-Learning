#include<bits/stdc++.h>
#define ha 998244353
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
const int N=300010;
int A[N],B[N],r[N];
int pw[20],ipw[20];
int ans,n;

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void NTT(int *A,int n,bool IDFT)
{
    for(int i=0;i<n;i++) if(i<r[i]) swap(A[i],A[r[i]]);
    for(int i=1,l=1;i<n;i<<=1,l++)
    {
        int wn=IDFT?ipw[l]:pw[l];
        for(int j=0;j<n;j+=i<<1)
            for(int k=0,w=1;k<i;k++)
            {
                int x=A[j+k],y=1ll*w*A[i+j+k]%ha;
                A[j+k]=(x+y)%ha;
                A[i+j+k]=(x-y+ha)%ha;
                w=1ll*w*wn%ha;
            }
    }
    int inv=IDFT?Pow(n,ha-2):0;
    if(IDFT) for(int i=0;i<n;i++) A[i]=1ll*A[i]*inv%ha;
}

void mul(int *a,int *b,int *res,int n,int m,int k)
{
    int len=1,l=0;for(;len<=n+m;len<<=1,l++);
    for(int i=0;i<len;i++) r[i]=(r[i>>1]>>1)|((i&1)<<l-1);
    for(int i=0;i<len;i++) A[i]=B[i]=0;
    for(int i=0;i<=n;i++) A[i]=a[i];
    for(int i=0;i<=m;i++) B[i]=b[i];
    NTT(A,len,0);NTT(B,len,0);
    for(int i=0;i<len;i++) A[i]=1ll*A[i]*B[i]%ha;
    NTT(A,len,1);memcpy(res,A,sizeof(int)*(k+1));
}

void divide(int L,int R,int *c,int *p)
{
    if(L==R)
    {
        int x=(read()+ans)%ha;
        p[0]=(1-x+ha)%ha;p[1]=x;
        ans=(1ll*p[0]*c[0]+1ll*p[1]*c[1])%ha;
        print(ans);return;
    }
    int M=(L+R)/2;
    divide(L,M,c,p);
    int *cr=new int[R-L+2];
    reverse(p,p+M-L+2);
    mul(p,c,cr,M-L+1,R-L+1,R-L+1);
    for(int i=0;i<=R-M;i++) cr[i]=cr[i+M-L+1];
    reverse(p,p+M-L+2);
    divide(M+1,R,cr,p+M-L+2);
    mul(p,p+M-L+2,p,M-L+1,R-M,R-L+1);
}

int main()
{
    for(int i=1,l=1;i<N;i<<=1,l++)
    {
        pw[l]=Pow(3,(ha-1)/(i<<1));
        ipw[l]=Pow(pw[l],ha-2);
    }
    ans=read();n=read();
    int *c=new int[N],*p=new int[N];
    for(int i=0;i<=ans;i++) c[i]=ans-i;
    divide(1,n,c,p);flush();
    return 0;
}