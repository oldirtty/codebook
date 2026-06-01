// Algoritmo de Hierholzer
// Para grafos não direcionados:
// O(V + E)

vector<vector<pair<int,int>>> adj; // {vizinho, id_aresta}
vector<bool> usado;
int n, m;

int temCaminhoEuleriano() {
  int ini = -1, impar = 0;

  for (int i = 1; i <= n; i++) {
    if (!adj[i].empty() && ini == -1) ini = i;
    if (adj[i].size() & 1)
      impar++, ini = i;
  }

  if (ini == -1) return 2;
  if (impar != 0 && impar != 2) return 0;

  vector<int> ptr(n + 1, 0); // próxima aresta a visitar
  stack<int> st;
  vector<int> caminho;
  st.push(ini);

  while (!st.empty()) {
    int u = st.top();
    // Avança ptr até achar aresta não usada
    while (ptr[u] < (int)adj[u].size() && usado[adj[u][ptr[u]].second])
      ptr[u]++;
    if (ptr[u] < (int)adj[u].size()) {
      auto [v, id] = adj[u][ptr[u]++];
      usado[id] = true;
      st.push(v);
    }
    else {
      caminho.push_back(u);
      st.pop();
    }
  }

  for (int i = 0; i < m; i++)
    if (!usado[i]) return 0;

  reverse(caminho.begin(), caminho.end());
  for (auto i : caminho) cout << i << ' ';
  cout << '\n';

  return impar == 0 ? 2 : 1;
}

// Para grafos direcionados:
// O(V + E)
vector<vector<int>> adj;
vector<int> in, out;
int n;
int temCaminhoEuleriano() {
  int ini = -1, fim = -1, temCiclo = 1;

  for (int i = 1; i <= n; i++) {
    if (out[i] - in[i] == 1) {
      if (ini != -1) return 0; // Invalido: soh 1 no pode ter out > in
      ini = i;
    }
    else if (in[i] - out[i] == 1) {
      if (fim != -1) return 0; // Invalido: soh 1 no pode ter in > out
      fim = i;
    }
    else if (in[i] != out[i])
      return 0; // Invalido: |in-out| de um no NAO pode ser > 1
  }

  // Se não achou ini, é circuito
  if (ini == -1) {
    temCiclo = 2;
    for (int i = 1; i <= n; i++) {
      if (out[i] > 0) {
        ini = i;
        break;
      }
    }
  }

  if (ini == -1) return 0;

  // Algoritmo de Hierholzer
  stack<int> st;
  vector<int> caminho;
  st.push(ini);

  while (!st.empty()) {
    int u = st.top();
    if (!adj[u].empty()) {
      int v = adj[u].back();
      adj[u].pop_back();
      st.push(v);
    }
    else {
      caminho.push_back(u);
      st.pop();
    }
  }

  // Verifica se o grafo é conexo
  for (int i = 1; i <= n; i++)
    if (!adj[i].empty()) return 0;

  reverse(caminho.begin(), caminho.end());
  for (auto& i : caminho)
    cout << i << ' ';
  cout << '\n';

  return temCiclo; // 1 = Caminho, 2 = Ciclo
}