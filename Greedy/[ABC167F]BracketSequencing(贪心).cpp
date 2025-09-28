#include <bits/stdc++.h>
using namespace std;

struct Bracket {
    int cntl, cntr;
    bool operator< (const Bracket& other) const {
        if (cntl > cntr && other.cntl <= other.cntr) return 1;
        if (cntl <= cntr && other.cntl > other.cntr) return 0;
        if (cntl > cntr && other.cntl > other.cntr) return cntr < other.cntr;
        return cntl > other.cntl;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector<Bracket> brackets(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (auto c : s) {
            if (c == '(') brackets[i].cntl++;
            else if (brackets[i].cntl > 0) brackets[i].cntl--;
            else brackets[i].cntr++;
        }
    }
    // 现在每个括号序列都型如 ))...))((..(
    sort(brackets.begin(), brackets.end());
    int balance = 0;
    for (int i = 0; i < n; i++) {
        balance -= brackets[i].cntr;
        if (balance < 0) {
            cout << "No\n";
            return 0;
        }
        balance += brackets[i].cntl;
    }
    cout << (balance == 0 ? "Yes\n" : "No\n");
    return 0;
}