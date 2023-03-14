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

const int N = 5e5 + 7, L = 20;
vpl g[N];
vl aux[N];
ll ans[N], a[N], tin[N], tout[N], up[N][L], sum[N];
map<ll, vl> nodes;

void solve() {
	ll n;
	cin >> n;
	nodes.clear();
	F0(n, i) {
		cin >> a[i];
		g[i].clear();
		aux[i].clear();
		ans[i] = 0;
		nodes[a[i]].pb(i);
		F0(L, j) up[i][j] = 0;
		sum[i] = 0;
	}
	ll t = 0;
	function<void(ll, ll)> dfs = [&](ll i, ll p) -> void {
		tin[i] = t++;
		if(p != -1) {
			up[i][0] = p;
			for(ll j = 1; j < L; j++) {
				up[i][j] = up[up[i][j - 1]][j - 1];
			}
		}
		each(g[i]) {
			if(e.F != p) {
				dfs(e.F, i);
			}
		}
		tout[i] = t++;
	};
	F0(n - 1, i) {
 		ll u, v;
		cin >> u >> v;
		u--; v--;
		g[u].pb({v, i});
		g[v].pb({u, i});
	}
	F0(n, i) {
		debug(i, g[i]);
	}
	dfs(0, -1);
	auto is = [&](ll u, ll v) {
		return tin[u] <= tin[v] && tout[u] >= tout[v];
	};
	auto lca = [&](ll u, ll v) {
		if(is(u, v)) return u;
		if(is(v, u)) return v;
		for(ll j = L - 1; j >= 0; j--) {
			if(!is(up[u][j], v)) u = up[u][j];
		}
		return up[u][0];
	};
	for(auto& [c, vx]: nodes) {
		sort(all(vx), [&](ll u, ll v) {
			return tin[u] < tin[v];
		});
		ll m = sz(vx);
		for(ll i = 1; i < m; i++) vx.pb(lca(vx[i - 1], vx[i]));
		sort(all(vx), [&](ll u, ll v) {
			return tin[u] < tin[v];
		});
		vl _vx {vx[0]};
		for(ll i = 1; i < sz(vx); i++) {
			if(vx[i] != _vx.back()) _vx.pb(vx[i]);
		}
		swap(_vx, vx);
		m = sz(vx);
		debug(vx);
		F0(m, i) aux[vx[i]].clear();
		stack<ll> s;
		s.push(vx[0]);
		for(ll i = 1; i < m; i++) {
			while(sz(s) && !is(s.top(), vx[i])) s.pop();
			assert(sz(s));
			aux[s.top()].pb(vx[i]);
			s.push(vx[i]);
		}
		function<void(ll, ll)> dfs2 = [&](ll i, ll p) {
			debug(i, p, aux[i]);
			sum[i] += c;
			sum[p] -= c;
			each(aux[i]) {
				dfs2(e, i);
			}
		};
		dfs2(vx[0], vx[0]);
	}
	function<void(ll, ll, ll)> dfs3 = [&](ll i, ll p, ll j) {
		for(auto& [v, x]: g[i]) {
			if(v == p) continue;
			dfs3(v, i, x);
			sum[i] += sum[v];
		}
		if(j != -1) ans[j] += sum[i];
	};
	dfs3(0, -1, -1);
	F0(n - 1, i) cout << ans[i] << ' ';
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
