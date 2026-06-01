// sa[i] = índice do i-ésimo menor sufixo de s (0-based)
// rank[i] = posição do sufixo i no SA
// lcp[i] = longest common prefix entre sa[i] e sa[i-1]
//
// Usos:
//   - Busca de padrão: binary search no SA
//   - Substring mais longa que aparece ≥ k vezes: maior intervalo de LCP ≥ k-1
//   - Número de substrings distintas: n*(n+1)/2 - sum(lcp)
//   - Comparar sufixos rapidamente: rank[i] < rank[j] => sufixo i < sufixo j
//   - Maior substring comum entre strings: concatenar com '#' e checar LCP
//

//O(N logN)
vector<int> build_sa(string s) {
  s += "$";
  int n = s.size();
  vector<int> sa(n), r(n), nr(n);
  iota(sa.begin(), sa.end(), 0);

  // ordena pelos primeiros caracteres
  sort(sa.begin(), sa.end(), [&](int i, int j) { return s[i] < s[j]; });

  r[sa[0]] = 0;
  for (int i = 1; i < n; i++)
    r[sa[i]] = r[sa[i-1]] + (s[sa[i]] != s[sa[i-1]]);

  // dobra o tamanho do prefixo comparado
  for (int k = 1; k < n; k <<= 1) {
    sort(sa.begin(), sa.end(), [&](int i, int j) {
      if (r[i] != r[j]) return r[i] < r[j];
      int ri = (i + k < n) ? r[i + k] : -1;
      int rj = (j + k < n) ? r[j + k] : -1;
      return ri < rj;
    });

    nr[sa[0]] = 0;
    for (int i = 1; i < n; i++)
      nr[sa[i]] = nr[sa[i-1]] + ((r[sa[i]] != r[sa[i-1]]) ||
        ((sa[i]+k < n ? r[sa[i]+k] : -1) != (sa[i-1]+k < n ? r[sa[i-1]+k] : -1)));

    r = nr;
    if (r[sa[n-1]] == n-1) break; // ranks todos distintos
  }

  return sa; // último elemento é o '$' (n-1)
}

// Kasai's algorithm O(N)
vector<int> build_lcp(string &s, vector<int> &sa) {
  int n = s.size();
  vector<int> rank(n), lcp(n);
  for (int i = 0; i < n; i++) rank[sa[i]] = i;

  int k = 0;
  for (int i = 0; i < n; i++) {
    if (rank[i] == n-1) { k = 0; continue; } // último no SA (o '$')
    int j = sa[rank[i] + 1];
    while (i + k < n && j + k < n && s[i+k] == s[j+k]) k++;
    lcp[rank[i]] = k;
    if (k) k--;
  }
  return lcp; // lcp[i] = LCP entre sa[i] e sa[i-1], lcp[0] = 0
}

// Busca padrão p: retorna {primeira, última} posição no SA
// s deve ter '$' no final
// Quantidade de p no texto será second - first + 1, se exisitr p (first != -1)
// O(|p| * logN)
pair<int,int> find_pattern(string &s, vector<int> &sa, string &p) {
  int n = s.size(), m = p.size();
  int L = 0, R = n-1;

  // lower_bound
  int first = -1;
  while (L <= R) {
    int mid = (L + R) / 2;
    int cmp = s.compare(sa[mid], m, p);
    if (cmp >= 0) {
      if (cmp == 0) first = mid;
      R = mid - 1;
    }
    else L = mid + 1;
  }
  if (first == -1) return {-1, -1};

  // upper_bound
  L = 0, R = n-1;
  int last = first;
  while (L <= R) {
    int mid = (L + R) / 2;
    int cmp = s.compare(sa[mid], m, p);
    if (cmp <= 0) {
      if (cmp == 0) last = mid;
      L = mid + 1;
    }
    else R = mid - 1;
  }
  return {first, last};
}