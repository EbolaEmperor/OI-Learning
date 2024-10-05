#include <bits/stdc++.h>
using namespace std;

const int N = 30010;
int f[16][11][N], pw3[11];
bool inited = 0;

void init(int n){
    pw3[0] = 1;
    for(int i = 1; i <= 10; i++)
        pw3[i] = pw3[i - 1] * 3;
    for(int y = 30000; y >= 0; y--)
        for(int a = 15; a >= 0; a--)
            for(int b = 10; b >= 0; b--){
                if((1<<a) * pw3[b] + y >= n) f[a][b][y] = 0;
                else{
                    if(f[0][0][(1<<a) * pw3[b] + y] == 0) f[a][b][y] = 1;
                    else if(f[a+1][b][y] == 0) f[a][b][y] = 2;
                    else if(f[a][b+1][y] == 0) f[a][b][y] = 3;
                    else f[a][b][y] = 0;
                }
            }
    inited = 1;
}

extern "C" int _opt(int n, int x, int y){
    if(!inited) init(n);
    int p2 = 0, p3 = 0;
    while(x % 2 == 0) x /= 2, p2++;
    while(x % 3 == 0) x /= 3, p3++;
    return f[p2][p3][y];
}