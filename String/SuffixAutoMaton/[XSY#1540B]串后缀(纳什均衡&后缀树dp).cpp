#include<bits/stdc++.h>
using namespace std;

namespace Output
{
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
    inline void printd(int d,double x)
    {
        long long t=(long long)floor(x);
        print(t);putc('.');x-=t;
        while(d--)
        {
            double y=x*10;x*=10;
            int c=(int)floor(y);
            putc(c+'0');x-=floor(y);
        }
    }
}

const int N=400010;
int T,n,lst=1,tot=1,c[N];
int ch[N][26],prt[N],len[N],tag[N],p[N];
double g[N];
char ss[N];

void reset()
{
    for(int i=0;i<=tot;i++) memset(ch[i],0,sizeof(ch[i]));
    memset(prt,0,sizeof(int)*(tot+1));
    memset(len,0,sizeof(int)*(tot+1));
    memset(tag,0,sizeof(int)*(tot+1));
    memset(g,0,sizeof(double)*(tot+1));
    memset(c,0,sizeof(int)*(n+1));
    lst=tot=1;
}

void insert(int c)
{
	int p=lst,np=++tot;len[np]=len[p]+1;tag[np]=1;
	while(p&&!ch[p][c]) ch[p][c]=np,p=prt[p];
	if(!p) prt[np]=1;
	else
	{
		int q=ch[p][c];
		if(len[p]+1==len[q]) prt[np]=q;
		else
		{
			int nq=++tot;len[nq]=len[p]+1;
			memcpy(ch[nq],ch[q],sizeof(ch[nq]));
			prt[nq]=prt[q];prt[q]=prt[np]=nq;
			while(ch[p][c]==q) ch[p][c]=nq,p=prt[p];
		}
	}
	lst=np;
}

void topo_sort()
{
    for(int i=1;i<=tot;i++) c[len[i]]++;
    for(int i=1;i<=n;i++) c[i]+=c[i-1];
    for(int i=tot;i>=1;i--) p[c[len[i]]--]=i;
}

int main()
{
    for(scanf("%d",&T);T;T--)
    {
        scanf("%s",ss+1);n=strlen(ss+1);
        for(int i=n;i>=1;i--) insert(ss[i]-'a');
        topo_sort();
        for(int i=tot;i>=0;i--)
        {
            int x=p[i];
            g[x]=tag[x]?0:1.0/g[x];
            if(x) g[prt[x]]+=1.0/(g[x]+len[x]-len[prt[x]]);
        }
        Output::printd(10,g[0]);
        Output::putc('\n');
        reset();
    }
    return Output::flush(),0;
}