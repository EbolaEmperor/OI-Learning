#include<bits/stdc++.h>
using namespace std;

int calc(int n)
{
    int m=sqrt(n);
    for(int i=m;i>=1;i--)
        if(n%i==0) return i;
}

void gao(int a,int b,int c)
{
    int n=a+b+c+4;
    printf("%d\n",n);
    puts("1 2 1");
    puts("1 3 1");
    puts("1 4 1");
    for(int i=1;i<=a;i++)
        printf("2 %d 1\n",i+4);
    for(int i=1;i<=b;i++)
        printf("3 %d 1\n",i+4+a);
    for(int i=1;i<=c;i++)
        printf("4 %d 1\n",i+4+a+b);
}

int main()
{
    int k;
    cin>>k;
    int c=0,a=calc(k+c*c)-c,b=(k+c*c)/(a+c)-c;
    while(a<0||b<0||a+b+c+4>5000)
    {
        c++;
        a=calc(k+c*c)-c;
        b=(k+c*c)/(a+c)-c;
    }
    gao(a,b,c);
    return 0;
}