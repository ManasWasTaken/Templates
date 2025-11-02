// JAI SHREE RAM //
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) 8
#endif
const int M=1e9+7;
#define int long long

typedef long double ftype;
const ftype EPS = 1e-9;
const ftype PI = acosl(-1.0L);

/* ----------------- 2D Point Struct ------------------ */
struct point2d {
    ftype x, y;
    point2d() : x(0), y(0) {}
    point2d(ftype x, ftype y) : x(x), y(y) {}

    point2d& operator+=(const point2d &p) { x += p.x; y += p.y; return *this; }
    point2d& operator-=(const point2d &p) { x -= p.x; y -= p.y; return *this; }
    point2d& operator*=(ftype k) { x *= k; y *= k; return *this; }
    point2d& operator/=(ftype k) { x /= k; y /= k; return *this; }

    point2d operator+(const point2d &p) const { return point2d(*this) += p; }
    point2d operator-(const point2d &p) const { return point2d(*this) -= p; }
    point2d operator*(ftype k) const { return point2d(*this) *= k; }
    point2d operator/(ftype k) const { return point2d(*this) /= k; }

    bool operator==(const point2d &p) const { return fabsl(x - p.x) < EPS && fabsl(y - p.y) < EPS; }
    bool operator<(const point2d &p) const { return x < p.x - EPS || (fabsl(x - p.x) < EPS && y < p.y - EPS); }
};
point2d operator*(ftype k, point2d p) { return p * k; }

/* ----------------- 3D Point Struct ------------------ */
struct point3d {
    ftype x, y, z;
    point3d() : x(0), y(0), z(0) {}
    point3d(ftype x, ftype y, ftype z) : x(x), y(y), z(z) {}

    point3d& operator+=(const point3d &p) { x += p.x; y += p.y; z += p.z; return *this; }
    point3d& operator-=(const point3d &p) { x -= p.x; y -= p.y; z -= p.z; return *this; }
    point3d& operator*=(ftype k) { x *= k; y *= k; z *= k; return *this; }
    point3d& operator/=(ftype k) { x /= k; y /= k; z /= k; return *this; }

    point3d operator+(const point3d &p) const { return point3d(*this) += p; }
    point3d operator-(const point3d &p) const { return point3d(*this) -= p; }
    point3d operator*(ftype k) const { return point3d(*this) *= k; }
    point3d operator/(ftype k) const { return point3d(*this) /= k; }
};
point3d operator*(ftype k, point3d p) { return p * k; }

/* ----------------- 2D Utility Functions ------------------ */
ftype dot(point2d a, point2d b) { return a.x * b.x + a.y * b.y; }
ftype cross(point2d a, point2d b) { return a.x * b.y - a.y * b.x; }
ftype norm(point2d a) { return dot(a, a); }
ftype absval(point2d a) { return sqrtl(norm(a)); }

ftype dist(point2d a, point2d b) { return absval(a - b); }
ftype angle(point2d a, point2d b) { return acosl(dot(a, b) / (absval(a) * absval(b))); }

point2d unit(point2d a) { ftype len = absval(a); return (len < EPS ? point2d(0,0) : a / len); }

int orientation(point2d a, point2d b, point2d c) {
    ftype v = cross(b - a, c - a);
    if (fabsl(v) < EPS) return 0; // collinear
    return (v > 0 ? 1 : -1); // 1 = counterclockwise, -1 = clockwise
}

point2d rotate(point2d a, ftype ang) {
    ftype cs = cosl(ang), sn = sinl(ang);
    return {a.x * cs - a.y * sn, a.x * sn + a.y * cs};
}

point2d rotateAround(point2d a, point2d p, ftype ang) {
    return p + rotate(a - p, ang);
}

point2d proj(point2d a, point2d b) { // projection of a onto b
    return (dot(a, b) / norm(b)) * b;
}

bool onSegment(point2d a, point2d b, point2d p) { // collinearity && p is between a and b
    return fabsl(cross(b - a, p - a)) < EPS && dot(p - a, p - b) <= EPS;
}

// Line intersection: a1 + t*d1 and a2 + s*d2
bool line_intersect(point2d a1, point2d d1, point2d a2, point2d d2, point2d &res) {
    ftype det = cross(d1, d2);
    if (fabsl(det) < EPS) return false; // Parallel or coincident
    res = a1 + (cross(a2 - a1, d2) / det) * d1;
    return true;
}

// Check if two line segments [a,b] and [c,d] intersect
bool segments_intersect(point2d a, point2d b, point2d c, point2d d) {
    int o1 = orientation(a, b, c);
    int o2 = orientation(a, b, d);
    int o3 = orientation(c, d, a);
    int o4 = orientation(c, d, b);

    // General case: intersecting at a single point
    if (o1 != o2 && o3 != o4) return true;

    // Special cases: collinear segments
    if (o1 == 0 && onSegment(a, b, c)) return true;
    if (o2 == 0 && onSegment(a, b, d)) return true;
    if (o3 == 0 && onSegment(c, d, a)) return true;
    if (o4 == 0 && onSegment(c, d, b)) return true;

    // Otherwise, no intersection
    return false;
}

ftype dist_point_line(point2d p, point2d a, point2d b) {
    return fabsl(cross(b - a, p - a)) / absval(b - a);
}

ftype dist_point_segment(point2d p, point2d a, point2d b) {
    if (dot(b - a, p - a) < 0) return absval(p - a);
    if (dot(a - b, p - b) < 0) return absval(p - b);
    return dist_point_line(p, a, b);
}

bool left(point2d a, point2d b, point2d p) {
    return cross(b - a, p - a) > EPS;
}
bool right(point2d a, point2d b, point2d p) {
    return cross(b - a, p - a) < -EPS;
}

/* ----------------- 3D Utility Functions ------------------ */
ftype dot(point3d a, point3d b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
point3d cross(point3d a, point3d b) {
    return {a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x};
    }
ftype triple(point3d a, point3d b, point3d c) { return dot(a, cross(b, c)); }
ftype norm(point3d a) { return dot(a, a); }
ftype absval(point3d a) { return sqrtl(norm(a)); }
point3d unit(point3d a) { ftype len = absval(a); return (len < EPS ? point3d(0,0,0) : a / len); }

point3d intersect_planes(point3d a1, point3d n1,
    point3d a2, point3d n2,
    point3d a3, point3d n3) {
    point3d x(n1.x, n2.x, n3.x);
    point3d y(n1.y, n2.y, n3.y);
    point3d z(n1.z, n2.z, n3.z);
    point3d d(dot(a1, n1), dot(a2, n2), dot(a3, n3));
    return point3d(triple(d, y, z),
                   triple(x, d, z),
                   triple(x, y, d)) / triple(n1, n2, n3);
}

/* ----------------- Polygon Utilities ------------------ */
ftype polygon_area(const vector<point2d> &p) {
    ftype area = 0;
    for (int i = 0, n = p.size(); i < n; i++)
        area += cross(p[i], p[(i + 1) % n]);
    return fabsl(area) / 2;
}

point2d polygon_centroid(const vector<point2d> &poly) {
    ftype A = 0, Cx = 0, Cy = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        ftype cross_val = cross(poly[i], poly[(i + 1) % n]);
        A += cross_val;
        Cx += (poly[i].x + poly[(i + 1) % n].x) * cross_val;
        Cy += (poly[i].y + poly[(i + 1) % n].y) * cross_val;
    }
    A *= 0.5;
    if (fabsl(A) < EPS) return poly[0];
    Cx /= (6 * A);
    Cy /= (6 * A);
    return {Cx, Cy};
}

bool point_in_polygon(const vector<point2d> &poly, point2d p) {
    bool inside = false;
    int n = poly.size();
    for (int i = 0, j = n - 1; i < n; j = i++) {
        if (onSegment(poly[i], poly[j], p)) return true;
        bool intersect = ((poly[i].y > p.y) != (poly[j].y > p.y)) &&
                         (p.x < (poly[j].x - poly[i].x) * (p.y - poly[i].y) / (poly[j].y - poly[i].y) + poly[i].x);
        if (intersect) inside = !inside;
    }
    return inside;
}

/* ----------------- Convex Hull (Monotone Chain) ------------------ */
vector<point2d> convex_hull(vector<point2d> pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    if (pts.size() < 3) return pts;
    vector<point2d> lower, upper;

    for (auto &p : pts) {
        while (lower.size() >= 2 && cross(lower.back() - lower[lower.size() - 2], p - lower.back()) <= 0) lower.pop_back();
        lower.push_back(p);
    }
    for (int i = (int)pts.size() - 1; i >= 0; i--) {
        auto p = pts[i];
        while (upper.size() >= 2 && cross(upper.back() - upper[upper.size() - 2], p - upper.back()) <= 0) upper.pop_back();
        upper.push_back(p);
    }

    lower.pop_back(); upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}


void solve(){
    
}
int32_t main(){
    cout<<fixed;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<setprecision(15)<<fixed;
    int t=1;
    while(t--){
       solve(); 
    }
    return 0;
}