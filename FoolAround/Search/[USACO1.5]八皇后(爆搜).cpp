#include<bits/stdc++.h>
using namespace std;

const int N = 15;
bool used[N], ldiag[2*N], rdiag[2*N];
int pos[N], n, ans = 0;

void dfs(int u){
	if(u > n){
		if(ans < 3){
			for(int i = 1; i <= n; i++) 
				cout << pos[i] << " ";
			cout << endl;
		}
		ans++;
		return;
	}
	for(int i = 1; i <= n; i++){
		if(used[i] || ldiag[u-i+n] || rdiag[i+u]) continue;
		used[i] = ldiag[u-i+n] = rdiag[i+u] = 1;
        pos[u]=i; dfs(u+1);
		used[i] = ldiag[u-i+n] = rdiag[i+u] = 0;
	}
}

int main(){
	cin >> n;
	dfs(1);
	cout << ans << endl;
	return 0;
} 