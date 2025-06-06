#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;
vector<int> G[MAXN];
int ch[MAXN][26], prt[MAXN];
int len[MAXN], sz[MAXN], minend[MAXN];
int lst = 1, tot = 1;
char s[MAXN];

void insert(int c, int pos)
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
	sz[np] = 1;
    minend[np] = pos;
	lst = np;
}

void dfs(int u, int fa)
{
    if (!minend[u]) minend[u] = INT_MAX;
	for (int v : G[u])
	{
		if (v == fa) continue;
		dfs(v, u);
        sz[u] += sz[v];
        minend[u] = min(minend[u], minend[v]);
	}
}

void clear()
{
    for (int i = 1; i <= tot; ++i) {
        G[i].clear();
        memset(ch[i], 0, sizeof(ch[i]));
        prt[i] = 0;
        len[i] = sz[i] = minend[i] = 0;
    }
    lst = tot = 1;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        scanf("%s", s + 1);
        int n = strlen(s + 1);
        for (int i = 1; i <= n; ++i)
            insert(s[i] - 'a', i);
        for (int i = 2; i <= tot; ++i)
            G[prt[i]].push_back(i);
        dfs(1, 0);
        int ans = n / 2;
        for (int i = 1; i <= tot; ++i)
            if (sz[i] > 1)
                ans = max(ans, len[i] + (n - minend[i]) / 2);
        cout << ans << "\n";
        if (T) clear();
    }
    return 0;
}