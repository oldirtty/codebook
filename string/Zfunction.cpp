// O(n)
// z[i] = comprimento do maior prefixo de s que também é prefixo de s[i..]
// Usos:
//   - Busca de padrão: z(p + "#" + t), ocorrências onde z[i] == |p|
//   - Menor período de string: menor k tal que k | n e z[k] == n - k
//   - Contar prefixos distintos que ocorrem em s: acumular z[i] com cuidado
//   - Comparar sufixos rapidamente sem suffix array
vector<int> z_function(string s) {
  int n = s.size();
  vector<int> z(n);
  int l = 0, r = 0;
  for (int i = 1; i < n; i++) {
    if (i < r) z[i] = min(r - i, z[i - l]);

    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;

    if (i + z[i] > r) {
      l = i;
      r = i + z[i];
    }
  }
  return z;
}