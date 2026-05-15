// O(n + m) médio, O(nm) pior caso
// Busca de padrão p em texto t usando hashing de janela deslizante
// Usos:
//   - Busca de múltiplos padrões simultaneamente (coloca todos num set de
//   hashes)
//   - Detectar strings repetidas / substrings duplicadas (+busca binária)
//
// Atenção: colisões são raras mas possíveis — confirme com strcmp se necessário
// Use double hashing (dois módulos) para competições com anti-hash tests

const ll MOD = 1e9 + 7, BASE = 31;

vector<int> rabin_karp(string t, string p) {
  int n = t.size(), m = p.size();
  vector<int> ocorrencias;

  // Pré-computa potências de BASE
  vector<ll> pw(max(n, m) + 1);
  pw[0] = 1;
  for (int i = 1; i <= max(n, m); i++) pw[i] = pw[i - 1] * BASE % MOD;

  // Hash do padrão
  ll hp = 0;
  for (int i = 0; i < m; i++) hp = (hp + (p[i] - 'a' + 1) * pw[i]) % MOD;

  // Hash prefixo do texto: h[i] = hash(t[0..i-1])
  vector<ll> h(n + 1, 0);
  for (int i = 0; i < n; i++) h[i + 1] = (h[i] + (t[i] - 'a' + 1) * pw[i]) % MOD;

  // Hash de t[l..r-1] = (h[r] - h[l]) / pw[l]  ≡  (h[r] - h[l]) * inv(pw[l])
  // Evita inversão modular: compara (h[r] - h[l]) com hp * pw[l]
  for (int i = 0; i + m <= n; i++) {
    ll ht = (h[i + m] - h[i] + MOD) % MOD;
    if (ht == hp * pw[i] % MOD) ocorrencias.push_back(i);
  }

  return ocorrencias; // índices (0-based) onde p ocorre em t
}