// https://www.codechef.com/problems/PIARQ

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

const int N = 2e5 + 7, B = 690;
int a[N], ans[N], mn[N], mnb[B], li[N], ri[N], l, r;
vi lout[N], rout[N], lin[N], rin[N];
array<int, 3> q[N];

void add(int i, char side) {
	if(side == 'l') {
		while(sz(lout[i]) && lout[i].back() <= r) {
			int j = lout[i].back();
			lin[i].push_back(j);
			rin[j].push_back(i);
			lout[i].pop_back();
			rout[j].pop_back();
			int rem = j - i - 3;
			mn[rem]++;
			mnb[rem / B]++;
		}
	} else {
		while(sz(rout[i]) && rout[i].back() >= l) {
			int j = rout[i].back();
			rin[i].push_back(j);
			lin[j].push_back(i);
			rout[i].pop_back();
			lout[j].pop_back();
			int rem = i - j - 3;
			mn[rem]++;
			mnb[rem / B]++;
		}
	}
}

void del(int i, char side) {
	if(side == 'l') {
		while(sz(lin[i])) {
			int j = lin[i].back();
			lout[i].push_back(j);
			rout[j].push_back(i);
			lin[i].pop_back();
			rin[j].pop_back();
			int rem = j - i - 3;
			mn[rem]--;
			mnb[rem / B]--;
		}
	} else {
		while(sz(rin[i])) {
			int j = rin[i].back();
			rout[i].push_back(j);
			lout[j].push_back(i);
			rin[i].pop_back();
			lin[j].pop_back();
			int rem = i - j - 3;
			mn[rem]--;
			mnb[rem / B]--;
		}
	}
}

void solve() {
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for(int i = 0; i <= n; i++) {
		li[i] = ri[i] = -1;
		mn[i] = mnb[i] = 0;
		lin[i].clear();
		rin[i].clear();
		lout[i].clear();
		rout[i].clear();
	}
	stack<int> gt;
	gt.push(n - 1);
	for(int i = n - 2; i >= 0; i--) {
		while(sz(gt) && a[gt.top()] < a[i]) {
			gt.pop();
		}
		if(sz(gt)) ri[i] = gt.top() + 1;
		gt.push(i);
	}
	stack<int> lt;
	lt.push(0);
	for(int i = 1; i < n; i++) {
		while(sz(lt) && a[lt.top()] > a[i]) {
			lt.pop();
		}
		if(sz(lt)) li[i] = lt.top();
		lt.push(i);
	}
	for(int i = 0; i < n; i++) {
		if(li[i] != -1 && ri[i] != -1) {
			lout[li[i]].push_back(ri[i]);
			rout[ri[i]].push_back(li[i]);
		}
	}
	for(int i = 0; i <= n; i++) {
		sort(all(lout[i]), greater<int>());
		sort(all(rout[i]));
	}
	for(int i = 0; i < m; i++) {
		cin >> q[i][0] >> q[i][1];
		q[i][0]--;
		q[i][2] = i;
		ans[i] = -1;
	}
	sort(q, q + m, [&](auto& x, auto& y) {
		if(x[0] / B == y[0] / B) return x[1] < y[1];
		return x[0] < y[0];
	});
	l = 0; r = 0; // l is 0-indexed, r is 1-indexed: basically [l, r)
	for(int i = 0; i < m; i++) {
		while(r > q[i][1]) {
			del(r, 'r');
			r--;
		}
		while(r < q[i][1]) {
			r++;
			add(r, 'r');
		}
		while(l > q[i][0]) {
			l--;
			add(l, 'l');
		}
		while(l < q[i][0]) {
			del(l, 'l');
			l++;
		}
		for(int j = 0; j < B; j++) {
			if(mnb[j] > 0) {
				for(int k = B * j; k < B * (j + 1); k++) {
					if(mn[k] > 0) {
						ans[q[i][2]] = q[i][1] - q[i][0] - k;
						break;
					}
				}
				assert(ans[q[i][2]] != -1);
				break;
			}
		}
	}
	for(int i = 0; i < m; i++) {
		cout << ans[i] << endl;
	}
}

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t = 1;
	cin >> t;
	while(t--) {
		solve();
	}
	return 0;
}
