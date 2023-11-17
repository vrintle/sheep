// Credits: Editorial code of Codeforces Round #909 (Div. 3)
// Problem: https://codeforces.com/contest/1899/problem/G

#include <bits/stdc++.h>
 
using namespace std;
 
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
 
struct SegmentTree {
    int n;
    vector<vector<int>> tree;
 
    void build(vector<int> &a, int x, int l, int r) {
        if (l + 1 == r) {
            tree[x] = {a[l]};
            return;
        }
 
        int m = (l + r) / 2;
        build(a, 2 * x + 1, l, m);
        build(a, 2 * x + 2, m, r);
        merge(all(tree[2 * x + 1]), all(tree[2 * x + 2]), back_inserter(tree[x]));
    }
 
    SegmentTree(vector<int>& a) : n(a.size()) {
        int SIZE = 1 << (__lg(n) + bool(__builtin_popcount(n) - 1));
        tree.resize(2 * SIZE - 1);
        build(a, 0, 0, n);
    }
 
    int count(int lq, int rq, int mn, int mx, int x, int l, int r) {
        if (rq <= l || r <= lq) return 0;
        if (lq <= l && r <= rq) return lower_bound(all(tree[x]), mx) - lower_bound(all(tree[x]), mn);
 
        int m = (l + r) / 2;
        int a = count(lq, rq, mn, mx, 2 * x + 1, l, m);
        int b = count(lq, rq, mn, mx, 2 * x + 2, m, r);
        return a + b;
    }
 
    int count(int lq, int rq, int mn, int mx) {
        return count(lq, rq, mn, mx, 0, 0, n);
    }
};
 
vector<vector<int>> g;
 
vector<int> tin, tout;
int timer;
void dfs(int v, int p) {
    tin[v] = timer++;
    for (auto u : g[v]) {
        if (u != p) {
            dfs(u, v);
        }
    }
    tout[v] = timer;
}
 
void solve() {
    int n, q;
    cin >> n >> q;
    
    g.assign(n, vector<int>());
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
 
    timer = 0;
    tin.resize(n);
    tout.resize(n);
    dfs(0, -1);
    
    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];
 
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = tin[p[i] - 1];
    SegmentTree ST(a);
 
    for (int i = 0; i < q; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        l--; x--;
        if (ST.count(l, r, tin[x], tout[x])) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
 
int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
        if(tests > 0) cout << "\n";
    }
    return 0;
}
