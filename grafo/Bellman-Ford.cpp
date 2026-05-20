// Calcula a menor distancia
// entre a a todos os vertices a
// detecta ciclo negativo
// Retorna 1 se ha ciclo negativo
// Nao precisa representar o grafo,
// soh armazenar as arestas
//
// Para achar ciclo positivo basta
// negar todos os pesos, logo
// um ciclo positivo vira negativo
//
// Para caminho máximo:
// Inicilizar dist com -INF
// e funcao agora detecta ciclo
// positivo na n-ésima iteração
//
// O(V * E)

const ll INF = 1e18; // 1e9 para int
struct Edge {
  int a, b, c;
};
vector<Edge> arestas;
vector<ll> dist, pai; // pai[i] = nó anterior a i
int n, m;

bool bellman_ford(int s) {
  dist.assign(n + 1, INF);
  pai.assign(n + 1, -1);
  dist[s] = 0;

  int ultimo_relaxado;
  for (int i = 0; i < n; ++i) {
    ultimo_relaxado = -1;
    for (Edge& aresta : arestas) {
      if (dist[aresta.a] < INF && dist[aresta.b] > dist[aresta.a] + aresta.c) {
        dist[aresta.b] = dist[aresta.a] + aresta.c;
        pai[aresta.b] = aresta.a;
        ultimo_relaxado = aresta.b;
      }
    }
  }

  return ultimo_relaxado != -1; // true se tem ciclo negativo
}

// Returna true se existe qualquer ciclo negativo
bool acharCicloNegativo() {
  dist.assign(n+1, 0);
  pai.assign(n+1, -1);
  
  ll ciclo;
	for (int i = 0; i < n; ++i) {
    ciclo = -1;
    for (Edge& a : arestas) {
      if (dist[a.a] < INF && dist[a.b] > dist[a.a] + a.c) {
        dist[a.b] = dist[a.a] + a.c;
        pai[a.b] = a.a;
        ciclo = a.b;
      }
    }
  }

  if (ciclo == -1) return false; // não tem ciclo negativo

  for (int i = 0; i < n; ++i) ciclo = pai[ciclo];

  stack<ll> caminho;
  for (ll atual = ciclo;; atual = pai[atual]) {
    caminho.push(atual);
    if (atual == ciclo && caminho.size() > 1)
      break;
  }
  while (!caminho.empty()) {
    cout << caminho.top() << ' ';
    caminho.pop();
  }
  cout << '\n';

  return true;
}