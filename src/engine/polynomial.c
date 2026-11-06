/* Polynomials: Horner evaluation and real roots inside an interval (Brent's method on bracketed sign changes). */

#include "engine/polynomial.h"

typedef struct Poly_t {
    float *mpCoef;
    int mDegree;
} Poly_t;

static inline float _PolynomialAbs(float x)
{
    return __builtin_fabs(x);
}

static float _PolynomialEvaluateHorner(float *pCoef, int degree, float x)
{
    float result = pCoef[degree];

    while (--degree >= 0) {
        result = x * result + pCoef[degree];
    }
    return result;
}

static float _PolynomialCalculateHornerRoot(float a, float b, float fa, float fb, Poly_t *pPoly, float tol)
{
    float eps = 1.0e-7f;
    float c;
    float d;
    float e;
    float fc;
    float p;
    float q;
    float r;
    float s;
    float tol1;
    float xm;
    int searching;

bracket:
    c = a;
    fc = fa;
    e = d = b - a;
iterate:
    if (!(_PolynomialAbs(fc) >= _PolynomialAbs(fb))) {
        a = b;
        b = c;
        c = a;
        fa = fb;
        fb = fc;
        fc = fa;
    }
    tol1 = 2.0f * eps * _PolynomialAbs(b) + 0.5f * tol;
    xm = 0.5f * (c - b);
    searching = !(_PolynomialAbs(xm) <= tol1) && fb != 0.0f;
    if (searching) {
        if (!(_PolynomialAbs(e) < tol1) && !(_PolynomialAbs(fa) <= _PolynomialAbs(fb))) {
            s = fb / fa;
            if (a == c) {
                p = 2.0f * xm * s;
                q = 1.0f - s;
            } else {
                q = fa / fc;
                r = fb / fc;
                p = s * (2.0f * xm * q * (q - r) - (b - a) * (r - 1.0f));
                q = (q - 1.0f) * (r - 1.0f) * (s - 1.0f);
            }
            if (!(p <= 0.0f)) {
                q = -q;
            } else {
                p = -p;
            }
            s = e;
            e = d;
            if (!(2.0f * p >= xm * (3.0f * q) - _PolynomialAbs(tol1 * q)) && !(p >= _PolynomialAbs(s * (0.5f * q)))) {
                d = p / q;
            } else {
                d = xm;
                e = d;
            }
        } else {
            d = xm;
            e = d;
        }
        a = b;
        fa = fb;
        if (!(_PolynomialAbs(d) <= tol1)) {
            b += d;
        } else if (!(xm <= 0.0f)) {
            b += tol1;
        } else {
            b -= tol1;
        }
        fb = _PolynomialEvaluateHorner(pPoly->mpCoef, pPoly->mDegree, b);
        if (fb * (fc / _PolynomialAbs(fc)) > 0.0f) {
            goto bracket;
        }
        goto iterate;
    }
    return b;
}

static float _PolynomialFindHornerRoot(float a, float b, Poly_t *pPoly, float tol)
{
    float fa = _PolynomialEvaluateHorner(pPoly->mpCoef, pPoly->mDegree, a);
    float fb;

    if (_PolynomialAbs(fa) < 1.0e-7f) {
        return a;
    }
    fb = _PolynomialEvaluateHorner(pPoly->mpCoef, pPoly->mDegree, b);
    if (_PolynomialAbs(fb) < 1.0e-7f) {
        return b;
    }
    return _PolynomialCalculateHornerRoot(a, b, fa, fb, pPoly, tol);
}

/* Derivative roots partition the interval into monotonic spans. */
int PolynomialCalculateRoots(float *pCoef, int degree, float lo, int includeLo, float hi, int includeHi, float *pRoots)
{
    float workspace[3][22];
    float *norm;
    float *deriv;
    float *extrema;
    Poly_t poly;
    float x1 = 0.0f;
    float f1 = 0.0f;
    float sum = 0.0f;
    float eps;
    float x0;
    float f0;
    float root;
    int count;
    int numExtrema;
    int inLo;
    int inHi;
    int skip;
    int coefficient;
    int i;

    for (coefficient = 0; coefficient < degree + 1; coefficient++) {
        sum += _PolynomialAbs(pCoef[coefficient]);
    }
    eps = (_PolynomialAbs(lo) + _PolynomialAbs(hi)) * (float)(degree + 1) * 1.0e-7f;
    if (!(sum > eps)) {
        return -1;
    }
    norm = workspace[0];
    deriv = workspace[1];
    extrema = workspace[2];
    for (coefficient = 0; coefficient < degree + 1; coefficient++) {
        norm[coefficient] = (1.0f / sum) * pCoef[coefficient];
    }
    if (!(_PolynomialAbs(norm[degree]) >= eps)) {
        do { degree--; } while (_PolynomialAbs(norm[degree]) < eps);
    }
    count = 0;
    if (degree == 0) {
        return 0;
    }
    if (degree == 1) {
        pRoots[0] = -norm[0] / norm[1];
        inLo = lo < (includeLo ? pRoots[0] + eps : pRoots[0] - eps);
        inHi = hi > (includeHi ? pRoots[0] - eps : pRoots[0] + eps);
        count = 0;
        if (inLo && inHi) {
            count = 1;
        }
        if (count) {
            if (includeLo && !(pRoots[0] >= lo)) {
                pRoots[0] = lo;
            } else if (includeHi && !(pRoots[0] <= hi)) {
                pRoots[0] = hi;
            }
        }
        return count;
    }
    poly.mpCoef = norm;
    poly.mDegree = degree;
    for (coefficient = 1; coefficient <= degree; coefficient++) {
        deriv[coefficient - 1] = (float)coefficient * norm[coefficient];
    }
    numExtrema = PolynomialCalculateRoots(deriv, degree - 1, lo, 0, hi, 0, extrema);
    if (numExtrema == -1) {
        return 0;
    }
    skip = 0;
    for (i = 0; i <= numExtrema; i++) {
        if (count > degree) {
            return count;
        }
        if (i == 0) {
            x0 = lo;
            f0 = _PolynomialEvaluateHorner(norm, degree, x0);
            if (!(_PolynomialAbs(f0) > eps) && includeLo) {
                pRoots[count++] = x0;
            }
        } else {
            x0 = x1;
            f0 = f1;
        }
        if (i == numExtrema) {
            x1 = hi;
            skip = 0;
        } else {
            x1 = extrema[i];
        }
        f1 = _PolynomialEvaluateHorner(norm, degree, x1);
        if (skip) {
            skip = 0;
        } else if (!(_PolynomialAbs(f1) >= eps)) {
            if (i != numExtrema || includeHi) {
                pRoots[count++] = x1;
                skip = 1;
            }
        } else if ((!(f0 >= 0.0f) && f1 > 0.0f) || (!(f0 <= 0.0f) && !(f1 >= 0.0f))) {
            root = _PolynomialFindHornerRoot(x0, x1, &poly, 0.0f);
            pRoots[count++] = root;
            if (count > 1 && !(pRoots[count - 2] < pRoots[count - 1] - eps)) {
                pRoots[count - 2] = (pRoots[count - 2] + pRoots[count - 1]) * 0.5f;
                count--;
            }
        }
    }
    return count;
}
