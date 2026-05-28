// Knapsack 0/1 — cada item usado no máximo 1 vez
// dp[j] = maior valor com capacidade exatamente j
// Itera j de trás pra frente: evita usar o item duas vezes
// O(N * W)
void knapsack01(int n, int W, vector<ll>& w, vector<ll>& v) {
  vector<ll> dp(W + 1, 0);
  for (int i = 0; i < n; i++)
    for (int j = W; j >= w[i]; j--)
      dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
  cout << dp[W] << '\n';
}

// Knapsack ilimitado — cada item pode ser usado infinitas vezes
// Itera j da frente pra trás: permite reusar o mesmo item
// O(N * W)
void knapsack(int n, int W, vector<ll>& w, vector<ll>& v) {
  vector<ll> dp(W + 1, 0);
  for (int i = 0; i < n; i++)
    for (int j = w[i]; j <= W; j++)
      dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
  cout << dp[W] << '\n';
}

// Knapsack 0/1 — quando W é muito grande, inverte dimensões
// dp[j] = menor peso para atingir exatamente valor j
// Útil quando V (soma dos valores) << W
// O(N * V)
void knapsack01ByValue(int n, int W, vector<ll>& w, vector<ll>& v) {
  ll total = 0;
  for (ll x : v) total += x;
  vector<ll> dp(total + 1, LLONG_MAX / 2);
  dp[0] = 0;
  for (int i = 0; i < n; i++)
    for (int j = total; j >= v[i]; j--)
      dp[j] = min(dp[j], dp[j - v[i]] + w[i]);
  ll ans = 0;
  for (ll j = 0; j <= total; j++)
    if (dp[j] <= W) ans = j;
  cout << ans << '\n';
}