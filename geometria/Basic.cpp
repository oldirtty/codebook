// === 2D Geometry Basics ===
// Complexidade: O(1) para todas operações básicas

using ld = long double;
const ld EPS = 1e-9;
const ld PI = acos(-1);

struct Point {
    ld x, y;
    Point(ld x = 0, ld y = 0) : x(x), y(y) {}

    Point operator+(Point p) { return Point(x + p.x, y + p.y); }
    Point operator-(Point p) { return Point(x - p.x, y - p.y); }
    Point operator*(ld d) { return Point(x * d, y * d); }
    Point operator/(ld d) { return Point(x / d, y / d); }

    bool operator<(Point p) const {
        if (fabs(x - p.x) > EPS) return x < p.x;
        return y < p.y - EPS;
    }
    bool operator==(Point p) { return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS; }

    ld dist2() { return x * x + y * y; }
    ld dist() { return sqrt(dist2()); }
    ld dot(Point p) { return x * p.x + y * p.y; }
    ld cross(Point p) { return x * p.y - y * p.x; }
    ld angle() { return atan2(y, x); }
    Point rotate(ld a) { return Point(x*cos(a) - y*sin(a), x*sin(a) + y*cos(a)); }
    Point perp() { return Point(-y, x); } // rotaciona 90° CCW
    Point unit() { return *this / dist(); }
};

// Distância entre pontos
ld dist(Point a, Point b) { return (a - b).dist(); }

// Ângulo entre vetores (0 a PI)
ld angle(Point a, Point b) { return acos(a.dot(b) / (a.dist() * b.dist())); }

// Orientação: 0 = colinear, >0 = CCW, <0 = CW
ld orient(Point a, Point b, Point c) { return (b - a).cross(c - a); }

// Projeção de p na reta ab
Point project(Point a, Point b, Point p) {
    Point v = b - a;
    return a + v * ((p - a).dot(v) / v.dist2());
}

// Distância de ponto p à reta ab
ld dist_to_line(Point a, Point b, Point p) {
    return fabs((p - a).cross(b - a)) / (b - a).dist();
}

// Distância de ponto p ao segmento ab
ld dist_to_seg(Point a, Point b, Point p) {
    if (a == b) return dist(a, p);
    Point v = b - a;
    ld t = (p - a).dot(v) / v.dist2();
    if (t < 0) return dist(a, p);
    if (t > 1) return dist(b, p);
    return dist_to_line(a, b, p);
}

// Interseção de retas ab e cd (assume não paralelas)
Point line_intersect(Point a, Point b, Point c, Point d) {
    Point v1 = b - a, v2 = d - c;
    ld t = (c - a).cross(v2) / v1.cross(v2);
    return a + v1 * t;
}

// Segmentos ab e cd se intersectam?
bool seg_intersect(Point a, Point b, Point c, Point d) {
    ld o1 = orient(a, b, c), o2 = orient(a, b, d);
    ld o3 = orient(c, d, a), o4 = orient(c, d, b);
    if (o1 == 0 && o2 == 0 && o3 == 0 && o4 == 0) {
        if (b < a) swap(a, b); if (d < c) swap(c, d);
        return !(b < c || d < a);
    }
    return ((o1 > EPS) != (o2 > EPS)) && ((o3 > EPS) != (o4 > EPS));
}