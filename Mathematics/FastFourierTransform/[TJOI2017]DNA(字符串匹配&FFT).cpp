#include "PolynomialFL.h"

string s, t;

void check(vector<int> &cnt, char c){
    int n = s.size(), m = t.size();
    Polynomial S(n - 1), T(m - 1);
    for(int i = 0; i < n; i++) S[i] = (s[i] == c);
    for(int i = 0; i < m; i++) T[i] = (t[i] == c);
    auto Q = S * T.reverse();
    for(int i = 0; i < n; i++)
        cnt[i] += round(Q[m - 1 + i]);
}

int work(){
    cin >> s >> t;
    if(t.size() > s.size()) return 0;
    vector<int> cnt(s.size());
    check(cnt, 'A');
    check(cnt, 'C');
    check(cnt, 'G');
    check(cnt, 'T');
    int ans = 0;
    for(int i = 0; i + t.size() <= s.size(); i++)
        if(cnt[i] >= t.size() - 3) ans++;
    return ans;
}

int main(){
    int T;
    cin >> T;
    while(T--)
        cout << work() << "\n";
    return 0;
}