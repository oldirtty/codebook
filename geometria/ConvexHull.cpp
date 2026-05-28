// === Andrew's Monotone Chain ===
// Complexidade: O(N * logN)
// Retorna pontos do casco em ordem CCW, sem pontos colineares na borda

vector<Point> convex_hull(vector<Point> pts) {
    if (pts.size() <= 1) return pts;
    sort(pts.begin(), pts.end());
    vector<Point> hull(pts.size() * 2);
    int k = 0;

    // Lower hull
    for (int i = 0; i < pts.size(); i++) {
        while (k >= 2 && orient(hull[k-2], hull[k-1], pts[i]) <= EPS) k--;
        hull[k++] = pts[i];
    }

    // Upper hull
    for (int i = pts.size()-2, t = k+1; i >= 0; i--) {
        while (k >= t && orient(hull[k-2], hull[k-1], pts[i]) <= EPS) k--;
        hull[k++] = pts[i];
    }

    hull.resize(k-1);
    return hull;
}

// Área do polígono (pontos em ordem CCW ou CW)
// Complexidade: O(N)
ld polygon_area(vector<Point> &poly) {
    ld area = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++)
        area += poly[i].cross(poly[(i+1) % n]);
    return fabs(area) / 2.0;
}

// Perímetro do polígono
// Complexidade: O(N)
ld polygon_perimeter(vector<Point> &poly) {
    ld per = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++)
        per += dist(poly[i], poly[(i+1) % n]);
    return per;
}

// Ponto dentro do polígono? (assume polígono simples)
// 0 = fora, 1 = dentro, 2 = na borda
// Complexidade: O(N)
int point_in_polygon(vector<Point> &poly, Point p) {
    int n = poly.size(), wn = 0;
    for (int i = 0; i < n; i++) {
        Point a = poly[i], b = poly[(i+1) % n];
        if (dist_to_seg(a, b, p) < EPS) return 2; // na borda
        if (a.y <= p.y + EPS) {
            if (b.y > p.y + EPS && orient(a, b, p) > EPS) wn++;
        } else {
            if (b.y <= p.y + EPS && orient(a, b, p) < -EPS) wn--;
        }
    }
    return wn != 0;
}