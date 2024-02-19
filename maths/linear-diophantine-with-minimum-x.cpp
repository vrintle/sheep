// Author: vrintle (Rahul Verma)
// Problem: https://codeforces.com/problemset/problem/1932/G

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

int gcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

void shift_solution(int & x, int & y, int a, int b, int cnt) {
    x += cnt * b;
    y -= cnt * a;
}

int min_time(int a, int b, int c, int mnx) {
	int x, y, g;
	bool exists = find_any_solution(a, b, c, x, y, g);
	if(!exists) return -1;
	// cerr << a << ' ' << b << ' ' << c << ' ' << x << ' ' << y << ' ' << g << endl;
	a /= g;
	b /= g;
	int sign_a = a > 0 ? +1 : -1;
	int sign_b = b > 0 ? +1 : -1;
	shift_solution(x, y, a, b, (mnx - x) / b);
	if(x < mnx) {
		shift_solution(x, y, a, b, sign_b);
	}
	return x;
}

const int N = 1e5 + 7;
int l[N], s[N], ans[N];
vi g[N];

void solve(int tc) {
	int n, m, h;
	cin >> n >> m >> h;
	for(int i = 0; i < n; i++) {
		cin >> l[i];
		g[i].clear();
		ans[i] = inf;
	}
	for(int i = 0; i < n; i++) {
		cin >> s[i];
	}
	rep(m) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	priority_queue<pii, vector<pii>, greater<pii>> q;
	ans[0] = 0;
	q.push({0, 0});
	while(sz(q)) {
		auto [t, u] = q.top();
		q.pop();
		if(t != ans[u]) continue;
		// cerr << t << ' ' << u << endl;
		for(auto& v: g[u]) {
			int rs = (s[v] - s[u] + h) % h, rl = (l[v] - l[u] + h) % h;
			int tt = min_time(rs, -h, -rl, t);
			if(tt == -1) continue;
			// cerr << u << ' ' << v << ": " << tt << endl;
			int nt = tt + 1;
			if(ans[v] > nt) {
				ans[v] = nt;
				q.push({nt, v});
			}
		}
	}
	cout << (ans[n - 1] == inf ? -1 : ans[n - 1]);
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
	for(int i = 1; i <= t; i++) {
		solve(i);
		cout << endl;
	}
	return 0;
}
