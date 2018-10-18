#include<iostream>
#include<cstdio>
using namespace std;

int t[103],v[103];
int f[103][1003];

int max(int t1,int t2){return (t1>t2)?t1:t2;}

int main()
{
    int tottime,m;
    cin>>tottime>>m;
    int i,j;
    for(i=1;i<=m;i++)
        scanf("%d%d",&t[i],&v[i]);
    for(i=1;i<=m;i++)
        for(j=0;j<=tottime;j++)
        {
            f[i+1][j]=max(f[i][j],f[i+1][j]);
            if(j+t[i]<=tottime) f[i+1][j+t[i]]=max(f[i+1][j+t[i]],f[i][j]+v[i]);
        }
    cout<<f[m+1][tottime]<<endl;
    return 0;
}
