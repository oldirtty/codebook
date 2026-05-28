// Armazena strings para buscas eficientes por prefixo
// O(N) por inserção e busca, onde N = tamanho da string
//
// Usos comuns em CP:
//   - Contar strings com determinado prefixo
//   - Verificar se string/prefixo existe
//   - XOR máximo com Trie binária (ver abaixo)
//
// Como usar:
//   Trie t;
//   t.insert("hello");
//   t.search("hello")  → true  (string completa existe)
//   t.search("hell")   → false (prefixo existe mas string não foi inserida)
//   t.startsWith("hell") → true  (prefixo existe)
//   t.count("hel")     → quantas strings inseridas começam com "hel"

struct Trie {
    struct Node {
        int filho[26];  // índice dos filhos (a=0, b=1, ..., z=25)
        int fim;        // quantas strings terminam aqui
        int passa;      // quantas strings passam por este nó
        Node() : fim(0), passa(0) { fill(filho, filho + 26, -1); }
    };

    vector<Node> nos;

    Trie() { nos.emplace_back(); } // nó raiz = índice 0

    void insert(const string& s) {
        int cur = 0;
        for (char c : s) {
            int ch = c - 'a';
            if (nos[cur].filho[ch] == -1) {
                nos[cur].filho[ch] = nos.size();
                nos.emplace_back();
            }
            cur = nos[cur].filho[ch];
            nos[cur].passa++;
        }
        nos[cur].fim++;
    }

    // Retorna true se a string completa foi inserida
    bool search(const string& s) {
        int cur = 0;
        for (char c : s) {
            int ch = c - 'a';
            if (nos[cur].filho[ch] == -1) return false;
            cur = nos[cur].filho[ch];
        }
        return nos[cur].fim > 0;
    }

    // Retorna true se alguma string inserida começa com s
    bool startsWith(const string& s) {
        int cur = 0;
        for (char c : s) {
            int ch = c - 'a';
            if (nos[cur].filho[ch] == -1) return false;
            cur = nos[cur].filho[ch];
        }
        return true;
    }

    // Quantas strings inseridas começam com o prefixo s
    int count(const string& s) {
        int cur = 0;
        for (char c : s) {
            int ch = c - 'a';
            if (nos[cur].filho[ch] == -1) return 0;
            cur = nos[cur].filho[ch];
        }
        return nos[cur].passa;
    }
};