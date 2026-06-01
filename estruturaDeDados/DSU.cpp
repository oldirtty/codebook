// O(α(N)) ≈ O(1)

vector<int> pai, tam;
void init(int n) {
  pai.resize(n+1);
  tam.assign(n+1, 1);
  iota(pai.begin(), pai.end(), 0); // pai[i] = i
}

int find(int x) {
  if (x == pai[x]) return x;
  return pai[x] = find(pai[x]); // path compression
}

// Union by Size: anexa a árvore menor na maior
void join(int x, int y) {
  x = find(x), y = find(y);
  if (x == y) return;
  if (tam[x] < tam[y]) swap(x, y);

  pai[y] = x;
  tam[x] += tam[y];
}

// Verifica se dois elementos estão no mesmo conjunto
bool mesmoConjunto(int x, int y) {
  return find(x) == find(y);
}

// Retorna o tamanho do componente que contém x
int tamanho(int x) {
  return tam[find(x)];
}