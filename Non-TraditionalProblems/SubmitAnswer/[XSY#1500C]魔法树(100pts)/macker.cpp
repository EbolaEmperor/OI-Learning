#include<bits/stdc++.h>
using namespace std;

int main()
{
    char cmd[50];
    for(int i=1;i<=10;i++)
    {
        sprintf(cmd,"C.exe < tree/tree%d.in > tree/tree%d.out",i,i);
        system(cmd);
    }
    return 0;
}