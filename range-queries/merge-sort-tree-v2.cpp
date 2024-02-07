// Author: vrintle (Rahul Verma)
// Problem: https://atcoder.jp/contests/abc339/tasks/abc339_g

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

const int N = 2e5 + 7;

vector<int> t[4 * N], sum[4 * N];

void build(vector<int>& a, int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = vector<int>(1, a[tl]);
        sum[v].push_back(0);
	sum[v].push_back(a[tl]);
    } else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        merge(t[v*2].begin(), t[v*2].end(), t[v*2+1].begin(), t[v*2+1].end(), back_inserter(t[v]));
	sum[v].push_back(0);
	for(int i = 0; i < sz(t[v]); i++) {
		sum[v].push_back(sum[v].back() + t[v][i]);
	}
    }
}

int query(int v, int tl, int tr, int l, int r, int x) {
    if (l > r)
        return 0;
    if (l == tl && r == tr) {
        auto k = upper_bound(t[v].begin(), t[v].end(), x) - t[v].begin();
        return sum[v][k];
    }
    int tm = (tl + tr) / 2;
    return query(v*2, tl, tm, l, min(r, tm), x) + query(v*2+1, tm+1, tr, max(l, tm+1), r, x);
}

void solve() {
	int n;
	cin >> n;
	vi a(n);
	for(int i = 0; i < n; i++) {
		cin >> a[i];
	}
	build(a, 1, 0, n - 1);
	int m, b = 0;
	cin >> m;
	rep(m) {
		int x, y, z;
		cin >> x >> y >> z;
		int l = x ^ b, r = y ^ b, k = z ^ b;
		l--; r--;
		// cerr << l << ' ' << r << ' ' << k << endl;
		b = query(1, 0, n - 1, l, r, k);
		cout << b << endl; 
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
