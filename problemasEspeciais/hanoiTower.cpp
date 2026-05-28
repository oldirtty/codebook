// Torre de Hanoi: move n discos de 'a' para 'b' usando 'c' como auxiliar
// Complexidade: O(2^n), gera exatamente 2^n - 1 movimentos
vector<pair<int, int>> moves;
void hanoi(int n, int a, int b, int c) {
    if (n == 1) moves.push_back({a, b});
    else {
        hanoi(n - 1, a, c, b);
        hanoi(1, a, b, c);
        hanoi(n - 1, c, b, a);
    }
}
// Uso: hanoi(n, 1, 3, 2);