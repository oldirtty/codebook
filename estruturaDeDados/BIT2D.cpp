// O(logN * logM)
struct FenwickTree2D {
    vector<vector<int>> bit;
    int n, m;

    FenwickTree2D(int n, int m) : n(n), m(m), bit(n + 1, vector<int>(m + 1, 0)) {}

    // Adiciona delta em (x, y) (1-based)
    void add(int x, int y, int delta) {
        for (int i = x; i <= n; i += i & (-i))
        for (int j = y; j <= m; j += j & (-j))
            bit[i][j] += delta;
    }

    // Soma prefixo [1,1] até (x, y)
    int soma(int x, int y) {
        int ret = 0;
        for (int i = x; i > 0; i -= i & (-i))
        for (int j = y; j > 0; j -= j & (-j))
            ret += bit[i][j];
        return ret;
    }

    // Soma retângulo (x1,y1) até (x2,y2) (1-based)
    int soma(int x1, int y1, int x2, int y2) {
        return soma(x2, y2)
            - soma(x1 - 1, y2)
            - soma(x2, y1 - 1)
            + soma(x1 - 1, y1 - 1);
    }
};