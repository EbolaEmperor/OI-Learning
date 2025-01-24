#include <bits/stdc++.h>
#include "bigint.h"
using namespace std;

int main(){
    bigint a, b;
    cin >> a >> b;
    cout << gcd(std::move(a), std::move(b)) << endl;
    return 0;
}