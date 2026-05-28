// O(V + E) - Algoritmo de Kosaraju
// Encontra todos os componentes fortemente conexos em grafo direcionado

const int MAXN = 1e5+1;
vector<vector<int>> grafo, grafoReverso;
vector<int> ordem; // Ordem topológica
bitset<MAXN> visitado;
int n, m; // vértices, arestas

// ordenação topológica
void dfsOrdem(int u) {
    visitado[u] = true;
    for (auto& v : grafo[u])
        if (!visitado[v])
            dfsOrdem(v);
    ordem.push_back(u);
}

// DFS no grafo reverso para encontrar SCCs
void dfsComponente(int u) {
    visitado[u] = true;
    for (auto& v : grafoReverso[u])
        if (!visitado[v])
            dfsComponente(v);
}

// Retorna vetor com um representante de cada componente
vector<int> kosaraju() {
    for (int i = 1; i <= n; ++i)
        if (!visitado[i])
            dfsOrdem(i);
    reverse(ordem.begin(), ordem.end());

    visitado.reset();
    vector<int> componentes;

    for (auto& u : ordem) {
        if (!visitado[u]) {
            dfsComponente(u);
            componentes.push_back(u);
        }
    }

    return componentes;
}