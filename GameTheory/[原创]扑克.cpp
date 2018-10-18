#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int mod(string a,int b)
{
    int d=0;
    for(int i=0;i<a.size();i++) d=(d*10+(int)(a[i]-'0'))%b;
    return d;
}

void reads(string &s)
{
    char c=getchar();
    while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9') s+=c,c=getchar();
}

int main()
{
    string n;
    int q,a;
    scanf("%d",&q);
    for(int T=1;T<=q;T++)
    {
        n.clear();
        scanf("%d",&a);
        reads(n);
        if(a%2==1)
        {
            if((int)n[n.size()-1]%2==1) printf("lsq Win\n");
            else printf("wzt Win\n");
        }
        else
        {
            int m=mod(n,a+1);
            if(m==0) printf("wzt Win\n");
            else if(m%2==1) printf("lsq Win\n");
            else if(m==a) printf("lsq Win\n");
            else printf("wzt Win\n");
        }
    }
    return 0;
}
