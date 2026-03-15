#include <bits/stdc++.h>
#define bk dq.back()
using namespace std;

void output(__int128 x){
    if(x >= 10) output(x / 10);
    putchar('0' + (x % 10));
}

const int N = 4e7 + 10, M = 1e5 + 10;
int n, type;
int pre[N];
long long sum[N];
deque<int> dq;

void input()
{
    const int mod = 1 << 30;
    int x, y, z, m;
    static int p[M], l[M], r[M];
    int *b = pre;
    scanf("%d%d%d%d%d%d", &x, &y, &z, b+1, b+2, &m);
	for(int i = 1 ; i <= m ; ++i)
        scanf("%d%d%d", p+i, l+i, r+i);
	for(int i = 3 ; i <= n ; ++i)
        b[i] = ( ( 1ll * x * b[i - 1] + 1ll * y * b[i - 2] ) % mod + z ) % mod;
	p[0] = 0;
	for(int j = 1 ; j <= m; ++j)
		for(int i = p[j - 1] + 1 ; i <= p[j] ; ++i)
			sum[i] = sum[i-1] + b[i] % ( r[j] - l[j] + 1 ) + l[j];
}

inline long long minlast(int i){
    return sum[i] - sum[pre[i]];
}

int main(){
    scanf("%d%d", &n, &type);
    if(type == 1) input();
    else for(int i = 1, tmp; i <= n; ++i)
        scanf("%d", &tmp), sum[i] = sum[i-1] + tmp;
    dq.push_back(0);
    for(int i = 1; i <= n; ++i){
        // sum[i] >= sum[j] + minlast[j]
        while(dq.size() >= 2 && 
              sum[i] >= sum[dq[1]] + minlast(dq[1]))
            dq.pop_front();
        pre[i] = dq[0];
        while(!dq.empty() &&
              sum[i] + minlast(i) <= sum[bk] + minlast(bk))
            dq.pop_back();
        dq.push_back(i);
    }
    __int128 ans = 0;
    for(int j = n; j; j = pre[j])
        ans += (__int128) (sum[j] - sum[pre[j]]) * (sum[j] - sum[pre[j]]);
    output(ans);
    return 0;
}
