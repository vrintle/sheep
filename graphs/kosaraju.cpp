#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

template <typename T> using pbds = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int int64_t
#define endl '\n'
#define sz(v) ((int) v.size())
#define all(v) v.begin(), v.end()
#define vi vector<int>
#define pii pair<int, int>
#define inf 2e18

int max(int x, int y) { return x > y ? x : y; }
int min(int x, int y) { return x < y ? x : y; }

const int N = 2e5 + 7, mod = 998244353;

int power(int n, int k) {
	int ans = 1;
	for(int b = 0, res = n % mod; b < 36; b++, res = res * res % mod) {
		if((1LL << b) & k) ans = ans * res % mod;
	}
	return ans;
}
 
int inv(int n) { return power(n, mod - 2); }

vi g[N], g_rev[N], order, component;
vector<bool> used;
int a[N];

void solve() {
	function<void(int)> dfs1 = [&](int v) {
		used[v] = true;
		for(auto u: g[v]) {
			if(!used[u]) {
				dfs1(u);
			}
		}
		order.push_back(v);
	};
	function<void(int)> dfs2 = [&](int v) {
		used[v] = true;
		component.push_back(v);
		for(auto u: g_rev[v]) {
			if(!used[u]) {
				dfs2(u);
			}
		}
	};
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < n; i++) {
		cin >> a[i];
		g[i].clear();
		g_rev[i].clear();
	}
	for(int _ = 0; _ < m; _++) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		g[u].push_back(v);
		g_rev[v].push_back(u);
	}
	used.assign(n, false);
	for(int i = 0; i < n; i++) {
		if(!used[i]) {
			dfs1(i);
		}
	}
	used.assign(n, false);
	reverse(order.begin(), order.end());
	vi roots(n, 0), root_nodes;
	vector<vi> g_scc(n);
	for(auto v : order) {
		if(!used[v]) {
			dfs2(v);
			int root = component.front();
			for(auto u: component) roots[u] = root;
			root_nodes.push_back(root);
			component.clear();
		}
	}
	for(int v = 0; v < n; v++) {
		for(auto u: g[v]) {
			int root_v = roots[v],
			root_u = roots[u];
			if(root_u != root_v) {
				g_scc[root_v].push_back(root_u);
			} 
		}	
	}
	vi indeg(n), cnt(n);
	for(int i = 0; i < n; i++) {
		cnt[roots[i]]++;
	}
	int ways = 1, num = 0;
	for(int r: root_nodes) {
		for(auto& u: g_scc[r]) {
			indeg[u]++;
		}
	}
	for(int i: root_nodes) {
		if(indeg[i]) continue;
		ways = ways * cnt[i] % mod;
	}
	for(int i = 0; i < n; i++) {
		int r = roots[i];
		if(indeg[r]) continue;
		int other = ways * inv(cnt[r]) % mod;
		num = (num + other * a[i]) % mod;
	}
	cout << num * inv(ways) % mod;
}

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t = 1;
	// cin >> t;
	while(t--) {
		solve();
		cout << endl;
	}
	return 0;
}
