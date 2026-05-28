// Levenshtein Distance
// Problema: menor custo para transformar string s em t
// Operações: inserir (custo 1), remover (custo 1), substituir (custo (s[i]!=t[j]))
// DP 2D: O(N*M) tempo, O(N*M) espaço
int editDistance(string& s, string& t) {
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 1e9));
    dp[0][0] = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i) dp[i][j] = min(dp[i][j], dp[i-1][j] + 1); // remove
            if (j) dp[i][j] = min(dp[i][j], dp[i][j-1] + 1);  // insere
            if (i && j) dp[i][j] = min(dp[i][j], dp[i-1][j-1] + (s[i-1] != t[j-1])); // substitui
        }
    }
    return dp[n][m];
}

// DP 1D: O(N*M) tempo, O(M) espaço
int editDistance1D(string& s, string& t) {
    int n = s.size(), m = t.size();
    vector<int> prev(m+1), cur(m+1);
    iota(prev.begin(), prev.end(), 0);
    for (int i = 1; i <= n; i++) {
        cur[0] = i;
        for (int j = 1; j <= m; j++) {
            cur[j] = min({prev[j] + 1, cur[j-1] + 1, prev[j-1] + (s[i-1] != t[j-1])});
        }
        swap(prev, cur);
    }
    return prev[m];
}