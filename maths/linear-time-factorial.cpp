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

const int N = 2e6 + 7, mod = 998244353;
int fac[N + 1], ifac[N + 1];
 
int power(int n, int k) {
	int ans = 1;
	for(int b = 0, res = n % mod; b < 36; b++, res = res * res % mod) {
		if((1LL << b) & k) ans = ans * res % mod;
	}
	return ans;
}
 
int inv(int n) { return power(n, mod - 2); }

void precum() {
	fac[0] = 1;
	for(int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[N] = inv(fac[N]);
	for(int i = N - 1; i >= 0; i--) {
		ifac[i] = ifac[i + 1] * (i + 1) % mod;
	}
}

int C(int n, int r) {
	if(n < r || r < 0) return 0;
	int num = fac[n], den = ifac[r] * ifac[n - r] % mod;
	return num * den % mod;
}

void solve() {
	int n, m, k;
	cin >> n >> m >> k;
	vi a(n);
	for(int i = 0; i < n; i++) {
		cin >> a[i];
	}
	map<int, int> cnt;
	for(int i = 0; i < k; i++) {
		int mx = 0, c = 0;
		for(int j = i; j < n; j += k) mx = max(mx, a[j]), c++;
		cnt[c]++;
		for(int j = i; j < n; j += k) {
			m -= mx - a[j];
			a[j] = mx;
		}
	}
	if(m < 0) return void(cout << 0);
	int ans = 0;
	int x = cnt.begin()->first, y = x + 1, u = cnt[x], v = cnt[y];
	for(int i = 0; i * x <= m; i++) {
		int j = (m - i * x) / y;
		int p1 = C(i + u - 1, i);
		int p2 = C(j + v, j);
		ans = (ans + p1 * p2) % mod;
	}
	cout << ans;
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
