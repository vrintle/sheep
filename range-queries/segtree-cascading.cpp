// Author: vrintle (Rahul Verma)
// Problem: https://codeforces.com/contest/438/problem/D

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

template<typename T>
class segtree {
	public:
	vector<T> t;
	int n;
	T ldef, rdef;
	function<T(T, T)> fx;
	void build(int _n, T _ldef, T _rdef, function<T(T, T)> _fx) {
		n = 1;
		while(n < _n) n *= 2;
		ldef = _ldef, rdef = _rdef, fx = _fx;
		t.assign(n * 2, rdef);
		for(int i = n - 1; i > 0; i--) {
			t[i] = fx(t[i * 2], t[i * 2 + 1]);
		}
	}
	void update(int i, T v) {
		for(t[i += n] = v; i > 1; ) {
			i /= 2;
			t[i] = fx(t[i * 2], t[i * 2 + 1]);
		}
	}
	// this query is made on [l, r)
	T ask(int i, int tl, int tr, int l, int r) {
		if(tl >= r) return rdef;
		if(tr <= l) return ldef;
		if(l <= tl && tr <= r) {
			return t[i];
		}
		int tm = (tl + tr) >> 1;
		return fx(ask(i * 2, tl, tm, l, r), ask(i * 2 + 1, tm, tr, l, r));
	}
	T ask(int l, int r) {
		return ask(1, 0, n, l, r);
	}
	// this query is made on [l, r)
	int cascade(int i, int tl, int tr, int l, int r, T x) {
		if(tl >= r) return rdef;
		if(tr <= l) return ldef;
		if(t[i] > x) return ldef;
		if(tl + 1 == tr) return tl;
		int tm = (tl + tr) >> 1;
		T val = cascade(i * 2, tl, tm, l, r, x);
		if(val == ldef) return cascade(i * 2 + 1, tm, tr, l, r, x);
		return val;
	}
	int next_time(int i, T x) {
		return cascade(1, 0, n, i, n, x);
	}
};

#define a3 array<int, 3>

const int N = 1e5 + 7;
vector<pii> typ3[N];
vi typ2[N];

void solve() {
	int n, m;
	cin >> n >> m;
	vi a(n);
	for(int i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<a3> changes, typ1;
	vector<pii> srt2;
	segtree<int> st;
	st.build(m, inf, inf, [&](int x, int y) {
		return min(x, y);
	});
	for(int tm = 0; tm < m; tm++) {
		int t;
		cin >> t;
		if(t == 1) {
			int l, r;
			cin >> l >> r;
			l--;
			typ1.push_back({tm, l, r});
		} else if(t == 2) {
			int l, r, x;
			cin >> l >> r >> x;
			l--;
			typ2[tm] = {l, r, x};
			srt2.push_back({l, tm});
		} else {
			int i, x;
			cin >> i >> x;
			i--;
			typ3[i].push_back({tm, x});
		}
	}
	for(int i = 0; i < n; i++) {
		reverse(all(typ3[i]));
	}
	sort(all(srt2));
	priority_queue<pii, vector<pii>, greater<pii>> q;
	int j = 0;
	for(int i = 0; i < n; i++) {
		while(j < sz(srt2) && srt2[j].first <= i) {
			auto [l, tm] = srt2[j];
			vi v = typ2[tm];
			q.push({v[1], tm});
			st.update(tm, v[2]);
			j++;
		}
		while(sz(q) && q.top().first <= i) {
			auto [r, tm] = q.top();
			q.pop();
			st.update(tm, inf);
		}
		int tm = -1, val = a[i];
		while(1) {
			int t = st.next_time(tm, val);
			assert(t != tm);
			if(sz(typ3[i]) && typ3[i].back().first < t) {
				auto [tt, x] = typ3[i].back();
				t = tt;
				val = x;
				typ3[i].pop_back();
			} else if(t < inf) {
				val %= typ2[t][2];
			} else break;
			tm = t;
			changes.push_back({tm, i, val});
		}
	}
	sort(all(changes), [&](auto& x, auto& y) {
		return x[0] < y[0];
	});
	segtree<long long> sum;
	sum.build(n, 0, 0, [&](auto x, auto y) {
		return x + y;
	});
	for(int i = 0; i < n; i++) {
		sum.update(i, a[i]);
	}
	j = 0;
	for(auto& v: typ1) {
		int tm = v[0], l = v[1], r = v[2];
		while(j < sz(changes) && changes[j][0] <= tm) {
			a3 cv = changes[j];
			sum.update(cv[1], cv[2]);
			j++;
		}
		cout << sum.ask(l, r) << endl;
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
