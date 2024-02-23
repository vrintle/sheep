// Author: vrintle (Rahul Verma)
// Problem: https://codeforces.com/contest/1923/problem/E

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
#define rep(n) for(int _ = 0; _ < n; _++)

int max(int x, int y) { return x > y ? x : y; }
int min(int x, int y) { return x < y ? x : y; }

const int N = 2e5 + 7, L = 20;
vi g[N], idx[N], aux[N];
int a[N], tin[N], tout[N], up[N][L], cnt[N];

void solve() {
	int n;
	cin >> n;
	for(int i = 0; i < n; i++) {
		g[i].clear();
		idx[i].clear();
		for(int j = 0; j < L; j++) up[i][j] = 0;
	}
	for(int i = 0; i < n; i++) {
		cin >> a[i];
		a[i]--;
		idx[a[i]].push_back(i);
	}
	int t = 0, ans = 0;
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
				dfs(v, i);
			}
		}
		tout[i] = t++;
	};
	rep(n - 1) {
 		int u, v;
		cin >> u >> v;
		u--; v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
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
	for(int c = 0; c < n; c++) {
		if(sz(idx[c]) == 0) continue;
		vi vx;
		for(auto& u: idx[c]) vx.push_back(u);	
		sort(all(vx), [&](int u, int v) {
			return tin[u] < tin[v];
		});
		int m = sz(vx);
		for(int i = 1; i < m; i++) vx.push_back(lca(vx[i - 1], vx[i]));
		sort(all(vx), [&](int u, int v) {
			return tin[u] < tin[v];
		});
		vi _vx {vx[0]};
		for(int i = 1; i < sz(vx); i++) {
			if(vx[i] != _vx.back()) _vx.push_back(vx[i]);
		}
		swap(_vx, vx);
		m = sz(vx);
		for(int i = 0; i < m; i++) {
			aux[vx[i]].clear();
			cnt[vx[i]] = 0;
		}
		stack<int> s;
		s.push(vx[0]);
		for(int i = 1; i < m; i++) {
			while(sz(s) && !is(s.top(), vx[i])) s.pop();
			assert(sz(s));
			aux[s.top()].push_back(vx[i]);
			s.push(vx[i]);
		}
		function<void(int, int)> dfs2 = [&](int i, int p) {
			vi ch;
			int sum = 0;
			for(auto& v: aux[i]) {
				dfs2(v, i);
				ch.push_back(cnt[v]);
				sum += cnt[v];
			}
			if(a[i] == c) {
				cnt[i] = 1;
				for(auto& e: ch) ans += e;
			} else {
				cnt[i] = sum;
				for(auto& e: ch) {
					sum -= e;
					ans += e * sum;
				}
			}
		};
		dfs2(vx[0], -1);
	}
	cout << ans;
}

// PRE-SUBMIT CHECKLIST
// --------------------
//
// -- reset the global arrays
// -- sort vector of vectors carefully
// more to be added...

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t = 1;
	cin >> t;
	while(t--) {
		solve();
		cout << endl;
		// cerr << endl;
	}
	return 0;
}
