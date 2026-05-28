// Retorna mapa {primo -> expoente}
// Exemplo: 12 = 2^2 * 3^1 → {{2,2},{3,1}}

// --- Fatoração de um único número ---
// O(sqrt(N))
map<int,int> fatorar(int n) {
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
int spf[MXN];
void buildSPF(int n) {
    for (int i = 1; i <= n; i++) spf[i] = i;
    for (ll p = 2; p * p <= n; p++) {
        if (spf[p] == p) { // p é primo
        for (int j = p * p; j <= n; j += p)
            if (spf[j] == j) spf[j] = p; // marca menor fator
        }
    }
}

map<int,int> fatorarSPF(int n) {
    map<int,int> fat;
    while (n > 1) {
        fat[spf[n]]++;
        n /= spf[n];
    }
    return fat;
}