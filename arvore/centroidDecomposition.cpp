// O(N)
int n;
vector<vector<int>> tree;
// 1-based, subtree inclui o nó raiz = inicializa com 1
vector<int> subsize(n+1, 1);
void dfs(int u, int p) {
  for (auto& v : tree[u])
    if (v != p) {
      dfs(v,u);
      subsize[u] += subsize[v];
    }
}

int get_centroid(int u, int p) {
  for (auto& v : tree[u]) {
    if (v == p) continue;
    if (subsize[v] * 2 > n) return get_centroid(v, u);
  }
  return u;
}
