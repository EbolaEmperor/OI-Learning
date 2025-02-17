#include <bits/stdc++.h>
#include "bigint.h"
using namespace std;

int main(){
    // M = 3300 大约可以算准 e 的前 10000 位
    const int M = 3300;
    bigint fact = 1, e = 1;
    for(long long i = M; i >= 1; i--){
        fact = fact * i;
        e = e + fact;
    }
    e = e * pow(bigint(10), 11000);
    for(int i = 2; i <= M; i++)
        e = e / i;
    stringstream sout;
    sout << e;
    string s = sout.str();

    int trunc;
    cin >> trunc;
    printf("2.\n");
    for(int i = 1; i <= trunc; i += 50){
        for(int j = 1; j <= 50 && i + j - 1 <= trunc; j++){
            putchar(s[i + j - 1]);
            if(j % 10 == 0) printf(" ");
        }
        putchar('\n');
    }
    return 0;
}