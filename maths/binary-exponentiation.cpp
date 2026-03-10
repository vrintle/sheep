// https://leetcode.com/problems/sum-of-k-digit-numbers-in-a-range/

class Solution {
public:
    int sumOfNumbers(int l, int r, int k) {
        int mod = 1e9 + 7;
      
        auto exp = [&](int x, int p) {
            int ans = 1;
            for(int b = 0, res = x % mod; b < 30; b++, res = (1LL * res * res) % mod) {
                if(p & (1LL << b)) {
                    ans = (ans * 1LL * res) % mod;
                }
            }
            return ans;
        };
      
        auto inv = [&](int x) {
            return exp(x, mod - 2);
        };
      
        int ans = 0, x = r - l + 1;
        int tot = exp(x, k);
        int fr = tot * 1LL * inv(x) % mod;
        int p10 = exp(10, k);
        p10 = (p10 - 1 + mod) % mod;
        int p11 = p10 * 1LL * inv(9) % mod;
        // cout << tot << ' ' << fr << ' ' << p11 << endl;
        for(int i = l; i <= r; i++) {
            ans = (ans + (i * 1LL * p11 % mod) * fr) % mod;
        }
        return ans;
    }
};
