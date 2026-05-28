// Prim
// O((V + E) * logV)

const int MAXN = 1e5+1;
bitset<MAXN> visitado;

int prim() {
    priority_queue<pair<int,int>> pq; // {peso, no}
    pq.emplace(0,1); // começa no no 1

    int sum = 0;
    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();

        if (visitado[u]) continue;

        sum += -w;
        visitado[u] = true;

        for (auto& [v,w] : adj[u]) // adj = {no, peso}
            if (!visitado[v])
                pq.emplace(-w, v);
    }

    return visitado[n]? sum : -1;
}

// Kruskal (usa Union-find)
// O(E * logE)
// N precisa guardar grafo, soh arestas
struct Edge {
    int a,b, c;
};
vector<Edge> arestas;
vector<int> p;

int kruskal() {
    for (int i = 1; i <= n; ++i) p[i] = i;
    sort(arestas.begin(), arestas.end(), [](auto a, auto b){
        return a.c < b.c;
    });

    int sum = 0;
    for (auto& e : arestas) {
        if (find(e.a) != find(e.b)) {
            join(e.a, e.b);
            sum += e.c;
        }
    }

    return find(1)==find(n)? sum : -1;
}

int find(int x) {
    if (x == p[x]) return x;
    return p[x] = find(p[x]);
}

void join(int x, int y) {
    p[find(x)] = find(y);
}