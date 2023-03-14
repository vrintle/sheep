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
#define inf 2e18
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

void solve() {
	ll n, c0;
	cin >> n >> c0;
	vvl g(n), up(n, vl(20));
	vl cnt(n), prt(n, -1), q(n), dp(n, inf);
	q[0] = c0 - 1;
	F1(n - 1, i) cin >> q[i], q[i]--;
	function<void(ll, ll)> dfs_1 = [&](ll i, ll p) -> void {
		// dfs_1: to find size
		cnt[i] = 1;
		each(g[i]) {
			if(e == p || ~prt[e]) continue;
			dfs_1(e, i);
			cnt[i] += cnt[e];
		}
	};
	function<ll(ll, ll, ll)> dfs_2 = [&](ll i, ll p, ll r) {
		for(auto& e: g[i]) {
			if(e == p || ~prt[e]) continue;
			if(cnt[e] * 2 > cnt[r]) return dfs_2(e, i, r);
		}
		return i;
	};
	function<void(ll, ll)> decompose = [&](ll i, ll p) -> void {
		// decompose into centroid tree
		dfs_1(i, p);
		ll ct = dfs_2(i, p, i);
		debug(ct, i, p);
		prt[ct] = ~p ? p : ct;
		for(auto& e: g[ct]) {
			if(e == p || ~prt[e]) continue;
			decompose(e, ct);
		}
	};
	vl tin(n), tout(n), dep(n);
	ll t = 0;
	function<void(ll, ll, ll)> dfs = [&](ll i, ll p, ll d) {
		tin[i] = t++;
		dep[i] = d;
		if(~p) {
			up[i][0] = p;
			for(ll j = 1; j < 20; j++) {
				up[i][j] = up[up[i][j - 1]][j - 1];
			}	
		}
		each(g[i]) {
			if(e == p) continue;
			dfs(e, i, d + 1);
		}
		tout[i] = t++;
	};
	F0(n - 1, _) {
 		ll u, v;
		cin >> u >> v;
		u--; v--;
		g[u].pb(v);
		g[v].pb(u);
	}
	debug(g);
	dfs(0, -1, 0);
	decompose(0, -1);
	debug(prt);
	auto is = [&](ll u, ll v) {
		return tin[u] <= tin[v] && tout[u] >= tout[v];
	};
	auto lca = [&](ll u, ll v) {
		if(is(u, v)) return u;
		if(is(v, u)) return v;
		for(ll j = 19; j >= 0; j--) {
			if(!is(up[u][j], v)) u = up[u][j];
		}
		return up[u][0];
	};
	auto dist = [&](ll u, ll v) {
		return dep[u] + dep[v] - 2 * dep[lca(u, v)];
	};
	auto update = [&](ll u) {
		ll i = u;
		while(1) {
			dp[i] = min(dp[i], dist(i, u));
			if(i == prt[i]) break;
			i = prt[i];
		}
	};
	auto query = [&](ll u) {
		ll i = u, ans = dp[i];
		while(i != prt[i]) {
			i = prt[i];
			ans = min(ans, dist(i, u) + dp[i]);
		}
		return ans;
	};
	vl ans(n, inf);
	update(q[0]);
	F1(n - 1, i) {
		ans[i] = min(ans[i - 1], query(q[i]));
		update(q[i]);
		cout << ans[i] << ' ';
	}
}

int32_t main() {
	auto start = high_resolution_clock::now();
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	ll t = 1;
	cin >> t;
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
