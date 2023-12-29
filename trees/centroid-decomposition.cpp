// Author: vrintle (Rahul Verma)
// https://codeforces.com/contest/342/problem/E

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

const int N = 1e5 + 7, L = 17;
vi g[N];
int up[N][L], tin[N], tout[N], cnt[N], q[N][2], dep[N];

void solve() {
	int n, m;
	cin >> n >> m;
	vi par(n, -1);
	for(int _ = 0; _ < n - 1; _++) {
 		int u, v;
		cin >> u >> v;
		u--; v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i = 0; i < m; i++) {
		cin >> q[i][0] >> q[i][1];
		q[i][1]--;
	}
	function<void(int, int)> dfs_1 = [&](int i, int p) -> void {
		// dfs_1: to find size
		cnt[i] = 1;
		for(auto& e: g[i]) {
			if(e == p || ~par[e]) continue;
			dfs_1(e, i);
			cnt[i] += cnt[e];
		}
	};
	function<int(int, int, int)> dfs_2 = [&](int i, int p, int r) {
		for(auto& e: g[i]) {
			if(e == p || ~par[e]) continue;
			if(cnt[e] * 2 > cnt[r]) return dfs_2(e, i, r);
		}
		return i;
	};
	function<void(int, int)> decompose = [&](int i, int p) -> void {
		// decompose into centroid tree
		dfs_1(i, p);
		int ct = dfs_2(i, p, i);
		par[ct] = ~p ? p : ct;
		for(auto& e: g[ct]) {
			if(e == p || ~par[e]) continue;
			decompose(e, ct);
		}
	};
	decompose(0, -1);
	int t = 0;
	function<void(int, int)> dfs = [&](int i, int p) -> void {
		tin[i] = t++;
		if(p != -1) {
			up[i][0] = p;
			for(int j = 1; j < L; j++) {
				up[i][j] = up[up[i][j - 1]][j - 1];
			}
		}
		for(auto& v: g[i]) {
			if(v != p) {
				dep[v] = dep[i] + 1;
				dfs(v, i);
			}
		}
		tout[i] = t++;
	};
	dfs(0, -1);
	auto is = [&](int u, int v) {
		return tin[u] <= tin[v] && tout[u] >= tout[v];
	};
	auto lca = [&](int u, int v) {
		if(is(u, v)) return u;
		if(is(v, u)) return v;
		for(int j = L - 1; j >= 0; j--) {
			if(!is(up[u][j], v)) u = up[u][j];
		}
		return up[u][0];
	};
	auto dist = [&](int u, int v) {
		return dep[u] + dep[v] - 2 * dep[lca(u, v)];
	};
	vi dp(n, inf);
	auto update = [&](int u) {
		int i = u;
		while(1) {
			dp[i] = min(dp[i], dist(i, u));
			if(i == par[i]) break;
			i = par[i];
		}
	};
	auto query = [&](int u) {
		int i = u, ans = dp[i];
		while(i != par[i]) {
			i = par[i];
			ans = min(ans, dist(i, u) + dp[i]);
		}
		return ans;
	};
	update(0);
	for(int i = 0; i < m; i++) {
		int t = q[i][0], u = q[i][1];
		if(t == 1) update(u);
		else cout << query(u) << endl;
	}	
}

int32_t main() {
	int t = 1;
	// cin >> t;
	for(int i = 1; i <= t; i++) {
		// cout << "Case #" << i << ": ";
		solve();
		cout << endl;
		// cerr << endl;
	}
	return 0;
}
