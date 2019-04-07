#include<bits/stdc++.h>
using namespace std;

int main()
{
    freopen("triple4.in","w",stdout);
    srand(time(0));
    int n=10,m=10;
    printf("%d %d\n",n,m);
    for(int i=1;i<=n;i++)
    {
        int x=rand()%m+1,y=rand()%m+1;
        if(x==y) x=rand()%m+1,y=rand()%m+1;
        char s[155];
        for(int i=1;i<=m;i++) s[i]='0';
        s[x]=s[y]='1';
        printf("%s\n",s+1);
    }
    return 0;
}
