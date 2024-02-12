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
#define inf numeric_limits<ll>::max()
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

class lazy {
	public:
	vector<long long> t, cnt;
	vector<pair<long long, long long>> v;
	vector<bool> p;
	int n;
	lazy(int _n) : n(1) {
		while(n < _n) n *= 2;
		t.assign(n * 2, 0);
		v.assign(n * 2, {0, 0});
		p.assign(n * 2, 0);
		cnt.assign(n * 2, 0);
		for(int i = 0; i < _n; i++) cnt[i + n] = 1;
		for(int i = n - 1; i > 0; i--) cnt[i] = cnt[i * 2] + cnt[i * 2 + 1];
	}
	void push(int i) {
		if(v[i].second) t[i] = v[i].second * cnt[i];
		if(v[i].first) t[i] += v[i].first * cnt[i];
		if(i < n) {
			p[i * 2] = p[i * 2 + 1] = 1;
			if(v[i].second) {
				v[i * 2] = v[i * 2 + 1] = v[i];
			} else {
				v[i * 2].first += v[i].first;
				v[i * 2 + 1].first += v[i].first;
			}
		}
		v[i] = {0, 0};
		p[i] = 0;
	}
	// tr and r is 1 indexed
	long long add(int i, int tl, int tr, int l, int r, int x) {
		if(p[i]) push(i);
		if(tl >= r || tr <= l) return t[i];
		if(l <= tl && tr <= r) {
			p[i] = 1;
			v[i] = {x, 0};
			push(i);
			return t[i];
		}
		int tm = (tl + tr) >> 1;
		return (t[i] = add(i * 2, tl, tm, l, r, x) + add(i * 2 + 1, tm, tr, l, r, x));
	}
	void add(int l, int r, int x) {
		add(1, 0, n, l, r, x);
	}
	void add(int i, int x) {
		add(1, 0, n, i, i + 1, x);
	}
	long long set(int i, int tl, int tr, int l, int r, int x) {
		if(p[i]) push(i);
		if(tl >= r || tr <= l) return t[i];
		if(l <= tl && tr <= r) {
			p[i] = 1;
			v[i] = {0, x};
			push(i);
			return t[i];
		}
		int tm = (tl + tr) >> 1;
		return (t[i] = set(i * 2, tl, tm, l, r, x) + set(i * 2 + 1, tm, tr, l, r, x));
	}
	void set(int l, int r, int x) {
		set(1, 0, n, l, r, x);
	}
	void set(int i, int x) {
		set(1, 0, n, i, i + 1, x);
	}
	long long sum(int i, int tl, int tr, int l, int r) {
		if(p[i]) push(i);
		if(tl >= r || tr <= l) return 0;
		if(l <= tl && tr <= r) return t[i];
		int tm = (tl + tr) >> 1;
		return sum(i * 2, tl, tm, l, r) + sum(i * 2 + 1, tm, tr, l, r);
	}
	long long sum(int l, int r) {
		return sum(1, 0, n, l, r);
	}
	long long sum(int i) {
		return sum(1, 0, n, i, i + 1);
	}
};

void solve() {
	ll n, q;
	cin >> n >> q;
	vl a(n);
	F0(n, i) cin >> a[i];
	lazy st(n);
	F0(n, i) {
		st.set(i, a[i]);
		// debug(st.v);
	}
	while(q--) {
		ll t, l, r;
		cin >> t >> l >> r;
		if(t == 1) {
			ll x; cin >> x;
			st.add(l - 1, r, x);
		} else if(t == 2) {
			ll x; cin >> x;
			st.set(l - 1, r, x);
		} else {
			cout << st.sum(l - 1, r) << '\n';
		}
		debug(st.t);
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
