// Operações com Bitmask
// Índices 0-based. "bit i" = posição i da direita.
// Uso típico: representar subconjuntos de {0, 1, ..., N-1}

// --- Operações básicas ---
mask | (1 << i)   // liga bit i
mask & ~(1 << i)  // desliga bit i
mask ^ (1 << i)   // inverte bit i
(mask >> i) & 1   // lê bit i (0 ou 1)
mask & (1 << i)   // testa bit i (0 se desligado)

// --- Propriedades do conjunto ---
__builtin_popcount(mask)   // quantos bits ligados
__builtin_ctz(mask)    // índice do bit menos significativo ligado
__builtin_clz(mask)    // zeros à esquerda (cuidado: UB se mask==0)
(mask & (mask-1)) == 0   // mask é potência de 2 (exatamente 1 bit)
mask == 0          // conjunto vazio

// --- Iteração ---

// Todos os subconjuntos de {0..N-1}
for (int mask = 0; mask < (1 << n); mask++) { }

// Todos os bits ligados de mask
for (int tmp = mask; tmp; tmp &= tmp-1) {
  int i = __builtin_ctz(tmp); // índice do bit
}

// Todos os subconjuntos de mask (incluindo vazio)
for (int sub = mask; sub > 0; sub = (sub-1) & mask) { }
// Atenção: não itera o subconjunto vazio; adicione caso sub==0 se necessário

// --- Máscaras úteis ---
(1 << n) - 1   // todos os n bits ligados
(1 << i)     // só o bit i ligado

// --- Padrão DP em subconjuntos ---
// dp[mask][v] = valor considerando exatamente os vértices em mask,
//         terminando/passando em v
// Transição típica:
//   int prev = mask ^ (1 << v);  // remove v do conjunto
//   dp[mask][v] = f(dp[prev][u]) para u vizinho de v em prev
//
// Exemplo (Hamiltonian Path — O(2^N * N^2)):
// dp[mask][v] += dp[mask ^ (1<<v)][u] * adj[u][v]
//   para todo u em (mask ^ (1<<v)) com adj[u][v] > 0