// Author: vrintle (Rahul Verma)

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
#define ff first
#define ss second

int max(int x, int y) { return x > y ? x : y; }
int min(int x, int y) { return x < y ? x : y; }

void solve() {
	
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
