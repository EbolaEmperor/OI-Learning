#include<bits/stdc++.h>
using namespace std;
 
const int S=1<<20;
char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
template <class I>inline void print(I x)
{
    if(!x) putc('0');
    while(x) qu[++qr]=x%10+'0',x/=10;
    while(qr) putc(qu[qr--]);
}
 
const int N=1010;
int a[6][6][6][6][6][6];
int sx,sy,tx,ty,vis[6][6];
int ans[N][N],n,m,cnt=0;
bool done[210][210];
 
bool check(int x,int y)
{
    if(x<1||x>5) return 0;
    if(y<1||y>5) return 0;
    if(vis[x][y]) return 0;
    return 1;
}
 
bool predfs(int x,int y,int d)
{
    if(d==25)
    {
        if(x!=tx||y!=ty) return 0;
        memcpy(a[sx][sy][tx][ty],vis,sizeof(vis));
        return 1;
    }
    vis[x][y]=d;
    if(check(x,y-3)&&predfs(x,y-3,d+1)) return 1;
    if(check(x,y+3)&&predfs(x,y+3,d+1)) return 1;
    if(check(x-3,y)&&predfs(x-3,y,d+1)) return 1;
    if(check(x+3,y)&&predfs(x+3,y,d+1)) return 1;
    if(check(x-2,y-2)&&predfs(x-2,y-2,d+1)) return 1;
    if(check(x-2,y+2)&&predfs(x-2,y+2,d+1)) return 1;
    if(check(x+2,y-2)&&predfs(x+2,y-2,d+1)) return 1;
    if(check(x+2,y+2)&&predfs(x+2,y+2,d+1)) return 1;
    vis[x][y]=0;
    return 0;
}
 
void gao(int kx,int ky,int sx,int sy,int tx,int ty)
{
    done[kx][ky]=1;
    int stx=(kx-1)*5,sty=(ky-1)*5;
    int typ=0,pos[26]={0};
    if(kx<m&&!done[kx+1][ky]) typ=1;
    else if(kx>1&&!done[kx-1][ky]) typ=2;
    else if(ky<m) typ=3;
    for(int i=1;i<=5;i++)
        for(int j=1;j<=5;j++)
            pos[a[sx][sy][tx][ty][i][j]]=i<<3|j;
    for(int i=1;i<=25;i++)
    {
        int x=pos[i]>>3,y=pos[i]&7;
        ans[stx+x][sty+y]=++cnt;
        if(!typ) continue;
        int nxtx=pos[i+1]>>3,nxty=pos[i+1]&7;
        if(typ==1&&x>=3&&nxtx>=3) gao(kx+1,ky,x-2,y,nxtx-2,nxty),typ=0;
        if(typ==2&&x<=3&&nxtx<=3) gao(kx-1,ky,x+2,y,nxtx+2,nxty),typ=0;
        if(typ==3&&y>=3&&nxty>=3) gao(kx,ky+1,x,y-2,nxtx,nxty-2),typ=0;
    }
}
 
int main()
{
    for(sx=1;sx<=5;sx++)
        for(sy=1;sy<=5;sy++)
            for(tx=1;tx<=5;tx++)
                for(ty=1;ty<=5;ty++)
                {
                    memset(vis,0,sizeof(vis));
                    predfs(sx,sy,1);
                    a[sx][sy][tx][ty][tx][ty]=25;
                }
    scanf("%d",&n);m=n/5;
    memset(vis,0,sizeof(vis));
    gao(1,1,1,1,3,3);
    for(int i=1;i<=n;i++,putc('\n'))
        for(int j=1;j<=n;j++)
            print(ans[i][j]),putc(' ');
    flush();
    return 0;
}
