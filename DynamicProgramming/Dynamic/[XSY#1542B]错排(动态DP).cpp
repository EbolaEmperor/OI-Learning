#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=30010;
const LL INF=0x3f3f3f3f3f3f3f3fLL;
struct P{int val,pos;} a[N],b[N];
int n,m,rk[N];

inline void upmax(LL &x,const LL &y){if(y>x) x=y;}
struct Matrix
{
    LL a[3][3];
    Matrix(){memset(a,-0x3f,sizeof(a));}
    LL* operator [] (const int &x){return a[x];}
    Matrix operator * (Matrix &B)
    {
        Matrix C;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                for(int k=0;k<3;k++)
                    upmax(C[i][j],a[i][k]+B[k][j]);
        return C;
    }
} mat[N<<2];

void gao(int o,int x)
{
    mat[o][0][0]=(a[x].pos==b[x].pos)?-INF:(LL)a[x].val*b[x].val;
    mat[o][1][0]=(x>1)?(LL)a[x].val*b[x-1].val+(LL)a[x-1].val*b[x].val:-INF;
    mat[o][2][0]=(x>2)?(LL)a[x].val*b[x-1].val+(LL)a[x-1].val*b[x-2].val+(LL)a[x-2].val*b[x].val:-INF;
    if(x>2) upmax(mat[o][2][0],(LL)a[x].val*b[x-2].val+(LL)a[x-1].val*b[x].val+(LL)a[x-2].val*b[x-1].val);
    mat[o][0][2]=mat[o][1][1]=mat[o][2][1]=mat[o][2][2]=-INF;
    mat[o][0][1]=mat[o][1][2]=0;
}

void build(int o,int l,int r)
{
    if(l==r){gao(o,l);return;}
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    mat[o]=mat[o<<1]*mat[o<<1|1];
}

void update(int o,int l,int r,int k)
{
    if(l==r){gao(o,l);return;}
    int mid=(l+r)/2;
    if(k<=mid) update(o<<1,l,mid,k);
    else update(o<<1|1,mid+1,r,k);
    mat[o]=mat[o<<1]*mat[o<<1|1];
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i].val),a[i].pos=i;
    for(int i=1;i<=n;i++) scanf("%d",&b[i].val),b[i].pos=i;
    sort(a+1,a+1+n,[](P a,P b){return a.val<b.val;});
    sort(b+1,b+1+n,[](P a,P b){return a.val<b.val;});
    for(int i=1;i<=n;i++) rk[b[i].pos]=i;
    build(1,1,n);
    while(m--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        x=rk[x];y=rk[y];
        swap(b[x].pos,b[y].pos);
        rk[b[x].pos]=x;
        rk[b[y].pos]=y;
        update(1,1,n,x);
        update(1,1,n,y);
        printf("%lld\n",mat[1][0][0]);
    }
    return 0;
}