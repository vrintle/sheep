struct Trie {
    Trie *l, *r;
    int cnt = 0;
    Trie() {
        l = r = nullptr;
        cnt = 0;
    }
};

class Solution {
public:
    int maximumStrongPairXor(vector<int>& a) {
        sort(a.begin(), a.end());
        int j = 0, n = a.size();
        Trie* root = new Trie();
        auto insert = [&](int i) {
            Trie* t = root;
            for(int j = 20; j >= 0; j--) {
                if(a[i] & (1 << j)) {
                    if(t->r == nullptr) t->r = new Trie();
                    t = t->r;
                } else {
                    if(t->l == nullptr) t->l = new Trie();
                    t = t->l;
                }
                t->cnt++;
            }
        };
        auto erase = [&](int i) {
            Trie* t = root;
            for(int j = 20; j >= 0; j--) {
                if(a[i] & (1 << j)) {
                    t = t->r;
                } else {
                    t = t->l;
                }
                t->cnt--;
            }
        };
        auto get = [&](int x) {
            Trie* t = root;
            int ans = 0;
            for(int j = 20; j >= 0; j--) {
                if(x & (1 << j)) {
                    if(t->l != nullptr && t->l->cnt > 0) t = t->l, ans += 1 << j;
                    else t = t->r;
                } else {
                    if(t->r != nullptr && t->r->cnt > 0) t = t->r, ans += 1 << j;
                    else t = t->l;
                }
            }
            return ans;
        };
        int ans = 0;
        for(int i = 0; i < n; i++) {
            while(j <= i && abs(a[j] - a[i]) > min(a[i], a[j])) {
                erase(j);
                j++;
            }
            if(j < i) ans = max(get(a[i]), ans);
            insert(i);
        }
        return ans;
    }
};
