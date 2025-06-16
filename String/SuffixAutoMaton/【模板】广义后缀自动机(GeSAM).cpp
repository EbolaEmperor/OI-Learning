#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

const int N = 2000010;
// len[p]: 节点 p 代表的串的长度
int ch[N][26], prt[N], len[N];
int lst = 1, tot = 1, T = 0;
char s[N];
int sum[N];
string str[N];

void insert(int c) {
	int p = lst, np = ++tot;
	len[np] = len[p] + 1;
	while (p && !ch[p][c])
		ch[p][c] = np, p = prt[p];
	if (!p) prt[np] = 1;
	else {
		int q = ch[p][c];
		if (len[p] + 1 == len[q]) prt[np] = q;
		else {
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

void insert_string(char *s)
{
	str[++T] = s;
	int l = strlen(s);
	lst = 1;
	for (int i = 0; i < l; i++)
		insert(s[i] - 'a');
}

// 统计有多少个有用的节点（如果从 1 出发无法到达，就是没用的）
int bfs() {
	static bool vis[N];
	queue<int> q;
	q.push(1);
	int ans = 1;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int j = 0; j < 26; j++)
			if(ch[u][j] && !vis[ch[u][j]]) {
				vis[ch[u][j]] = true;
				q.push(ch[u][j]), ++ans;
			}
	}
	return ans;
}

int main()
{
	int n; scanf("%d", &n);
	while(n--) scanf("%s", s), insert_string(s);
	long long ans = 0;
	for (int i = 1; i <= tot; i++)
		ans += len[i] - len[prt[i]];
	printf("%lld\n", ans);
	printf("%d\n", bfs());
	return 0;
}