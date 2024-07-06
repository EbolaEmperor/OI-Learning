#include <bits/stdc++.h>
using namespace std;

const int ha = 1e9 + 7;
const int N = 4010;
int C[N][N];

inline int mns(int x, int y){
    return x - y < 0 ? x - y + ha : x - y;
}
inline int add(int x, int y){
    return x + y >= ha ? x + y - ha : x + y;
}

int main(){
    for(int i = 0; i < N; ++i){
        C[i][0] = 1;
        for(int j = 1; j <= i; ++j)
            C[i][j] = add(C[i-1][j-1], C[i-1][j]);
    }
    int t, n, m, k;
    scanf("%d", &t);
    while(t--){
        scanf("%d%d%d", &n, &m, &k);
        if(k > min(n, m)) puts("0");
        else printf("%d\n", mns(C[n+m][k], C[n+m][k-1]));
    }
    return 0;
}