// O(N) build, O(logN) update e query
//
// Uso:
//     SegTree st(n);
//     for (int i = 1; i <= n; i++) st.v[i] = valor;
//     st.build(1, 1, n);
//     st.update(1, 1, n, pos, novoValor);    // atualiza posição pos
//     st.query(1, 1, n, l, r);               // soma em [l, r]
//
// Indexação 1-based. Nó 1 = raiz.
// Filho esquerdo de no = 2*no, direito = 2*no+1
// tree[4*N] garante espaço suficiente para a árvore

struct SegTree {
    vector<int> v, tree;
    int n;

    SegTree(int n) : n(n) {
        tree.resize(4*n);
        v.resize(n + 1);
    }

    // Constrói a árvore a partir de v[]
    // Chame: build(1, 1, n)
    void build(int no, int l, int r) {
        if (l == r) {
            tree[no] = v[l];
            return;
        }
        int m = l + (r - l) / 2;
        build(2 * no, l, m);
        build(2 * no + 1, m + 1, r);
        tree[no] = tree[2 * no] + tree[2 * no + 1]; // merge (operacao de soma)
    }

    // Atualiza posição pos com valor val (substitui)
    // Chame: update(1, 1, n, pos, val)
    void update(int no, int l, int r, int pos, int val) {
        if (l == r) {
            tree[no] = val;
            return;
        }
        int m = l + (r - l) / 2;
        if (pos <= m) update(2 * no, l, m, pos, val);
        else update(2 * no + 1, m + 1, r, pos, val);
        tree[no] = tree[2 * no] + tree[2 * no + 1]; // atualiza nós pai
    }

    // Retorna soma em [ql, qr]
    // Chame: query(1, 1, n, ql, qr)
    int query(int no, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return 0; // fora do intervalo
        if (l >= ql && r <= qr) return tree[no]; // totalmente dentro
        int m = l + (r - l) / 2;

        return query(2 * no, l, m, ql, qr) + query(2 * no + 1, m + 1, r, ql, qr);
    }
};