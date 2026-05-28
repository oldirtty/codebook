// Usa ponteiros em vez de array estático
// O(logN) por operação, O(Q logN) espaço total (Q = número de updates)
//
// Quando usar no lugar da SegTree estática:
// - N muito grande (até 1e18) mas poucas operações
// - Coordenadas não compactadas (ex: queries em [1, 1e9])
// - Quer evitar alocar 4*N de antemão
//
// Uso:
// DinamicSegTree st;
// st.update(st.root, 1, N, pos, val);
// st.query(st.root, 1, N, l, r);

struct DinamicSegTree {
    struct Node {
        ll val;
        Node *left, *right;
        Node() : val(0), left(nullptr), right(nullptr) {}
    };
    
    Node* root = new Node();
    
    void update(Node* no, ll l, ll r, ll pos, ll val) {
        if (l == r) {
            no->val = val;
            return;
        }
        ll m = l + (r - l) / 2;
        // Cria filho só quando necessário (dinâmico)
        if (pos <= m) {
            if (!no->left) no->left = new Node();
            update(no->left, l, m, pos, val);
        } else {
            if (!no->right) no->right = new Node();
            update(no->right, m + 1, r, pos, val);
        }
        // Filho inexistente contribui com 0
        no->val = (no->left ? no->left->val : 0) + (no->right ? no->right->val : 0);
    }
    
    ll query(Node* no, ll l, ll r, ll ql, ll qr) {
        if (!no || l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return no->val;
        ll m = l + (r - l) / 2;
        return query(no->left, l, m, ql, qr) + query(no->right, m + 1, r, ql, qr);
    }
};