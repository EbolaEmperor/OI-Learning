#include<bits/stdc++.h>
using namespace std;

int main()
{
    puts("999 500");
    for(int i=1;i<=499;i++)
        if(i&1) printf("1 %d\n1 %d\n",i,i);
        else printf("2 %d %d\n2 %d %d\n",i,i-1,i,i+1);
    puts("1 1");
    return 0;
}