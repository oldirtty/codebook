// Resolve sistema: x ≡ a[i] (mod m[i])
// Complexidade: O(N log M) onde M = prod(m[i])
// Retorna {x, M} ou {-1, -1} se sem solução

pair<ll, ll> crt(vector<ll> &a, vector<ll> &m) {
    ll x = 0, M = 1;
    for (int i = 0; i < a.size(); i++) {
        ll ai = a[i] % m[i];
        if (ai < 0) ai += m[i];

        // Resolve: M * t ≡ ai - x (mod m[i])
        ll g = gcd(M, m[i]);
        if ((ai - x) % g != 0) return {-1, -1};

        ll M_ = M / g, m_ = m[i] / g;
        ll t = ((ai - x) / g) * inv_mod(M_ % m_, m_) % m_;
        if (t < 0) t += m_;

        x += t * M;
        M *= m[i] / g;
        x %= M;
    }
    return {x, M};
}

// Garner's algorithm: recupera x mod MOD dado x ≡ a[i] (mod m[i])
// Requer m[i] coprimos entre si
// Complexidade: O(N²)
ll garner(vector<ll> &a, vector<ll> &m, ll MOD) {
    int n = a.size();
    vector<ll> x(n);
    for (int i = 0; i < n; i++) {
        x[i] = a[i];
        for (int j = 0; j < i; j++) {
            x[i] = (x[i] - x[j]) * inv_mod(m[j], m[i]) % m[i];
            if (x[i] < 0) x[i] += m[i];
        }
    }
    ll ans = 0, mult = 1;
    for (int i = 0; i < n; i++) {
        ans = (ans + x[i] * mult) % MOD;
        mult = mult * m[i] % MOD;
    }
    return ans;
}