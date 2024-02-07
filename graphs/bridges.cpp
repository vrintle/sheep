// Author: vrintle (Rahul Verma)
// Problem: https://codeforces.com/contest/1927/problem/F

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

class Graph {
    int V;
    void bridgeUtil(int v, vector<bool> &visited, vector<int> &disc, vector<int> &low, vector<int> &parent, vector<vi> &bridges);

public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    void remBridges();
    vector<set<pii>> adj;
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int u, int v, int w) {
    adj[u].insert({v, w});
    adj[v].insert({u, w}); // undirected graph
}

void Graph::bridgeUtil(int u, vector<bool> &visited, vector<int> &disc, vector<int> &low, vector<int> &parent, vector<vi> &bridges) {
    static int time = 0;

    visited[u] = true;
    disc[u] = low[u] = ++time;

    for (auto [v, w]: adj[u]) {
        if (!visited[v]) {
            parent[v] = u;
            bridgeUtil(v, visited, disc, low, parent, bridges);
            low[u] = min(low[u], low[v]);
            if (low[v] > disc[u])
                bridges.push_back(vi{u, v, w});
        } else if (v != parent[u])
            low[u] = min(low[u], disc[v]);
    }
}

void Graph::remBridges() {
    vector<bool> visited(V, false);
    vector<int> disc(V, -1);
    vector<int> low(V, -1);
    vector<int> parent(V, -1);
    vector<vi> bridges;

    for (int i = 0; i < V; i++) {
        if (!visited[i])
            bridgeUtil(i, visited, disc, low, parent, bridges);
    }

    for (auto& e: bridges) {
        int u = e[0], v = e[1], w = e[2];
	adj[u].erase({v, w});
	adj[v].erase({u, w});	
    }
}

void solve() {
	int n, m;
	cin >> n >> m;
	Graph gg(n);
	rep(m) {
		int u, v, w;
		cin >> u >> v >> w;
		u--; v--;
		gg.addEdge(u, v, w);
	}
	gg.remBridges();
	vector<set<pii>> g = gg.adj;
	int mn = inf;
	pii edge;
	for(int u = 0; u < n; u++) {
		// cerr << u << ": ";
		for(auto& [v, w]: g[u]) {
			// cerr << v << ' ' << w << " | ";
			if(mn > w) {
				mn = w;
				edge = {u, v};
			}
		}
		// cerr << endl;
	}
	vi list, ans, vis(n);
	list.push_back(edge.first);
	vis[edge.first] = 1;
	// cerr << edge.first << ' ' << edge.second << endl;
	function<void(int)> dfs = [&](int u) {
		// cerr << u << endl;
		vis[u] = 1;
		list.push_back(u);
		for(auto& [v, w]: g[u]) {
			if(vis[v] == 1) {
				if(v == edge.first && u != edge.second && ans.empty()) {
					ans = list;
					// cerr << "eureka!!\n";
				}
			} else dfs(v);
		}
		list.pop_back();
	};
	dfs(edge.second);
	cout << mn << ' ' << sz(ans) << endl;
	for(auto& e: ans) cout << e + 1 << ' ';
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
	cin >> t;
	while(t--) {
		solve();
		cout << endl;
		// cerr << endl;
	}
	return 0;
}
