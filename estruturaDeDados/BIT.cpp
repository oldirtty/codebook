// O(logN)
struct FenwickTree {
    vector<int> bit;
    int n;

    FenwickTree(int n) : n(n), bit(n + 1, 0) {}

    FenwickTree(vector<int> const& v) : FenwickTree(v.size()) {
        for (int i = 0; i < (int)v.size(); i++)
        add(i + 1, v[i]);
    }

    // Soma prefixo [1, r]
    int soma(int r) {
        int ret = 0;
        for (; r > 0; r -= r & (-r))
        ret += bit[r];
        return ret;
    }

    // Soma intervalo [l, r] (1-based)
    int soma(int l, int r) {
        return soma(r) - soma(l - 1);
    }

    // Adiciona delta no índice idx (1-based)
    void add(int idx, int delta) {
        for (; idx <= n; idx += idx & (-idx))
        bit[idx] += delta;
    }
};