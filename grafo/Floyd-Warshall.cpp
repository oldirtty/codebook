// O(V^3); S(V^2)
int n, m;
void floyd_warshall(vector<vector<ll>>& d){
  for (int k = 1; k <= n; ++k)
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        if (d[i][k] < INF && d[k][j] < INF)
          d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 
}
// no main:
vector<vector<ll>> d(n+1, vector<ll>(n+1, INF));
for (int i = 1; i <= n; ++i)
  d[i][i] = 0; // dist = 0 para auto-laço