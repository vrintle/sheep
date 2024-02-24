// Author: vrintle (Rahul Verma)
// Problem: https://atcoder.jp/contests/abc342/tasks/abc342_g
// Template: https://cp-algorithms.com/data_structures/segment_tree.html#addition-on-segments

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

const int N = 1e6 + 7;
multiset<int> t[N];
int a[N];

void build(vi& a, int v, int tl, int tr) {
    if (tl == tr) {
        t[v].insert(a[tl]);
    } else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v].clear();
	t[v].insert(0);
    }
}

void update(int v, int tl, int tr, int l, int r, int x) {
    if (l > r)
        return;
    if (l == tl && r == tr) {
        if(x > 0) t[v].insert(x);
        else t[v].erase(t[v].find(-x));
    } else {
        int tm = (tl + tr) / 2;
        update(v*2, tl, tm, l, min(r, tm), x);
        update(v*2+1, tm+1, tr, max(l, tm+1), r, x);
    }
}

int get(int v, int tl, int tr, int pos) {
    if (tl == tr)
        return *t[v].rbegin();
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        return max(*t[v].rbegin(), get(v*2, tl, tm, pos));
    else
        return max(*t[v].rbegin(), get(v*2+1, tm+1, tr, pos));
}

void solve() {
	int n, m;
	cin >> n;
	vi a(n);
	for(int i = 0; i < n; i++) {
		cin >> a[i];
	}
	build(a, 1, 0, n - 1);
	cin >> m;
	vector<vi> info(m);
	for(int i = 0; i < m; i++) {
		int t;
		cin >> t;
		if(t == 1) {
			int l, r, x;
			cin >> l >> r >> x;
			l--; r--;
			info[i] = {l, r, x};
			update(1, 0, n - 1, l, r, x);
		} else if(t == 2) {
			int j;
			cin >> j;
			j--;
			int l = info[j][0], r = info[j][1], x = info[j][2];
			update(1, 0, n - 1, l, r, -x);
		} else {
			int j;
			cin >> j;
			j--;
			cout << get(1, 0, n - 1, j) << endl;
		}
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
