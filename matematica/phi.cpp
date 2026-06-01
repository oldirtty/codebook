// φ(n) = quantidade de inteiros em [1, n] coprimos com n
// Propriedades:
//   φ(1) = 1
//   p primo → φ(p) = p - 1
//   p primo → φ(p^k) = p^k - p^(k-1)
//   mdc(a,b)=1 → φ(a*b) = φ(a) * φ(b)  (multiplicativa)
//
// Fórmula: φ(n) = n * Π (1 - 1/p) para todo primo p | n
//    = n * Π (p-1)/p
// Exemplo: φ(12) = 12 * (1-1/2) * (1-1/3) = 12 * 1/2 * 2/3 = 4
//
// Uso com exponenciação modular:
//   a^b mod c = a^(b % φ(c) + φ(c)) mod c   se b >= φ(c)
//       = a^b mod c          se b <  φ(c)

// --- Totiente de um único número ---
// O(sqrt(N))
int phi(int n) {
  int res = n;
  // Fatoramos n e para cada primo p encontrado
  // aplicamos res = res * (p-1)/p
  // (equivalente a res -= res/p, evitando divisão com perda)
  for (int p = 2; p * p <= n; p++) {
    if (n % p == 0) {
      // p é fator primo de n
      res = res / p * (p - 1); // res *= (1 - 1/p)
      while (n % p == 0) n /= p; // remove todas as ocorrências de p
    }
  }
  // Se ainda sobrou um fator > 1, ele é primo
  if (n > 1) res = res / n * (n - 1);
  return res;
}

// --- Tabela de totientes para [1, n] ---
// O(N * log(logN)) — igual ao crivo de Eratóstenes
// Ideia: para cada primo p, multiplica todos os múltiplos por (p-1)/p
int phi_table[MAXN];
void phitable(int n) {
  // Inicializa φ(i) = i para todo i (valor antes de aplicar os fatores)
  for (int i = 1; i <= n; i++) phi_table[i] = i;

  for (int p = 2; p <= n; p++) {
    // Se φ(p) ainda é p, então p é primo (não foi modificado por nenhum fator)
    if (phi_table[p] == p) {
    // Aplica o fator (p-1)/p em todos os múltiplos de p
    for (int j = p; j <= n; j += p)
      phi_table[j] = phi_table[j] / p * (p - 1);
    }
  }
}