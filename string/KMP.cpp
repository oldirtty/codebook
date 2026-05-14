// p[i] = comprimento do maior prefixo próprio do padrão s que também é sufixo do texto t[0..i]
// Prefixo/Sufixo próprio é um prefixo/sufixo que não é a string inteira
// Usos:
//   - Busca de padrão único (igual Z, mas mais natural para busca online)
//   - Busca online/streaming: processa t caractere a caractere sem ter t completo
//   - Menor período de string: n - lps[n-1] é o período mínimo
//   - Autômato de string: transformar lps em DFA para múltiplas consultas no mesmo padrão

// O(m), m = s.size()
vector<int> pi(string s){
    vector<int> p(s.size());
    for (int i = 1, j = 0; i < s.size(); ++i){
        while (j > 0 && s[j] != s[i]) j = p[j-1];
        if (s[j] == s[i]) j++;
        p[i] = j;
    }
    return p;
}

// O(n + m) KMP: busca padrao s em texto t, retorna índices de cada ocorrência (0-based)
vector<int> kmp(string& t, string& s){
    vector<int> p = pi(s+'$'), match;
    for (int i = 0, j = 0; i < t.size(); ++i){
        while (j > 0 && s[j] != t[i]) j = p[j-1];
        if (s[j] == t[i]) j++;
        if (j==s.size()) match.push_back(i-j+1);
    }
    return match;
}