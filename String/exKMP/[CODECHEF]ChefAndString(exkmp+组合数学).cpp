#include <bits/stdc++.h>
using namespace std;

void get_z(char s[], int z[]){
    int n = strlen(s+1);
    int l = 1, r = 1;
    for(int i = 2; i <= n; i++){
        z[i] = (i <= r) ? min(z[i-l+1], r-i+1) : 0;
        // 注意：当 i<=r 且 z[i-l+1]<r-i+1 时，while 循环一定不会执行
        while(i+z[i] <= n && s[1+z[i]] == s[i+z[i]]) z[i]++;
        if(i+z[i]-1 > r) l = i, r = i+z[i]-1;
    }
    z[1] = n;
}

const int N = 5010;
int f[N], ans[N];

void couting_substr(char s[]){
    static int cnt[N*N], maxidx;
    static int idx[N][N];
    static int z[N];

    int n = strlen(s+1);
    maxidx = 0;
    memset(cnt, 0, sizeof(int)*(n*n+1));
    memset(f, 0, sizeof(int)*(n+1));

    idx[n][n] = ++maxidx;
    for(int i = n-1; i >= 1; i--){
        get_z(s+i-1, z);
        int maxz = -1;
        for(int j = 2; j <= n-i+1; j++)
            if(maxz == -1 || z[j] > z[maxz]) maxz = j;
        for(int j = 1; j <= z[maxz]; j++)
            idx[i][i+j-1] = idx[i+maxz-1][i+maxz+j-2];
        for(int j = z[maxz]+1; j <= n-i+1; j++)
            idx[i][i+j-1] = ++maxidx;
    }
    
    for(int i = 1; i <= n; i++)
        for(int j = i; j <= n; j++)
            cnt[idx[i][j]]++;
    for(int i = 1; i <= maxidx; i++)
        f[cnt[i]]++;
}

void get_ans(int n){
    const int mod = 1e9 + 7;
    static int C[N][N];
    for(int i = 0; i <= n; i++){
        C[i][0] = 1;
        for(int j = 1; j <= i; j++)
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % mod;
    }

    for(int k = 1; k <= n; k++){
        ans[k] = 0;
        for(int i = k; i <= n; i++)
            ans[k] = (ans[k] + (long long) f[i] * C[i][k]) % mod;
    }
}

int main(){
    int T, n, q, k;
    static char s[N];
    scanf("%d", &T);
    while(T--){
        scanf("%d%d%s", &n, &q, s+1);
        couting_substr(s);
        get_ans(n);
        while(q--){
            scanf("%d", &k);
            printf("%d\n", k <= n ? ans[k] : 0);
        }
    }
    return 0;
}