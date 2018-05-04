#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int a[1005][1005];
int d1[1005][1005], d2[1005][1005], d3[1005][1005], d4[1005][1005];
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    d1[1][1] = a[1][1];
    for (int j = 2; j <= m; j++) {
        d1[1][j] = d1[1][j - 1] + a[1][j];
    }
    for (int i = 2; i <= n; i++) {
        d1[i][1] = d1[i - 1][1] + a[i][1];
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= m; j++) {
            d1[i][j] = max(d1[i - 1][j], d1[i][j - 1]) + a[i][j];
        }
    }

    d2[1][m] = a[1][m];
    for (int j = m - 1; j >= 1; j--) {
        d2[1][j] = d2[1][j + 1] + a[1][j];
    }
    for (int i = 2; i <= n; i++) {
        d2[i][m] = d2[i - 1][m] + a[i][m];
    }
    for (int i = 2; i <= n; i++) {
        for (int j = m - 1; j >= 1; j--) {
            d2[i][j] = max(d2[i - 1][j], d2[i][j + 1]) + a[i][j];
        }
    }

    d3[n][1] = a[n][1];
    for (int i = n - 1; i >= 1; i--) {
        d3[i][1] = d3[i + 1][1] + a[i][1];
    }
    for (int j = 2; j <= m; j++) {
        d3[n][j] = d3[n][j - 1] + a[n][j];
    }
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 2; j <= m; j++) {
            d3[i][j] = max(d3[i + 1][j], d3[i][j - 1]) + a[i][j];
        }
    }

    d4[n][m] = a[n][m];
    for (int i = n - 1; i >= 1; i--) {
        d4[i][m] = d4[i + 1][m] + a[i][m];
    }
    for (int j = m; j >= 1; j--) {
        d4[n][j] = d4[n][j + 1] + a[n][j];
    }
    for (int i = n - 1; i >= 1; i--) {
        for (int j = m - 1; j >= 1; j--) {
            d4[i][j] = max(d4[i + 1][j], d4[i][j + 1]) + a[i][j];
        }
    }

    int mx = -1;
    for (int i = 2; i <= n - 1; i++) {
        for (int j = 2; j <= m - 1; j++) {
            int dis = max(d1[i - 1][j] + d2[i][j + 1] + d4[i + 1][j] + d3[i][j - 1],
                          d2[i - 1][j] + d4[i][j + 1] + d3[i + 1][j] + d1[i][j - 1]);
            mx = max(mx, dis);
        }
    }
    cout << mx << endl;
    return 0;
}
/*
3 4
1 2 3 4
5 6 7 8
9 10 11 12
*/
