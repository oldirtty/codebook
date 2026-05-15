// a^b O(logN)
ll exp(ll a, ll b, const ll M = 1e9 + 7) {
  a %= M;
  ll res = 1;

  while (b) {
    if (b % 2) res = res * a % M;
    a = a * a % M;
    b /= 2;
  }
  return res;
}