#include<bits/stdc++.h>
using namespace std;

const int N=800;
unsigned int r[N][N],g[N][N],b[N][N];
unsigned int n,m,posx=0,posy=32;
char s[5000];
int dig[35];

void read()
{
    freopen("base.txt","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            scanf("%d",r[i]+j);
            r[i][j]>>=1;
            r[i][j]<<=1;
        }
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",g[i]+j);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",b[i]+j);
}

void write()
{
    freopen("ciphertext.txt","w",stdout);
    printf("%d %d\n",n,m);
    for(int i=0;i<n;i++,puts(""))
        for(int j=0;j<m;j++)
            printf("%d ",r[i][j]);
    for(int i=0;i<n;i++,puts(""))
        for(int j=0;j<m;j++)
            printf("%d ",g[i][j]);
    for(int i=0;i<n;i++,puts(""))
        for(int j=0;j<m;j++)
            printf("%d ",b[i][j]);
}

int main()
{
    scanf("%s",s);read();
    int len=strlen(s),x=len;
    for(int i=0;i<32;i++) dig[i]=x&1,x>>=1;
    for(int i=0;i<32;i++) r[0][i]|=dig[31-i];
    for(int i=0;i<len;i++)
    {
        int x=s[i];
        for(int j=0;j<8;j++) dig[j]=x&1,x>>=1;
        for(int j=7;j>=0;j--)
        {
            if(posy==715) posx++,posy=0;
            r[posx][posy++]|=dig[j];
        }
    }
    write();
    return 0;
}