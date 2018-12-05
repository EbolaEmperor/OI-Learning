#include<bits/stdc++.h>
using namespace std;

const int N=110;
int a[N],n,m;
int oddnum[2];

int main()
{
    int odd=0,tot=0;
    scanf("%d%d",&n,&m);
    oddnum[0]=1;oddnum[1]=m;
    for(int i=1;i<=m;i++)
    {
        scanf("%d",a+i);
        if(~a[i]&1) continue;
        oddnum[odd++]=i;
        if(odd>2) return puts("Impossible"),0;
    }
    swap(a[1],a[oddnum[0]]);
    swap(a[m],a[oddnum[1]]);
    if(m==1&&a[1]==1) return puts("1\n1\n1"),0;
    for(int i=1;i<=m;i++) printf("%d ",a[i]);
    if(m==1) return printf("\n2\n%d 1\n",a[1]-1),0;
    printf("\n%d\n%d ",a[m]>1?m:m-1,a[1]+1);
    for(int i=2;i<m;i++) printf("%d ",a[i]);
    if(a[m]>1) printf("%d\n",a[m]-1);
    return 0;
}