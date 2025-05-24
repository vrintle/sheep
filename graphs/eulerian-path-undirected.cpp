// Author: vrintle (Rahul Verma)
// Concept: Eulerian Path in Undirected Graph
// Problem: https://codeforces.com/contest/2110/problem/E

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
#define loop(n, i) for(int i = 0; i < n; i++)
#define ff first
#define ss second
#define pb push_back
#define pc __builtin_popcountll

// Debug Template, copied from Mikel_Arteta_8 (https://codeforces.com/blog/entry/68809)
void __print(int x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifdef VRINTLE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif
// End of debugging template

int max(int x, int y) { return x > y ? x : y; }
int min(int x, int y) { return x < y ? x : y; }

void solve() {
	int n;
	cin >> n;
	vector<pii> a(n);
	set<int> v, p;
	map<pii, int> idx;
	loop(n, i) {
		cin >> a[i].ff >> a[i].ss;
		v.insert(a[i].ff);
		p.insert(a[i].ss);
	}
	int m1 = sz(v), m2 = sz(p);
	vi vv(all(v)), pp(all(p));
	map<int, int> vo, po;
	for(int i = 0; i < m1; i++) {
		vo[vv[i]] = i;
	}
	for(int i = 0; i < m2; i++) {
		po[pp[i]] = i;
	}
	vector<set<pii>> g(m1 + m2);
	for(int i = 0; i < n; i++) {
		int x = vo[a[i].ff], y = m1 + po[a[i].ss];
		g[x].insert({y, i});
		g[y].insert({x, i});
		idx[{x, y}] = i;
	}
	int c = 0, start = 0;
	for(int i = 0; i < m1 + m2; i++) {
		if(sz(g[i]) % 2) {
			start = i;
			c++;
		}		
	}
	if(c != 0 && c != 2) return void(cout << "NO");
	vi ans;
	function<void(int)> euler = [&](int u) {
		while(sz(g[u])) {
			auto& [v, i] = *g[u].begin();
			g[u].erase({v, i});
			g[v].erase({u, i});
			euler(v);
		}
		ans.push_back(u);
	};
	euler(start);
	if(sz(ans) != n + 1) return void(cout << "NO");
	cout << "YES\n";
	for(int i = 0; i < n; i++) {
		int f = ans[i], s = ans[i + 1];
		if(f > s) swap(f, s);
		cout << idx[{f, s}] + 1 << ' ';
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
	cin >> t;
	while(t--) {
		solve();
		cout << endl;
		// cerr << endl;
	}
	return 0;
}
