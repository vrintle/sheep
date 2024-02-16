#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <list>
#include <iterator>
#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include <stack>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;
typedef vector<ll> vll;
typedef vector<double> vd;
typedef vector<vll> vvll;
typedef vector<pll> vpll;
typedef vector<pdd> vpdd;
typedef vector<vd> vvd;
template <typename T> using pbds = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define yn(ans) printf("%s\n", (ans)?"Yes":"No");
#define YN(ans) printf("%s\n", (ans)?"YES":"NO");
template<class T> bool chmax(T &a, T b) {
	if (a >= b) return false;
	a = b; return true;
}
template<class T> bool chmin(T &a, T b) {
	if (a <= b) return false;
	a = b; return true;
}
int max(int x, int y) { return x > y ? x : y; }
int min(int x, int y) { return x < y ? x : y; }
#define FOR(i, s, e, t) for ((i) = (s); (i) < (e); (i) += (t)) 
#define REP(i, e) for (int i = 0; i < (e); ++i) 
#define REP1(i, s, e) for (int i = (s); i < (e); ++i)
#define RREP(i, e) for (int i = (e); i >= 0; --i)
#define RREP1(i, e, s) for (int i = (e); i >= (s); --i)
#define int int64_t
#define vi vector<int>
#define pii pair<int, int>
#define all(v) v.begin(), v.end()
#define pb push_back
#define qb pop_back
#define pf push_front
#define qf pop_front
#define maxe max_element
#define mine min_element
#define endl '\n'
#define inf 2e18
#define sz(v) ((int) v.size())
#define DEBUG printf("%d\n", __LINE__); fflush(stdout);
template<class T> void print(vector<T> &v, bool withSize = false) {
	if (withSize) cout << v.size() << endl;
	REP(i, v.size()) cout << v[i] << " "; 
	cout << endl;
}

int __FAST_IO__ = []() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	return 0;
}();

// https://atcoder.github.io/ac-library/production/document_en/lazysegtree.html
// https://cses.fi/problemset/task/1735
// S: return type, op: how to merge at return, e: S default constructor
// F: value type of lazy value
// mapping: called on apply() to each item, mapping(F f, S item)
// composition: called on apply() to lazy value of a seg, composition(F f, F lazy)
// id: default falue of lazy value

template <class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
struct lazy_segtree {
  public:
    lazy_segtree() : lazy_segtree(0) {}
    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
    explicit lazy_segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = 0;
        while ((1 << log) < _n) ++log;
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        lz = std::vector<F>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }
 
    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }
 
    S get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }
 
    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return e();
 
        l += size;
        r += size;
 
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
 
        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
 
        return op(sml, smr);
    }
 
    S all_prod() { return d[1]; }
 
    void apply_single(int p, F f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;
 
        l += size;
        r += size;
 
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
 
        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }
 
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }
 
    template <bool (*g)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }
 
    template <bool (*g)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
	
	void debug() {
		cerr << "start of debug\n";
		for(auto& el: d) {
			el.debug();
		}
		cerr << "end of debug\n";
	}
 
  private:
    int _n, size, log;
    std::vector<S> d;
    std::vector<F> lz;
 
    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};

// S: return type, op: how to merge at return, e: S default constructor
// F: value type of lazy value
// mapping: called on apply() to each item, mapping(F f, S item)
// composition: called on apply() to lazy value of a seg, composition(F f, F lazy)
// id: default falue of lazy value
// template <class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>

struct S {
	int sum, days;
	void debug() {
		cerr << sum << ' ' << days << endl;
	}
};
S op(S l, S r) {
	return S{l.sum + r.sum, l.days + r.days};
}
// NOTE: default node should be such that it doesn't affect other nodes
S e() {
	return S{0, 0};
}
struct F {
	int val;
};
S mapping(F f, S e) {
	return S{f.val == -1 ? e.sum : e.days * f.val, e.days};
}
F composition(F next, F prev) {
	return next.val == -1 ? prev : next;
}
// NOTE: default function should be such that it doesn't affect the node
F id() {
	return F{-1};
}

void solve() {
	int n, m;
	cin >> n >> m;
	vector<vi> q(m, vi(3));
	vi compress;
	for(int i = 0; i < m; i++) {
		cin >> q[i][0] >> q[i][1] >> q[i][2];
		q[i][0]--;
		compress.push_back(q[i][0]);
		compress.push_back(q[i][1]);
	}
	compress.push_back(n);
	sort(all(compress));	
	auto it = unique(all(compress));
	compress.resize(distance(compress.begin(), it));
	int k = sz(compress);
	vector<S> tr(k);
	tr[0] = S{compress[0], compress[0]};
	for(int i = 1; i < k; i++) {
		int x = compress[i] - compress[i - 1];
		tr[i] = S{x, x};
	}
	lazy_segtree<S, op, e, F, mapping, composition, id> st(tr);
	for(int i = 0; i < m; i++) {
		int l = upper_bound(all(compress), q[i][0]) - compress.begin();
		int r = upper_bound(all(compress), q[i][1]) - compress.begin();
		int bit = q[i][2] - 1;
		st.apply(l, r, F{bit});
		cout << st.prod(0, k).sum << endl;
	}
}

int32_t main() {
	int t = 1;
	// cin >> t;
	for(int i = 1; i <= t; i++) {
		// cout << "Case #" << i << ": ";
		solve();
		cout << endl;
		// cerr << endl;
	}
	return 0;
}
