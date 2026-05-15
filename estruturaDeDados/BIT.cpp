struct FenwickTree {
  vector<int> bit; // binary indexed tree
  int n;

  FenwickTree(int n) {
    this->n = n;
    bit.assign(n, 0);
  }

    FenwickTree(vector<int> const &v) : FenwickTree(v.size()){
        for (int i = 0; i < v.size(); ++i)
            add(i, v[i]);
    }

  int soma(int r) {
    int ret = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1) ret += bit[r];
    return ret;
  }

  int soma(int l, int r) {
    return soma(r) - soma(l - 1);
  }

  void add(int idx, int delta) {
    for (; idx < n; idx = idx | (idx + 1)) bit[idx] += delta;
  }
};
