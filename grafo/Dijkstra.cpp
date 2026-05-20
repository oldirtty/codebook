// O((V + E)logV) ou O(E logV) - S(V)
const ll N = 2e5 + 1, INF = 1e18;
vector<pair<ll, ll>> graph[N];
vector<ll> dist(N);
int n, m;

void dijkstra(int s) {
  dist.assign(n + 1, INF);
  priority_queue<pair<ll, ll>> pq;
  dist[s] = 0;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [du, u] = pq.top();
    pq.pop();
    if (-du > d[u])
      continue; // otimização

    // v = vizinho, w = peso
    for (auto &[v, w] : graph[u]) {
      if (d[u] + w < d[v]) {
        d[v] = d[u] + w;
        pq.push({-d[v], v}); // -d[v] p manter ordenação crescente
      }
    }
  }
}
