//////////////////////////////////////////////////////////////////
/////                                                           //
////  Credits: Rahul Verma (CC @vrintle, CF @BlindingKnight)   ///
///  Institution: Delhi Technological University (aka. DCE)   ////
//                                                           /////
//////////////////////////////////////////////////////////////////

#include <chrono>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace chrono;
using namespace __gnu_pbds;

template <typename T> using pbds = tree<T, null_type,
	less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// find_by_order(K): Returns an iterator to the Kth largest element (counting from zero)
// order_of_key (K): Returns the number of items that are strictly smaller than K

/*

                ~ You don't know the power of the dark side! ~

..-..,'".-     BM\dF. jM@'    !MMM.&^'jjjM#*..`.              !*m.F.    `.....
-`.'^-".^.   ._'-".   ``       `"#.# .]MF.      _.  __-gg..      jMg.   ......
'......._   j#M' jMf       jg_jm..-`  .Mf_ ja   "`  .`  `^" ,_ 4g."@!.  ...,.,
',3&^jCgf ._`"`"'.         .` """!.   .`^^       .....        .""LTgJf.  =/<.,
_@#MMQK##-@"^                         ..                         .'QK_. .!$AGz
MM&&#0$#yF.                          !-M.    .gmMM@!               ."q. ..K#MD
ZM#ZM#$.                             q4M.    ..__,,yg_.              ^\. ..M0#
A0NWM@.                    jggp.    .,m*      .#MMMMM#'..              '  ."M0
BMM$@"                     !MM#'..   -*'      ."QMMMM#`..                 ..^$
BMMM'                      .^@#.'`   _     ,yy___````.                     . `
MMMP                        ...  j.  1.L   .""9*qwwwJ,.                     ..
@@@.                   .     ...P`,  .F`            .`.                     ..
0T`                   .P. . F`      :"~~-  ._.e.,wyyw..,,....
yg.                             '  _g0M0g. .-'`'^`Q$_
Mf                                .jMMMMML    .`-"0M#
@.                              . ."MMMM@^        ."".
f                              .    -.            ...
.                             .                 ._  ...
                            .           .        .    ..
                       ..  -'          .,              ..,   ..,.
                        `.          . ..*. . _     ,   .p_ .-,'jb.
_                     jgg, -'-+..--!.!!!` !' .~.      _0MM/.-.-/@.   .yyygggMM
M0gyy__________.      ^0M'                            "MM^  ...".     `^MMMMMM
MMMMMMMMMMMMMM'.                                                   ..        .

*/

#define F first
#define S second
#define db double
#define ld long db
#define M 1000000007
#define pb push_back
#define ll long long
#define lll __int128
#define vl vector<ll>
#define vd vector<db>
#define vld vector<ld>
#define vvl vector<vl>
#define pl pair<ll,ll>
#define pd pair<db,db>
#define vpl vector<pl>
#define vpd vector<pd>
#define lld __float128
#define ull unsigned ll
#define sz(a) ((ll) a.size())
#define PI 3.141592653589793238
#define all(v) v.begin(), v.end()
#define each(seq) for(auto e: seq)
#define acc(a) accumulate(all(a), 0ll)
#define shuff(a) random_shuffle(all(a))
#define F0(n, i) for(ll i = 0; i < n; i++)
#define F1(n, i) for(ll i = 1; i <= n; i++)
#define google cout << "Case #" << i << ": ";
#define dbgpr(pr) cout << ' ' << #pr << " {" << pr.F << ',' << pr.S << "} "
#define dbgprs(seq) cout << #seq << " <"; each(seq) { dbgpr(e); } cout << ">\n"
#define dbgarr(seq) cout << #seq << " < "; each(seq) { cout << e << ' '; } cout << ">\n"
#define dbgmtx(mat) cout << #mat << " {\n"; each(mat) { cout << ' '; dbgarr(e); } cout << "}\n"
#define lrot(a, l, r, k) rotate(a.begin() + l, a.begin() + l + (k % (r - l + 1)), a.begin() + r + 1)
#define rrot(a, l, r, k) rotate(a.begin() + l, a.begin() + r + 1 - (k % (r - l + 1)), a.begin() + r + 1)
#define dbgmap(hash) cout << #hash << " { "; each(hash) { cout << e.first << ':' << e.second << ' '; } cout << "}\n"
#define dbgtree(tree) cout << #tree << " {\n"; each(tree) { cout << e.first << ": "; dbgarr(e.second); } cout << "}\n"

// Debug Template, copied from Mikel_Arteta_8 (https://codeforces.com/blog/entry/68809)
void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifdef VRINTLE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif
// End of debugging template

/* ostream& operator<<(ostream& o, const __int128& x) {
    if (x == numeric_limits<__int128>::min()) return o << "-170141183460469231731687303715884105728";
    if (x < 0) return o << "-" << -x;
    if (x < 10) return o << (char)(x + '0');
    return o << x / 10 << (char)(x % 10 + '0');
} */

ll sieve_size = 0, facto_size = 0;
vector<ll> F(facto_size+1);
vector<bool> state(sieve_size+1, 1);
// exp() for (N^K)%M is only valid, when N%M != 0, else return 0
ll exp(ll n,ll k,ll m=M){ll r=1,a=n%m;do{r=k&1?r*a%m:r;a=a*a%m;}while(k/=2);return r;}
ll imod(ll a,ll m=M){return exp(a,m-2,m)%m;}
ll C(ll n,ll r,ll m=M){return r?(F[n]*imod(F[r],m)%m*imod(F[n-r],m)%m)%m:1;}
void facto(ll n=facto_size,ll m=M){F[0]=1;F1(n,i)F[i]=(F[i-1]*i)%m;}
void sieve(ll n=sieve_size){for(ll i=4;i<=n;i+=2)state[i]=0;for(ll i=3;i<=n;i+=2)for(ll j=i*i;j<=n;j+=i)state[j]=0;}
// when floor(-1 / 4) = -1, use this one
template<class T>T fdivf(T a,T b){return a/b-((a^b)<0&&a%b);}

ll m, q, inf = 1e17;

struct node {
	ll r, mx, mn;
};

template<typename T>
class segtree {
	public:
	vector<T> t;
	int n;
	T ldef, rdef;
	function<T(T&, T&)> fx;
	void build(int _n, T _ldef, T _rdef, function<T(T&, T&)> _fx) {
		n = 1;
		while(n < _n) n *= 2;
		ldef = _ldef, rdef = _rdef, fx = _fx;
		t.assign(n * 2, rdef);
		for(int i = n - 1; i > 0; i--) {
			t[i] = fx(t[i * 2], t[i * 2 + 1]);
		}
	}
	void update(int i, T v) {
		for(t[i += n] = v; i > 1; ) {
			i /= 2;
			t[i] = fx(t[i * 2], t[i * 2 + 1]);
		}
	}
	// this query is made on [l, r)
	// BEWARE: you may require ldef, rdef incase of direction specific queries
	T ask(int i, int tl, int tr, int l, int r) {
		if(tl >= r) return rdef;
		if(tr <= l) return ldef;
		if(l <= tl && tr <= r) {
			return t[i];
		}
		int tm = (tl + tr) >> 1;
		T x, y;
		return fx(x = ask(i * 2, tl, tm, l, r), y = ask(i * 2 + 1, tm, tr, l, r));
	}
	T ask(int l, int r) {
		return ask(1, 0, n, l, r);
	}
};

segtree<node> st;

class lazy {
	public:
	vector<node> t;
	vector<long long> cnt;
	vector<pair<long long, long long>> b;
	vector<long long> p, d;
	int n;
	node ldef, rdef;
	lazy(int _n) : n(1) {
		while(n < _n) n *= 2;
		ldef = node{0, -inf, inf};
		rdef = node{0, -inf, inf};
		t.assign(n * 2, rdef);
		b.assign(n * 2, {0, 0});
		p.assign(n * 2, 0);
		d.assign(n * 2, 0);
		cnt.assign(n * 2, 0);
		for(int i = 0; i < _n; i++) {
			cnt[i + n] = 1;
			b[i + n] = {i, i + 1};
		}
		for(int i = n - 1; i > 0; i--) {
			cnt[i] = cnt[i * 2] + cnt[i * 2 + 1];
			b[i] = {b[i * 2].first, b[i * 2 + 1].second};
		}
	}
	node fx(node& x, node& y) {
		return node {
			max({x.r, y.r, y.mx - x.mn}),
			max(x.mx, y.mx),
			min(x.mn, y.mn)
		};
	}
	void push(int i) {
		t[i] = st.ask(b[i].F + d[i], b[i].S + d[i]);
		if(i < n) {
			p[i * 2] = p[i * 2 + 1] = 1;
			d[i * 2] = d[i];
			d[i * 2 + 1] = d[i];
		}
		d[i] = p[i] = 0;
	}
	node dev(int i, int tl, int tr, int l, int r, ll xx) {
		if(p[i]) push(i);
		if(tl >= r || tr <= l) return t[i];
		if(l <= tl && tr <= r) {
			d[i] = xx;
			p[i] = 1;
			push(i);
			return t[i];
		}
		int tm = (tl + tr) >> 1;
		node x, y;
		return (t[i] = fx(x = dev(i * 2, tl, tm, l, r, xx), y = dev(i * 2 + 1, tm, tr, l, r, xx)));
	}
	void dev(int l, int r, ll x) {
		dev(1, 0, n, l, r, x);
	}
	node set(int i, int tl, int tr, int l, int r, node v) {
		if(p[i]) push(i);
		if(tl >= r || tr <= l) return t[i];
		if(l <= tl && tr <= r) {
			t[i] = v;
			return t[i];
		}
		int tm = (tl + tr) >> 1;
		node x, y;
		return (t[i] = fx(x = set(i * 2, tl, tm, l, r, v), y = set(i * 2 + 1, tm, tr, l, r, v)));
	}
	void set(int l, int r, node v) {
		set(1, 0, n, l, r, v);
	}
	void set(int i, node v) {
		set(1, 0, n, i, i + 1, v);
	}
	node ask(int i, int tl, int tr, int l, int r) {
		if(p[i]) push(i);
		if(tl >= r) return rdef;
		if(tr <= l) return ldef;
		if(l <= tl && tr <= r) {
			return t[i];
		}
		int tm = (tl + tr) >> 1;
		node x, y;
		return fx(x = ask(i * 2, tl, tm, l, r), y = ask(i * 2 + 1, tm, tr, l, r));
	}
	node ask(int l, int r) {
		return ask(1, 0, n, l, r);
	}
};

void solve() {
	cin >> m >> q;
	vl a(m), b(m);
	F0(m, i) cin >> a[i];
	F0(m, i) cin >> b[i];
	F0(m, i) b.pb(b[i]);
	st.build(2 * m, node{0, -inf, inf}, node{0, -inf, inf}, [&](auto& x, auto& y) {
		return node {
			max({x.r, y.r, y.mx - x.mn}),
			max(x.mx, y.mx),
			min(x.mn, y.mn)
		};
	});
	F0(2 * m, i) {
		st.update(i, node{0, b[i], b[i]});
	}
	lazy st2(m);
	F0(m, i) {
		st2.set(i, node{0, a[i], a[i]});
	}
	while(q--) {
		ll t, l, r;
		cin >> t >> l >> r;
		r++;
		if(t == 1) {
			ll k;
			cin >> k;
			ll d = (k - l + m) % m;
			st2.dev(l, r, d);
			cout << st2.t[1].r << '\n';
		} else {
			cout << st2.ask(l, r).r << '\n';
		}
	}
}

int32_t main() {
	auto start = high_resolution_clock::now();
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	ll t = 1;
	// cin >> t;
	F1(t, i) {
		// google
		solve();
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	debug(duration.count(), " µs!");
	return 0;
}
