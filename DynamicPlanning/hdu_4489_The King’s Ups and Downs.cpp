// 一道想了一段时间的递推
// 问交错排列的种数，一开始想歪了，递推式总也不对，不是漏情况就是多算了
// 后来换一种思路，枚举最后一个数插入的位置，这样就不重不漏了
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
long long dp[22];
long long multi(int m) {
    long long sum = 1;
    for (int i = m; i >= 1; i--) {
        sum = sum * i;
    }
    return sum;
}
long long C(int m, int r) {
    if (r == 0) return 1;
    long long mm = multi(m);
    long long rr = multi(r);
    long long m_r = multi(m - r);
    return mm / rr / m_r;
}
int main() {
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i < 21; i++) {
        dp[i] = 0;
        for (int j = 0; j <= i - 1; j++) {
            long long lft = dp[j] / 2;
            if (lft == 0) lft = 1;
            long long rt = dp[i - 1 - j] / 2;
            if (rt == 0) rt = 1;
            long long mid = C(i - 1, j);
            dp[i] += lft * mid * rt;
        }
    }
    int P;
    scanf("%d", &P);
    while (P--) {
        int D, n;
        scanf("%d%d", &D, &n);
        printf("%d %lld\n", D, dp[n]);
    }
    return 0;
}
