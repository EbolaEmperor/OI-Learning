#include <bits/stdc++.h>
using namespace std;

const int N = 100010, S = 400, BN = N / S + 10;
int n, c, m, a[N];
int L[BN], R[BN], belong[N], tot = 0;
int cnt[BN][N];
// cnt[i][c]: 在前 i 块中，数字 c 出现了几次
int ans[BN][BN];
// ans[i][j]: 在第 i 到第 j 块中，出现次数为偶数的数字有几个
int bucket[N];

void prework(){
    for(int i = 1; i <= n; i += S){
        L[++tot] = i; R[tot] = min(n, i + S - 1);
        memcpy(cnt[tot], cnt[tot-1], sizeof(cnt[tot]));
        for(int j = 0; j < S; ++j){
            belong[i+j] = tot;
            ++cnt[tot][a[i+j]];
        }
    }
    for(int i = 1; i <= tot; ++i){
        for(int j = i; j <= tot; ++j){
            ans[i][j] = ans[i][j-1];
            for(int x = L[j]; x <= R[j]; ++x){
                if(bucket[a[x]] & 1) ++ans[i][j];
                else if(bucket[a[x]]) --ans[i][j];
                ++bucket[a[x]];
            }
        }
        memset(bucket, 0, sizeof(bucket));
    }
}

int countBucket(int l, int r, int lb = -1, int rb = -1){
    int even = 0;
    for(int i = l; i <= r; ++i){
        if(bucket[a[i]] == 0 && lb != -1 && lb <= rb)
            bucket[a[i]] = cnt[rb][a[i]] - cnt[lb-1][a[i]];
        if(bucket[a[i]] & 1) ++even;
        else if(bucket[a[i]]) --even;
        ++bucket[a[i]];
    }
    return even;
}

void clearBucket(int l, int r){
    for(int i = l; i <= r; ++i) bucket[a[i]] = 0;
}

int query(int l, int r){
    if(belong[l] + 1 >= belong[r]){
        int even = countBucket(l, r);
        clearBucket(l, r);
        return even;
    } else {
        int lb = belong[l], rb = belong[r];
        int even = (lb+1 <= rb-1) ? ans[lb+1][rb-1] : 0;
        even += countBucket(l, R[lb], lb+1, rb-1);
        even += countBucket(L[rb], r, lb+1, rb-1);
        clearBucket(l, R[lb]);
        clearBucket(L[rb], r);
        return even;
    }
}

int main(){
    scanf("%d%d%d", &n, &c, &m);
    for(int i = 1; i <= n; ++i) scanf("%d", a + i);
    prework();
    cerr << tot << endl;
    int l, r, lastans = 0;
    while(m--){
        scanf("%d%d", &l, &r);
        l = (l + lastans) % n + 1;
        r = (r + lastans) % n + 1;
        if(l > r) swap(l, r);
        printf("%d\n", lastans = query(l, r));
    }
    return 0;
}