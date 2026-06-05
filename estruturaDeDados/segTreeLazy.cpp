// O(N) build, O(logN) update e query
//
// Lazy: adia updates para filhos até que sejam necessários
// Sem lazy, update em intervalo seria O(N  * logN)
//
// Uso:
//  SegTreeLazy st(n);
//  for (int i = 1; i <= n; i++) st.v[i] = valor;
//  st.build(1, 1, n);
//  st.update(1, 1, n, l, r, val); // soma val em todos de [l, r]
//  st.query(1, 1, n, l, r);     // soma em [l, r]

struct SegTreeLazy {
  vector<ll> tree, lazy, v;
  int n;

  SegTreeLazy(int n) : n(n) {
    tree.resize(4*n, 0);
    lazy.resize(4*n, 0);
    v.resize(n + 1, 0);
  }

  void build(int no, int l, int r) {
    if (l == r) { tree[no] = v[l]; return; }
    int m = l + (r-l)/2;
    build(2*no, l, m);
    build(2*no + 1, m + 1, r);
    tree[no] = tree[2*no] + tree[2*no + 1];
  }

  // Desce o lazy do nó atual para seus filhos
  // Chamado antes de qualquer descida na árvore
  void pushDown(int no, int l, int r) {
    if (lazy[no] == 0) return;
    int m = l + (r-l)/2;
    // Aplica lazy nos filhos
    tree[2*no] += lazy[no] * (m - l + 1);
    tree[2*no + 1] += lazy[no] * (r - m);
    lazy[2*no] += lazy[no];
    lazy[2*no + 1] += lazy[no];
    lazy[no] = 0; // limpa lazy do nó atual
  }

  // Soma val em todos os elementos de [ql, qr]
  // Chame: update(1, 1, n, ql, qr, val)
  void update(int no, int l, int r, int ql, int qr, ll val) {
    if (l > qr || r < ql) return;
    if (l >= ql && r <= qr) {
      // Intervalo totalmente coberto: aplica lazy aqui e para
      tree[no] += val * (r - l + 1);
      lazy[no] += val;
      return;
    }
    pushDown(no, l, r); // desce lazy antes de dividir
    int m = l + (r-l)/2;
    update(2*no, l, m, ql, qr, val);
    update(2*no + 1, m + 1, r, ql, qr, val);
    tree[no] = tree[2*no] + tree[2*no + 1];
  }

  // Soma em [ql, qr]
  // Chame: query(1, 1, n, ql, qr)
  ll query(int no, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) return 0;
    if (l >= ql && r <= qr) return tree[no];
    pushDown(no, l, r); // desce lazy antes de dividir
    int m = l + (r-l)/2;
    return query(2*no, l, m, ql, qr) + query(2*no + 1, m + 1, r, ql, qr);
  }
};