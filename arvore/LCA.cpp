// Build: O(N log N) | Query: O(log N)
int LOG, n;
void dfs_lca(int u, int p) {
  up[0][u] = p;
  for (int i = 1; i <= LOG; ++i)
    up[i][u] = up[i-1][up[i-1][u]];

  for (auto v : tree[u]) {
    if (v != p) {
      depth[v] = depth[u] + 1;
      dfs_lca(v, u);
    }
  }
}

int lca(int u, int v) {
  if (depth[u] < depth[v]) swap(u, v);
  int diff = depth[u] - depth[v];

  for (int i = 0; i <= LOG; ++i)
    if (diff & (1 << i)) u = up[i][u];

  if (u == v) return u;

  for (int i = LOG; i >= 0; --i) {
    if (up[i][u] != up[i][v]) {
      u = up[i][u];
      v = up[i][v];
    }
  }

  return up[0][u];
}

void build_lca(int root = 0) {
  LOG = (int)ceil(log2(n));
  depth.assign(n+1, 0); // 1-based
  up.assign(LOG+1, vector<int>(n+1));
  tree.assign(n+1, {});
  dfs_lca(root, root);
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