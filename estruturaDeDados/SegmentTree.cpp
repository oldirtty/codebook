struct SegTree {
  vector<ll> vet, tree;
  int n;

  SegTree(int n) : n(n) {
    tree.resize(4 * n);
    vet.resize(n + 1);
  }

  void build(int no, int l, int r) {
    if (l == r) {
      tree[no] = vet[l];
      return;
    }

    int m = l + (r - l) / 2;
    build(2 * no, l, m);
    build(2 * no + 1, m + 1, r);

    tree[no] = tree[2 * no] + tree[2 * no + 1];
  }

  void update(int no, int l, int r, int pos, ll val) {
    if (l == r) {
      tree[no] = val;
      return;
    }
    int m = l + (r - l) / 2;

    if (pos <= m) update(2 * no, l, m, pos, val);
    else
      update(2 * no + 1, m + 1, r, pos, val);

    tree[no] = tree[2 * no] + tree[2 * no + 1];
  }

  ll query(int no, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) return 0;
    if (l >= ql && r <= qr) return tree[no];

    int m = l + (r - l) / 2;
    return m;
  }
};