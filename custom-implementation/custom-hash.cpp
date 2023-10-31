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

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

void solve() {
	int n, x, y;
	cin >> n >> x >> y;
	vi a(n);
	for(int i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<vi> moves(2);
	for(int i = 0; i < n; i++) {
		moves[i % 2].push_back(a[i]);
	}
	auto check = [&](vi& v, int sum) -> int {
		int m = sz(v), h1 = m / 2, h2 = m - h1;
		unordered_map<int, int, custom_hash> m1, m2;
		for(int x = 0; x < (1 << h1); x++) {
			int net = 0;
			for(int i = 0; i < h1; i++) {
				if((1 << i) & x) net += v[i + h2];
				else net -= v[i + h2];
			}
			m1[net] = x << h2;
		}
		for(int x = 0; x < (1 << h2); x++) {
			int net = 0;
			for(int i = 0; i < h2; i++) {
				if((1 << i) & x) net += v[i];
				else net -= v[i];
			}
			m2[net] = x;
		}
		for(auto& [s, x]: m1) {
			if(m2.find(sum - s) != m2.end()) return m1[s] + m2[sum - s];
		}
		return -1;
	};
	int nx = sz(moves[1]), ny = sz(moves[0]);
	int rx = check(moves[1], x), ry = check(moves[0], y);
	if(rx == -1 || ry == -1) return void(cout << "No");
	cout << "Yes\n";
	auto get = [&](int x, int n) {
		vi ans(n);
		for(int j = 0; j < n; j++) {
			if((1LL << j) & x) ans[j] = 1;
			else ans[j] = -1;
		}
		return ans;
	};
	vi mx = get(rx, nx), my = get(ry, ny);
	string s1 = bitset<64>(rx).to_string(), s2 = bitset<64>(ry).to_string();
	int sx = 0, sy = 0;
	for(int i = 0; i < nx; i++) {
		sx += moves[1][i] * mx[i];
	}
	for(int i = 0; i < ny; i++) {
		sy += moves[0][i] * my[i];
	}
	assert(sx == x && sy == y);
	string ans(n, '.');
	for(int i = 0; i < sz(mx); i++) {
		ans[i * 2 + 1] = mx[i] * my[i] < 0 ? 'L' : 'R';
	}
	for(int i = 1; i < sz(my); i++) {
		ans[i * 2] = my[i] * mx[i - 1] > 0 ? 'L' : 'R';
	}
	ans[0] = my[0] > 0 ? 'L' : 'R';
	cout << ans;
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
