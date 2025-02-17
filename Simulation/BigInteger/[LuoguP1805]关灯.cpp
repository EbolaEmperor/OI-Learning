#include <bits/stdc++.h>
#include "bigint.h"
using namespace std;

int main(){
    bigint f = 0, pw2 = 1;
    int n, x; cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> x;
        pw2 = pw2 * 2;
        if(x) f = pw2 - 1 - f;
    }
    cout << f << endl;
    return 0;
}