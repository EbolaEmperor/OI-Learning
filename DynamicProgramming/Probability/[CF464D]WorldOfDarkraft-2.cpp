#include<bits/stdc++.h>
using namespace std;

double f[2][630];

int main()
{
	int n;double K;
    scanf("%d%lf",&n,&K);
    int k=0;
    for(int i=1;i<=n;i++,k^=1)
        for(int j=1;j<=625;j++)
        	f[k][j]=(1/K)*((j*f[k^1][j]+f[k^1][j+1]+j)/(j+1)+(K-1)*f[k^1][j]+j/2.0);
    printf("%.9f",K*f[k^1][1]);
    return 0;
}
