// O(logN)
struct FenwickTree {
  vector<int> v;
  int n;

  FenwickTree(int n) : n(n), v(n + 1, 0) {}

  FenwickTree(vector<int> const& v) : FenwickTree(v.size()) {
    for (int i = 0; i < (int)v.size(); i++) add(i + 1, v[i]);
  }

  // Soma prefixo [1, r]
  int sum(int r) {
    int ret = 0;
    for (; r > 0; r -= r & (-r)) ret += v[r];
    return ret;
  }

  // Soma intervalo [l, r] (1-based)
  int sum(int l, int r) {
    return sum(r) - sum(l - 1);
  }

  // Adiciona delta no índice idx (1-based)
  void add(int idx, int delta) {
    for (; idx <= n; idx += idx & (-idx)) v[idx] += delta;
  }
};
