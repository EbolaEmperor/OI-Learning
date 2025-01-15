// 做法解析见 Lecture 16 - Problem Q
#include <bits/stdc++.h>
using namespace std;

const int N = (1 << 16) + 5;
int num[9][N], n;
long long rec[9][9];
int f[N], bit[N];

inline int lowbit(int x){
    return x & -x;
}

void add(int p, int x){
    for(; p <= n; p += lowbit(p))
        bit[p] += x;
}

int query(int p){
    int ans = 0;
    for(; p; p -= lowbit(p))
        ans += bit[p];
    return ans;
}

long long doPartialOrder2D(int *a, int *b){
    for(int i = 1; i <= n; i++) f[a[i]] = b[i];
    memset(bit, 0, sizeof(bit));
    long long ans = 0;
    for(int i = 1; i <= n; i++){
        ans += query(f[i]);
        add(f[i], 1);
    }
    return ans;
}

long long partialOrder2D(int i, int j){
    if(rec[i][j] != -1) return rec[i][j];
    return rec[i][j] = doPartialOrder2D(num[i], num[j]);
}

long long compute(int i, int j, int k){
    static const long long Cn2 = (long long) n * (n - 1) / 2;
    int X = partialOrder2D(i, j) + partialOrder2D(i, k) + partialOrder2D(j, k);
    return (X - Cn2) / 2;
}

int main(){
    memset(rec, -1, sizeof(rec));
    scanf("%d", &n);
    for(int i = 0; i < 9; i++)
        for(int j = 1; j <= n; j++){
            int x;
            scanf("%d", &x);
            num[i][x] = j;
        }
    long long maxrec = -1;
    int c1, c2, c3;
    for(int i = 0; i < 9; i++)
        for(int j = i + 1; j < 9; j++)
            for(int k = j + 1; k < 9; k++){
                int tmp = compute(i, j, k);
                if(maxrec == -1 || tmp < maxrec){
                    maxrec = tmp;
                    c1 = i; c2 = j; c3 = k;
                }
            }
    printf("%d %d %d\n", c1 + 1, c2 + 1, c3 + 1);
    return 0;
}