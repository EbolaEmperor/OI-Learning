### Algorithm 1. $O(n^2)$

```cpp
int LIS(int *a, int n)
{
	int ans = 0;
	for(int i = 0; i < n; i++)
	{
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
int LIS(int *a, int n)
{
    int ans = 0;
    int *g = new int[n];
    memset(g, 0x7f, sizeof(int) * (n));
    for(int i = 0; i < n; i++)
    {
        int p = lower_bound(g, g + ans, a[i]) - g;
        ans = max(ans, p + 1);
        g[p] = a[i];
    }
    delete[] g;
    return ans;
}
```
