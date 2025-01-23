#include <bits/stdc++.h>
#include "bigint.h"
using namespace std;

int main(){
    int trunc;
    cin >> trunc;
    int M = trunc * 3.5;

    bigint fact = 1, pi = 1;
    for(int i = 1; i <= M; i++){
        fact = fact * i;
        pi = pi * (2 * i + 1) + fact;
    }
    pi = pi * pow(bigint(10), trunc + 5) * 2;
    for(int i = 0; i <= M; i++)
        pi = pi / (2 * i + 1);
    stringstream sout;
    sout << pi;
    string s = sout.str();

    printf("3.\n");
    for(int i = 1; i <= trunc; i += 50){
        for(int j = 1; j <= 50 && i + j - 1 <= trunc; j++){
            putchar(s[i + j - 1]);
            if(j % 10 == 0) printf(" ");
        }
        putchar('\n');
    }
    return 0;
}