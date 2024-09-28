#include <bits/stdc++.h>
using namespace std;

const int N = (1<<20) + 5;

// suf[i]: F(S[i,n])
// f[i][j]: S[1,1], S[1,2], ..., S[1,i] 中有几个串满足 F<=j
void get_f(char s[], int suf[], int f[][27]){
    int n = strlen(s+1);
    static int pre[N], cnt[27];
    // pre[i]: F(S[1,i])

    pre[0] = 0;
    memset(cnt, 0, sizeof(cnt));
    for(int i = 1; i <= n; i++){
        cnt[s[i]-'a']++;
        if(cnt[s[i]-'a'] & 1) pre[i] = pre[i-1] + 1;
        else pre[i] = pre[i-1] - 1;
    }

    suf[n+1] = 0;
    memset(cnt, 0, sizeof(cnt));
    for(int i = n; i >= 1; i--){
        cnt[s[i]-'a']++;
        if(cnt[s[i]-'a'] & 1) suf[i] = suf[i+1] + 1;
        else suf[i] = suf[i+1] - 1;
    }

    for(int i = 1; i <= n; i++){
        memcpy(f[i], f[i-1], sizeof(f[i]));
        f[i][pre[i]]++;
    }
    for(int i = 1; i <= n; i++)
        for(int c = 1; c <= 26; c++)
            f[i][c] += f[i][c-1];
}

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

int main(){
    int T;
    static char s[N];
    static int z[N], suf[N], f[N][27];

    scanf("%d", &T);
    while(T--){
        scanf("%s", s+1);
        get_f(s, suf, f);
        get_z(s, z);

        int n = strlen(s+1);
        long long ans = 0;

        // 枚举 AB = S[1,p]
        for(int p = 2; p < n; p++){
            int ed = min(p + z[p+1], n-1);
            // 枚举 (AB)^i 中的 i
            for(int i = 1; i * p <= ed; i++){
                // 寻找 S[1,p] 有几种划分成 AB 的方案使得 F(A)<=F(C)
                ans += f[p-1][suf[i * p + 1]];
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}