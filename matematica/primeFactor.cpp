// --- Fatoração de um único número ---
// Retorna mapa {primo -> expoente}
// Exemplo: 12 = 2^2 * 3^1 → {{2,2},{3,1}}
// O(sqrt(N))
map<int,int> factor(int n) {
    map<int,int> fat;
    for (int p = 2; p * p <= n; p++) {
        while (n % p == 0) {
        fat[p]++;
        n /= p;
        }
    }
    // Fator primo restante > sqrt(N)
    if (n > 1) fat[n]++;
    return fat;
}

// --- Menor fator primo (SPF) ---
// Pré-computa spf[i] = menor fator primo de i
// Pré-processamento: O(N * log(logN))
// Fatoração de qualquer n <= N: O(logN)
vector<int> spf;
void buildSPF(int n) {
    iota(spf.begin(), spf.end(), 0);
    for (int p = 2; p * p <= n; p++) {
        if (spf[p] == p) { // p é primo
            for (int j = p * p; j <= n; j += p)
                if (spf[j] == j)
                    spf[j] = p; // marca menor fator
        }
    }
}

map<int,int> factorSPF(int n) {
    map<int,int> fat;
    while (n > 1) {
        fat[spf[n]]++;
        n /= spf[n];
    }
    return fat;
}