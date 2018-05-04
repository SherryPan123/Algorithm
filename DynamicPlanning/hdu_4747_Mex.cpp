#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
const int MAXN = 200010;
int n;
int a[MAXN], mex[MAXN];
map<int, int> nxt_pos;
// segment tree
struct Node {
  int mini, mx;
  long long sum;
  int lazy;
}tr[MAXN << 2];
void pushup(int id) {
  tr[id].mx = max(tr[id << 1].mx, tr[id << 1 | 1].mx);
  tr[id].mini = min(tr[id << 1].mini, tr[id << 1 | 1].mini);
  tr[id].sum = tr[id << 1].sum + tr[id << 1 | 1].sum;
  tr[id].lazy = -1;
}
void pushdown(int id, int m_lf, int m_rt) {
  if (tr[id].lazy != -1) {
    tr[id << 1].lazy = tr[id].lazy;
    tr[id << 1 | 1].lazy = tr[id].lazy;
    tr[id << 1].mini = tr[id << 1].mx = tr[id].lazy;
    tr[id << 1 | 1].mini = tr[id << 1 | 1].mx = tr[id].lazy;
    tr[id << 1].sum = tr[id].lazy * m_lf;
    tr[id << 1 | 1].sum = tr[id].lazy * m_rt;
    tr[id].lazy = -1;
  }
}
void build(int L, int R, int id) {
  if (L == R) {
    tr[id].mini = tr[id].mx = tr[id].sum = mex[L];
    tr[id].lazy = -1;
  } else {
    int mid = (L + R) >> 1;
    build(L, mid, id << 1);
    build(mid + 1, R, id << 1 | 1);
    pushup(id);
  }
}

void update(int L, int R, int id, int lf, int rt, int val) {
  if (lf <= L && R <= rt) {
    tr[id].sum = val * (R - L + 1);
    tr[id].lazy = val;
    tr[id].mini = tr[id].mx = val;
  } else {
    int mid = (L + R) >> 1;
    pushdown(id, mid - L + 1, R - mid);
    if (lf <= mid) update(L, mid, id << 1, lf, rt, val);
    if (rt > mid) update(mid + 1, R, id << 1 | 1, lf, rt, val);
    pushup(id);
  }
}
long long query(int L, int R, int id, int lf, int rt) {
  if (lf <= L && R <= rt) {
    return tr[id].sum;
  }
  int mid = (L + R) >> 1;
  pushdown(id, mid - L + 1, R - mid);
  long long ans = 0;
  if (lf <= mid) ans += query(L, mid, id << 1, lf, rt);
  if (rt > mid) ans += query(mid + 1, R, id << 1 | 1, lf, rt);
  return ans;
}
void getMex() {
  map<int, int> mymap;
  mex[1] = (a[1] == 0 ? 1 : 0);
  mymap[a[1]] = 1;
  for (int i = 2; i <= n; i++) {
    mymap[a[i]] = 1;
    if (mex[i - 1] != a[i]) mex[i] = mex[i - 1];
    else {
      int num = a[i] + 1;
      while (mymap[num] == 1) {
        num++;
      }
      mex[i] = num;
    }
  }
}
int search(int L, int R, int id, int val) {
  if (L >= R) {
    if (tr[id].mx <= val) return L + 1;
    else return L;
  }
  int mid = (L + R) >> 1;
  pushdown(id, mid - L + 1, R - mid);
  if (tr[id << 1].mx <= val) return search(mid + 1, R, id << 1 | 1, val);
  else return search(L, mid, id << 1, val);
}
int main() {
    while(~scanf("%d", &n)) {
        if (n == 0) break;
        nxt_pos.clear();
        map<int, int> mymap;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            if (mymap[a[i]] != 0) {
        int pre_pos = mymap[a[i]];
        nxt_pos[pre_pos] = i - 1;
      }
      mymap[a[i]] = i;
        }
        for (int i = 1; i <= n; i++) {
      if (nxt_pos[i] == 0) nxt_pos[i] = n;
    }
        // init
        getMex();
        long long sum = 0;
        // build tree
        build(1, n, 1);
        // get sum
        sum += query(1, n, 1, 1, n);
        // delete and sum
        for (int i = 1; i < n; i++){
      int k =  nxt_pos[i];
      int lf = search(1, n, 1, a[i]);
      if (lf < i + 1) lf = i + 1;
      if (lf <= k) update(1, n, 1, lf, k, a[i]);
      sum += query(1, n, 1, i + 1, n);
    }
    printf("%lld\n", sum);
    }
    return 0;
}
/*
14
0 2 0 1 0 5 2 0 3 0 4 1 2 5
6
0 2 0 1 0 5
5
0 2 0 1 0
*/
