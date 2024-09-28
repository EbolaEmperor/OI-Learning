#include <bits/stdc++.h>
using namespace std;

const int N = 20000010;
char a[N], b[N<<1];
int z[N<<1];

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

long long get_val(int a[], int n){
    long long ans = 0;
    for(int i = 1; i <= n; i++)
        ans ^= (long long) i * (a[i] + 1);
    return ans;
}

int main(){
    scanf("%s", a+1);
    int n = strlen(a+1);
    scanf("%s", b+1);
    int m = strlen(b+1);
    b[m+1] = '#';
    memcpy(b+m+2, a+1, sizeof(char)*n);

    get_z(b, z);
    z[1] = m;
    cout << get_val(z, m) << endl;
    cout << get_val(z+m+1, n) << endl;
    return 0;
}