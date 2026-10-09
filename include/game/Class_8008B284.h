#ifndef GAME_CLASS_8008B284_H
#define GAME_CLASS_8008B284_H

struct Pool_801C750C;

/* 64-byte tree node allocated from the Class_8008B284 pool. A node at depth 7
   is created as a leaf; other nodes have eight children selected by one bit
   of each of the three color bytes (fn_8008B054). */
struct Node_8008AF90 {
    unsigned char mIsLeaf;
    int mIndex;
    unsigned int mCount;
    unsigned int mSum12;
    unsigned int mSum16;
    unsigned int mSum20;
    Node_8008AF90 *mpChildren[8];
    Node_8008AF90 *mpNext;
    Node_8008AF90 *mpPrev;
};

/* Color tree: fn_8008B09C adds the 32-bit words of an image and merges nodes
   until at most 256 leaves remain; fn_8008B134 numbers the leaves in tree
   order and writes for each the word fn_8008AE88 builds from its averaged
   sums (the averages of bits 16-23 and 0-7 trade places, bits 24-31 are
   0xFF, and the word is 0 when bits 8-15 average 0xFF), and fn_8008B1F0
   writes the leaf number of each image word as a byte. */
class Class_8008B284 {
public:
    Class_8008B284();
    ~Class_8008B284();

    void fn_8008AC68(Node_8008AF90 **ppNode, unsigned int color, int level, int link);
    void fn_8008AD4C();
    unsigned int fn_8008AE88(Node_8008AF90 *pNode);
    void fn_8008AED4(unsigned int color, unsigned char *pOut, int level, Node_8008AF90 *pNode);
    Node_8008AF90 *fn_8008AF5C(Node_8008AF90 *pList);
    Node_8008AF90 *fn_8008AF90(int level, int link);
    void fn_8008B030(Node_8008AF90 *pNode);
    int fn_8008B054(int level, unsigned int color);
    void fn_8008B09C(unsigned int *pImage, unsigned int width, unsigned int height);
    void fn_8008B134(unsigned int *pPalette, Node_8008AF90 *pNode, int *pIndex);
    void fn_8008B1F0(unsigned int *pImage, unsigned int width, unsigned int height, unsigned char *pOut);
    int fn_8008B27C();

private:
    Node_8008AF90 *mpRoot;
    Node_8008AF90 *mpLists[8];
    unsigned int mLeafCount;
    Pool_801C750C *mpPool;
};

#endif
