// build: O(N log N)  |  get: O(log N)

// === 1D ===
struct Compress {
  vector<int> c;
  void add(int x) { c.push_back(x); }
  void build() {
    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());
  }
  int get(int x) { return lower_bound(c.begin(), c.end(), x) - c.begin(); }
  int size() { return c.size(); }
};

// === 2D ===
struct Compress2D {
  vector<int> cx, cy;
  void add(int x, int y) { cx.push_back(x); cy.push_back(y); }
  void build() {
    sort(cx.begin(), cx.end());
    cx.erase(unique(cx.begin(), cx.end()), cx.end());
    sort(cy.begin(), cy.end());
    cy.erase(unique(cy.begin(), cy.end()), cy.end());
  }
  int get_x(int x) { return lower_bound(cx.begin(), cx.end(), x) - cx.begin(); }
  int get_y(int y) { return lower_bound(cy.begin(), cy.end(), y) - cy.begin(); }
  int size_x() { return cx.size(); }
  int size_y() { return cy.size(); }
};