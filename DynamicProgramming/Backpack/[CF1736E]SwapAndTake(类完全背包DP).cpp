#include <iostream>
#include <cstring>
using namespace std;

const int N = 505;
int f[N][N][N], a[N], n;

inline void upmax(int &x, const int &y){
    x = (x > y) ? x : y;
}

int main(){
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    memset(f, -0x3f, sizeof(f));
    f[0][0][0] = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            int p = abs(i - j);
            for(int k = 0; k <= j; k++){
                if(k >= p) upmax(f[i][j][k], f[i-1][j-1][k-p] + a[i]);
                if(k) upmax(f[i][j][k], f[i][j-1][k-1] + a[i]);
            }
        }
        for(int j = 0; j <= n; j++)
            for(int k = 0; k <= j; k++)
                upmax(f[i][j][k], f[i-1][j][k]);
    }
    int ans = -INT_MAX;
    for(int k = 0; k <= n; k++)
        upmax(ans, f[n][n][k]);
    cout << ans << endl;
    return 0;
}