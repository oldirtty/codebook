// a^b O(logN)
ll bin_pow(ll a, ll b, const ll MOD = 1e9 + 7) {
  a %= MOD;
  ll res = 1;

  while (b) {
    if (b % 2) res = res * a % MOD;
    a = a * a % MOD;
    b /= 2;
  }
  return res;
}

ll inverso(ll a, ll MOD) {
	bin_pow(a, MOD-2); // MOD deve ser primo
}
