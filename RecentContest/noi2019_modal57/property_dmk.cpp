#include<bits/stdc++.h>
#include "rand.h"
using namespace std;

bool used[1000];

int main()
{
    int n=3,k=10;
    printf("%d %d\n",k,998244353);
    printf("%d\n",n);
    for(int i=1;i<=n;i++)
        printf("%d ",rand()%10+1);
    int m=3;
    printf("\n%d\n",m);
    for(int i=1;i<=m;i++)
    {
        int j=rand()%(k-n)+n;
        while(used[j]) j=rand()%(k-n)+n;
        used[j]=1;
        printf("%d %d\n",j,rand()%10+1);
    }
    return 0;
}