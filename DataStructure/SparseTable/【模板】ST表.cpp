#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get(){
	if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
	if(H==T) return -1;return *H++;
}
int read(){
	int x=0,fg=1;char c=Get();
	while(!isdigit(c)&&c!='-') c=Get();
	if(c=='-') fg=-1,c=Get();
	while(isdigit(c)) x=x*10+c-'0',c=Get();
	return x*fg;
}

const int N = 100010;
int mult[20][N];
int lg2[N];

int main(){
	int n = read(), m = read();
	for(int i = 1; i <= n; i++) mult[0][i] = read();
	for(int i = 2; i <= n; i++) lg2[i] = lg2[i >> 1] + 1;
	for(int i = 0; i <= 15; i++)
		for(int j = 1; j + (1 << i + 1) - 1 <= n; j++)
			mult[i + 1][j] = max(mult[i][j], mult[i][j + (1 << i)]);
	for(int i = 1, l, r; i <= m; i++){
		l = read(); r = read();
		int p = lg2[r - l + 1];
		printf("%d\n", max(mult[p][l], mult[p][r - (1 << p) + 1]));
	}
	return 0;
}