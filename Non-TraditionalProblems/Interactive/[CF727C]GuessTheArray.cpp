#include<iostream>
#include<cstdio>
using namespace std;

int a[5005],x[5005];

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<n;i++)
    {
        printf("? %d %d\n",i,i+1);
        fflush(stdout);
        scanf("%d",x+i);
    }
    printf("? 1 3\n");
    fflush(stdout);
    scanf("%d",x);
    a[2]=(x[1]+x[2]-x[0])/2;
    a[1]=x[1]-a[2];
    for(int i=3;i<=n;i++) a[i]=x[i-1]-a[i-1];
    printf("! ");
    for(int i=1;i<=n;i++) printf("%d ",a[i]);
    printf("\n");
    fflush(stdout);
    return 0;
}
