// Author: vrintle (Rahul Verma)

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

template <typename T> using pbds = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// #define int int64_t
#define endl '\n'
#define sz(v) ((int) v.size())
#define all(v) v.begin(), v.end()
#define vi vector<int>
#define pii pair<int, int>

int max(int x, int y) { return x > y ? x : y; }
int min(int x, int y) { return x < y ? x : y; }

const int N = 2e5 + 7, L = 20;
vi g[N];
int a[N], tin[N], tout[N], up[N][L], dep[N];
array<int, 20> basis[N][L];

void add(int mask, array<int, 20>& basis) {
	for (int i = L - 1; i >= 0; i--) {
		if ((mask & 1 << i) == 0) continue; // continue if i != f(mask)
		if (!basis[i]) { // If there is no basis vector with the i'th bit set, then insert this vector into the basis
			basis[i] = mask;
			return;
		}
		mask ^= basis[i]; // Otherwise subtract the basis vector from this vector
	}
}

void merge(array<int, 20>& src, array<int, 20>& dst) {
	for(int i = 0; i < L; i++) {
		if(src[i]) add(src[i], dst);
	}
}

bool check(int mask, array<int, 20>& basis) {
	for (int i = L - 1; i >= 0; i--) {
		if (mask & 1 << i) mask ^= basis[i];
	} 
	return !mask;
}

void solve() {
	int n;
	cin >> n;
	for(int i = 0; i < n; i++) {
		cin >> a[i];
		for(int j = 0; j < L; j++) {
			basis[i][j].fill(0);
		}
	}
	for(int _ = 0; _ < n - 1; _++) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	int t = 0;
	function<void(int, int)> dfs = [&](int i, int p) -> void {
		tin[i] = t++;
		add(a[i], basis[i][0]);
		if(p != -1) {
			up[i][0] = p;
			for(int j = 1; j < L; j++) {
				up[i][j] = up[up[i][j - 1]][j - 1];
				basis[i][j] = basis[up[i][j - 1]][j - 1];
				merge(basis[i][j - 1], basis[i][j]);
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
	auto get = [&](int u, int d) {
		array<int, 20> ans;
		ans.fill(0);
		for(int i = L - 1; i >= 0; i--) {
			if(d & 1 << i) {
				merge(basis[u][i], ans);
				u = up[u][i];
			}
		}
		return ans;
	};
	int m;
	cin >> m;
	while(m--) {
		int u, v, k;
		cin >> u >> v >> k;
		u--; v--;
		int z = lca(u, v);
		array<int, 20> uz = get(u, dep[u] - dep[z] + 1);
		array<int, 20> vz = get(v, dep[v] - dep[z] + 1);
		merge(uz, vz);
		cout << (check(k, vz) ? "YES" : "NO") << endl;
	}
}

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t = 1;
	// cin >> t;
	while(t--) {
		solve();
		cout << endl;
		// cerr << endl;
	}
	return 0;
}

// PRE-SUBMIT CHECKLIST
// --------------------
//
// reset the global arrays
// more to be added...
