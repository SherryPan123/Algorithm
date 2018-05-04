// 求满足I,D,?三种字符组成的字符串，数字的排列个数
// dp[i][j]表示到第i个字符最大的一个数为j的排列数，根据当前字符为'I','D'或'?'决定哪个递推式

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
long long dp[1010][1010];
const long long Mod = 1000000007;
int n;
int pre_sum[2][1010];
void init() {
    memset(dp, 0, sizeof(dp));
    memset(pre_sum, 0, sizeof(pre_sum));
    dp[0][1] = 1;
    pre_sum[0][1] = 1;
}
int main() {
    string s;
    while (cin >> s) {
        n = s.length() + 1;
        init();
        int id = 0;
        long long sum = 1;
        for (int i = 1; i < s.length() + 1; i++) {
            char c = s[i - 1];
            long long cur = 0;
            for (int j = 1; j <= i + 1; j++) {
                if (c == 'I') {
                    dp[i][j] = pre_sum[id][j - 1] % Mod;
                } else if (c == 'D') {
                    dp[i][j] = ((sum - pre_sum[id][j - 1]) % Mod + Mod) % Mod;
                } else {
                    dp[i][j] = (sum + dp[i][j]) % Mod;
                }
                pre_sum[id ^ 1][j] = (pre_sum[id ^ 1][j - 1] + dp[i][j]) % Mod;
                cur = (cur + dp[i][j]) % Mod;
                //cout<<i<<", "<<j<<", "<<dp[i][j]<<endl;
            }
            sum = cur;
            id = id ^ 1;
        }
        long long ans = 0;
        for (int j = 1; j <= n; j++) {
            ans = (ans + dp[n - 1][j]) % Mod;
        }
        cout << ans << endl;
    }
    return 0;
}
/*
IIDDDIIDDDIID
6913283
IIDDDIIDDDIIDIIDDDIIDDDIIDIIDDDIIDDDIIDIIDDDIIDDDIIDIIDDDIIDDDIIDIIDDDIIDDDIID
524858744
IIIIIIIDDDD???DDDDIIIDD???DDII?DDDI????DDDIIID??????DDDIIIDD????DDI??D
871850921
*/
