#include <bits/stdc++.h>
using namespace std;

const int N = 6000010;
// len[p]: 节点 p 代表的串的长度
// cnt[p]: 节点 p 代表的串是几个串的后缀
int ch[N][26], prt[N], len[N], cnt[N], bef[N];
int lst = 1, tot = 1, T = 0;
char s[N];
int sum[N];
string str[N];

void insert(int c, int id)
{
	int np;
	if (ch[lst][c] && len[ch[lst][c]] == len[lst] + 1)
		np = lst = ch[lst][c];
	else
	{
		int p = lst; np = ++tot;
		len[np] = len[p] + 1;
		while (p && !ch[p][c]) ch[p][c] = np, p = prt[p];
		if (!p) prt[np] = 1;
		else
		{
			int q = ch[p][c];
			if (len[q] == len[p] + 1) prt[np] = q;
			else
			{
				bool fuck = 0;
				if (p == lst) fuck = 1, np = 0, tot--;
				int nq = ++tot;
				len[nq] = len[p] + 1;
				bef[nq] = bef[q];
				cnt[nq] = cnt[q];
				memcpy(ch[nq], ch[q], sizeof(ch[nq]));
				prt[nq] = prt[q];
				prt[q] = prt[np] = nq;
				while (ch[p][c] == q) ch[p][c] = nq, p = prt[p];
				if (fuck) np = nq;
			}
		}
		lst = np;
	}
}

void insert_string(char *s)
{
	str[++T] = s;
	int l = strlen(s);
	lst = 1;
	for (int i = 0; i < l; i++)
		insert(s[i] - 'a', T);
    int np = lst;
    while(np && bef[np] != T)
		++cnt[np], bef[np] = T, np = prt[np];
}

vector<int> kmp_getnext(const string &s)
{
	int n = s.length();
	vector<int> next(n);
	for (int i = 1, j = 0; i < n; i++)
	{
		while (j && s[i] != s[j]) j = next[j - 1];
		if (s[i] == s[j]) j++;
		next[i] = j;
	}
	return next;
}

int main()
{
	int n, C, mod, maxlen = 0;
    scanf("%d%d%d", &n, &C, &mod);
	for(int i = 1; i <= n; i++){
		scanf("%s", s);
        insert_string(s);
        maxlen = max(maxlen, (int)str[i].size());
    }
    vector<int> pw(maxlen + 1);
    pw[0] = 1;
    for (int i = 1; i <= maxlen; i++)
        pw[i] = 1ll * pw[i - 1] * C % mod;
    int ans = 0;

	for(int i = 1; i <= n; i++)
    {
        vector<int> tmpcnt(str[i].size(), 0);
        vector<int> diffcnt(str[i].size(), 0);
        auto nxt = kmp_getnext(str[i]);

        int now = 1;
        for (int j = 0; j < str[i].size(); j++)
        {
            int c = str[i][j] - 'a';
            now = ch[now][c];
            diffcnt[j] = tmpcnt[j] = cnt[now];
        }

        int zero = n;
        for (int j = (int)str[i].size() - 1; j >= 0; j--)
        {
            if (nxt[j]) diffcnt[nxt[j] - 1] -= tmpcnt[j];
            ans = (ans + 1ll * diffcnt[j] * pw[j + 1]) % mod;
            zero -= diffcnt[j];
        }
        ans = (ans + zero) % mod;
    }

    cout << ans << endl;
	return 0;
}