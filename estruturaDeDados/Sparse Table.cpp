// Build: O(N * logN) | Query: O(1)
// Suporta operações idempotentes: min, max, gcd, lcm

vector<int> log2;
vector<vector<int>> st;

void build_sparse(vector<int> &v) {
    int n = v.size();
    log2.resize(n + 1);
    log2[1] = 0;
    for (int i = 2; i <= n; i++) log2[i] = log2[i/2] + 1;

    int K = log2[n] + 1;
    st.assign(K, vector<int>(n));
    st[0] = v;

    for (int j = 1; j < K; j++)
        for (int i = 0; i + (1 << j) <= n; i++)
            st[j][i] = min(st[j-1][i], st[j-1][i + (1 << (j-1))]);
}

// Retorna mínimo no intervalo [L, R] (0-indexed, inclusivo)
int query_min(int L, int R) {
    int j = log2[R - L + 1];
    return min(st[j][L], st[j][R - (1 << j) + 1]);
}

// Versão para vetor 2D: mínimo em submatriz
// Build: O(N * M * logN * logM) | Query: O(1)
vector<vector<vector<vector<int>>>> st2d;

void build_sparse2d(vector<vector<int>> &mat) {
    int n = mat.size(), m = mat[0].size();
    int K = log2[n] + 1, L = log2[m] + 1;
    st2d.assign(K, vector<vector<vector<int>>>(L, vector<vector<int>>(n, vector<int>(m))));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            st2d[0][0][i][j] = mat[i][j];

    for (int j = 1; j < L; j++)
        for (int i = 0; i < n; i++)
            for (int k = 0; k + (1 << j) <= m; k++)
                st2d[0][j][i][k] = min(st2d[0][j-1][i][k], st2d[0][j-1][i][k + (1 << (j-1))]);

    for (int i = 1; i < K; i++)
        for (int j = 0; j < L; j++)
            for (int k = 0; k + (1 << i) <= n; k++)
                for (int l = 0; l + (1 << j) <= m; l++)
                    st2d[i][j][k][l] = min(st2d[i-1][j][k][l], st2d[i-1][j][k + (1 << (i-1))][l]);
}

int query_min2d(int x1, int y1, int x2, int y2) {
    int i = log2[x2 - x1 + 1], j = log2[y2 - y1 + 1];
    return min({st2d[i][j][x1][y1],
                st2d[i][j][x1][y2 - (1 << j) + 1],
                st2d[i][j][x2 - (1 << i) + 1][y1],
                st2d[i][j][x2 - (1 << i) + 1][y2 - (1 << j) + 1]});
}