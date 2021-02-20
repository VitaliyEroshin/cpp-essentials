// coded by Vitaliy Eroshin with LOVE
// Happy new year 2021!

#include <bits/stdc++.h>
#define int long long
using namespace std;

typedef int cType;
const long double eps = 1e-9;

struct Point {
    cType x;
    cType y;

    Point(cType x, cType y): x(x), y(y) {};
    Point(): x(0), y(0) {};

    void input() {
        cin >> x >> y;
    } 
};

struct Vector {
    cType x;
    cType y;

    Vector(Point A, Point B): x(B.x - A.x), y(B.y - A.y) {};
    Vector(): x(0), y(0) {};

    long double length() {
        return sqrt(x * x + y * y);
    }

    void input() {
        cin >> x >> y;
    }
};

struct Segment {
    Point A, B;

    Segment(Point A, Point B): A(A), B(B) {};
};

cType dotProduct (Vector A, Vector B) { 
    return A.x * B.x + A.y * B.y;
}

cType crossProduct (Vector A, Vector B) {
    return A.x * B.y - A.y * B.x;
}

long double triangleArea (Vector A, Vector B) {
    return 0.5 * crossProduct(A, B);
}

long double polarAngle (Point A) {
    long double angle = atan2(A.y, A.x);
    if (angle < 0) angle += 2 * M_PI;
    return angle;
}

long double unorientedAngle (Vector A, Vector B) {
    return acos(dotProduct(A, B) / (A.length() * B.length()));
}

long double distance (Segment ab, Point C) {
    Vector AB = Vector(ab.A, ab.B);
    Vector BA = Vector(ab.B, ab.A);
    Vector AC = Vector(ab.A, C);
    Vector BC = Vector(ab.B, C);

    if (dotProduct(AB, AC) < 0) 
        return AC.length();
    if (dotProduct(BA, BC) < 0) 
        return BC.length();
        
    if (AB.length() == 0) return 0;
    return crossProduct(AB, AC) / AB.length();
}

bool oppositeSign (long double a, long double b) {
    if (a > b) swap(a, b);
    return (a < 0) and (b > 0);
}

bool isInside (Segment S, Point C) {
    Vector AB = Vector(S.A, S.B);
    Vector BA = Vector(S.B, S.A);
    Vector AC = Vector(S.A, C);
    Vector BC = Vector(S.B, C);

    return crossProduct(AB, AC) >= 0 and crossProduct(BA, BC) >= 0; 
}

bool isCrossing (Segment AB, Segment CD) {
    Point C = CD.A;
    Point D = CD.B;
    long double d1 = distance(AB, C);
    long double d2 = distance(AB, D);
    if (fabs(d1) <= eps or fabs(d2) <= eps) return true;

    return oppositeSign(d1, d2) and (fabs(d1) + fabs(d2) <= Vector(C, D).length() or (isInside(AB, C) and isInside(AB, D)));
}

void solve() {
    Point A, B, C, D;
    A.input(); B.input(); C.input(); D.input();

    Segment AB = Segment(A, B);
    Segment CD = Segment(C, D);

    if (isCrossing(AB, CD)) cout << "YES";
    else cout << "NO";
}
