// Encontra o maior palíndromo centrado em cada posição
// O(N) — linear, sem expansão quadrática
//
// Ideia central: reaproveita palíndromos já calculados
// usando a simetria do espelho em torno do centro atual
//
// String transformada: intercala '#' entre caracteres
// "abc" → "@#a#b#c#$"
//   - '@' e '$' são sentinelas (evitam checagem de bounds)
//   - '#' entre caracteres unifica palíndromos pares e ímpares
//   - p[i] = raio do palíndromo centrado em i na string transformada
//   - palíndromo real de tamanho p[i] (par ou ímpar)
//
// Exemplo: "abacaba"
// t = "@#a#b#a#c#a#b#a#$"
// p =   0 1 0 3 0 1 0 7 0 1 0 3 0 1 0
//
// Como usar:
//   1. Chame manacher(s) para pré-computar p[]
//   2. Use getLongest(i, true)  → raio do maior palíndromo ímpar centrado em i
//      Use getLongest(i, false) → raio do maior palíndromo par centrado entre i e i+1
//   3. O tamanho real do palíndromo é igual ao raio retornado
//      ímpar: tamanho = 2*raio + 1,  começa em i - raio
//      par:   tamanho = 2*raio,      começa em i - raio + 1
//
// Exemplo de uso (maior palíndromo):
//   manacher(s);
//   for (int i = 0; i < s.size(); i++) {
//     int r = getLongest(i, true);   // ímpar
//     // palíndromo: s.substr(i - r, 2*r + 1)
//     int r = getLongest(i, false);  // par
//     // palíndromo: s.substr(i - r + 1, 2*r)
//   }

vector<int> p;

void manacher(const string& s) {
  string t = "@";
  for (char c : s) t += "#" + string(1, c);
  t += "#$";

  int n = t.size();
  p.assign(n, 0);

  int c = 0, r = 0;
  for (int i = 1; i < n - 1; i++) {
    int mirror = 2 * c - i;
    if (i < r) p[i] = min(r - i, p[mirror]);
    while (t[i + p[i] + 1] == t[i - p[i] - 1]) p[i]++;
    if (i + p[i] > r) { c = i; r = i + p[i]; }
  }
}

// ímpar: centro real em t[2*i + 2]   (o próprio caractere)
// par:   centro real em t[2*i + 3]   (o '#' entre i e i+1)
int getLongest(int i, bool isOdd) {
  return p[2 * i + 2 + !isOdd];
}