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
ll nCr(ll n,ll r,ll m=M){return r?(F[n]*imod(F[r],m)%m*imod(F[n-r],m)%m)%m:1;}
void facto(ll n=facto_size,ll m=M){F[0]=1;F1(n,i)F[i]=(F[i-1]*i)%m;}
void sieve(ll n=sieve_size){for(ll i=4;i<=n;i+=2)state[i]=0;for(ll i=3;i<=n;i+=2)for(ll j=i*i;j<=n;j+=i)state[j]=0;}

template<typename T>
class segtree {
	public:
	vector<T> t;
	int n;
	T ldef, rdef;
	function<T(const T&, const T&)> fx;
	void build(int _n, T _ldef, T _rdef, function<T(const T&, const T&)> _fx) {
		n = 1;
		while(n < _n) n *= 2;
		ldef = _ldef, rdef = _rdef, fx = _fx;
		t.assign(n * 2, rdef);
	}
	void update(int i, const T& v) {
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
		if(l <= tl && tr <= r) return t[i];
		int tm = (tl + tr) >> 1;
		return fx(ask(i * 2, tl, tm, l, r), ask(i * 2 + 1, tm, tr, l, r));
	}
	T ask(int l, int r) {
		return ask(1, 0, n, l, r);
	}
};

void solve() {
	ll n;
	cin >> n;
	vector<vpl> g(n);
	vl par(n), big(n, -1), top(n), tin(n), tour(n), cnt(n, 1), dep(n), idx(n), wgt(n), node(n);
	function<void(ll, ll)> dfs = [&](ll i, ll p) -> void {
		ll mx = 0;
		each(g[i]) {
			if(e.F == p) continue;
			idx[e.F] = e.S;
			node[e.S] = e.F;
			par[e.F] = i;
			dep[e.F] = dep[i] + 1;
			dfs(e.F, i);
			cnt[i] += cnt[e.F];
			if(cnt[e.F] > mx) mx = cnt[e.F], big[i] = e.F;
		}
	};
	ll t = 0;
	function<void(ll, ll)> dfs2 = [&](ll i, ll p) -> void {
		tin[i] = t++;
		tour[tin[i]] = i;
		if(big[i] != -1) {
			top[big[i]] = top[i];
			dfs2(big[i], i);
		}
		each(g[i]) {
			if(e.F == p || e.F == big[i]) continue;
			top[e.F] = e.F;
			dfs2(e.F, i);
		}
	};
	F0(n - 1, i) {
 		ll u, v, w;
		cin >> u >> v >> w;
		u--; v--;
		wgt[i] = w;
		g[u].pb({v, i});
		g[v].pb({u, i});
	}
	debug(g);
	idx[0] = n - 1;
	dfs(0, -1);
	dfs2(0, -1);
	segtree<ll> st;
	st.build(n, 0, 0, [&](auto& x, auto& y) {
		return x + y;
	});
	debug(tour);
	debug(par);
	debug(big);
	debug(dep);
	F0(n, i) st.update(i, wgt[idx[tour[i]]]);
	ll q; cin >> q;
	while(q--) {
		ll t;
		cin >> t;
		if(t == 1) {
			ll i, w;
			cin >> i >> w;
			i--;
			wgt[i] = w;
			ll u = node[i];
			st.update(tin[u], w);
		} else {
			ll u, v, ans = 0;
			cin >> u >> v;
			u--; v--;
			while(1) {
				ll x = top[u], y = top[v];
				debug(u, v, x, y);
				if(x == y) {
					if(tin[u] > tin[v]) swap(u, v);
					ans += st.ask(tin[u] + 1, tin[v] + 1);
					debug(u, v, ans);
					break;
				} else if(dep[x] > dep[y]) {
					ans += st.ask(tin[x], tin[u] + 1);
					u = par[x];
				} else {
					ans += st.ask(tin[y], tin[v] + 1);
					v = par[y];		
				}
				debug(u, v, ans);
			}
			cout << ans << '\n';
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
		cout << '\n';
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	debug(duration.count(), " µs!");
	return 0;
}
