// Shortest Path Faster Algorithm
// Bellman-Ford com fila — relaxa só vértices que mudaram
// O(V * E) pior caso, O(E) caso médio na prática
//
// Detecta ciclo negativo contando quantas vezes
// cada vértice entra na fila (> N vezes = ciclo)
//
// Representação: lista de adjacência (diferente do Bellman-Ford)
// Mais eficiente que Bellman-Ford em grafos esparsos
//
// Para caminho máximo: negar todos os pesos
// Para ciclo positivo: negar todos os pesos e detectar ciclo negativo

const ll INF = 1e18;
vector<pair<int,ll>> adj[MXN]; // adj[u] = {v, peso}
vector<ll> dist, pai;
vector<int> cnt; // quantas vezes cada vértice entrou na fila
vector<bool> inQueue;
int n, m;

// Retorna true se há ciclo negativo alcançável a partir de s
bool spfa(int s) {
  dist.assign(n + 1, INF);
  pai.assign(n + 1, -1);
  cnt.assign(n + 1, 0);
  inQueue.assign(n + 1, false);

  dist[s] = 0;
  queue<int> q;
  q.push(s);
  inQueue[s] = true;
  cnt[s] = 1;

  while (!q.empty()) {
    int u = q.front(); q.pop();
    inQueue[u] = false;

    for (auto [v, w] : adj[u]) {
      if (dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        pai[v] = u;
        if (!inQueue[v]) {
          q.push(v);
          inQueue[v] = true;
          cnt[v]++;
          // Vértice entrou na fila mais de N vezes → ciclo negativo
          if (cnt[v] > n) return true;
        }
      }
    }
  }
  return false;
}

// Retorna true se existe qualquer ciclo negativo no grafo
// (incluindo componentes não alcançáveis por s)
// Inicializa dist=0 para todos: simula supersource
bool acharCicloNegativo() {
  dist.assign(n + 1, 0);
  pai.assign(n + 1, -1);
  cnt.assign(n + 1, 0);
  inQueue.assign(n + 1, false);

  queue<int> q;
  for (int i = 1; i <= n; i++) {
    q.push(i);
    inQueue[i] = true;
    cnt[i] = 1;
  }

  while (!q.empty()) {
    int u = q.front(); q.pop();
    inQueue[u] = false;

    for (auto [v, w] : adj[u]) {
      if (dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        pai[v] = u;
        if (!inQueue[v]) {
          q.push(v);
          inQueue[v] = true;
          cnt[v]++;
          if (cnt[v] > n) return true;
        }
      }
    }
  }
  return false;
}