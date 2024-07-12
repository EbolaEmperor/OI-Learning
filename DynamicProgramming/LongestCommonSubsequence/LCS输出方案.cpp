#include <bits/stdc++.h>
#define LL long long
using namespace std;

const int N = 5010;
char s[N], t[N];
int f[N][N], p[N][N];

int a(int i, int j){ return s[i] == t[j]; }

void output(int i, int j){
    if(i == 0 || j == 0) return;
    if(p[i][j] == 0) output(i, j-1);
    else if(p[i][j] == 1) output(i-1, j);
    else {
        output(i-1, j-1);
        putchar(s[i-1]);
    }
}

int main(){
    scanf("%s%s", s, t);
    int n = strlen(s), m = strlen(t);
    f[0][0] = a(0, 0);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j){
            if(a(i,j) == 0){
                if(f[i][j] + a(i, j+1) > f[i][j+1]){
                    f[i][j+1] = f[i][j] + a(i, j+1);
                    p[i][j+1] = 0;
                }
                if(f[i][j] + a(i+1, j) > f[i+1][j]){
                    f[i+1][j] = f[i][j] + a(i+1, j);
                    p[i+1][j] = 1;
                }
            } else {
                if(f[i][j] + a(i+1, j+1) > f[i+1][j+1]){
                    f[i+1][j+1] = f[i][j] + a(i+1, j+1);
                    p[i+1][j+1] = 2;
                }
            }
        }
    int maxval = 0, maxi, maxj;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            if(f[i][j] > maxval){
                maxval = f[i][j];
                maxi = i;
                maxj = j;
            }
    if(maxval > 0){
        output(maxi, maxj);
        if(a(maxi, maxj) == 1) putchar(s[maxi]);
    }
    return 0;
}