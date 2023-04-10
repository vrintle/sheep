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

using u64 = uint64_t;
using u128 = __uint128_t;

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool test(u64 n, int iter=5) { // Miller-Rabin: returns true if n is probably prime, else returns false.
    if (n < 4)
        return n == 2 || n == 3;

    int s = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    for (int i = 0; i < iter; i++) {
        int a = 2 + rand() % (n - 3);
        if (check_composite(n, a, d, s))
            return false;
    }
    return true;
}

const int N = 1000000;
vector<int> lp(N+1);
vector<int> pr;

void sieve() {
for (int i=2; i <= N; ++i) {
    if (lp[i] == 0) {
        lp[i] = i;
        pr.push_back(i);
    }
    for (int j = 0; i * pr[j] <= N; ++j) {
        lp[i * pr[j]] = pr[j];
        if (pr[j] == lp[i]) {
            break;
        }
    }
}
}

void solve() {
	ll n;
	cin >> n;
	if(n % 2) {
		cout << (test(n + 2) ? 2 : -1);
		return ;
	}
	for(ll i = 1; i < sz(pr); i++) {
		if(test(n + pr[i])) return void(cout << pr[i]);
	}
	assert(false);
}

int32_t main() {
	auto start = high_resolution_clock::now();
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	sieve();
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
