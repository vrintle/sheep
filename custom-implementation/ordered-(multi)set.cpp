// https://cses.fi/problemset/task/1076

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

class custom_pbds {
	public:
	vector<int> t;
	int n;
	custom_pbds(int _n): n(1) {
		while(n < _n) n *= 2;
		t.assign(n * 2, 0);
	}
	void update(int i, int v) {
		i += n;
		t[i] += v;
		for(; i > 1; ) {
			i /= 2;
			t[i] = t[i * 2] + t[i * 2 + 1];
		}
	}
	void insert(int i) { update(i, 1); }
	void erase(int i) { update(i, -1); }
	int ask(int i, int tl, int tr, int l, int r) {
		if(tl >= r || tr <= l) return 0;
		if(l <= tl && tr <= r) return t[i];
		int tm = (tl + tr) >> 1;
		return ask(i * 2, tl, tm, l, r) + ask(i * 2 + 1, tm, tr, l, r);
	}
	int order_of_key(int x) { return ask(1, 0, n, 0, x); }
	int cascade(int i, int tl, int tr, int x) {
		if(tl + 1 == tr) return tl;
		int tm = (tl + tr) >> 1;
		if(t[i * 2] >= x) return cascade(i * 2, tl, tm, x);
		return cascade(i * 2 + 1, tm, tr, x - t[i * 2]);
	}
	int find_by_order(int i) { return cascade(1, 0, n, i + 1); }
};

void solve() {
	int n, k;
	cin >> n >> k;
	vi a(n), compress;
	for(int i = 0; i < n; i++) {
		cin >> a[i];
		compress.push_back(a[i]);
	}
	sort(all(compress));
	auto it = unique(all(compress));
	compress.resize(distance(compress.begin(), it));
	int m = sz(compress);
	for(int i = 0; i < n; i++) {
		a[i] = lower_bound(all(compress), a[i]) - compress.begin();
	}
	custom_pbds s(m);
	for(int i = 0; i < k; i++) {
		s.insert(a[i]);
	}
	cout << compress[s.find_by_order((k - 1) / 2)] << ' ';
	for(int i = k; i < n; i++) {
		s.erase(a[i - k]);
		s.insert(a[i]);
		cout << compress[s.find_by_order((k - 1) / 2)] << ' ';
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
	}
	return 0;
}
