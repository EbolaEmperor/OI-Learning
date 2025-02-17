#include<bits/stdc++.h>
using namespace std;

const int P=120100,N=2010;
int u[P],d[P],l[P],r[P],tot;
int h[N],sum[N],pos[P],row[P];
int idrow[P],idcol[P],val[P];
int n,m,ans[N],top=0;

void link(int x,int c)
{
    sum[c]++;
    pos[++tot]=c;row[tot]=x;
    u[tot]=c;d[tot]=d[c];
    u[d[tot]]=d[u[tot]]=tot;
    if(h[x]!=-1)
    {
        l[tot]=h[x];r[tot]=r[h[x]];
        l[r[tot]]=r[l[tot]]=tot;
    }
    else h[x]=l[tot]=r[tot]=tot;
}

void del(int c)
{
    l[r[c]]=l[c];r[l[c]]=r[c];
    for(int o=u[c];o!=c;o=u[o])
        for(int q=r[o];q!=o;q=r[q])
        {
            u[d[q]]=u[q];
            d[u[q]]=d[q];
            sum[pos[q]]--;
        }
}

void add(int c)
{
    for(int o=u[c];o!=c;o=u[o])
        for(int q=r[o];q!=o;q=r[q])
        {
            u[d[q]]=d[u[q]]=q;
            sum[pos[q]]++;
        }
    l[r[c]]=r[l[c]]=c;
}

const int w[9][9]=
{
	{6,6,6,6,6,6,6,6,6},
	{6,7,7,7,7,7,7,7,6},
	{6,7,8,8,8,8,8,7,6},
	{6,7,8,9,9,9,8,7,6},
	{6,7,8,9,10,9,8,7,6},
	{6,7,8,9,9,9,8,7,6},
	{6,7,8,8,8,8,8,7,6},
	{6,7,7,7,7,7,7,7,6},
	{6,6,6,6,6,6,6,6,6}
};
int maxans = -1, curans = 0;

void dance()
{
    if(!r[0])
    {
        maxans = max(maxans, curans);
        return;
    }
    int x=r[0];
    for(int o=r[0];o;o=r[o])
        if(sum[o]<sum[x]) x=o;
    del(x);
    for(int o=d[x];o!=x;o=d[o])
    {
        for(int q=r[o];q!=o;q=r[q]) del(pos[q]);
        curans += val[row[o]] * w[idrow[row[o]]][idcol[row[o]]];
        dance();
        curans -= val[row[o]] * w[idrow[row[o]]][idcol[row[o]]];
        for(int q=l[o];q!=o;q=l[q]) add(pos[q]);
    }
    add(x);
}

void init(int m){
    for(int i=0;i<=m;i++)
    {
        u[i]=d[i]=i;
        l[i]=i-1;r[i]=i+1;
        pos[i]=i;sum[i]=0;
    }
    l[0]=m;r[m]=0;tot=m;
    memset(h,-1,sizeof(h));
}

int main()
{
    init(81*4);
    int cnt = 0;
    for(int x, i = 0; i < 9; ++i)
        for(int j = 0; j < 9; ++j){
            cin >> x;
            for(int k = 1; k <= 9; ++k){
                if(x != 0 && k != x) continue;
                link(++cnt, 1 + i * 9 + j);
                link(cnt, 81 + i * 9 + k);
                link(cnt, 162 + j * 9 + k);
                link(cnt, 243 + (i / 3 * 3 + j / 3) * 9 + k);
                idrow[cnt] = i;
                idcol[cnt] = j;
                val[cnt] = k;
            }
        }
    dance();
    cout << maxans << endl;
    return 0;
}