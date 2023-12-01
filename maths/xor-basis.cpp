// Author: vrintle (Rahul Verma)
// Problem: https://codeforces.com/contest/845/problem/G

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

const int N = 1e5 + 7, L = 30;
vector<pii> g[N];
int xr[N], vis[N];

// xor basis (or gaussian elimination, god knows...)
int basis[L]; // basis[i] keeps the mask of the vector whose f value is i
int sz; // Current size of the basis

void insertVector(int mask) {
	for (int i = L - 1; i >= 0; i--) {
		if ((mask & 1 << i) == 0) continue; // continue if i != f(mask)
		if (!basis[i]) { // If there is no basis vector with the i'th bit set, then insert this vector into the basis
			basis[i] = mask;
			++sz;
			return;
		}
		mask ^= basis[i]; // Otherwise subtract the basis vector from this vector
	}
}

void solve() {
	int n, m;
	cin >> n >> m;
	for(int _ = 0; _ < m; _++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--; v--;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	vi cyc;
	function<void(int)> dfs = [&](int u) {
		vis[u] = 1;
		for(auto& [v, w]: g[u]) {
			if(!vis[v]) {
				xr[v] = w ^ xr[u];
				dfs(v);
			} else {
				// cycle detected
				cyc.push_back(w ^ xr[u] ^ xr[v]);
			}
		}
	};
	dfs(0);
	int ans = xr[n - 1];
	for(auto& x: cyc) {
		insertVector(x);
	}
	for(int i = L - 1; i >= 0; i--) {
		ans = min(ans, ans ^ basis[i]);
	}
	cout << ans;
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
