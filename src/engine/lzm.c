#include "engine/cu_8027EFAC.h"
#include "game/fn_801D2B7C.h"

/* Red-black tree node in the index-linked array allocated by fn_802805C4;
   index 0 is the nil node, the header at 0x10001 holds the root in mRight. */
typedef struct Node_802805C4 {
    int mParent;
    int mLeft;
    int mRight;
    int mColor;
} Node_802805C4;

static unsigned char lbl_803EC578 = 0;
static unsigned int lbl_803EC57C = 0;
static int lbl_803EC580 = 31;
static int lbl_803ED414;
static unsigned short lbl_803ED418;
static int lbl_803ED41C;

#define SWAP32(x) (((x) << 24) | (((x) << 8) & 0xFF0000) | (((x) >> 8) & 0xFF00) | ((x) >> 24))

Node_802805C4 *fn_802805C4(void)
{
    Node_802805C4 *tree;

    tree = fn_801D2BB0(1, 0x100020, 0, 0);
    memset(tree, 0, 0x100020);
    tree[0x10001].mColor = 1;
    tree[0x10001].mParent = 0;
    tree[0x10001].mRight = 1;
    tree[0x10001].mLeft = 0;
    tree[1].mParent = 0x10001;
    tree[0].mLeft = 0;
    tree[0].mColor = 1;
    tree[1].mRight = 0;
    tree[1].mLeft = 0;
    tree[1].mColor = 1;
    tree[0].mParent = 0;
    tree[0].mRight = 0;
    return tree;
}

int fn_80280660(int node, Node_802805C4 *tree)
{
    int next;

    next = tree[node].mRight;
    if (next != 0) {
        while (tree[next].mLeft != 0) {
            next = tree[next].mLeft;
        }
        return next;
    }
    next = tree[node].mParent;
    while (next != 0 && node == tree[next].mRight) {
        node = next;
        next = tree[next].mParent;
    }
    return next;
}

void fn_802806F8(int old, int node, Node_802805C4 *tree)
{
    int parent;

    parent = tree[old].mParent;
    if (tree[parent].mLeft == old) {
        tree[parent].mLeft = node;
    } else {
        tree[parent].mRight = node;
    }
    tree[node].mParent = parent;
    tree[node].mRight = tree[old].mRight;
    tree[node].mLeft = tree[old].mLeft;
    tree[node].mColor = tree[old].mColor;
    tree[tree[node].mRight].mParent = node;
    tree[tree[node].mLeft].mParent = node;
    tree[old].mLeft = 0;
    tree[old].mRight = 0;
    tree[old].mParent = 0;
    tree[old].mColor = 1;
}

void fn_80280780(int node, Node_802805C4 *tree)
{
    int child;

    child = tree[node].mRight;
    tree[node].mRight = tree[child].mLeft;
    if (tree[child].mLeft != 0) {
        tree[tree[child].mLeft].mParent = node;
    }
    tree[child].mParent = tree[node].mParent;
    if (node == tree[tree[node].mParent].mLeft) {
        tree[tree[node].mParent].mLeft = child;
    } else {
        tree[tree[node].mParent].mRight = child;
    }
    tree[child].mLeft = node;
    tree[node].mParent = child;
}

void fn_802807F4(int node, Node_802805C4 *tree)
{
    int child;

    child = tree[node].mLeft;
    tree[node].mLeft = tree[child].mRight;
    if (tree[node].mLeft != 0) {
        tree[tree[node].mLeft].mParent = node;
    }
    tree[child].mParent = tree[node].mParent;
    if (node == tree[tree[node].mParent].mLeft) {
        tree[tree[node].mParent].mLeft = child;
    } else {
        tree[tree[node].mParent].mRight = child;
    }
    tree[child].mRight = node;
    tree[node].mParent = child;
}

void fn_80280864(int node, Node_802805C4 *tree)
{
    int y;
    int x;
    int color;
    int w;
    int p;

    if (tree[node].mParent == 0) {
        return;
    }
    if (tree[node].mLeft == 0 || tree[node].mRight == 0) {
        y = node;
    } else {
        y = fn_80280660(node, tree);
    }
    if (tree[y].mLeft != 0) {
        x = tree[y].mLeft;
    } else {
        x = tree[y].mRight;
    }
    tree[x].mParent = tree[y].mParent;
    if (tree[tree[y].mParent].mRight == y) {
        tree[tree[y].mParent].mRight = x;
    } else {
        tree[tree[y].mParent].mLeft = x;
    }
    color = tree[y].mColor;
    tree[y].mParent = 0;
    tree[y].mLeft = 0;
    tree[y].mRight = 0;
    tree[y].mColor = 1;
    if (y != node) {
        fn_802806F8(node, y, tree);
    }
    if (color != 1) {
        return;
    }
    while (x != tree[0x10001].mRight && tree[x].mColor == 1) {
        p = tree[x].mParent;
        if (x == tree[p].mLeft) {
            w = tree[p].mRight;
            if (tree[w].mColor == 0) {
                tree[w].mColor = 1;
                tree[p].mColor = 0;
                fn_80280780(p, tree);
                w = tree[p].mRight;
            }
            if (tree[tree[w].mLeft].mColor == 1 && tree[tree[w].mRight].mColor == 1) {
                tree[w].mColor = 0;
                x = p;
                continue;
            }
            if (tree[tree[w].mRight].mColor == 1) {
                tree[tree[w].mLeft].mColor = 1;
                tree[w].mColor = 0;
                fn_802807F4(w, tree);
                w = tree[p].mRight;
            }
            tree[w].mColor = tree[p].mColor;
            tree[p].mColor = 1;
            tree[tree[w].mRight].mColor = 1;
            fn_80280780(p, tree);
        } else {
            w = tree[p].mLeft;
            if (tree[w].mColor == 0) {
                tree[w].mColor = 1;
                tree[p].mColor = 0;
                fn_802807F4(p, tree);
                w = tree[p].mLeft;
            }
            if (tree[tree[w].mRight].mColor == 1 && tree[tree[w].mLeft].mColor == 1) {
                tree[w].mColor = 0;
                x = p;
                continue;
            }
            if (tree[tree[w].mLeft].mColor == 1) {
                tree[tree[w].mRight].mColor = 1;
                tree[w].mColor = 0;
                fn_80280780(w, tree);
                w = tree[p].mLeft;
            }
            tree[w].mColor = tree[p].mColor;
            tree[p].mColor = 1;
            tree[tree[w].mLeft].mColor = 1;
            fn_802807F4(p, tree);
        }
        x = tree[0x10001].mRight;
    }
    tree[x].mColor = 1;
}

int fn_80280B94(int node, Node_802805C4 *tree, unsigned char *window, int base, int *match)
{
    unsigned char *key;
    unsigned char *other;
    int cur;
    unsigned int best;
    unsigned int i;
    int cmp;
    int *link;
    int x;
    int y;
    int p;
    int gp;
    int start;

    start = (unsigned short)base - 0xFFFF;
    key = window + (((node - start) & 0xFFFF) + base);
    cur = tree[0x10001].mRight;
    best = 0;
    for (;;) {
        other = window + (((cur - start) & 0xFFFF) + base);
        if (best != 0) {
            cmp = memcmp(key, other, best);
        } else {
            cmp = 0;
        }
        if (cmp == 0) {
            for (i = best; i < lbl_803ED414; i++) {
                if (key[i] != other[i]) {
                    cmp = key[i] - other[i];
                    break;
                }
            }
        } else {
            i = 0;
        }
        if (i > best) {
            *match = cur;
            best = i;
            if (best == lbl_803ED414) {
                fn_802806F8(cur, node, tree);
                return best;
            }
        }
        if (cmp >= 0) {
            link = &tree[cur].mRight;
        } else {
            link = &tree[cur].mLeft;
        }
        if (*link == 0) {
            *link = node;
            tree[node].mParent = cur;
            tree[node].mRight = 0;
            tree[node].mLeft = 0;
            tree[node].mColor = 0;
            x = node;
            while (x != tree[0x10001].mRight && tree[tree[x].mParent].mColor == 0) {
                p = tree[x].mParent;
                gp = tree[p].mParent;
                if (p == tree[gp].mLeft) {
                    y = tree[gp].mRight;
                    if (tree[y].mColor == 0) {
                        tree[p].mColor = 1;
                        x = gp;
                        tree[y].mColor = 1;
                        tree[gp].mColor = 0;
                    } else {
                        if (x == tree[p].mRight) {
                            x = p;
                            fn_80280780(x, tree);
                            p = tree[x].mParent;
                            gp = tree[p].mParent;
                        }
                        tree[p].mColor = 1;
                        tree[gp].mColor = 0;
                        fn_802807F4(gp, tree);
                    }
                } else {
                    y = tree[gp].mLeft;
                    if (tree[y].mColor == 0) {
                        tree[p].mColor = 1;
                        x = gp;
                        tree[y].mColor = 1;
                        tree[gp].mColor = 0;
                    } else {
                        if (x == tree[p].mLeft) {
                            x = p;
                            fn_802807F4(x, tree);
                            p = tree[x].mParent;
                            gp = tree[p].mParent;
                        }
                        tree[p].mColor = 1;
                        tree[gp].mColor = 0;
                        fn_80280780(gp, tree);
                    }
                }
            }
            tree[tree[0x10001].mRight].mColor = 1;
            return best;
        }
        cur = *link;
    }
}

int fn_80280E70(unsigned int value, int count, unsigned char *out, int pos)
{
    int shift;

    lbl_803ED41C -= count;
    shift = lbl_803EC580 - count + 1;
    if (shift > 0) {
        lbl_803EC57C |= value << shift;
    } else if (shift < 0) {
        lbl_803EC57C |= value >> -shift;
    } else {
        lbl_803EC57C |= value;
    }
    lbl_803EC580 -= count;
    if (lbl_803EC580 < 0) {
        lbl_803EC57C = SWAP32(lbl_803EC57C);
        *(unsigned int *)(out + pos) = lbl_803EC57C;
        lbl_803EC580 += 32;
        if (lbl_803EC580 != 31) {
            lbl_803EC57C = value << (lbl_803EC580 + 1);
        } else {
            lbl_803EC57C = 0;
        }
        return 4;
    }
    return 0;
}

int fn_80280F38(unsigned char *out, int pos)
{
    int total;
    int count;

    total = 0;
    count = lbl_803ED41C - (lbl_803ED41C >> 5 << 5);
    while (count > 7) {
        total += fn_80280E70(0x80, 8, out, pos);
        count -= 8;
    }
    if (count > 0) {
        total += fn_80280E70(0, count, out, pos);
    }
    return total;
}

unsigned int fn_80280FC4(unsigned char *in, int count, int *pos)
{
    int over;
    int rest;
    unsigned int value;

    lbl_803ED41C -= count;
    over = count - lbl_803EC580 - 1;
    if (over < 0) {
        over = 0;
    }
    rest = count - over;
    if (over > 0) {
        value = (lbl_803EC57C & ((1 << rest) - 1)) << over;
        lbl_803EC57C = *(unsigned int *)(in + *pos);
        *pos += 4;
        lbl_803EC57C = SWAP32(lbl_803EC57C);
        lbl_803EC580 += 32;
        value |= lbl_803EC57C >> (32 - over);
    } else {
        value = (lbl_803EC57C >> (lbl_803EC580 - (count - 1))) & ((1 << count) - 1);
    }
    lbl_803EC580 -= count;
    return value;
}

int fn_80281090(unsigned char *in, int *pos)
{
    unsigned int mask;
    int count;
    unsigned int bit;

    mask = 1 << lbl_803EC580;
    count = -1;
    while (count <= 6) {
        if (lbl_803EC580 == -1) {
            lbl_803EC57C = *(unsigned int *)(in + *pos);
            *pos += 4;
            lbl_803EC57C = SWAP32(lbl_803EC57C);
            lbl_803EC580 += 32;
            mask = 0x80000000;
        }
        count++;
        lbl_803EC580--;
        lbl_803ED41C--;
        bit = lbl_803EC57C & mask;
        mask >>= 1;
        if (bit != 0) {
            break;
        }
    }
    return count;
}

int fn_8028113C(unsigned char *out, unsigned char *src, int len, int mode, int limit, int *state)
{
    int total;
    int i;
    int j;
    int n;
    unsigned char header;

    total = 0;
    switch (mode) {
    case 2:
        header = len | 0x80;
        total = fn_80280E70(header, 8, out, 0);
        for (i = 0; i < len; i++) {
            total += fn_80280E70(src[i], 8, out, total);
        }
        break;
    case 3:
        if (len * 8 + 8 <= lbl_803ED41C) {
            header = len | 0x80;
            total = fn_80280E70(header, 8, out, 0);
            for (i = 0; i < len; i++) {
                total += fn_80280E70(src[i], 8, out, total);
            }
            *state += total;
            if (lbl_803ED41C <= 7) {
                total += fn_80280F38(out, total);
                *state = 0;
                lbl_803ED41C = limit * 8;
                lbl_803ED418++;
            }
        } else if ((unsigned int)lbl_803ED41C < 16) {
            total = fn_80280F38(out, 0);
            lbl_803ED41C = limit * 8;
            header = len | 0x80;
            total += fn_80280E70(header, 8, out, total);
            for (i = 0; i < len; i++) {
                total += fn_80280E70(src[i], 8, out, total);
            }
            *state = *state + total - limit;
            lbl_803ED418++;
        } else {
            n = (lbl_803ED41C / 8 * 8 - 8) >> 3;
            total = fn_80280E70(n | 0x80, 8, out, 0);
            for (i = 0; i < n; i++) {
                total += fn_80280E70(src[i], 8, out, total);
            }
            total += fn_80280F38(out, total);
            n = len - n;
            lbl_803ED41C = limit * 8;
            total += fn_80280E70(n | 0x80, 8, out, total);
            for (j = 0; j < n; j++) {
                total += fn_80280E70(src[i + j], 8, out, total);
            }
            *state = *state + total - limit;
            lbl_803ED418++;
        }
        break;
    case 0:
        out[0] = len | 0x80;
        total = 1;
        for (i = 0; i < len; i++) {
            out[total++] = src[i];
        }
        break;
    case 1:
        *state += len + 1;
        if (*state == limit - 1) {
            out[0] = 0x80;
            total = 1;
            (*state)++;
        }
        if (*state <= limit) {
            out[total++] = len | 0x80;
            for (i = 0; i < len; i++) {
                out[total++] = src[i];
            }
        } else {
            out[total++] = (len - (*state - limit)) | 0x80;
            for (i = 0; i < len - (*state - limit); i++) {
                out[total++] = src[i];
            }
            out[total++] = (*state - limit) | 0x80;
            for (j = 0; j < *state - limit; j++) {
                out[total++] = src[i + j];
            }
            *state = *state - limit + 1;
            lbl_803ED418++;
        }
        if (*state == limit) {
            *state = 0;
            lbl_803ED418++;
        }
        break;
    }
    return total;
}

int fn_8028156C(int value)
{
    int count;

    count = 1;
    while (value > 1) {
        value >>= 1;
        count++;
    }
    return count;
}

int fn_80281590(unsigned char *out, int dist, int len, int mode, int limit, int *state, unsigned int pos, int bits)
{
    int total;
    int lenBits;
    int range;
    unsigned int i;
    int first;

    total = 0;
    switch (mode) {
    case 2:
        len -= 2;
        lenBits = fn_8028156C(len);
        len &= (1 << (lenBits - 1)) - 1;
        range = ((1 << bits) - 1) - (pos > 0x10000 ? 0x10000 : pos);
        if (range != -1) {
            if (dist < range) {
                bits--;
            } else {
                dist += range;
            }
        }
        total = fn_80280E70(1, lenBits + 1, out, 0);
        if (lenBits != 1) {
            total += fn_80280E70(len, lenBits - 1, out, total);
        }
        total += fn_80280E70(dist, bits, out, total);
        break;
    case 3:
        len -= 2;
        lenBits = fn_8028156C(len);
        len &= (1 << (lenBits - 1)) - 1;
        range = ((1 << bits) - 1) - (pos > 0x10000 ? 0x10000 : pos);
        if (range != -1) {
            if (dist < range) {
                bits--;
            } else {
                dist += range;
            }
        }
        if (lbl_803ED41C < (lenBits + 1) + (lenBits - 1) + bits) {
            while (lbl_803ED41C > 7) {
                total += fn_80280E70(0x80, 8, out, total);
            }
            total += fn_80280F38(out, total);
            lbl_803ED41C = limit * 8;
            first = fn_80280E70(1, lenBits + 1, out, total);
            if (lenBits != 1) {
                total += fn_80280E70(len, lenBits - 1, out, total);
            }
            first += fn_80280E70(dist, bits, out, total);
            *state = first;
            total += first;
            lbl_803ED418++;
        } else {
            total = fn_80280E70(1, lenBits + 1, out, 0);
            if (lenBits != 1) {
                total += fn_80280E70(len, lenBits - 1, out, total);
            }
            total += fn_80280E70(dist, bits, out, total);
            *state += total;
            if (lbl_803ED41C == 0) {
                *state = 0;
                lbl_803ED418++;
                lbl_803ED41C += limit * 8;
            }
        }
        break;
    case 0:
        out[0] = len & 0x7F;
        out[1] = dist;
        out[2] = dist >> 8;
        total = 3;
        break;
    case 1:
        *state += 3;
        if (*state <= limit) {
            out[0] = len & 0x7F;
            out[1] = dist;
            out[2] = dist >> 8;
            total = 3;
        } else {
            for (i = *state - 3; i < limit; i++) {
                out[total++] = 0x80;
            }
            out[total++] = len & 0x7F;
            out[total++] = dist;
            out[total++] = dist >> 8;
            *state = 3;
            lbl_803ED418++;
        }
        if (*state == limit) {
            *state = 0;
            lbl_803ED418++;
        }
        break;
    }
    return total;
}

void *fn_80281938(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    return 0;
}

void fn_80281C68(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, void *pState)
{
}

void *fn_80281C6C(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst)
{
    return 0;
}

void fn_802821E4(Buffer_8027F9AC *pSrc, Buffer_8027F9AC *pDst, void *pState)
{
}
