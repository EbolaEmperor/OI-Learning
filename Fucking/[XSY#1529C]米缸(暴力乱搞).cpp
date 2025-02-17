#include<bits/stdc++.h>
using namespace std;
 
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
inline void reads(char *s)
{
    char c=Get();int tot=0;
    while(c<'a'||c>'z') c=Get();
    while(c>='a'&&c<='z') s[tot++]=c,c=Get();
    s[tot]='\0';
}
 
struct pt{int x,y;};
const int N=2010;
int num[N][N],n,m;
int nxt[N],vis[N],p[N];
 
pt operator + (const pt &a,const pt &b){return {(a.x+b.x+n)%n,(a.y+b.y+m)%m};}
pt maxp(const pt &a,const pt &b){return num[a.x][a.y]>num[b.x][b.y]?a:b;}
void move(pt &t){t=maxp(t+(pt){0,1},maxp(t+(pt){-1,1},t+(pt){1,1}));}
void move(pt &t,int k){while(k--)move(t);}
 
void change(pt t)
{
    int l=t.x,r=t.x;
    pt ed=t;move(ed,m-t.y);
    for(int i=t.y;i;i--)
    {
        if(l>r) break;
        int L=(l+n)%n,R=(r+n)%n;
        pt tmp={L,i-1};move(tmp);
        if(tmp.x==(L-1+n)%n) l++;
        tmp={(L-1+n)%n,i-1};move(tmp);
        if(tmp.x==L) l--;
        tmp={R,i-1};move(tmp);
        if(tmp.x==(R+1)%n) r--;
        tmp={(R+1)%n,i-1};move(tmp);
        if(tmp.x==R) r++;
    }
    for(int i=l;i<=r;i++) nxt[(i+n)%n]=ed.x;
}
 
int main()
{
    n=read();m=read();
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            num[i][j]=read();
    for(int i=0;i<n;i++)
    {
        pt t={i,0};
        move(t,m);
        nxt[i]=t.x;
    }
    char opt[10];pt t={0,0};
    for(int T=read();T;T--)
    {
        reads(opt);
        if(opt[0]=='m')
        {
            int k=read(),cnt=0,x=t.x,st=1;
            while(k&&t.y) move(t),k--;
            while(vis[x]!=T) vis[p[++cnt]=x]=T,x=nxt[x];
            while(nxt[p[cnt]]!=p[st]) st++;
            while(k>=m&&t.x!=p[st]) t.x=nxt[t.x],k-=m;
            k%=m*(cnt-st+1);
            while(k>=m) t.x=nxt[t.x],k-=m;
            while(k) move(t),k--;
            printf("%d %d\n",t.x+1,t.y+1);
        }
        if(opt[0]=='c')
        {
            int a=read(),b=read();
            num[a-1][b-1]=read();
            pt cp={a-1,b-1};
            change(cp+(pt){-1,-1});
            change(cp+(pt){0,-1});
            change(cp+(pt){1,-1});
        }
    }
    return 0;
}