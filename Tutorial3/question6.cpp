#include <iostream>
using namespace std;

struct Point {
    int x, h;
};

int myMax(int a, int b) {
    return (a > b) ? a : b;
}

void insertionSortBuildings(int B[][3], int n) {
    for (int i = 1; i < n; ++i) {
        int keyL = B[i][0], keyR = B[i][1], keyH = B[i][2];
        int j = i - 1;
        while (j >= 0 && B[j][0] > keyL) {
            B[j + 1][0] = B[j][0];
            B[j + 1][1] = B[j][1];
            B[j + 1][2] = B[j][2];
            --j;
        }
        B[j + 1][0] = keyL;
        B[j + 1][1] = keyR;
        B[j + 1][2] = keyH;
    }
}

int mergeSkyline(Point *L, int nL, Point *R, int nR, Point *out) {
    int i = 0, j = 0, hL = 0, hR = 0, ph = -1, cnt = 0;
    while (i < nL && j < nR) {
        int x;
        if (L[i].x < R[j].x) {
            x = L[i].x;
            hL = L[i].h;
            i++;
        } else {
            x = R[j].x;
            hR = R[j].h;
            j++;
        }
        int mh = myMax(hL, hR);
        if (mh != ph) {
            out[cnt++] = {x, mh};
            ph = mh;
        }
    }
    while (i < nL) {
        if (L[i].h != ph) {
            out[cnt++] = L[i];
            ph = L[i].h;
        }
        i++;
    }
    while (j < nR) {
        if (R[j].h != ph) {
            out[cnt++] = R[j];
            ph = R[j].h;
        }
        j++;
    }
    return cnt;
}

int buildSkyline(int B[][3], int l, int r, Point *out) {
    if (l > r) return 0;
    if (l == r) {
        out[0] = {B[l][0], B[l][2]};
        out[1] = {B[l][1], 0};
        return 2;
    }
    int m = (l + r) >> 1;
    int sizeL = 2 * (m - l + 1);
    int sizeR = 2 * (r - m);

    Point *SL = new Point[sizeL];
    Point *SR = new Point[sizeR];

    int nL = buildSkyline(B, l, m, SL);
    int nR = buildSkyline(B, m + 1, r, SR);
    int n = mergeSkyline(SL, nL, SR, nR, out);

    delete[] SL;
