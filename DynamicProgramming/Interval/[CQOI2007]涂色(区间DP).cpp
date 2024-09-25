#include <bits/stdc++.h>
using namespace std;

const int N = 5010;
int f[N][N];
string s;

int main(){
    cin >> s;
    int n = s.size();
    memset(f, 0x3f, sizeof(f));
    for(int i = 0; i < n; i++)
        f[i][i] = 1;
    for(int len = 2; len <= n; len++)
        for(int l = 0; l < n; l++){
            int r = l + len - 1;
            if(r >= n) break;
            for(int k = l; k < r; k++)
                f[l][r] = min(f[l][r], f[l][k] + f[k+1][r]);
            if(s[l] == s[r]) f[l][r]--;
        }
    cout << f[0][n - 1] << endl;
    return 0;
}
