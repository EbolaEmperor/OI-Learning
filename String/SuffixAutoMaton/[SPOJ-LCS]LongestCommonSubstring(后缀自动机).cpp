#include <iostream>
#include <cstring>
using namespace std;

typedef long long LL;
const int MAXN = 500010;
int ch[MAXN][26], prt[MAXN], len[MAXN];
int lst = 1, tot = 1;
char s[MAXN], t[MAXN];

void insert(int c)
{
    int p = lst, np = ++tot;
    len[np] = len[p] + 1;
    while (p && !ch[p][c])
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
            memcpy(ch[nq], ch[q], sizeof(ch[nq]));
            prt[nq] = prt[q];
            prt[q] = prt[np] = nq;
            while (ch[p][c] == q)
                ch[p][c] = nq, p = prt[p];
        }
    }
    lst = np;
}

int main() {
    scanf("%s%s", s + 1, t + 1);
    int n = strlen(s + 1), m = strlen(t + 1);
    for(int i = 1; i <= n; i++) insert(s[i] - 'a');

    int cur = 1, ans = 0, cans = 0;
    for(int i = 1; i <= m; i++) {
        int c = t[i] - 'a';
        while(!ch[cur][c] && cur != 1)
            cur = prt[cur], cans = len[cur];
        if(ch[cur][c])
            cur = ch[cur][c], ++cans;
        // 注意由于 SAM 压缩机制的存在，这里不能直接和 len[cur] 取 max，必须维护一个 cans
        ans = max(ans, cans);
    }
    cout << ans << endl;
    return 0;
}