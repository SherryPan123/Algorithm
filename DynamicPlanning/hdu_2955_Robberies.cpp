//01背包，但需要把原问题转化一下
//要求在概率(连乘p_i) > P的情况下使(累加m_i)最大
//转化为求在总金额到达j时不被抓的最大概率（因为概率越乘越小）
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const int MAXN = 110;
double dp[10100];
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        double P;
        int N;
        int m[MAXN];
        double p[MAXN];
        scanf("%lf%d", &P, &N);
        P = 1 - P;
        int sum = 0;
        for (int i = 0; i < N; i++) {
            scanf("%d%lf", &m[i], &p[i]);
            p[i] = 1 - p[i];
            sum = sum + m[i];
        }
        memset(dp, 0, sizeof(dp));
        dp[0] = 1.0;
        for (int i = 0; i < N; i++) {
            for (int j = sum; j >= m[i]; j--) {
                dp[j] = max(dp[j], dp[j - m[i]] * p[i]);
            }
        }
        for (int j = sum; j >= 0; j--) {
            if (dp[j] > P) {
                printf("%d\n", j);
                break;
            }
        }
    }
    return 0;
}
