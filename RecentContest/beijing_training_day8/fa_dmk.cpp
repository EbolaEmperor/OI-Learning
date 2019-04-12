#include<bits/stdc++.h>
using namespace std;

const int N=15;
int e[N][N];

int main()
{
    int n=10,m=15;
    for(int i=2;i<=n;i++)
    {
        int fa=rand()%(i-1)+1;
        e[i][fa]=e[fa][i]=1;
        printf("%d %d\n",i,fa);
    }
}
