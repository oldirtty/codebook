// === Josephus Problem ===
// n pessoas numeradas 0..n-1 em círculo, remove k-ésima a cada passo
// Retorna posição do sobrevivente (0-indexed)
//
// Complexidade: O(n) ingênuo, O(log n) para k=2, O(k log n) caso geral
//
// Fórmula clássica: josephus(n,k) = (josephus(n-1,k) + k) % n

// --- k fixo = 2 (recorrência eficiente O(log n)) ---
// Base: josephus(1) = 0
// josephus(2n)   = 2*josephus(n) + 1
// josephus(2n+1) = 2*josephus(n) - 1
ll josephus2(ll n) {
    if (n == 1) return 0;
    if (n & 1) return 2 * josephus2(n / 2) + 1;
    return 2 * josephus2(n / 2) - 1;
}

// --- k arbitrário O(k log n) ---
ll josephus(ll n, ll k) {
    if (n == 1) return 0;
    if (k == 1) return n - 1;
    if (k > n) return (josephus(n - 1, k) + k) % n;
    ll cnt = n / k;
    ll res = josephus(n - cnt, k);
    res -= n % k;
    if (res < 0) res += n;
    else res += res / (k - 1);
    return res;
}

// --- Versão iterativa O(n) para n pequeno ---
ll josephus_iter(ll n, ll k) {
    ll res = 0;
    for (ll i = 2; i <= n; i++)
        res = (res + k) % i;
    return res; // 0-indexed
}