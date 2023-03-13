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
	T def;
	function<T(T, T)> fx;
	void build(int _n, T _def, function<T(T, T)> _fx) {
		n = _n, def = _def, fx = _fx;
		t.assign(n * 2, def);
		for(int i = n - 1; i > 0; i--) t[i] = fx(t[i * 2], t[i * 2 + 1]);
	}
	void build(vector<T>& a, T _def, function<T(T, T)> _fx) {
		n = a.size(), def = _def, fx = _fx;
		t.assign(n * 2, def);
		for(int i = 0; i < n; i++) t[i + n] = a[i];
		for(int i = n - 1; i > 0; i--) t[i] = fx(t[i * 2], t[i * 2 + 1]);
	}
	void update(int i, T v) {
		for(t[i += n] = v; i > 1; ) {
			i /= 2;
			t[i] = fx(t[i * 2], t[i * 2 + 1]);
		}
	}
	// this query is made on [l, r)
	// BEWARE: you may require ldef, rdef incase of direction specific queries
	T query(int l, int r) {
		T lans = def, rans = def;
		for(l += n, r += n; l < r; l /= 2, r /= 2) {
			if(l % 2) lans = fx(lans, t[l++]);
			if(r % 2) rans = fx(t[--r], rans);
		}
		return fx(lans, rans);
	}
};

void solve() {
	ll n;
	cin >> n;
	vl a(n), pfx(n + 1);
	F0(n, i) {
		cin >> a[i];
		pfx[i + 1] = pfx[i] + a[i];
	}
	segtree<ll> MinPfx, MaxPfx, MaxArr;
	MinPfx.build(n + 1, inf, [&](ll x, ll y) { return min(x, y); });
	MaxPfx.build(n + 1, -inf, [&](ll x, ll y) { return max(x, y); });
	MaxArr.build(a, -inf, [&](ll x, ll y) { return max(x, y); });
	for(ll i = 0; i < n; i++) {
		MinPfx.update(i, pfx[i]);
		ll left;
		{
			ll low = 0, high = i;
			while(high - low > 1) {
				ll mid = (high + low) / 2;
				if(MaxArr.query(mid, i + 1) > a[i]) low = mid;
				else high = mid;
			}
			left = (MaxArr.query(low, i + 1) <= a[i] ? low : high);
		}
		ll sum = MinPfx.query(left, i + 1);
		if(sum < pfx[i + 1] - a[i]) {
			cout << "NO";
			return ;
		}
	}
	for(ll i = n - 1; i >= 0; i--) {
		MaxPfx.update(i + 1, pfx[i + 1]);
		ll right;
		{
			ll low = i, high = n - 1;
			while(high - low > 1) {
				ll mid = (high + low) / 2;
				if(MaxArr.query(i, mid + 1) > a[i]) high = mid;
				else low = mid;
			}
			right = (MaxArr.query(i, high + 1) <= a[i] ? high : low);
		}
		ll sum = MaxPfx.query(i, right + 2);
		if(sum > pfx[i] + a[i]) {
			cout << "NO";
			return ;
		}
	}
	cout << "YES";
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
