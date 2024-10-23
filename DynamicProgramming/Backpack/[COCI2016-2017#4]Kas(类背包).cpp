#include <iostream>
#include <cstring>
using namespace std;

const int N = 200010;
// f[x + N]: 当前两人差值为 x，剩余的钱最少是多少
int f[2][N << 1];

int main(){
    int n, c, sum = 0;
    cin >> n;
    memset(f, 0x3f, sizeof(f));
    f[0][N] = 0;
    for(int i = 1, p = 0; i <= n; i++, p ^= 1){
        cin >> c;
        sum += c;
        for(int x = -1e5; x <= 1e5; x++)
            f[p ^ 1][x + N] = min(f[p][x + N] + c, min(f[p][x + c + N], f[p][x - c + N]));
    }
    cout << (sum + f[n & 1][N]) / 2 << endl;
    return 0;
}