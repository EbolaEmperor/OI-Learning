#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
inline void nosol(){putc('-');putc('1');putc('\n');}

bool check1[17]={1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1};
int ans1[17][3][3]={ { {1,1,1},{2,2,2},{2,2,2} },{ {1,1,1},{1,2,2},{1,2,2} },{ {1,1,1},{1,2,1},{1,2,1} },{ {1,1,1},{1,2,1},{1,1,2} },{ {1,1,1},{1,2,1},{1,1,1} },{ {1,1,1},{1,1,2},{2,2,2} },{ {1,1,1},{1,1,2},{1,2,2} },{ {1,1,1},{1,1,2},{2,1,1} },{ {1,1,1},{1,1,1},{2,2,2} },{ {1,1,1},{1,1,1},{1,2,2} },{ {1,1,1},{1,1,1},{1,2,1} },{ {0,0,0},{0,0,0},{0,0,0} },{ {0,0,0},{0,0,0},{0,0,0} },{ {1,1,1},{1,1,1},{1,1,2} },{ {0,0,0},{0,0,0},{0,0,0} },{ {0,0,0},{0,0,0},{0,0,0} },{ {1,1,1},{1,1,1},{1,1,1} } };

void gao_3x3(int k)
{
    if(k>=17||!check1[k]){nosol();return;}
    for(int i=0;i<3;i++,putc('\n'))
        for(int j=0;j<3;j++)
            putc((ans1[k][i][j]==1)?'*':'.');
}

typedef pair<int,int> pii;
const int N=100010;
bool flip=0,ans[N];
int n,m;

inline int idx(int x,int y){return (x-1)*m+y;}

void output()
{
    if(!flip)
    {
        for(int i=1;i<=n;i++,putc('\n'))
            for(int j=1;j<=m;j++)
                putc(ans[idx(i,j)]?'*':'.');
    }
    else
    {
        for(int j=1;j<=m;j++,putc('\n'))
            for(int i=1;i<=n;i++)
                putc(ans[idx(i,j)]?'*':'.');
    }
    putc('\n');
}

pii fill(int k)
{
    for(int i=1;i<=m;i++)
        ans[idx(1,i)]=1;
    int x=2,y=1;
    while(k)
    {
        ans[idx(x,y)]=1;
        if(y==1) k--;
        else if(y==m) k-=3;
        else k-=4;
        if(!k) break;
        if(y<m) y++;
        else x++,y=1;
    }
    return pii(x,y);
}

void gao_0(int k)
{
    if(k<=4*(m-1))
    {
        for(int i=1;i<=k/4+1;i++)
            ans[idx(1,i)]=ans[idx(2,i)]=1;
    }
    else
    {
        pii pp=fill(k+9);
        ans[idx(1,1)]=ans[idx(1,m)]=0;
        if(pp.second>1) ans[idx(pp.first,1)]=0;
        else ans[idx(pp.first-1,m)]=0;
    }
}

void gao_1(int k){fill(k);}

void gao_2(int k){fill(k+3);ans[idx(1,1)]=0;}

void gao_3(int k)
{
    pii falun=fill(k+6);
    if(falun.first==2)
    {
        memset(ans,0,sizeof(ans));
        falun=fill(k-2);
        ans[idx(falun.first,falun.second+2)]=1;
    }
    else ans[idx(1,1)]=ans[idx(1,m)]=0;
}

int main()
{
    int T,k;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        flip=(n>m);
        if(n>m) swap(n,m);
        if(n==3&&m==3){gao_3x3(k);continue;}
        int t=4*(n-1)*(m-1)-k;
        if(n==3&&t==8)
        {
            memset(ans,1,sizeof(ans));
            ans[idx(1,m)]=ans[idx(2,m)]=ans[idx(3,m)]=0;
            output();continue;
        }
        if(t==0)
        {
            memset(ans,1,sizeof(ans));
            output();continue;
        }
        memset(ans,0,sizeof(ans));
        if(k==0){output();continue;}
        if(t<0||t==1||t==2||t==4||t==5||t==8){nosol();continue;}
        switch (k&3)
        {
            case 0 : gao_0(k);break;
            case 1 : gao_1(k);break;
            case 2 : gao_2(k);break;
            case 3 : gao_3(k);break;
        }
        output();
    }
    flush();
    return 0;
}