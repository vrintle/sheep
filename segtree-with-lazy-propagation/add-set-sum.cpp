// Author: vrintle (Rahul Verma)
// Problem: https://codeforces.com/contest/558/problem/E

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
	int val, size;
};
S op(S l, S r) {
	return S{l.val + r.val, l.size + r.size};
}
// NOTE: default node should be such that it doesn't affect other nodes
S e() {
	return S{0, 1};
}
struct F {
	int type, val;
	// type: 0 for set, 1 for add
};
S mapping(F f, S e) {
	return f.type ? S{e.val + f.val * e.size, e.size} : S{f.val * e.size, e.size};
}
F composition(F next, F prev) {
	if(next.type == 0 && prev.type == 0) return F{0, next.val};
	if(next.type == 0 && prev.type == 1) return F{0, next.val};
	if(next.type == 1 && prev.type == 0) return F{0, prev.val + next.val};
	return F{1, prev.val + next.val};
}
// NOTE: default function should be such that it doesn't affect the node
F id() {
	return F{1, 0};
}

const int N = 26;
lazy_segtree<S, op, e, F, mapping, composition, id> st[N];

void solve() {
	int n, m;
	string s;
	cin >> n >> m >> s;
	for(int c = 0; c < N; c++) {
		st[c] = lazy_segtree<S, op, e, F, mapping, composition, id>(n);
	}
	for(int i = 0; i < n; i++) {
		st[s[i] - 'a'].apply(i, i + 1, F{1, 1});
	}
	while(m--) {
		int l, r, t;
		cin >> l >> r >> t;
		l--;
		if(t) {
			int curr = l;
			for(int c = 0; c < N; c++) {
				int cnt = st[c].prod(l, r).val;
				st[c].apply(l, r, F{0, 0});
				st[c].apply(curr, curr + cnt, F{1, 1});
				curr += cnt;
			}
		} else {
			int curr = l;
			for(int c = N - 1; c >= 0; c--) {
				int cnt = st[c].prod(l, r).val;
				st[c].apply(l, r, F{0, 0});
				st[c].apply(curr, curr + cnt, F{1, 1});
				curr += cnt;
			}			
		}
	}
	string ans(n, '_');
	for(char c = 'a'; c <= 'z'; c++) {
		for(int i = 0; i < n; i++) {
			if(st[c - 'a'].prod(i, i + 1).val > 0) ans[i] = c;
		}
	}
	cout << ans;
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
