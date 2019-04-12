#include<bits/stdc++.h>
using namespace std;

int main()
{
    freopen("choose3.in","w",stdout);
    srand(time(0));
    const int n=40,k=3,s=5;
    printf("%d %d %d\n",n,k,s);
    for(int i=1;i<=n;i++)
        printf("%d ",rand()%8+1);
    puts("");
    return 0;
}
