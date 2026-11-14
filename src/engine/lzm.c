/* LZM1 resource compression: a sliding-window dictionary and byte/bit token streams. */
#include "engine/GCmp.h"
#include "game/fn_801D2B7C.h"

/* Indexed red-black dictionary: node 0 is nil and node 0x10001 holds the root. */
typedef struct LZMTreeNode_t {
    int mParent;
    int mLeft;
    int mRight;
    int mColor;
} LZMTreeNode_t;

static unsigned char PacifyStatus = 0;
static unsigned int bitbuf = 0;
static int bitbufpos = 31;
static int LookAheadSize;
static unsigned short NumChunks;
static int BitsLeftInChunk;

#define SWAP32(x) (((x) << 24) | (((x) << 8) & 0xFF0000) | (((x) >> 8) & 0xFF00) | ((x) >> 24))

/* Initialize the sliding-window dictionary with nil and root sentinel nodes. */
LZMTreeNode_t *sInitTree(void)
{
    LZMTreeNode_t *tree;

    tree = fn_801D2BB0(1, 0x100020, 0, 0);
    memset(tree, 0, 0x100020);
    tree[0x10001].mParent = 0;
    tree[0x10001].mRight = 1;
    tree[0x10001].mLeft = 0;
    tree[0x10001].mColor = 1;
    tree[1].mParent = 0x10001;
    tree[1].mRight = 0;
    tree[1].mLeft = 0;
    tree[1].mColor = 1;
    tree[0].mParent = 0;
    tree[0].mRight = 0;
    tree[0].mLeft = 0;
    tree[0].mColor = 1;
    return tree;
}

/* Find the next dictionary node in sorted order. */
int sFindNextNode(int node, LZMTreeNode_t *tree)
{
    int next;
    int child;

    next = tree[node].mRight;
    if (next != 0) {
        while (tree[next].mLeft != 0) {
            next = tree[next].mLeft;
        }
        return next;
    }
    next = tree[node].mParent;
    /* FAKEMATCH: Separate climbing index preserves the original register copy without changing the walk. */
    child = node;
    while (next != 0 && child == tree[next].mRight) {
        child = next;
        next = tree[next].mParent;
    }
    return next;
}

/* Move a replacement node into an existing dictionary position. */
void sReplaceNode(int old, int node, LZMTreeNode_t *tree)
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

/* Rotate a dictionary subtree to the left. */
void sRotateNodeLeft(int node, LZMTreeNode_t *tree)
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

/* Rotate a dictionary subtree to the right. */
void sRotateNodeRight(int node, LZMTreeNode_t *tree)
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

/* Remove an expired window position and restore red-black balance. */
void sDeleteNode(int node, LZMTreeNode_t *tree)
{
    int y;
    int x;
    int color;
    int p;

    if (tree[node].mParent == 0) {
        return;
    }
    if (tree[node].mLeft == 0 || tree[node].mRight == 0) {
        y = node;
    } else {
        y = sFindNextNode(node, tree);
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
        sReplaceNode(node, y, tree);
    }
    if (color != 1) {
        return;
    }
    while (x != tree[0x10001].mRight && tree[x].mColor == 1) {
        p = tree[x].mParent;
        if (x == tree[p].mLeft) {
            y = tree[p].mRight;
            if (tree[y].mColor == 0) {
                tree[y].mColor = 1;
                tree[p].mColor = 0;
                sRotateNodeLeft(p, tree);
                y = tree[p].mRight;
            }
            if (tree[tree[y].mLeft].mColor == 1 && tree[tree[y].mRight].mColor == 1) {
                tree[y].mColor = 0;
                x = p;
                continue;
            }
            if (tree[tree[y].mRight].mColor == 1) {
                tree[tree[y].mLeft].mColor = 1;
                tree[y].mColor = 0;
                sRotateNodeRight(y, tree);
                y = tree[p].mRight;
            }
            tree[y].mColor = tree[p].mColor;
            tree[p].mColor = 1;
            tree[tree[y].mRight].mColor = 1;
            sRotateNodeLeft(p, tree);
        } else {
            y = tree[p].mLeft;
            if (tree[y].mColor == 0) {
                tree[y].mColor = 1;
                tree[p].mColor = 0;
                sRotateNodeRight(p, tree);
                y = tree[p].mLeft;
            }
            if (tree[tree[y].mRight].mColor == 1 && tree[tree[y].mLeft].mColor == 1) {
                tree[y].mColor = 0;
                x = p;
                continue;
            }
            if (tree[tree[y].mLeft].mColor == 1) {
                tree[tree[y].mRight].mColor = 1;
                tree[y].mColor = 0;
                sRotateNodeLeft(y, tree);
                y = tree[p].mLeft;
            }
            tree[y].mColor = tree[p].mColor;
            tree[p].mColor = 1;
            tree[tree[y].mLeft].mColor = 1;
            sRotateNodeRight(p, tree);
        }
        x = tree[0x10001].mRight;
    }
    tree[x].mColor = 1;
}

/* Insert a window position and return its longest dictionary match. */
int sAddNode(int node, LZMTreeNode_t *tree, unsigned char *window, int base, int *match)
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
            for (i = best; i < LookAheadSize; i++) {
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
            if (best == LookAheadSize) {
                sReplaceNode(cur, node, tree);
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
                            sRotateNodeLeft(x, tree);
                            p = tree[x].mParent;
                            gp = tree[p].mParent;
                        }
                        tree[p].mColor = 1;
                        tree[gp].mColor = 0;
                        sRotateNodeRight(gp, tree);
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
                            sRotateNodeRight(x, tree);
                            p = tree[x].mParent;
                            gp = tree[p].mParent;
                        }
                        tree[p].mColor = 1;
                        tree[gp].mColor = 0;
                        sRotateNodeLeft(gp, tree);
                    }
                }
            }
            tree[tree[0x10001].mRight].mColor = 1;
            return best;
        }
        cur = *link;
    }
}

/* Append bits to the output word, writing complete words in little-endian order. */
int sWriteBits(unsigned int value, int count, unsigned char *out, int pos)
{
    int shift;

    BitsLeftInChunk -= count;
    shift = bitbufpos - count + 1;
    if (shift > 0) {
        bitbuf |= value << shift;
    } else if (shift < 0) {
        bitbuf |= value >> -shift;
    } else {
        bitbuf |= value;
    }
    bitbufpos -= count;
    if (bitbufpos < 0) {
        bitbuf = SWAP32(bitbuf);
        *(unsigned int *)(out + pos) = bitbuf;
        bitbufpos += 32;
        if (bitbufpos != 31) {
            bitbuf = value << (bitbufpos + 1);
        } else {
            bitbuf = 0;
        }
        return 4;
    }
    return 0;
}

/* Pad the current bit-output chunk to a word boundary. */
int sQuadAlign_Outbuffer(unsigned char *out, int pos)
{
    int total;
    int count;

    total = 0;
    count = BitsLeftInChunk - (BitsLeftInChunk >> 5 << 5);
    while (count > 7) {
        total += sWriteBits(0x80, 8, out, pos);
        count -= 8;
    }
    if (count > 0) {
        total += sWriteBits(0, count, out, pos);
    }
    return total;
}

/* Read a fixed-width value from the buffered bit stream. */
unsigned int sReadBits(unsigned char *in, int count, int *pos)
{
    int over;
    int rest;
    unsigned int value;
    int shift;

    BitsLeftInChunk -= count;
    over = count - bitbufpos - 1;
    if (over < 0) {
        over = 0;
    }
    rest = count - over;
    if (over > 0) {
        value = bitbuf & ((1 << rest) - 1);
        value <<= over;
        bitbuf = *(unsigned int *)(in + *pos);
        *pos += 4;
        bitbuf = SWAP32(bitbuf);
        bitbufpos += 32;
        value |= bitbuf >> (32 - over);
    } else {
        shift = count - 1;
        shift = bitbufpos - shift;
        value = bitbuf >> shift;
        value &= (1 << count) - 1;
    }
    bitbufpos -= count;
    return value;
}

/* Read the zero prefix of a variable-length match code. */
int sReadZeroBits(unsigned char *in, int *pos)
{
    unsigned int mask;
    int count;
    unsigned int bit;

    mask = 1U << bitbufpos;
    count = -1;
    do {
        if (bitbufpos == -1) {
            bitbuf = *(unsigned int *)(in + *pos);
            *pos += 4;
            bitbuf = SWAP32(bitbuf);
            bitbufpos += 32;
            mask = 0x80000000;
        }
        count++;
        bitbufpos--;
        BitsLeftInChunk--;
        bit = bitbuf & mask;
        mask >>= 1;
    } while (bit == 0 && count <= 6);
    return count;
}

#if defined(DECOMP_COMPARE)

/* Write literal bytes in the selected byte or bit stream mode. */
int sFlushBuffer(unsigned char *out, unsigned char *src, int len, int mode, int limit, int *state)
{
    int total;
    int i;
    int n;

    total = 0;
    switch (mode) {
    case 2:
        total = sWriteBits((unsigned char)(len | 0x80), 8, out, 0);
        for (i = 0; i < len; i++) {
            total += sWriteBits(src[i], 8, out, total);
        }
        break;
    case 3:
        if (len * 8 + 8 <= BitsLeftInChunk) {
            total = sWriteBits((unsigned char)(len | 0x80), 8, out, 0);
            for (i = 0; i < len; i++) {
                total += sWriteBits(src[i], 8, out, total);
            }
            *state += total;
            if (BitsLeftInChunk <= 7) {
                total += sQuadAlign_Outbuffer(out, total);
                *state = 0;
                BitsLeftInChunk = limit * 8;
                NumChunks++;
            }
        } else if ((unsigned int)BitsLeftInChunk < 16) {
            total = sQuadAlign_Outbuffer(out, 0);
            BitsLeftInChunk = limit * 8;
            total += sWriteBits((unsigned char)(len | 0x80), 8, out, total);
            for (i = 0; i < len; i++) {
                total += sWriteBits(src[i], 8, out, total);
            }
            *state = *state + total - limit;
            NumChunks++;
        } else {
            n = (BitsLeftInChunk - BitsLeftInChunk % 8 - 8) >> 3;
            total = sWriteBits(n | 0x80, 8, out, 0);
            for (i = 0; i < n; i++) {
                total += sWriteBits(src[i], 8, out, total);
            }
            total += sQuadAlign_Outbuffer(out, total);
            n = len - n;
            BitsLeftInChunk = limit * 8;
            total += sWriteBits(n | 0x80, 8, out, total);
            len = i;
            for (i = 0; i < n; i++) {
                total += sWriteBits(src[len + i], 8, out, total);
            }
            *state = *state + total - limit;
            NumChunks++;
        }
        break;
    case 0:
        i = 0;
        out[0] = len | 0x80;
        total = 1;
        for (; i < len; i++) {
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
            i = 0;
            out[total++] = len | 0x80;
            for (; i < len; i++) {
                out[total++] = src[i];
            }
        } else {
            out[total++] = (len - (*state - limit)) | 0x80;
            for (i = 0; i < len - (*state - limit); i++) {
                out[total++] = src[i];
            }
            out[total++] = (*state - limit) | 0x80;
            len = i;
            for (i = 0; i < *state - limit; i++) {
                out[total++] = src[len + i];
            }
            *state = *state - limit + 1;
            NumChunks++;
        }
        if (*state == limit) {
            *state = 0;
            NumChunks++;
        }
        break;
    }
    return total;
}

/* Count the bits needed to represent a positive match length. */
int sCalcLogMagnitude(int value)
{
    int count;

    count = 1;
    while (value > 1) {
        value >>= 1;
        count++;
    }
    return count;
}

/* Write a length-and-distance match token in the selected stream mode. */
int sFlushMatch(unsigned char *out, int dist, int len, int mode, int limit, int *state, unsigned int pos, int bits)
{
    int total;
    int lenBits;
    int range;
    int needed;
    int maximum;
    int first;

    total = 0;
    switch (mode) {
    case 2:
        len -= 2;
        lenBits = sCalcLogMagnitude(len);
        len &= (1 << (lenBits - 1)) - 1;
        maximum = (1 << bits) - 1;
        range = maximum - (pos > 0x10000 ? 0x10000 : pos);
        if (range != -1) {
            if (dist < range) {
                bits--;
            } else {
                dist += range;
            }
        }
        total = sWriteBits(1, lenBits + 1, out, 0);
        if (lenBits != 1) {
            total += sWriteBits(len, lenBits - 1, out, total);
        }
        total += sWriteBits(dist, bits, out, total);
        break;
    case 3:
        len -= 2;
        lenBits = sCalcLogMagnitude(len);
        len &= (1 << (lenBits - 1)) - 1;
        needed = (lenBits + 1) + (lenBits - 1) + 16;
        maximum = (1 << bits) - 1;
        range = maximum - (pos > 0x10000 ? 0x10000 : pos);
        if (range != -1) {
            if (dist < range) {
                bits--;
            } else {
                dist += range;
            }
        }
        needed -= 16;
        needed += bits;
        if (BitsLeftInChunk < needed) {
            while (BitsLeftInChunk > 7) {
                total += sWriteBits(0x80, 8, out, total);
            }
            total += sQuadAlign_Outbuffer(out, total);
            BitsLeftInChunk = limit * 8;
            first = sWriteBits(1, lenBits + 1, out, total);
            if (lenBits != 1) {
                total += sWriteBits(len, lenBits - 1, out, total);
            }
            first += sWriteBits(dist, bits, out, total);
            *state = first;
            total += first;
            NumChunks++;
        } else {
            total = sWriteBits(1, lenBits + 1, out, 0);
            if (lenBits != 1) {
                total += sWriteBits(len, lenBits - 1, out, total);
            }
            total += sWriteBits(dist, bits, out, total);
            *state += total;
            if (BitsLeftInChunk == 0) {
                *state = 0;
                NumChunks++;
                BitsLeftInChunk += limit * 8;
            }
        }
        break;
    case 0:
        out[0] = len & 0x7F;
        out[1] = dist;
        out[2] = (dist & 0xFF00) >> 8;
        total = 3;
        break;
    case 1:
        *state += 3;
        if (*state <= limit) {
            out[0] = len & 0x7F;
            out[1] = dist;
            out[2] = (dist & 0xFF00) >> 8;
            total = 3;
        } else {
            for (pos = *state - 3; pos < limit; pos++) {
                out[total++] = 0x80;
            }
            out[total++] = len & 0x7F;
            out[total++] = dist;
            out[total++] = (dist & 0xFF00) >> 8;
            *state = 3;
            NumChunks++;
        }
        if (*state == limit) {
            *state = 0;
            NumChunks++;
        }
        break;
    }
    return total;
}

/* The encoder needs no per-stream state allocation. */
void *_LZMCoStart(GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst)
{
    return 0;
}

/* Encode a source buffer using the sliding-window dictionary. */
int _LZMCoProcess(GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst, void *pState)
{
    unsigned int size;
    unsigned char *in;
    unsigned char *out;
    unsigned int pos;
    int base;
    unsigned int progress;
    int total;
    int mode = 0;
    int limit;
    int blockPos;
    int len;
    int match;
    int literals;
    int literalStart;
    int bits;
    unsigned int threshold;
    int advance;
    int i;
    int node;
    int start;
    LZMTreeNode_t *tree;

    size = pSrc->mSize;
    in = pSrc->mpData;
    out = pDst->mpData;
    limit = 4096;
    BitsLeftInChunk = limit * 8;
    bitbuf = 0;
    bitbufpos = 31;
    out[0] = mode;
    bits = 1;
    threshold = 2;
    progress = 0;
    pos = 0;
    total = 1;
    base = 0;
    LookAheadSize = size > 127 ? 127 : size;
    literals = 0;
    tree = sInitTree();
    len = 0;
    match = 0;
    literalStart = 0;
    while (LookAheadSize != 0) {
        if (pos - progress > 1024 && PacifyStatus == 1) {
            progress = pos - (pos % 1024);
        }
        if (len <= 2) {
            if (literals == 0) {
                literalStart = pos;
            }
            if (literals++ == 126) {
                total += sFlushBuffer(out + total, in + literalStart, 127, mode, limit, &blockPos);
                literals = 0;
            }
            advance = 1;
        } else {
            if (literals != 0) {
                total += sFlushBuffer(out + total, in + literalStart, literals, mode, limit, &blockPos);
                literals = 0;
            }
            while (pos >= threshold) {
                if (threshold <= 0xFFFF) {
                    bits++;
                }
                threshold <<= 1;
            }
            start = (base & 0xFFFF) - 0xFFFF;
            total += sFlushMatch(out + total,
                pos - (((match - start) & 0xFFFF) + base),
                len, mode, limit, &blockPos, pos, bits);
            advance = len;
        }
        for (i = 0; i < advance; i++) {
            pos++;
            if (pos > 0xFFFF) {
                base++;
            }
            LookAheadSize = LookAheadSize > size - pos ? size - pos : LookAheadSize;
            node = (pos & 0xFFFF) + 1;
            sDeleteNode(node, tree);
            if (LookAheadSize != 0) {
                len = sAddNode(node, tree, in, base, &match);
            }
        }
    }
    if (literals != 0) {
        total += sFlushBuffer(out + total, in + literalStart, literals, mode, limit, &blockPos);
    }
    if (mode == 3) {
        total += sWriteBits(0, 8, out + total, 0);
        total += sQuadAlign_Outbuffer(out, total);
    } else if (mode == 2) {
        total += sWriteBits(0, 8, out + total, 0);
        if (bitbufpos != 31) {
            i = total;
            while (i == total) {
                total += sWriteBits(0x80, 8, out + total, 0);
            }
        }
    } else {
        out[total++] = 0;
    }
    fn_801D2BD0(tree);
    pDst->mSize = total;
    pDst->mPos = total;
    return 1;
}

/* Encoding leaves no per-stream state to release. */
void _LZMCoStop(GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst, void *pState)
{
}

/* The decoder needs no per-stream state allocation. */
void *_LZMDecStart(GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst)
{
    return 0;
}

/* Expand literals and backward matches from a byte or bit coded stream. */
int _LZMDecProcess(GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst, void *pState)
{
    unsigned char *in;
    unsigned char *out;
    unsigned int remaining;
    unsigned int pos;
    unsigned int progress;
    unsigned int offset;
    int inputPos;
    int mode;
    unsigned char bitMode;
    int blockSize;
    int blockPos;
    int len;
    int lenBits;
    int bits;
    unsigned int threshold;
    int range;
    int i;
    unsigned char token;
    unsigned int maximum;

    pos = 0;
    in = pSrc->mpData;
    out = pDst->mpData;
    remaining = pSrc->mSize;
    inputPos = 0;
    bitbuf = 0;
    bitbufpos = -1;
    blockSize = 0;
    blockPos = 0;
    len = 0;
    offset = 0;
    bits = 1;
    threshold = 2;
    mode = in[0];
    bitMode = mode == 2 || mode == 3;
    lenBits = progress = 0;
    switch (mode) {
    case 0:
    case 2:
        inputPos = blockPos = 1;
        in = pSrc->mpData;
        if (mode == 2) {
            inputPos = 0;
            sReadBits(in, 8, &inputPos);
        }
        break;
    case 1:
    case 3:
        i = pSrc->mpData[1];
        blockSize = i << 24;
        i = pSrc->mpData[2];
        blockSize |= i << 16;
        i = pSrc->mpData[3];
        blockSize |= i << 8;
        i = pSrc->mpData[4];
        blockSize |= i;
        inputPos = blockPos = 5;
        if (remaining > blockSize) {
            BitsLeftInChunk = blockSize * 8;
            in = pSrc->mpData;
            pSrc->mPos = 0;
            remaining -= blockSize;
        } else {
            BitsLeftInChunk = remaining * 8;
            BitsLeftInChunk += 32 - BitsLeftInChunk % 32;
            in = pSrc->mpData;
        }
        if (mode == 3) {
            inputPos = 0;
            for (i = 0; i < 5; i++) {
                sReadBits(in, 8, &inputPos);
            }
        }
        break;
    }
    if (bitMode) {
        token = sReadBits(in, 8, &inputPos);
    } else {
        token = in[inputPos++];
    }
    while (token != 0) {
        blockPos++;
        if (pos - progress > 1024 && PacifyStatus == 1) {
            progress = pos - (pos % 1024);
        }
        if (token & 0x80) {
            switch (mode) {
            case 1:
            case 3:
                len = token & 0x7F;
                blockPos += len;
                break;
            case 0:
            case 2:
                len = token & 0x7F;
                break;
            }
            if (bitMode) {
                for (i = 0; i < len; i++) {
                    out[pos++] = sReadBits(in, 8, &inputPos);
                }
            } else {
                for (i = 0; i < len; i++) {
                    out[pos++] = in[inputPos++];
                }
            }
        } else {
            switch (mode) {
            case 1:
                len = token;
                blockPos += 2;
                offset = in[inputPos] + (in[inputPos + 1] << 8);
                offset = pos - offset;
                inputPos += 2;
                break;
            case 0:
                len = token;
                offset = in[inputPos] + (in[inputPos + 1] << 8);
                offset = pos - offset;
                inputPos += 2;
                break;
            case 2:
            case 3:
                if (lenBits == 0) {
                    len = 1;
                } else {
                    len = (1 << lenBits) | sReadBits(in, lenBits, &inputPos);
                }
                len += 2;
                while (pos >= threshold) {
                    if (threshold <= 0xFFFF) {
                        bits++;
                    }
                    threshold <<= 1;
                }
                maximum = (1 << bits) - 1;
                range = maximum - (pos > 0x10000 ? 0x10000 : pos);
                if (range != -1) {
                    offset = sReadBits(in, bits - 1, &inputPos);
                    if (offset >= range) {
                        offset <<= 1;
                        offset |= sReadBits(in, 1, &inputPos);
                        offset -= range;
                    }
                } else {
                    offset = sReadBits(in, bits, &inputPos);
                }
                offset = pos - offset;
                blockPos = 9999;
                break;
            }
            for (i = 0; i < len; i++) {
                out[pos++] = out[offset + i];
            }
        }
        i = 0;
        if (mode == 3 && BitsLeftInChunk <= 7) {
            if (BitsLeftInChunk != 0) {
                sReadBits(in, BitsLeftInChunk, &inputPos);
            }
            BitsLeftInChunk = blockSize * 8;
            i = 1;
        } else if (mode == 1 && blockPos == blockSize) {
            blockPos = 0;
            i = 1;
        }
        if (i == 1) {
            if (remaining > blockSize) {
                pSrc->mPos += blockSize;
                in = pSrc->mpData + pSrc->mPos;
                remaining -= blockSize;
            } else {
                pSrc->mPos += remaining;
                in = pSrc->mpData + pSrc->mPos;
                blockSize = remaining;
            }
            inputPos = 0;
        }
        if (bitMode) {
            token = sReadBits(in, 1, &inputPos);
            if (token == 0) {
                lenBits = sReadZeroBits(in, &inputPos);
                if (lenBits == 7) {
                    token = 0;
                } else {
                    token = 1;
                }
            } else {
                token = sReadBits(in, 7, &inputPos) | 0x80;
            }
        } else {
            token = in[inputPos++];
        }
    }
    pDst->mSize = pos;
    pDst->mPos = pos;
    return 1;
}

/* Decoding leaves no per-stream state to release. */
void _LZMDecStop(GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst, void *pState)
{
}

#endif
