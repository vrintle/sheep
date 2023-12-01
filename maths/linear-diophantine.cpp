// Author: vrintle (Rahul Verma)
// Problem: https://codeforces.com/contest/1728/problem/E

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

int find_all_solutions(int a, int b, int c, int minx, int maxx, int miny, int maxy) {
    int x, y, g;
    if (!find_any_solution(a, b, c, x, y, g))
        return 0;
    a /= g;
    b /= g;

    int sign_a = a > 0 ? +1 : -1;
    int sign_b = b > 0 ? +1 : -1;

    shift_solution(x, y, a, b, (minx - x) / b);
    if (x < minx)
        shift_solution(x, y, a, b, sign_b);
    if (x > maxx)
        return 0;
    int lx1 = x;

    shift_solution(x, y, a, b, (maxx - x) / b);
    if (x > maxx)
        shift_solution(x, y, a, b, -sign_b);
    int rx1 = x;

    shift_solution(x, y, a, b, -(miny - y) / a);
    if (y < miny)
        shift_solution(x, y, a, b, -sign_a);
    if (y > maxy)
        return 0;
    int lx2 = x;

    shift_solution(x, y, a, b, -(maxy - y) / a);
    if (y > maxy)
        shift_solution(x, y, a, b, sign_a);
    int rx2 = x;

    if (lx2 > rx2)
        swap(lx2, rx2);
    int lx = max(lx1, lx2);
    int rx = min(rx1, rx2);

    if (lx > rx)
        return 0;
    return (rx - lx) / abs(b) + 1;
}

void solve() {
	int n, m;
	cin >> n;
	vector<vi> a(n, vi(2));
	vi rsum(n + 1), bsum(n + 1);
	for(int i = 0; i < n; i++) {
		cin >> a[i][0] >> a[i][1];
	}
	sort(all(a), [&](auto& x, auto& y) {
		return x[0] - x[1] > y[0] - y[1];
	});
	for(int i = 0; i < n; i++) {
		rsum[i + 1] = rsum[i] + a[i][0];
	}
	reverse(all(a));
	for(int i = 0; i < n; i++) {
		bsum[i + 1] = bsum[i] + a[i][1];
	}
	reverse(all(a));
	//for(int i = 1; i <= n; i++) {
		//cerr << i << ": " << rsum[i] << ' ' << bsum[i] << endl;
	//}
	int red = 0;
	for(int i = 0; i < n; i++) {
		if(a[i][0] - a[i][1] >= 0) red++;
	}
	cin >> m;
	while(m--) {
		int x, y;
		cin >> x >> y;
		int kt = find_all_solutions(x, y, n, 0, n / x, 0, n / y);
		//cerr << "total sol: " << kt << endl;
		int ans = -inf;
		// finding max k for which all red positive
		{
			int low = 0, high = red / x;
			auto check = [&](int k) {
				return find_all_solutions(x, y, n, k, red / x, 0, n / y);
			};
			while(high - low > 1) {
				int mid = (high + low) / 2;
				if(check(mid)) {
					low = mid;
				} else high = mid;
			}
			int k = check(high) ? high : low;
			//cerr << k << endl;
			if(find_all_solutions(x, y, n, k, k, 0, n / y)) {
				int s1 = x * k, s2 = n - s1;
				//cerr << s1 << ' ' << s2 << ": " << rsum[s1] << ' ' << bsum[s2] << endl;
				assert(s2 % y == 0);
				ans = max(ans, rsum[s1] + bsum[s2]);
			}			
		}
		// finding min k for which some red negative
		{
			int low = (red + x - 1) / x, high = n / x;
			auto check = [&](int k) {
				return find_all_solutions(x, y, n, (red + x - 1) / x, k, 0, n / y);
			};
			while(high - low > 1) {
				int mid = (high + low) / 2;
				if(check(mid)) {
					high = mid;
				} else low = mid;
			}
			int k = check(low) ? low : high;
			//cerr << k << endl;
			if(find_all_solutions(x, y, n, k, k, 0, n / y)) {
				int s1 = x * k, s2 = n - s1;
				//cerr << s1 << ' ' << s2 << ": " << rsum[s1] << ' ' << bsum[s2] << endl;
				assert(s2 % y == 0);
				ans = max(ans, rsum[s1] + bsum[s2]);
			}			
		}
		cout << (ans == -inf ? -1 : ans) << endl;
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
		// cerr << endl;
	}
	return 0;
}

// PRE-SUBMIT CHECKLIST
// --------------------
//
// reset the global arrays
// more to be added...
