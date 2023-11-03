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

const int N = 2e5 + 7;
vector<pii> G[N];
vi g[N], gx[N], dag[N];

void solve() {
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < n; i++) {
		G[i].clear();
	}
	for(int _ = 0; _ < m; _++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--; v--;
		G[u].push_back({v, w});
	}
	int low = 0, high = 1e9;
	auto check = [&](int mx) {		
		for(int i = 0; i < n; i++) {
			g[i].clear();
			gx[i].clear();
			dag[i].clear();
		}
		for(int u = 0; u < n; u++) {
			for(auto& [v, w]: G[u]) {
				g[u].push_back(v);
				gx[v].push_back(u);
				if(w <= mx) {
					g[v].push_back(u);
					gx[u].push_back(v);
				}
			}
		}
		vi vis(n), order;
		function<void(int)> dfs1 = [&](int u) {
			vis[u] = 1;
			for(auto& v: g[u]) {
				if(!vis[v]) dfs1(v);
			}
			order.push_back(u);
		};
		for(int i = 0; i < n; i++) {
			if(!vis[i]) {
				dfs1(i);
			}
		}
		reverse(all(order));
		vis.assign(n, 0);
		int cmp = 0;
		vi vt;
		function<void(int)> dfs2 = [&](int u) {
			vis[u] = 1;
			vt.push_back(u);
			for(auto& v: gx[u]) {
				if(!vis[v]) dfs2(v);
			}
		};
		vi prt(n), cnt(n);
		for(auto& u: order) {
			if(!vis[u]) {
				dfs2(u);
				cnt[cmp] = sz(vt);
				for(auto& e: vt) {
					prt[e] = cmp;
				}
				vt.clear();
				cmp++;
			}
		}
		vi indeg(n);
		for(int u = 0; u < n; u++) {
			for(auto& v: g[u]) {
				if(prt[v] != prt[u]) {
					int x = prt[u], y = prt[v];
					dag[x].push_back(y);
					indeg[y]++;
				}
			}
		}
		int heads = 0;
		for(int i = 0; i < n; i++) {
			if(indeg[i] == 0 && cnt[i] > 0) {
				heads++;
			}
		}
		return heads == 1;
	};
	while(high - low > 1) {
		int mid = (high + low) / 2;
		if(check(mid)) high = mid;
		else low = mid;
	}
	int ans = check(low) ? low : high;
	cout << (ans == 1e9 ? -1 : ans);
}

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t = 1;
	cin >> t;
	while(t--) {
		solve();
		cout << endl;
	}
	return 0;
}
