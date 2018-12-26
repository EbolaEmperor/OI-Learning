#include<bits/stdc++.h>
using namespace std;

const int S=1<<20;
char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
inline void print(int x)
{
    if(!x) putc('0');
    while(x) qu[++qr]=x%10+'0',x/=10;
    while(qr) putc(qu[qr--]);
}

const int N=1010,L=110;
bitset<N*L> can,tmp;
int n,h[N],v[L];

void falun_dafa_is_good()
{
    can[0]=1;
    sort(h+1,h+1+n);
    reverse(h+1,h+1+n);
    for(int i=3;i<=n;i++)
    {
        memset(v,0,sizeof(v));
        for(int j=2;j<i;j++) v[h[j]-h[i]]=1;
        tmp.reset();
        for(int j=0;j<=100;j++)
            if(v[j]) tmp|=can<<j;
        can|=tmp;
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",h+i);
    falun_dafa_is_good();
    for(int i=0;i<=100*n;i++)
        if(can[i]) print(i),putc(' ');
    flush();
    return 0;
}