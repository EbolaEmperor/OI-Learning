#include <bits/stdc++.h>
using namespace std;

int n, col, diag, codiag;
vector<int> board;
int cnt = 0;

void solve(int row) {
    if (row == n) {
        cnt++;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i] == j) cout << "Q ";
                else cout << ". ";
            }
            cout << "\n";
        }
        cout << "\n";
        return;
    }
    for (int j = 0; j < n; ++j) {
        if ((col & (1 << j)) || 
            (diag & (1 << (row + j))) || 
            (codiag & (1 << (row - j + n - 1)))) continue;
        board[row] = j;
        col |= (1 << j);
        diag |= (1 << (row + j));
        codiag |= (1 << (row - j + n - 1));
        solve(row + 1);
        col ^= (1 << j);
        diag ^= (1 << (row + j));
        codiag ^= (1 << (row - j + n - 1));
    }
}

int main() {
    cin >> n;
    col = diag = codiag = 0;
    board.resize(n);
    solve(0);
    cout << "Total solutions: " << cnt << "\n";
    return 0;
}

/*
目前人类已经计算出的极限是 27，表格如下
(来源: https://oeis.org/A000170)
n	a(n)
0	1
1	1
2	0
3	0
4	2
5	10
6	4
7	40
8	92
9	352
10	724
11	2680
12	14200
13	73712
14	365596
15	2279184
16	14772512
17	95815104
18	666090624
19	4968057848
20	39029188884
21	314666222712
22	2691008701644
23	24233937684440
24	227514171973736
25	2207893435808352
26	22317699616364044
27	234907967154122528
*/