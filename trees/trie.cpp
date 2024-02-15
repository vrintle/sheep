// Author: vrintle (Rahul Verma)
// Problem: https://codeforces.com/contest/888/problem/G

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

struct Trie {
	Trie *l, *r;
	int cnt = 0;
	Trie() {
		l = r = nullptr;
		cnt = 0;
	}
};

const int N = 2e5 + 7, L = 31;
int a[N];
Trie* tr[N][L];

void insert(Trie* t, int x) {
	for(int j = L - 1; j >= 0; j--) {
		if(x & (1 << j)) {
			if(t->r == nullptr) t->r = new Trie();
			t = t->r;
		} else {
			if(t->l == nullptr) t->l = new Trie();
			t = t->l;
		}
		t->cnt++;
	}
}

int get_min(Trie* t, int x) {
	int ans = 0;
	for(int j = L - 1; j >= 0; j--) {
		if(x & (1 << j)) {
			if(t->r != nullptr && t->r->cnt > 0) t = t->r;
			else t = t->l, ans += 1 << j;
		} else {
			if(t->l != nullptr && t->l->cnt > 0) t = t->l;
			else t = t->r, ans += 1 << j;
		}
	}
	return ans;
}

int get_max(Trie* t, int x) {
	int ans = 0;
	for(int j = L - 1; j >= 0; j--) {
		if(x & (1 << j)) {
			if(t->l != nullptr && t->l->cnt > 0) t = t->l, ans += 1 << j;
			else t = t->r;
		} else {
			if(t->r != nullptr && t->r->cnt > 0) t = t->r, ans += 1 << j;
			else t = t->l;
		}
	}
	return ans;
}

Trie *merge(Trie *u, Trie *v) {
	if(u == nullptr) {
		return v;
	}
	if(v == nullptr) {
		return u;
	}
	u->l = merge(u->l, v->l);
	u->r = merge(u->r, v->r);
	delete v;
	return u;
}

void solve() {
	int n;
	cin >> n;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < L; j++) {
			tr[i][j] = nullptr;
		}
	}
	for(int i = 0; i < n; i++) {
		cin >> a[i];
	}
	sort(a, a + n);
	function<int(int, int, int, int)> recur = [&](int b, int l, int r, int mask) -> int {
		if(b < 0 || l == r) return 0;
		int m = lower_bound(a + l, a + r, mask | 1 << b) - a;
		int lsum = recur(b - 1, l, m, mask), rsum = recur(b - 1, m, r, mask | 1 << b), mn = inf;
		if(b == 0) {
			tr[l][0] = new Trie();
			for(int i = l; i < r; i++) {
				insert(tr[l][0], a[i]);
			}
			return m != l && m != r;
		}
		if(m == l || m == r) {
			tr[l][b] = tr[l][b - 1];
			return lsum + rsum;
		}
		if(m - l > r - m) {
			for(int i = m; i < r; i++) {
				mn = min(mn, get_min(tr[l][b - 1], a[i]));
			}
			tr[l][b] = merge(tr[l][b - 1], tr[m][b - 1]);
			return lsum + mn + rsum;
		}
		for(int i = l; i < m; i++) {
			mn = min(mn, get_min(tr[m][b - 1], a[i]));
		}
		tr[l][b] = merge(tr[l][b - 1], tr[m][b - 1]);
		return lsum + mn + rsum;
	};
	cout << recur(30, 0, n, 0);
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
