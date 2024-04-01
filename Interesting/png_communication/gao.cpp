#include<bits/stdc++.h>
using namespace std;

const int N=1300;
unsigned int r[N][N],g[N][N],b[N][N];
unsigned char buffer[10000000];
unsigned int len=0,n,m;

void read()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",r[i]+j);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",g[i]+j);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",b[i]+j);
}

void print(unsigned char x){buffer[len++]=x;}

void printi(unsigned int x)
{
    static unsigned char tmp[4];
    for(int i=0;i<4;i++) tmp[i]=x&255u,x>>=8u;
    for(int i=3;i>=0;i--) print(tmp[i]);
}

void alder32(unsigned char *v,int n)
{
    unsigned int a=1,b=0;
    for(int i=0;i<n;i++)
    {
        (a+=v[i])%=65521u;
        (b+=a)%=65521u;
    }
    printi(b*65536u+a);
}

void crc(unsigned char *a,int n)
{
    static bool key[33]={1,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,0,0,0,1,1,1,0,1,1,0,1,1,0,1,1,1};
    static bool bit[15000000];
    int len=0;
    for(int i=0;i<n;i++)
    {
        unsigned char x=a[i];
        for(int j=0;j<8;j++)
            bit[len++]=x&1,x>>=1;
    }
    for(int i=0;i<32;i++) bit[len++]=0;
    for(int i=0;i<32;i++) bit[i]^=1;
    for(int i=0;i<n*8;i++)
    {
        while(i<n*8&&!bit[i]) i++;
        if(i>=n*8) break;
        for(int j=0;j<=32;j++)
            bit[i+j]^=key[j];
    }
    static bool ans[32];
    for(int i=0;i<32;i++) ans[i]=bit[n*8+i]^1;
    reverse(ans,ans+32);
    unsigned char x;int pos=0;
    x=0;for(int i=0;i<8;i++) x=x<<1|ans[pos++];print(x);
    x=0;for(int i=0;i<8;i++) x=x<<1|ans[pos++];print(x);
    x=0;for(int i=0;i<8;i++) x=x<<1|ans[pos++];print(x);
    x=0;for(int i=0;i<8;i++) x=x<<1|ans[pos++];print(x);
}

void HEAD()
{
    print(0x89);print(0x50);print(0x4e);print(0x47);
    print(0x0d);print(0x0a);print(0x1a);print(0x0a);
}

void IHDR()
{
    print(0x00);print(0x00);print(0x00);print(0x0d);
    print(0x49);print(0x48);print(0x44);print(0x52);
    printi(m);printi(n);print(0x08);print(0x02);print(0x00);print(0x00);print(0x00);
    static unsigned char tmp[17];
    for(int i=0;i<17;i++) tmp[i]=buffer[12+i];
    crc(tmp,17);
}

void IDAT()
{
    printi(6*n+3*n*m+2+4);
    print(0x49);print(0x44);print(0x41);print(0x54);
    print(0x78);print(0x01);
    static unsigned char tmp[10000000];
    int len=0;
    for(int i=0;i<n;i++)
    {
        print((i<n-1)?0x00:0x01);
        static unsigned char t[2];
        int tmpm=m*3+1;
        t[0]=tmpm&255u;t[1]=tmpm>>8u;
        print(t[0]);print(t[1]);
        print(t[0]^255u);print(t[1]^255u);
        print(tmp[len++]=0x00);
        for(int j=0;j<m;j++)
        {
            print(tmp[len++]=r[i][j]);
            print(tmp[len++]=g[i][j]);
            print(tmp[len++]=b[i][j]);
        }
    }
    alder32(tmp,len);
    crc(buffer+37,6*n+3*n*m+2+4+4);
}

void IEND()
{
    print(0x00);print(0x00);print(0x00);print(0x00);
    print(0x49);print(0x45);print(0x4e);print(0x44);
    print(0xae);print(0x42);print(0x60);print(0x82);
}

int main(int argc,char* argv[])
{
    freopen(argv[1],"r",stdin);
    read();HEAD();IHDR();IDAT();IEND();
    freopen(argv[2],"wb",stdout);
    for(int i=0;i<len;i++) fputc(buffer[i],stdout);
    return 0;
}