#include <iostream>
#include <map>
using namespace std;

typedef long long LL;
const int MAXN = 200010;
int prt[MAXN], len[MAXN];
map<int, int> ch[MAXN];
int lst = 1, tot = 1;
LL ans = 0;

void insert(int c)
{
    int p = lst, np = ++tot;
    len[np] = len[p] + 1;
    while (p && !ch[p].count(c))
        ch[p][c] = np, p = prt[p];
    if (!p) prt[np] = 1;
    else
    {
        int q = ch[p][c];
        if (len[p] + 1 == len[q]) prt[np] = q;
        else
        {
            int nq = ++tot;
            len[nq] = len[p] + 1;
            ch[nq] = ch[q];
            prt[nq] = prt[q];
            prt[q] = prt[np] = nq;
            while (ch[p].count(c) && ch[p][c] == q)
                ch[p][c] = nq, p = prt[p];
        }
    }
    lst = np;
    ans += len[lst] - len[prt[lst]];
}

int main() {
    int n, x;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> x;
        insert(x);
        cout << ans << "\n";
    }
    return 0;
}