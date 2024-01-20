// Author: vrintle (Rahul Verma)

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
vi g[N];
pbds<int>* s[N];
int tin[N], tout[N];

void solve() {
	int n;
	cin >> n;
	for(int _ = 0; _ < n - 1; _++) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	int t = 0;
	function<void(int, int)> dfs0 = [&](int i, int p) -> void {
		tin[i] = t++;
		for(auto& v: g[i]) {
			if(v != p) {
				dfs0(v, i);
			}
		}
		tout[i] = t++;
	};
	dfs0(0, -1);
	vi pfx(n * 2);
	function<void(int, int)> dfs = [&](int i, int p) -> void {
		s[i] = new pbds<int>();
		int mx = 0, big = i;
		for(auto& e: g[i]) {
			if(e != p) {
				dfs(e, i);
				if((int) s[e]->size() > mx) mx = s[e]->size(), big = e;
			}
		}
		if(big != i) {
			int r = s[big]->order_of_key(i);
			pfx[0] += r; pfx[tin[big]] -= r;
			pfx[tout[big]] += r; pfx[2 * n - 1] -= r;
			s[i] = s[big];
		}
		s[i]->insert(i);
		for(auto& e: g[i]) {
			if(e != p && e != big) {
				int r = s[e]->order_of_key(i);
				pfx[0] += r; pfx[tin[e]] -= r;
				pfx[tout[e]] += r; pfx[2 * n - 1] -= r;
				for(auto it = s[e]->begin(); it != s[e]->end(); it++) {
					s[i]->insert(*it);
				}
			}
		}
		int out = i - s[i]->order_of_key(i);
		pfx[tin[i]] += out;
		pfx[tout[i]] -= out;
	};
	dfs(0, -1);
	for(int i = 1; i < n * 2; i++) {
		pfx[i] += pfx[i - 1];
	}
	for(int i = 0; i < n; i++) {
		cout << pfx[tin[i]] << ' ';
	}
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
	// cin >> t;
	while(t--) {
		solve();
		cout << endl;
		// cerr << endl;
	}
	return 0;
}
