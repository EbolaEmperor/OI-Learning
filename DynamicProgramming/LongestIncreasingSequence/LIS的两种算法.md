### Algorithm 1. $O(n^2)$

```cpp
int LIS(const vector<int> &a) {
	int ans = 0, n = a.size();
    vector<int> f(n, 0);
	for(int i = 0; i < n; i++) {
		f[i] = 1;
		for(int j = 0; j < i; j++)
			if(a[j] < a[i]) f[i] = max(f[i], f[j] + 1);
		ans = max(ans, f[i]);
	}
	return ans;
}
```

### Algorithm 2. $O(n log n)$

```cpp
int LIS(const vector<int> &a) {
    vector<int> g;
    for(int x : a) {
        int p = lower_bound(g.begin(), g.end(), x) - g.begin();
        if (p == g.size()) g.push_back(x);
        else g[p] = x;
    }
    return g.size();
}
```
