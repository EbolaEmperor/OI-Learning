#include <bits/stdc++.h>
using namespace std;

const int N = 510;
int f[N][N];
char a[N];
int z[N];

void get_z(char s[], int n, int z[]){
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
    while(1){
        scanf("%s", a+1);
        if(a[1] == '*') break;
        int n = strlen(a+1);
        memset(f, 0x3f, sizeof(f));
        
        for(int len = 1; len <= n; len++){
            for(int l = 1; l <= n-len+1; l++){
                if(len == 1){
                    f[l][l] = 1;
                    continue;
                }
                int r = l + len - 1;
                get_z(a+l-1, len, z);
                for(int i = 1; i <= len; i++){
                    if(len % i) continue;
                    if(i == len || i + z[i+1] == len){
                        f[l][r] = f[l][l+i-1];
                        break;
                    }
                }
                for(int k = l; k < r; k++)
                    f[l][r] = min(f[l][r], f[l][k] + f[k+1][r]);
            }
        }
        printf("%d\n", f[1][n]);
    }
    return 0;
}