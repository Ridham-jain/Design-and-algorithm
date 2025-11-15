#include <iostream>
using namespace std;

struct Point {
    double x, y;
};

double cross(const Point &O, const Point &A, const Point &B) {
    return (A.x - O.x)*(B.y - O.y) - (A.y - O.y)*(B.x - O.x);
}

void swapP(Point &a, Point &b) {
    Point t = a; a = b; b = t;
}

void insertionSort(Point pts[], int n) {
    for (int i = 1; i < n; ++i) {
        Point key = pts[i];
        int j = i - 1;
        while (j >= 0 && (pts[j].x > key.x || (pts[j].x == key.x && pts[j].y > key.y))) {
            pts[j + 1] = pts[j];
            --j;
        }
        pts[j + 1] = key;
    }
}

int bruteHull(Point *pts, int n, Point *hull) {
    if (n <= 1) {
        if (n == 1) hull[0] = pts[0];
        return n;
    }
    int idx = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            bool left = false, right = false;
            for (int k = 0; k < n; ++k) {
                if (k == i || k == j) continue;
                double c = cross(pts[i], pts[j], pts[k]);
                if (c > 0) left = true;
                if (c < 0) right = true;
                if (left && right) break;
            }
            if (!(left && right)) {
                hull[idx++] = pts[i];
                hull[idx++] = pts[j];
            }
        }
    }
    int m = 0;
    for (int i = 0; i < idx; ++i) {
        bool dup = false;
        for (int j = 0; j < m; ++j) {
            if (hull[j].x == hull[i].x && hull[j].y == hull[i].y) {
                dup = true; break;
            }
        }
        if (!dup) hull[m++] = hull[i];
    }
    insertionSort(hull, m);
    return m;
}

int mergeHulls(Point *L, int nL, Point *R, int nR, Point *out) {
    if (nL == 0) { for (int i = 0; i < nR; ++i) out[i] = R[i]; return nR; }
    if (nR == 0) { for (int i = 0; i < nL; ++i) out[i] = L[i]; return nL; }

    int idxL = 0, idxR = 0;
    for (int i = 1; i < nL; ++i)
        if (L[i].x > L[idxL].x) idxL = i;
    for (int i = 1; i < nR; ++i)
        if (R[i].x < R[idxR].x) idxR = i;

    int iU = idxL, jU = idxR;
    bool cont = true;
    while (cont) {
        cont = false;
        while (cross(R[jU], L[iU], L[(iU + 1) % nL]) > 0)
            iU = (iU + 1) % nL;
        while (cross(L[iU], R[jU], R[(jU - 1 + nR) % nR]) < 0) {
            jU = (jU - 1 + nR) % nR;
            cont = true;
        }
    }

    int iLw = idxL, jLw = idxR;
    cont = true;
    while (cont) {
        cont = false;
        while (cross(R[jLw], L[iLw], L[(iLw - 1 + nL) % nL]) < 0)
            iLw = (iLw - 1 + nL) % nL;
        while (cross(L[iLw], R[jLw], R[(jLw + 1) % nR]) > 0) {
            jLw = (jLw + 1) % nR;
            cont = true;
        }
    }

    int cnt = 0;
    int i = iU;
    out[cnt++] = L[i];
    while (i != iLw) {
        i = (i + 1) % nL;
        out[cnt++] = L[i];
    }
    int j = jLw;
    out[cnt++] = R[j];
    while (j != jU) {
        j = (j + 1) % nR;
        out[cnt++] = R[j];
    }

    return cnt;
}

int divideHull(Point pts[], int l, int r, Point *hull) {
    int n = r - l + 1;
    if (n <= 5) return bruteHull(pts + l, n, hull);

    int mid = (l + r) >> 1;
    Point *HL = new Point[n];
    Point *HR = new Point[n];
    int nL = divideHull(pts, l, mid, HL);
    int nR = divideHull(pts, mid + 1, r, HR);
    int h = mergeHulls(HL, nL, HR, nR, hull);
    delete[] HL;
    delete[] HR;
    return h;
}

int main() {
    int n;
    cin >> n;
    Point *pts = new Point[n];
    for (int i = 0; i < n; i++) {
        cin >> pts[i].x >> pts[i].y;
    }

    insertionSort(pts, n);

    Point *hull = new Point[n * 2];
    int h = divideHull(pts, 0, n - 1, hull);

    for (int i = 0; i < h; i++) {
        cout << "(" << hull[i].x << ", " << hull[i].y << ")\n";
    }

    delete[] pts;
    delete[] hull;
    return 0;
}
