//01����������Ҫ��ԭ����ת��һ��
//Ҫ���ڸ���(����p_i) > P�������ʹ(�ۼ�m_i)���
//ת��Ϊ�����ܽ���jʱ����ץ�������ʣ���Ϊ����Խ��ԽС��
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
