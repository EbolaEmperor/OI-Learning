#include <bits/stdc++.h>
#define popcnt __builtin_popcount
using namespace std;

const int N = 18, K = 1e5 + 5;
int n, k, a[K], honorWhom[N * K * 2], f[1 << N];

bool check(int day){
    memset(f, 0, sizeof(f));
    // f[s]: the number of days which can exactly honor all the friends in the set s. 
    for(int i = 0; i <= day; i++) f[honorWhom[i]]++;
    // Let f[s] = sum(f[t]) for all t the subset of s.
    for(int i = 0; i < n; i++)
        for(int s = 0; s < 1 << n; s++)
            if(s >> i & 1) f[s] += f[s ^ 1 << i];
    // Now f[s] is the number of days which can only honor some friends in the set s.
    //  --->  f[complement(s)] is the number of days which can never honor the set s,
    //        while other days may honor someone in the set s.
    for(int s = 0; s < 1 << n; s++)
        if(day + 1 - f[((1 << n) - 1) ^ s] < popcnt(s) * k) return false;
    return true;
}

int main(){
    cin >> n >> k;
    for(int i = 0; i < n; i++) cin >> a[i];
    int l = n * k - 1, r = 2 * n * k - 1, mid;
    for(int day = 0; day < r; day++){
        // honorWhom[day]: the friend who can be honored at this day.
        for(int i = 0; i < n; i++)
            if(day / a[i] % 2 == 0)
                honorWhom[day] |= 1 << i;
    }
    while(l < r){
        mid = (l + r) / 2;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l + 1 << endl;
    return 0;
}