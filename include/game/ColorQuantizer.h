#ifndef GAME_COLORQUANTIZER_H
#define GAME_COLORQUANTIZER_H

struct Pool_801C750C;

/* 64-byte tree node allocated from the ColorQuantizer pool. A node at depth 7
   is created as a leaf; other nodes have eight children selected by one bit
   of each of the three color bytes (GetChildIndex). */
struct ColorQuantizerNode_t {
    unsigned char mIsLeaf;
    int mIndex;
    unsigned int mCount;
    unsigned int mSum12;
    unsigned int mSum16;
    unsigned int mSum20;
    ColorQuantizerNode_t *mpChildren[8];
    ColorQuantizerNode_t *mpNext;
    ColorQuantizerNode_t *mpPrev;
};

/* Color tree: AddImage adds the 32-bit words of an image and merges nodes
   until at most 256 leaves remain; BuildPalette numbers the leaves in tree
   order and writes for each the word GetNodeColor builds from its averaged
   sums (the averages of bits 16-23 and 0-7 trade places, bits 24-31 are
   0xFF, and the word is 0 when bits 8-15 average 0xFF), and MapImage
   writes the leaf number of each image word as a byte. */
class ColorQuantizer {
public:
    ColorQuantizer();
    ~ColorQuantizer();

    void AddColor(ColorQuantizerNode_t **ppNode, unsigned int color, int level, int link);
    void ReduceTree();
    unsigned int GetNodeColor(ColorQuantizerNode_t *pNode);
    void FindPaletteIndex(unsigned int color, unsigned char *pOut, int level, ColorQuantizerNode_t *pNode);
    ColorQuantizerNode_t *FindSmallestNode(ColorQuantizerNode_t *pList);
    ColorQuantizerNode_t *NewNode(int level, int link);
    void FreeNode(ColorQuantizerNode_t *pNode);
    int GetChildIndex(int level, unsigned int color);
    void AddImage(unsigned int *pImage, unsigned int width, unsigned int height);
    void BuildPalette(unsigned int *pPalette, ColorQuantizerNode_t *pNode, int *pIndex);
    void MapImage(unsigned int *pImage, unsigned int width, unsigned int height, unsigned char *pOut);
    int GetLeafCount();

private:
    ColorQuantizerNode_t *mpRoot;
    ColorQuantizerNode_t *mpLists[8];
    unsigned int mLeafCount;
    Pool_801C750C *mpPool;
};

#endif
