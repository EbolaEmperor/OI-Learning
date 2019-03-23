#include<bits/stdc++.h>
using namespace std;

const int ha=1e9+7;
const int N=1010,M=500010;
struct{int opt,r,c;} qry[M];
vector<int> num[N],bit[N],allow[N];
map<int,int> idx[N];
int n,m,q,len[N];

void add(int &x,const int &y){x=(x+y>=ha)?(x+y-ha):(x+y);}

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void prework()
{
    for(int i=1;i<=n;i++)
    {
        sort(num[i].begin(),num[i].end());
        int unq=unique(num[i].begin(),num[i].end())-num[i].begin();
        num[i].resize(unq);
        for(int x : num[i])
        {
            bit[i].emplace_back(Pow(2,x));
            idx[i][x]=len[i]++;
        }
        allow[i].resize(len[i]);
    }
}

int getans()
{
    static int lastans[M],must[M];
    int ans=0,anslen=0;
    for(int i=1;i<=n;i++)
    {
        int pos=len[i]-1,id=-1;
        for(int j=anslen-1;j>=0;j--)
        {
            while(pos>=0&&num[i][pos]>lastans[j]) pos--;
            if(pos<0||num[i][pos]!=lastans[j]||!allow[i][pos]){id=j;break;}
            must[pos]=1;
        }
        int choose=-1;
        for(int j=0;j<len[i];j++)
            if((id<0||num[i][j]>lastans[id])&&!must[j]&&allow[i][j])
                {choose=j;must[j]=1;break;}
        if(choose<0)
        {
            memset(must,0,sizeof(must));
            return -1;
        }
        anslen=0;
        for(int j=0;j<choose;j++) must[j]=0;
        for(int j=choose;j<len[i];j++)
        {
            if(!must[j]) continue;
            lastans[anslen++]=num[i][j];
            add(ans,bit[i][j]);
            must[j]=0;
        }
    }
    return ans;
}

int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=q;i++)
    {
        scanf("%d",&qry[i].opt);
        if(qry[i].opt==1)
        {
            scanf("%d%d",&qry[i].r,&qry[i].c);
            qry[i].c=m-qry[i].c;
            num[qry[i].r].emplace_back(qry[i].c);
        }
    }
    prework();
    for(int i=1;i<=q;i++)
    {
        if(qry[i].opt==2)
            printf("%d\n",getans());
        else
        {
            int r=qry[i].r,id=idx[r][qry[i].c];
            allow[r][id]^=1;
        }
    }
    return 0;
}