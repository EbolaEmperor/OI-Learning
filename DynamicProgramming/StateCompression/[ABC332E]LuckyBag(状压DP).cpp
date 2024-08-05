#include<bits/stdc++.h>
using namespace std;

double dp[16][1<<15];
long long w[15];

int main(){
	int n, d;
	cin >> n >> d;
	long long sum = 0;
	for(int i = 0; i < n; i++)
		cin >> w[i], sum += w[i];
	double xbar = (double) sum / d;
	for(int s = 0; s < 1<<n; s++){
		for(int i = 0; i < n; i++)
			if(s>>i&1) dp[1][s] += w[i];
		dp[1][s] = pow(dp[1][s] - xbar, 2);
	}
	for(int i = 2; i <= d; i++)
		for(int s = 0; s < 1<<n; s++){
			dp[i][s] = 1e100;
			for(int t = s; t; t = s & (t-1))
				dp[i][s]=min(dp[i][s], dp[i-1][s^t] + dp[1][t]);
		}
	printf("%.8lf", dp[d][(1<<n)-1] / d);
	return 0;
}