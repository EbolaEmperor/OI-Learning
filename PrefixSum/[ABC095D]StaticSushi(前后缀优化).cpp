// EFR-#4-Div.2 maybach
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 100010;
LL oil[N], dis[N], invdis[N];
LL earn[N], invearn[N];
LL C; int n;

int main(){
	scanf("%d%lld", &n, &C);
	LL sumoil = 0, ans = 0;
	for(int i = 1; i <= n; ++i){
		scanf("%lld%lld", dis + i, oil + i);
		invdis[i] = C - dis[i];
		sumoil += oil[i];
		earn[i] = max(earn[i - 1], sumoil - dis[i]);
		ans = max(ans, sumoil - dis[i]);
	}
	sumoil = 0;
	for(int i = n; i >= 1; --i){
		sumoil += oil[i];
		invearn[i] = max(invearn[i + 1], sumoil - invdis[i]);
		ans = max(ans, sumoil - invdis[i]);
	}
	sumoil = 0;
	for(int i = 1; i <= n; ++i){
		sumoil += oil[i];
		ans = max(ans, sumoil - 2 * dis[i] + invearn[i+1]);
	}
	sumoil = 0;
	for(int i = n; i >= 1; --i){
		sumoil += oil[i];
		ans = max(ans, sumoil - 2 * invdis[i] + earn[i - 1]);
	}
	cout << ans << endl;
	return 0;
}