// Build: O(N log N) | Query: O(log N)
vector<vector<int>> graph;
vector<vector<int>> up;
vector<int> depth;
int LOG;

void dfs_lca(int u, int p) {
    up[u][0] = p;
    for (int i = 1; i <= LOG; i++)
        up[u][i] = up[up[u][i-1]][i-1];

    for (int v : graph[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs_lca(v, u, graph);
        }
    }
}

void build_lca(int root = 0) {
    int n = graph.size();
    LOG = 32 - __builtin_clz(n);
    up.assign(n, vector<int>(LOG + 1));
    depth.assign(n, 0);
    dfs_lca(root, root, graph);
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);

    // Sobe u para mesma profundidade de v
    int diff = depth[u] - depth[v];
    for (int i = 0; i <= LOG; i++)
        if (diff & (1 << i)) u = up[u][i];

    if (u == v) return u;

    // Sobe ambos até o LCA
    for (int i = LOG; i >= 0; i--)
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    return up[u][0];
}

// Distância entre dois vértices
int dist_lca(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}

// k-ésimo ancestral (k=0: próprio nó, k=1: pai)
int kth_ancestor(int u, int k) {
    for (int i = 0; i <= LOG; i++)
        if (k & (1 << i)) u = up[u][i];
    return u;
}