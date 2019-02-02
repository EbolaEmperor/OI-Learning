#include<bits/stdc++.h>
using namespace std;

int main()
{
    printf("node 1\n");
    printf("read 0 a\n");
    printf("add a 4\n");
    printf("jmp a\n");
    static int f[45];
    f[0]=0;f[1]=1;
    for(int i=2;i<=45;i++)
        f[i]=f[i-1]+f[i-2];
    for(int i=0;i<=45;i++)
        printf("write %d 0\n",f[i]);
}