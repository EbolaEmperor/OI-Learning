#include<bits/stdc++.h>
#include "rand.h"
using namespace std;

int main()
{
    int n=150,m=1000;
    printf("%d %d 1\n",n,m);
    for(int i=1;i<=m;i++)
    {
        int u=rand()%n+1,v=rand()%n+1;
        printf("%d %d %d\n",u,v,i);
    }
    int a=rand()%n+1,b=rand()%n+1,c=rand()%n+1;
    printf("%d %d %d\n",a,b,c);
    return 0;
}