class lazy {
	public:
	vector<long long> t, cnt;
	vector<int> p;
	int n;
	lazy(int _n) : n(1) {
		while(n < _n) n *= 2;
		t.assign(n * 2, 0);
		p.assign(n * 2, 0);
		cnt.assign(n * 2, 0);
		for(int i = 0; i < _n; i++) cnt[i + n] = 1;
		for(int i = n - 1; i > 0; i--) cnt[i] = cnt[i * 2] + cnt[i * 2 + 1];
	}
	void push(int i) {
		if(p[i] % 2) t[i] = cnt[i] - t[i];
		if(i < n) {
			p[i * 2] += p[i];
			p[i * 2 + 1] += p[i];
		}
		p[i] = 0;
	}
	long long flip(int i, int tl, int tr, int l, int r) {
		if(p[i]) push(i);
		if(tl >= r || tr <= l) return t[i];
		if(l <= tl && tr <= r) {
			p[i]++;
			push(i);
			return t[i];
		}
		int tm = (tl + tr) >> 1;
		return (t[i] = flip(i * 2, tl, tm, l, r) + flip(i * 2 + 1, tm, tr, l, r));
	}
	void flip(int l, int r) {
		flip(1, 0, n, l, r);
	}
	void flip(int i) {
		flip(1, 0, n, i, i + 1);
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
};

class Solution {
public:
    vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        int n = nums1.size();
        lazy st(n);
        for(int i = 0; i < n; i++) {
            if(nums1[i]) st.flip(i);
        }
        vector<long long> ans;
        long long sum = 0;
        for(int i = 0; i < n; i++) sum += nums2[i];
        for(auto& v: queries) {
            if(v[0] == 1) {
                st.flip(v[1], v[2] + 1);
            } else if(v[0] == 2) {
                sum += st.sum(0, n) * v[1];
            } else ans.push_back(sum);
        }
        return ans;
    }
};
