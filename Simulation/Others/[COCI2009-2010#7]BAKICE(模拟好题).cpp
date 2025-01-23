#include <bits/stdc++.h>
#define sqr(x) ((x)*(x))
using namespace std;
typedef pair<int, int> pii;

const int N = 55;
int n, m;
char s[N][N];
vector<pii> cat, box;
bool found[N * N];
int mindis[N * N], cnt[N * N];

int dist2(const pii &a, const pii &b){
	return sqr(a.first - b.first) + sqr(a.second - b.second);
}

struct CatBoxPair{
	int catid, boxid, dist;
	CatBoxPair(int cid = 0, int bid = 0, int d = 0)
		: catid(cid), boxid(bid), dist(d) {}
	bool operator < (const CatBoxPair &rhs){
		return dist < rhs.dist;
	}
};
vector<CatBoxPair> cbp;

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i){
		scanf("%s", s[i]);
		for(int j = 0; j < m; ++j){
			if(s[i][j] == 'X') cat.emplace_back(i, j);
			if(s[i][j] == 'L') box.emplace_back(i, j);
		}
	}
	for(int i = 0; i < cat.size(); ++i)
		for(int j = 0; j < box.size(); ++j)
			cbp.emplace_back(i, j, dist2(cat[i], box[j]));
	sort(cbp.begin(), cbp.end());
	int ans = 0;
	memset(mindis, 0x3f, sizeof(mindis));
	for(auto &p : cbp){
		if(found[p.catid] || p.dist > mindis[p.boxid]) continue;
		mindis[p.boxid] = p.dist;
		found[p.catid] = 1;
		if(cnt[p.boxid] == 1) ++ans;
		++cnt[p.boxid];
	}
	cout << ans << endl;
    return 0;
}
