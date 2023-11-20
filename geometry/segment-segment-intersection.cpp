#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

template <typename T> using pbds = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int int64_t
#define ld long double
#define endl '\n'
#define sz(v) ((int) v.size())
#define all(v) v.begin(), v.end()
#define vi vector<int>
#define pii pair<int, int>
#define inf 2e18

int max(int x, int y) { return x > y ? x : y; }
int min(int x, int y) { return x < y ? x : y; }

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

typedef Point<ld> P;

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P> vector<P> segInter(P a, P b, P c, P d) {
	auto oa = c.cross(d, a), ob = c.cross(d, b),
	     oc = a.cross(b, c), od = a.cross(b, d);
	// Checks if intersection is single non-endpoint point.
	if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
		return {(a * ob - b * oa) / (ob - oa)};
	set<P> s;
	if (onSegment(c, d, a)) s.insert(a);
	if (onSegment(c, d, b)) s.insert(b);
	if (onSegment(a, b, c)) s.insert(c);
	if (onSegment(a, b, d)) s.insert(d);
	return {all(s)};
}

void solve() {
	int n, m;
	cin >> m >> n;
	vector<P> a(m);
	vector<pair<P, P>> b(n);
	for(int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		a[i] = P(x, y);
	}
	for(int i = 0; i < n; i++) {
		int j, x, y;
		cin >> j >> x >> y;
		b[i].first = a[j - 1];
		b[i].second = P(x, y);
	}
	vector<vi> g(n);
	for(int i = 0; i < n; i++) {
		for(int j = i + 1; j < n; j++) {
			vector<P> inter = segInter(b[i].first, b[i].second, b[j].first, b[j].second);
			assert(sz(inter) <= 1);
			if(sz(inter) == 1 && (inter[0].x != b[i].first.x || inter[0].y != b[i].first.y)) {
				g[i].push_back(j);
				g[j].push_back(i);
			}
		}
	}
	/*for(int i = 0; i < n; i++) {
		cerr << i << ": ";
		for(auto& v: g[i]) cerr << v << ' ';
		cerr << endl;
	}*/	
	vi color(n, -1);
	bool cyc = 0;
	function<void(int)> dfs = [&](int u) {
		for(auto& v: g[u]) {
			if(color[v] == -1) {
				color[v] = 1 - color[u];
				dfs(v);
			} else if(color[v] == color[u]) {
				cyc = 1;
			}
		}
	};
	for(int i = 0; i < n; i++) {
		if(color[i] == -1) {
			color[i] = 0;
			dfs(i);
			if(cyc) return void(cout << "impossible");
		}
	}
	cout << "possible";
}

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t = 1;
	// cin >> t;
	while(t--) {
		solve();
		cout << endl;
	}
	return 0;
}
